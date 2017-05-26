#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <list>
#include "MsgQueue.h"
#include "ProcessModel.h"

#include "MyHook.h"




MyHook::MyHook() {
	//Dll loading and connection
	hModule = LoadLibrary(L"dll.dll");
	if (!hModule){
		std::cout << "no module loaded!";
	}	
	//Initialization of the pointer to RunStopHook method
	RunStopHook = NULL;
	RunStopHook = (RunStopHookProc*)::GetProcAddress((HMODULE)hModule, "RunStopHook");
	//Initialization of the pointer to the set dll message queue method
	SetDllMsgQueue = NULL;
	SetDllMsgQueue = (SetMessageQueueProc*)::GetProcAddress((HMODULE)hModule, "SetDllMessageQueue");
	
};

//Singleton
MyHook& MyHook::Instance() {
		static MyHook myHook;
		return myHook;
	}

int MyHook::Messages() {
	while (msg.message != WM_QUIT) { //while we do not close our application
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}

	MyHook::Instance().UninstallHook();

	return (int)msg.wParam; //return the messages
}

//Set the message queue to pass it to the dll
void MyHook::SetMessageQueue(MessageQueue * msgQue)
{
	msgQueue = msgQue;
	(*SetDllMsgQueue)(msgQueue);
}

//Method used to start monitoring processes 
int MyHook::StartMonitoringProcesses() {
	//TODO GESTIRE CASO IN CUI NON SIA STATA CREATA LA CODA MESSAGGI
	MyHook::Instance().InstallHook();
	return MyHook::Instance().Messages();
}

void MyHook::InstallHook() {
	//Chiamo la funzione di aggancio hook
	
	(*RunStopHook)(true, GetModuleHandle(0));
	
}

void MyHook::UninstallHook()
{
	(*RunStopHook)(false, GetModuleHandle(0));
	FreeLibrary(hModule);

	std::string path = "C:\\Users\\David\\Desktop\\exit.txt";
	std::fstream File(path, std::ios::app);
	File << "Chiuso!";
	File.close();
	
}

