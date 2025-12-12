// Simple TCP Client
// Steps: Init → Socket → Connect → Chat

#include <stdio.h>
#include <winsock2.h>
#include<string.h>

int main() {
    WSADATA wsa;
    SOCKET server;
    struct sockaddr_in serv_addr;
    char msg[1000], reply[1000];

    // 1️⃣ Initialize
    WSAStartup(MAKEWORD(2,2), &wsa);
    printf("Winsock Initialized.\n");

    // 2️⃣ Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created.\n");
    // 3️⃣ Connect to server (localhost)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);
    connect(server, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Connected to server!\n");

    // 4️⃣ Chat
    while(1) {
        printf("Client: ");
        gets(msg);
        send(server, msg, strlen(msg), 0);

        if(strcmp(msg,"exit")==0) break;

        int r = recv(server, reply, sizeof(reply), 0);
        reply[r] = '\0';
        printf("Server: %s\n", reply);
    }

    closesocket(server);
    WSACleanup();
}
