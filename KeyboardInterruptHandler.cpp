#include "KeyboardInterruptHandler.h"

#ifdef _WIN32
HANDLE KeyboardInterruptHandler::ghSignalEvent = CreateEvent(
    NULL,               // default security attributes
    TRUE,               // manual-reset event
    FALSE,              // initial state is nonsignaled
    TEXT("WriteEvent")  // object name
);

BOOL WINAPI KeyboardInterruptHandler::CtrlHandler(DWORD fdwCtrlType)
{
    if (fdwCtrlType == CTRL_C_EVENT)
    {
        printf("Ctrl-C event\n\n");
        if (!SetEvent(ghSignalEvent))
        {
            printf("SetEvent failed (%d)\n", GetLastError());
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
#endif
#ifdef linux
void KeyboardInterruptHandler::CtrlHandler(int s)
{
    printf("Ctrl-C event\n\n");
}
#endif

int KeyboardInterruptHandler::handleKeyboardInterrupt()
{
#ifdef _WIN32
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        printf("\nERROR: Could not set control handler\n");
        return 1;
    }

    DWORD dwWaitResult = WaitForSingleObject(
        ghSignalEvent, // event handle
        INFINITE);    // indefinite wait

    switch (dwWaitResult)
    {
        // Event object was signaled
    case WAIT_OBJECT_0:
        printf("Exit\n");
        break;
    default:
        printf("Wait error (%d)\n", GetLastError());
        return 0;
    }
#endif
#ifdef linux
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = CtrlHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    pause();
    return 0;
#endif
}
