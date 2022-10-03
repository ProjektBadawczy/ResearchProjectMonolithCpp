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
        cout << endl << "Ctrl-C event" << endl;
        if (!SetEvent(ghSignalEvent))
        {
            cout << endl << "SetEvent failed (" << GetLastError() << ")" << endl;
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
    cout << endl << "Ctrl-C event" << endl;
}
#endif

int KeyboardInterruptHandler::handleKeyboardInterrupt()
{
    cout << endl << "app started" << endl;
#ifdef _WIN32
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        cout << endl << "ERROR: Could not set control handler" << endl;
        return 1;
    }

    DWORD dwWaitResult = WaitForSingleObject(
        ghSignalEvent, // event handle
        INFINITE);    // indefinite wait

    switch (dwWaitResult)
    {
        // Event object was signaled
    case WAIT_OBJECT_0:
        cout << endl << "Exit" << endl;
        break;
    default:
        cout << endl << "Wait error" << endl;
    }
    return 0;
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
