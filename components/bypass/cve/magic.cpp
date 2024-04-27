//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "../../linker/stdafx.hpp"

// KTHREAD -> PreviousMode
const uint64_t OffsetPreviousMode = 0x232;
// KTHREAD -> MiscFlags
const uint64_t OffsetMiscFlags = 0x74;

HANDLE deviceHandle;
volatile uint64_t currentProcess;
volatile uint64_t currentThread;

typedef struct _Flags
{
    union
    {
        struct
        {
            ULONG AutoBoostActive : 1;                                        //0x74
            ULONG ReadyTransition : 1;                                        //0x74
            ULONG WaitNext : 1;                                               //0x74
            ULONG SystemAffinityActive : 1;                                   //0x74
            ULONG Alertable : 1;                                              //0x74
            ULONG UserStackWalkActive : 1;                                    //0x74
            ULONG ApcInterruptRequest : 1;                                    //0x74
            ULONG QuantumEndMigrate : 1;                                      //0x74
            ULONG Spare1 : 1;                                                 //0x74
            ULONG TimerActive : 1;                                            //0x74
            ULONG SystemThread : 1;                                           //0x74
            ULONG ProcessDetachActive : 1;                                    //0x74
            ULONG CalloutActive : 1;                                          //0x74
            ULONG ScbReadyQueue : 1;                                          //0x74
            ULONG ApcQueueable : 1;                                           //0x74
            ULONG ReservedStackInUse : 1;                                     //0x74
            ULONG Spare2 : 1;                                                 //0x74
            ULONG TimerSuspended : 1;                                         //0x74
            ULONG SuspendedWaitMode : 1;                                      //0x74
            ULONG SuspendSchedulerApcWait : 1;                                //0x74
            ULONG CetUserShadowStack : 1;                                     //0x74
            ULONG BypassProcessFreeze : 1;                                    //0x74
            ULONG CetKernelShadowStack : 1;                                   //0x74
            ULONG StateSaveAreaDecoupled : 1;                                 //0x74
            ULONG IsolationWidth : 1;                                         //0x74
            ULONG Reserved : 7;                                               //0x74
        } BitFields;
        LONG MiscFlags;                                                     //0x74
    } Internal;
} Flags;

DWORD WINAPI MagicThread(LPVOID dummy)
{
	UNREFERENCED_PARAMETER(dummy);

    currentProcess = intel_driver::IoGetCurrentProcess(deviceHandle);
    currentThread = intel_driver::PsGetCurrentThread(deviceHandle);

    memory::Loop();

	return 0;
}

bool magic::Run()
{
    no_iat( wprintf )( L"[+] executing\n" );
	deviceHandle = intel_driver::Load();
	if (deviceHandle == INVALID_HANDLE_VALUE)
		return false;

    no_iat( wprintf )( L"[+] deploying\n" );
    CreateThread(nullptr, 0, MagicThread, nullptr, 0, nullptr);

    while (!currentThread)
        Sleep(1);

    Sleep(500);

    if (!(currentThread && currentProcess))
    {
        no_iat( wprintf )( L"[-] fatal #40, contact support\n" );
        if ( !intel_driver::Unload( deviceHandle ) )
        {
            no_iat( wprintf )( L"[-] fatal #43, contact support\n" );
            return false;
        }

        memset( driver_resource::driverBuffer, 0, sizeof( driver_resource::driverBuffer ) );
        return bool( );
    }

    bool status = false;

    char mode = 0; // KernelMode
    if (!intel_driver::WriteMemory(deviceHandle, currentThread + OffsetPreviousMode, &mode, sizeof(char)))
    {
        no_iat( wprintf )( L"[-] fatal #40, contact support\n" );
        if ( !intel_driver::Unload( deviceHandle ) )
        {
            no_iat( wprintf )( L"[-] fatal #43, contact support\n" );
            return false;
        }

        memset( driver_resource::driverBuffer, 0, sizeof( driver_resource::driverBuffer ) );
        return status;
    }

    Flags flags;
    if (!intel_driver::ReadMemory(deviceHandle, currentThread + OffsetMiscFlags, &flags, sizeof(Flags)))
    {
        no_iat( wprintf )( L"[-] fatal #42, contact support\n" );
        if ( !intel_driver::Unload( deviceHandle ) )
        {
            no_iat( wprintf )( L"[-] fatal #43, contact support\n" );
            return false;
        }

        memset( driver_resource::driverBuffer, 0, sizeof( driver_resource::driverBuffer ) );
        return status;
    }

    flags.Internal.BitFields.ApcQueueable = false;

    if (!intel_driver::WriteMemory(deviceHandle, currentThread + OffsetMiscFlags, &flags, sizeof(Flags)))
    {
        no_iat( wprintf )( L"[-] fatal #41, contact support\n" );
        if ( !intel_driver::Unload( deviceHandle ) )
        {
            no_iat( wprintf )( L"[-] fatal #43, contact support\n" );
            return false;
        }

        memset( driver_resource::driverBuffer, 0, sizeof( driver_resource::driverBuffer ) );
        return status;
    }

    status = true;

    if (!intel_driver::Unload(deviceHandle))
    {
        no_iat(wprintf)(L"[-] fatal #43, contact support\n");
        return false;
    } 

    memset(driver_resource::driverBuffer, 0, sizeof(driver_resource::driverBuffer));
    return status;
}
