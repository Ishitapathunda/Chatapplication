// server.cpp
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);

    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    cout << "Listening for incoming connections..." << endl;

    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
        cout << "Client connected!" << endl;

        while (true) {
            memset(buffer, 0, sizeof(buffer));
            recv(client, buffer, sizeof(buffer), 0);
            cout << "Client: " << buffer << endl;

            cout << "You: ";
            cin.getline(buffer, sizeof(buffer));
            send(client, buffer, strlen(buffer), 0);
        }
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}
