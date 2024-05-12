#include "stdafx.h"
#include <windows.h>

char infomes[512];
char servicedir[MAX_PATH];

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	lstrcpy(infomes, "Service Created at path:\n");
	lstrcpy(servicedir, "C:\\WindowsMyService.exe");

	SC_HANDLE scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if(scm!=NULL) {
		SC_HANDLE svc=CreateService(scm,
			"Terra-Incognita",
			"Terra-Incognita",
			0,
			SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_IGNORE,
			servicedir,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);
	
		if(svc!=NULL) {
			CloseServiceHandle(svc);
			strcat(infomes, servicedir);
			MessageBox(NULL, infomes, "Install", NULL);
		}
		CloseServiceHandle(scm); 
	}
	else  {
		MessageBox(NULL, "Could not create service.", "Install", NULL);
	}

	return 0;
}
