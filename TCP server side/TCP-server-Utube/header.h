#pragma once
#include <string>
//#include <WinSock2.h>

void printIsDone(std::string whatIsDone)
{
	std::cout << whatIsDone << " - done" << std::endl;
}
void printError(std::string errorWhere) {
	std::cerr << "ERROR: " << errorWhere << std::endl;
}

void printSockInfo(std::string sockName, sockaddr_in* PservAddr) {
	std::cout << std::endl;
	std::cout << "================ [SOCKET ADDR INFO]================== " << std::endl;
	std::cout << "	 socket : " << sockName << std::endl;

	if (PservAddr->sin_family == 2) {
		std::cout << "     IP version : " << PservAddr->sin_family << " = IPv4" << std::endl;
	}
	else if (PservAddr->sin_family == 23) {
		std::cout << "     IP version : " << PservAddr->sin_family << " = IPv6" << std::endl;
	}
	std::cout << "	   prot : " << sockName << std::endl;

	std::cout << "===================================================== " << std::endl;

}

/*
class PrintClass
{
public:
	void printIsDone(std::string whatIsDone);
	void printError(std::string errorWhere);
	void printSockInfo(std::string sockName, sockaddr_in* PservAddr);
};



void PrintClass::printIsDone(std::string whatIsDone)
{
	std::cout << whatIsDone << " - done" << std::endl;
}
void PrintClass::printError(std::string errorWhere) {
	std::cerr << "ERROR: " << errorWhere << std::endl;
}

void PrintClass::printSockInfo(std::string sockName, sockaddr_in* PservAddr) {
	std::cout << std::endl;
	std::cout << "================ [SOCKET ADDR INFO]================== " << std::endl;
	std::cout << "	 socket : " << sockName << std::endl;

	if (PservAddr->sin_family == 2) {
		std::cout << "     IP version : " << PservAddr->sin_family << " = IPv4" << std::endl;
	}
	else if (PservAddr->sin_family == 23) {
		std::cout << "     IP version : " << PservAddr->sin_family << " = IPv6" << std::endl;
	}
	std::cout << "	   prot : " << sockName << std::endl;

	std::cout << "===================================================== " << std::endl;

}

*/