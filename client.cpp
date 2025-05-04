// client.cpp
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change IP for remote server
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(sock, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;

    char buffer[1024];

    while (true) {
        cout << "You: ";
        cin.getline(buffer, sizeof(buffer));
        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        cout << "Server: " << buffer << endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
