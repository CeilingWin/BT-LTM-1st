#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32")
using namespace std;
//union data : fix lỗi hàm memcpy() khi copy vào biến addr với addrlen dài sẽ chiếm dụng bộ nhớ của biến khác 
union Data {
	SOCKADDR_IN addr;
	char c[50];
};
bool checkDomain(char *domain) {
	//kiểm tra xem domain có phải tên miền hợp lệ không, nếu đúng trả về true 
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
		Data data;
		addrinfo *info;
		int cannotGetAddrInfo = getaddrinfo(domain, "http", NULL, &info);
		if (cannotGetAddrInfo) {
			cout << "khong the phan giai ten mien\n";
		}
		else {
			int ipSt = 0;
			do {
				ipSt++;
				memcpy(&data.addr, info->ai_addr, info->ai_addrlen);
				cout <<"dia chi ip "<<ipSt<<":"<< inet_ntoa(data.addr.sin_addr) << "\n";
				info = info->ai_next;
			} while (info != NULL);
		}
	}
	WSACleanup();
	system("pause");
	return 0;
}