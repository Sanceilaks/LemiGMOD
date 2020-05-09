// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "framework.h"

void HackStart(void* dll)
{
    HackCore::Get().Init();


}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackStart, hModule, NULL, NULL); //Create new Thread
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

