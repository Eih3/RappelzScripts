/*
// The launcher create an handle that is inherited to it's child process (that is sframe.exe), 
// and sframe try to use the handle. If it fails, it shows the messagebox about not having launched 
// sframe from the launcher. To pass the handle value, an environment variable is used (on 32bit systems, 
// this variable is 64bit even though there is only 32 bits used), this is usually something like 
// sframe.exe_runner.
// The program has to be launcher with admin rights to be able to inherit it's environment variables, 
// else sframe.exe (which need to have admin rights anyway) won't have the environment variables from it's 
// parent process, thus will report not being launched from the official launcher.
//
// Explanation by glandu2: http://www.elitepvpers.com/forum/rappelz-private-server/2732190-release-tool-launch-sframe-exe-without-launcher.html#post23939690
//
// This is just an example script of how it COULD look like.
//
*/

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <WinBase.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// Create the 2 enviroment strings which are required to bypass the launcher check
	putenv("sframe.exe_PARENT=Launcher.exe");
	putenv("sframe.exe_RUNNER=192");
	// Get a pointer to the current environment settings (including the new ones just created)
	char* a = GetEnvironmentStrings();

	// Just useless initiaton :p
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; 
	
	// Start the sframe
	CreateProcess("SFrame.exe",
		"/auth_ip:127.0.0.1 /auth_port:58422 /use_nprotect:0 /help_url_w:611 /help_url_h:625 /locale:windows-1256 /country:DE /cash /commercial_shop /layout_dir:6 /layout_auto:0 /cash_url_w:800 /cash_url_h:631",
		0, 
		0, 
		// SFrame should inherit the handles!
		TRUE, 
		0, 
		// Link the current environment strings
		a,
		"C:\\Program Files (x86)\\Webzen\\Rappelz", 
		&StartupInfo, 
		&ProcessInfo);
	return 0;
}

