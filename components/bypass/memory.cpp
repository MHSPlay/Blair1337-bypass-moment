//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "../linker/stdafx.hpp"

DWORD targetPid = 0;
HANDLE targetProcess = nullptr;

volatile memory::ControlData controlData;
std::mutex actionMutex;

void memory::HandleOpenProcess(volatile ControlData* data)
{
	DWORD processId = static_cast<DWORD>(data->Data[0]);
	targetProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, processId);
    if (!targetProcess || targetProcess == INVALID_HANDLE_VALUE)
    {
        data->Status = StatusError;
        return;
    }

    data->Status = StatusDone;
}

void memory::HandleReadMemory(volatile ControlData* data)
{
	LPCVOID address = reinterpret_cast<LPCVOID>(data->Data[0]);
    LPVOID buffer = reinterpret_cast<LPVOID>(data->Data[1]);
    SIZE_T size = data->Data[2];
    SIZE_T* outputSize = const_cast<SIZE_T*>(&data->Data[3]);
    bool status = ReadProcessMemory(targetProcess, address, buffer, size, outputSize);
    if (!status)
    {
        data->Status = StatusError;
        return;
    }

    data->Status = StatusDone;
}

void memory::HandleWriteMemory(volatile ControlData* data)
{
	LPVOID address = reinterpret_cast<LPVOID>(data->Data[0]);
    LPVOID buffer = reinterpret_cast<LPVOID>(data->Data[1]);
    SIZE_T size = data->Data[2];
    SIZE_T* outputSize = const_cast<SIZE_T*>(&data->Data[3]);
    bool status = WriteProcessMemory(targetProcess, address, buffer, size, outputSize);
    if (!status)
    {
        data->Status = StatusError;
        return;
    }

    data->Status = StatusDone;
}

void memory::HandleModuleQuery(volatile ControlData* data)
{
    wchar_t* moduleName = reinterpret_cast<wchar_t*>(data->Data[0]);
    uint64_t modBaseAddr = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, targetPid);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32FirstW(snapshot, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, moduleName))
                {
                    modBaseAddr = reinterpret_cast<uint64_t>(modEntry.modBaseAddr);
                    break;
                }
            } while (Module32NextW(snapshot, &modEntry));
        }
    }
    CloseHandle(snapshot);

    *reinterpret_cast<uint64_t*>(data->Data[1]) = modBaseAddr;
    if (!modBaseAddr)
    {
        data->Status = StatusError;
        return;
    }

    data->Status = StatusDone;
}

memory::ActionStatus memory::PerformAction(ActionType type, uint64_t data1, uint64_t data2, uint64_t data3,
	uint64_t data4, uint64_t data5)
{
	actionMutex.lock();
	memset((void*)&controlData, 0, sizeof(ControlData));

    controlData.Action = type;
    controlData.Data[0] = data1;
    controlData.Data[1] = data2;
    controlData.Data[2] = data3;
    controlData.Data[3] = data4;
    controlData.Data[4] = data5;

	controlData.Status = StatusPending;
    while (controlData.Status == StatusPending) { }

	actionMutex.unlock();
    return controlData.Status;
}

void memory::Loop()
{
    while ( !defines::should_break_magic )
    {
        if (controlData.Status != StatusPending)
            continue;

        switch (controlData.Action)
        {
        case ActionOpenProcess:
            HandleOpenProcess(&controlData);
            break;
        case ActionReadMemory:
            HandleReadMemory(&controlData);
            break;
        case ActionWriteMemory:
            HandleWriteMemory(&controlData);
            break;
        case ActionModuleQuery:
            HandleModuleQuery(&controlData);
            break;
        default:
            break;
        }
    }
}

DWORD ac::GetProcessPID(const wchar_t* processName)
{
	PROCESSENTRY32W processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32FirstW(snapshot, &processInfo);
    if (!wcscmp(processName, processInfo.szExeFile))
    {
        CloseHandle(snapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32NextW(snapshot, &processInfo))
    {
        if (!wcscmp(processName, processInfo.szExeFile))
        {
            CloseHandle(snapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(snapshot);
    return 0;
}

uint64_t ac::module(const wchar_t* moduleName)
{
	uint64_t moduleBaseAddress = 0;
    memory::ActionStatus status = memory::PerformAction(memory::ActionModuleQuery, reinterpret_cast<uint64_t>(moduleName), reinterpret_cast<uint64_t>(&moduleBaseAddress));
    if (status != memory::StatusDone || !moduleBaseAddress)
    {
        Sleep(INT_MAX);
    }

    return moduleBaseAddress;
}

void ac::target(const wchar_t* processName)
{ 
    while (!targetPid)
        targetPid = GetProcessPID(processName);

    Sleep(5000);

    targetPid = GetProcessPID(processName);
    if (!targetPid)
    { 
        Sleep(INT_MAX);
    }

    memory::ActionStatus status = memory::PerformAction(memory::ActionOpenProcess, targetPid);
    if (status != memory::StatusDone)
    { 
        Sleep(INT_MAX);
    }
     
}

bool ac::read_memory(uint64_t address, void* buffer, size_t size)
{
    memory::ActionStatus status = memory::PerformAction(memory::ActionReadMemory, address, reinterpret_cast<uint64_t>(buffer), size);
    return status == memory::StatusDone;
}

bool ac::WriteMemory(uint64_t address, void* buffer, size_t size)
{
    memory::ActionStatus status = memory::PerformAction(memory::ActionWriteMemory, address, reinterpret_cast<uint64_t>(buffer), size);
    return status == memory::StatusDone;
}