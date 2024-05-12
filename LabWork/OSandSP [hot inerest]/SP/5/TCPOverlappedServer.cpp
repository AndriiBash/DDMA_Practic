#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <list> 
#include <conio.h>
#include "iostream"
#pragma comment (lib,"ws2_32.lib") 

using namespace std;
#define BUFF_SIZE 1024 
#define PORT 28912 
DWORD WINAPI ServerPool(HANDLE hp);

void SendToAll(char* buffer, unsigned long bytes);

SOCKET server_sock;
int ClientCount;
list<SOCKET> ClientList;

struct ovpConnection : public OVERLAPPED
{
	int client_number;
	SOCKET c;
	char* buffer;
	enum
	{
		op_type_send,
		op_type_recv
	}op_type;
};

void main(int argc, char* argv[])
{
	int err;
	char buffer[128];
	WORD wVersionRequested;
	WSADATA wsaData;
	HANDLE hCp;
	LPOVERLAPPED overlapped;
	HANDLE hThread;
	DWORD ThreadId;
	DWORD flags;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == SOCKET_ERROR)
	{
		strcpy(buffer, "Помилка функцiї WSAStartup");
		CharToOem((LPCSTR)buffer, buffer);
		printf("%s %d\n", buffer, WSAGetLastError());
		WSACleanup();
		getch();
		return;
	}

	hCp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hCp == NULL)
	{
		strcpy(buffer, "Помилка функцiї CreateIoCompletionPort");
		CharToOem((LPCSTR)buffer, buffer);
		printf("%s %d\n", buffer, GetLastError());
		WSACleanup();
		getch();
		return;
	}

	server_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (server_sock == INVALID_SOCKET)
	{
		strcpy(buffer, "Помилка функцiї WSASocket");
		CharToOem((LPCSTR)buffer, buffer);
		printf("%s %d\n", buffer, WSAGetLastError());
		WSACleanup();
		getch();
		return;
	}
	else
	{
		if (CreateIoCompletionPort((HANDLE)server_sock, hCp, 0, 0) == NULL)
		{
			strcpy(buffer, "Помилка функцiї CreateIoCompletionPort");
			CharToOem((LPCSTR)buffer, buffer);
			printf("%s %d\n", buffer, GetLastError());
			WSACleanup();
			getch();
			return;
		}
	}

	SOCKADDR_IN sinServer;
	sinServer.sin_family = AF_INET;
	sinServer.sin_port = htons(PORT);
	sinServer.sin_addr.s_addr = INADDR_ANY;
	err = bind(server_sock, (LPSOCKADDR)&sinServer, sizeof(sinServer));
	if (err == -1)
	{
		strcpy(buffer, "Помилка функцiї bind");
		CharToOem((LPCSTR)buffer, buffer);
		printf("%s %d\n", buffer, GetLastError());
		WSACleanup();
		getch();
		return;
	}

	err = listen(server_sock, SOMAXCONN);
	if (err == -1)
	{
		strcpy(buffer, "Помилка функцiї listen");
		CharToOem((LPCSTR)buffer, buffer);
		printf("%s %d\n", buffer, GetLastError());
		WSACleanup();
		getch();
		return;
	}

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerPool, hCp, 0, &ThreadId);
	ClientCount = 0;
	strcpy(buffer, "Сервер запущено\n");
	CharToOem((LPCSTR)buffer, buffer);
	printf("%s", buffer);

	while (true)
	{

		SOCKADDR_IN sinClient;
		int lenClient = sizeof(sinClient);
		SOCKET client = accept(server_sock, (struct sockaddr*)&sinClient, &lenClient);
		CreateIoCompletionPort((HANDLE)client, hCp, 0, 0);

		ClientList.insert(ClientList.end(), client);

		ovpConnection* op = new ovpConnection;

		op->c = client;
		op->op_type = ovpConnection::op_type_recv;
		op->buffer = new char[BUFF_SIZE];
		op->hEvent = 0;
		op->client_number = ++ClientCount;
		strcpy(buffer, "Клiєнт № %d пiдключився, активних клiєнтiв %d\n");
		CharToOem((LPCSTR)buffer, buffer);
		printf(buffer, ClientCount, ClientList.size());
		unsigned long b;
		WSABUF buf;
		buf.buf = op->buffer;
		buf.len = BUFF_SIZE;
		flags = 0;
		err = WSARecv(op->c, &buf, 1, &b, &flags, op, 0);
		if (!err)
		{
			strcpy(buffer, "Помилка функцiї WSARecv");
			CharToOem((LPCSTR)buffer, buffer);
			printf("%s %d\n", buffer, WSAGetLastError());
		}
	}
	return;
}

DWORD WINAPI ServerPool(HANDLE hp)
{
	int err;
	unsigned long bytes;
	unsigned long key;
	char buffer[128];
	LPOVERLAPPED overlapped;
	HANDLE hport = hp;
	DWORD flags;
	while (true)
	{

		if (GetQueuedCompletionStatus(hport, &bytes, &key, &overlapped, INFINITE))
		{

			ovpConnection* op = (ovpConnection*)overlapped;

			switch (op->op_type)
			{

			case ovpConnection::op_type_send:
				delete[] op->buffer;
				delete op;
				break;

			case ovpConnection::op_type_recv:
				if (!bytes)
				{

					ClientList.remove(op->c);
					closesocket(op->c);
					strcpy(buffer, "Клiєнт № %d вiдключився, активних клiєнтів %d\n");
					CharToOem((LPCSTR)buffer, buffer);
					printf(buffer, op->client_number, ClientList.size());
					break;
				}
				op->buffer[bytes] = '\0';
				if (op->buffer[0] == '*')

				{
					strcpy(buffer, "Вiд клiєнта № %d отримано повiдомлення для всiх %s\n");
					CharToOem((LPCSTR)buffer, buffer);
					printf(buffer, op->client_number, (op->buffer + 1));
					SendToAll(op->buffer, bytes);
				}
				else
				{
					strcpy(buffer, "Вiд клiєнта № %d отримано повiдомлення %s\n");
					CharToOem((LPCSTR)buffer, buffer);
					printf(buffer, op->client_number, op->buffer);
				}
				unsigned long b;
				WSABUF buf;
				buf.buf = op->buffer;
				buf.len = BUFF_SIZE;
				err = WSARecv(op->c, &buf, 1, &b, &flags, op, 0);
				if (!err)
				{
					strcpy(buffer, "Помилка функцiї WSARecv");
					CharToOem((LPCSTR)buffer, buffer);
					printf("%s %d\n", buffer, WSAGetLastError());
				}
			}
		}
		else
		{
			if (!overlapped)
			{

				for (list<SOCKET>::iterator i = ClientList.begin(); i != ClientList.end(); i++)
				{
					closesocket(*i);
				}
				ClientList.clear();
				closesocket(server_sock);
				CloseHandle(hport);
				strcpy(buffer, "Помилка порту № %d, сервер завершує роботу\n");
				CharToOem((LPCSTR)buffer, buffer);
				printf(buffer, GetLastError());
				getch();
				exit(0);
			}
			else
			{

				closesocket(((ovpConnection*)overlapped)->c);
				ClientList.remove(((ovpConnection*)overlapped)->c);
				strcpy(buffer, "Клiєнт № %d вiдключився, активних клiєнтiв %d\n");
				CharToOem((LPCSTR)buffer, buffer);
				printf(buffer, ((ovpConnection*)overlapped)->client_number, ClientList.size());
			}
		}
	}
	return 0;
}

void SendToAll(char* buffer, unsigned long bytes)
{

	for (list<SOCKET>::iterator i = ClientList.begin(); i != ClientList.end(); i++)
	{
		ovpConnection* op = new ovpConnection;
		op->c = *i;
		op->op_type = ovpConnection::op_type_send;
		op->buffer = new char[bytes - 1];
		memcpy(op->buffer, (buffer + 1), bytes - 1);
		op->buffer[bytes - 1] = '\0';
		unsigned long b;
		WSABUF buf;
		buf.buf = op->buffer;
		buf.len = BUFF_SIZE;
		WSASend(op->c, &buf, 1, &b, 0, op, 0);
	}
	return;
}
