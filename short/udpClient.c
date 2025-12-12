// Simple UDP Client
// Steps: Init → Socket → Set server addr → sendto/recvfrom

#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA w;
    SOCKET server;
    struct sockaddr_in serv_addr;
    int serv_len, r;
    char msg[1000];

    WSAStartup(MAKEWORD(2,2), &w);

    // 1️⃣ Create UDP socket
    server = socket(AF_INET, SOCK_DGRAM, 0);

    // 2️⃣ Server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);
    serv_len = sizeof(serv_addr);

    // 3️⃣ Chat loop
    while(1) {
        printf("Client: ");
        gets(msg);
        sendto(server, msg, strlen(msg), 0, (struct sockaddr*)&serv_addr, serv_len);

        if(strcmp(msg,"exit")==0) break;

        r = recvfrom(server, msg, sizeof(msg), 0, (struct sockaddr*)&serv_addr, &serv_len);
        msg[r] = '\0';
        printf("Server: %s\n", msg);

        if(strcmp(msg,"exit")==0) break;
    }

    closesocket(server);
    WSACleanup();
}
