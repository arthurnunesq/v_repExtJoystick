// v_repExtJoystickConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "v_repExtJoystickConsole.h"
#include "v_repExtJoystick.h"
#include <iostream>
#include <windows.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
bool exit_flag = false;

using namespace std;

BOOL WINAPI consoleHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT) {
		printf("Ctrl-C handled\n"); // do cleanup
		exit_flag = true;
	}

	return TRUE;
}

int run() {

	HWND handle = nullptr;
	handle = FindWindowA(NULL, "E:\\OneDrive\\Projetos\\VREPExtensionJoystick\\Debug\\v_repExtJoystickConsole.exe");
	if (!handle) {
		printf("Could not get window handle.\n");
	}
	v_repExtJoystick::setWindowHandle(handle);

	std::cout << "v_repExtJoystick" << std::endl;
	std::cout << "Joystick count: " << v_repExtJoystick::getJoyCount() << std::endl;

	//while (!exit_flag) {
	//	system("cls"); // Avoids flickering
	//	v_repExtJoystick::printJoyState(0);

	//	Sleep(100);
	//}

	int joy_count = 0;
	while (!exit_flag) {
		joy_count = v_repExtJoystick::getJoyCount();
		if (joy_count > 0) break;
		Sleep(100);
	}
	if (joy_count < 1) return 0;

	int joy_id = 0;
	//v_repExtJoystick::enableJoyForceControl(joy_id);
	v_repExtJoystick::setJoyForces(joy_id, { 0.2f, 0.0f });
	Sleep(5000);
	//v_repExtJoystick::disableJoyForceControl(joy_id);

	v_repExtJoystick::stop();

	std::system("pause");
	return 0;
}

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: change error code to suit your needs
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
			if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
				printf("\nERROR: Could not set control handler");
				nRetCode =  1;
			}
			else {
				nRetCode = run();
			}
		}
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
