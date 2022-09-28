#pragma once
#ifndef KEYBOARDINTERRUPTHANDLER_H_INCLUDED
#define KEYBOARDINTERRUPTHANDLER_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef linux
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#endif
#include <iostream>

using namespace std;

class KeyboardInterruptHandler {
public:
	static int handleKeyboardInterrupt();
private:
#ifdef _WIN32
	static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);
	static HANDLE ghSignalEvent;
#endif
#ifdef linux
	static void CtrlHandler(int s);
#endif
};

#endif // KEYBOARDINTERRUPTHANDLER_H_INCLUDED
