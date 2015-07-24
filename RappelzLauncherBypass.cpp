#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <WinBase.h>

int _tmain(int argc, _TCHAR* argv[])
{
	putenv("sframe.exe_PARENT=Launcher.exe");
	putenv("sframe.exe_RUNNER=192");
	char* a = GetEnvironmentStrings();

	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field
	CreateProcess("SFrame.exe",
		"/auth_ip:127.0.0.1 /auth_port:58422 /use_nprotect:0 /help_url_w:611 /help_url_h:625 /locale:windows-1256 /country:DE /cash /commercial_shop /layout_dir:6 /layout_auto:0 /cash_url_w:800 /cash_url_h:631",
		0, 
		0, 
		// Inherit handles
		TRUE, 
		0, 
		// Link the current environment strings
		a, 
		"C:\\Program Files (x86)\\Webzen\\Rappelz", 
		&StartupInfo, 
		&ProcessInfo);
	return 0;
}

