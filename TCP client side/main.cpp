#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
void printError(string errorWhere)
{
	cerr<< "ERROR - " << errorWhere << endl;
}

int main()
{	
	cout << " [ TCP - CLIENT ]" << endl;
	string ipAddress = "127.0.0.1";
	int port = 54000;             // listening port # of the server

	// initialize winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) { printError("wsa initialization"); WSACleanup();
	}

	// create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { 
		printError("creating server"); 
		WSAGetLastError();
		WSACleanup();
	}


	// fill in a hint str
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &(hint.sin_addr));
	
	// connect to server     == ¬ä¬Ú¬á¬Ñ bind
	int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connRes == SOCKET_ERROR) { 
		printError("connection"); 
		WSACleanup();
		WSAGetLastError(); 
	}
	
	// do-while loop to send and recv data
	char buf[1000];
	string userInput;

	do {
		// prompt the user for some text
		cout << "your msg to the server > ";
		getline(cin, userInput);
		//cout << "userInput.size() = " << userInput.size() << endl;

		if(userInput.size() > 0)
		{
			// send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {     // if successfully sends user input data to the server
				// wait for response
				ZeroMemory(buf, 1000);
				int bytesReceived = recv(sock, (char*)&buf, 1000, 0);    // put received data from server to the buf
				if (bytesReceived > 0) {
					// ehco response to console
					
					cout << "received data from SERVER > " << string(buf, 0, bytesReceived) << endl;	
					//cout << "SERVER > ";
					//for (int i = 0; i < bytesReceived; i++)
					//{
					//	cout << buf[i] << "";
					//}
					cout << endl;

				}
			}
			

		}

	} while (userInput.size() > 0);

	// gracefully close down everything
	closesocket(sock);
	WSACleanup();
}