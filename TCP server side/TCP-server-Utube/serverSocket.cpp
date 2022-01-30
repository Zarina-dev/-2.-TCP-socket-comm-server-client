#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "header.h"
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define PORT 54000



void debugFunc(int dbg = 0)
{
	if (dbg != 0) {
		#define DEBUG
	}
	else {
		#undef DEBUG
	}
}






int main()
{

	cout << " [ TCP - SERVER ]" << endl;
	// wsa initialization
	WSADATA wsaData;
	int wsaStartapRtn = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaStartapRtn != 0) { printError("wsa initialization ");}
	else { printIsDone("wsa Initialization"); }

	/*	WORKING!!
	debugFunc(0);
	#ifdef DEBUG
	cout << "DEBUG" << endl;
	#endif*/



	// create server socket  
	SOCKET servSocket;
	servSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSocket == INVALID_SOCKET) { printError("server socket creation"); }
	else {
		printIsDone("server socket creation");
		cout << "server socket descriptor : " << servSocket << endl;
	}


	// server addr data
	const char* ip = "127.0.0.1"; // ip cout --> 170.30.1.10
	
	sockaddr_in servAddr;
	sockaddr_in *PservAddr = &servAddr;
	memset(PservAddr, 0, sizeof(servAddr));

	PservAddr->sin_family = AF_INET;
	PservAddr->sin_port = htons(PORT);
	PservAddr->sin_addr.s_addr = htonl(INADDR_ANY);  //inet_pton(AF_INET, ip, &(servAddr.sin_addr));   

	printSockInfo("server socket", PservAddr);



	// binding
	int bindRtn = bind(servSocket, (sockaddr*)PservAddr, sizeof(servAddr));
	if (bindRtn == SOCKET_ERROR) { WSAGetLastError(); printError("server binding"); }
	else { printIsDone("server binding"); }


	// listen
	int listenRtn = listen(servSocket, SOMAXCONN);
	if (listenRtn != 0) { printError("server listening"); }
	else { cout << "\n\n----------------------- server is listening...------------------\n" << endl; }
	
	
	// -------------- client ------

	// accept
	SOCKET clientSocket;
	sockaddr_in clienSocketAddr;
	int szClnAddr = sizeof(clienSocketAddr);

	clientSocket = accept(servSocket, (sockaddr*)&clienSocketAddr, &szClnAddr);
	if (clientSocket == SOCKET_ERROR) { WSAGetLastError(); printError("client accepting"); }
	else {
		printIsDone("client acception ");
		printSockInfo("client server", &clienSocketAddr);
	}


	// receive
	char buf[1000];
	char stopIn = ' ';
	while (stopIn != 'q')
	{
		int recvRtn = recv(clientSocket, (char*)&buf, 1000, 0);
		if (recvRtn == SOCKET_ERROR) { printError("receiving message"); }
		else if ((recvRtn == 1) && (buf[0] == 'q'))    // oh yeahhhh
		{
			stopIn = 'q';
			cout << "quit connecting with server" << endl;
		}
		else { cout << "received data byte = " << recvRtn << " bytes" << endl; }

		cout << "sended data to CLIENT > " << buf << endl;
		// send
		send(clientSocket, (char*)&buf, recvRtn, 0);

	}
	// close sockets
	closesocket(servSocket);
	closesocket(clientSocket);

	// clean up wsa
	WSACleanup();


}