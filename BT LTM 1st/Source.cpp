#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32")
using namespace std;
bool checkDomain(char *domain) {
	//kiem tra co phai la ten mien hay khong
	//neu dung tra ve true
	//sai tra ve false
	int i = 0;
	char c;
	while (domain[i] != 0) {
		c = domain[i];
		i++;
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0'&& c <= '9')
			|| (c == '.')
			|| (c == '\\')
			|| (c == '-')
			) {
			continue;
		}
		else
			return false;

	}
	return true;
}
int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	char domain[100];
	gets_s(domain);

	if (!checkDomain(domain)) {
		cout << "chuoi vua nhap khong phai ten mien\n";
	}
	else {
		SOCKADDR_IN addr;
		addrinfo *info;
		int cannotGetAddrInfo = getaddrinfo(domain, "http", NULL, &info);
		if (cannotGetAddrInfo) {
			cout << "khong the phan giai ten mien\n";
		}
		else {
			int ipSt = 0;
			do {
				ipSt++;
				memcpy(&addr, info->ai_addr, info->ai_addrlen);
				cout <<"dia chi ip "<<ipSt<<":"<< inet_ntoa(addr.sin_addr) << "\n";
				info = info->ai_next;
			} while (info != NULL);
		}
	}
	WSACleanup();
	system("pause");
	return 0;
}