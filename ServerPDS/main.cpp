// ServerPDS.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <list>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "EventInfo.h"
#include "IconExtractor.h"
#include "MyHook.h"
#include "ProcessModel.h"
#include "json\json.h"
#include "JsonSerializer.h"
#include "Network.h"
#include "Controller.h"






int _tmain(int argc, _TCHAR* argv[]) {
	

	Controller controller;
	controller.Init();	
	controller.Run();

	return 0;

}
