#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <iostream>

#define PORT 28912  

DWORD WINAPI ClientPool(SOCKET client);

void main() {
	setlocale(LC_ALL, "ukr");
	int j;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	char address[16] = { 0 };
	char buffer[128];
	SOCKET sd;
	HANDLE hThread;
	DWORD ThreadId;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == SOCKET_ERROR)
	{
		strcpy(buffer, "Помилка функцiї WSASTARTUP №");
		CharToOem((LPCWSTR)buffer, buffer);
		printf("%s %d\n", buffer, WSAGetLastError());
		WSACleanup();
		getch();
		return;
	}
	strcpy(buffer, "Введiть адресу вiддаленого комп'ютера");
	CharToOem((LPCWSTR)buffer, buffer);
	printf("%s\n", buffer);
	scanf("%s", address);

	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == INVALID_SOCKET)
	{
		strcpy(buffer, "Помилка функцiї socket ");
		CharToOem((LPCWSTR)buffer, buffer);
		printf("%s %d\n", buffer, WSAGetLastError());
		WSACleanup();
		getch();
		return;
	}

	SOCKADDR_IN sin;
	ZeroMemory(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = inet_addr(address);

	if (connect(sd, (PSOCKADDR)&sin, sizeof(SOCKADDR)) == -1)
	{
		strcpy(buffer, "Не можу пiдключитися до сервера №");
		CharToOem((LPCWSTR)buffer, buffer);
		printf("%s %d\n", buffer, GetLastError());
		WSACleanup();
		getch();
		return;
	}

	strcpy(buffer, "Пiдключення до серверу успiшно");
	CharToOem((LPCWSTR)buffer, buffer);
	printf("%s\n", buffer);

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientPool, (void*)sd, 0, &ThreadId);

	while (true)
	{
		scanf("%s", buffer);
		if (strcmp(buffer, "EXIT") == 0)
		{
			TerminateThread(hThread, 0);
			if (sd != INVALID_SOCKET) closesocket(sd);
			break;
		}
		send(sd, buffer, strlen(buffer), 0);
	}
	WSACleanup();
	return;
}

DWORD WINAPI ClientPool(SOCKET client)
{
	int bytes;
	char buffer[128];

	while (true)
	{
		bytes = recv(client, buffer, sizeof(buffer), 0);
		buffer[strlen(buffer)] = '\0';
		if (strlen(buffer) != 0) printf("%s\n", buffer);
	}
	return 0;
}

