//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#ifndef MEMORY_H
#define MEMORY_H

namespace memory
{
	enum ActionType
	{
		ActionUnknown,
		ActionOpenProcess,
		ActionReadMemory,
		ActionWriteMemory,
		ActionModuleQuery
	};

	enum ActionStatus
	{
		StatusInvalid,
		StatusPending,
		StatusError,
		StatusDone
	};

	typedef struct _ControlData
	{
		ActionType Action;
		ActionStatus Status;
		uint64_t Data[5];
	} ControlData;

	void HandleOpenProcess(volatile ControlData* data);
	void HandleReadMemory(volatile ControlData* data);
	void HandleWriteMemory(volatile ControlData* data);
	void HandleModuleQuery(volatile ControlData* data);
	ActionStatus PerformAction(ActionType type, uint64_t data1 = 0, uint64_t data2 = 0, uint64_t data3 = 0, uint64_t data4 = 0, uint64_t data5 = 0);
	void Loop();
}

namespace ac
{
	DWORD GetProcessPID(const wchar_t* processName);
	uint64_t module(const wchar_t* moduleName);
	void target(const wchar_t* processName);
	bool read_memory(uint64_t address, void* buffer, size_t size);
	bool WriteMemory(uint64_t address, void* buffer, size_t size);

	template<typename T>
	T read(uint64_t address)
	{
		T val = T();
		read_memory(address, &val, sizeof(T));
		return val;
	}

	template<typename T>
	void Write(DWORD64 address, T value)
	{
		WriteMemory(address, &value, sizeof(T));
	}
}

#endif