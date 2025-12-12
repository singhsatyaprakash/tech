// Simple TCP Server (easy to remember)
// Steps: Init → Socket → Bind → Listen → Accept → Chat

#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in serv_addr, client_addr;
    int addr_len;
    char msg[1000];

    // 1️⃣ Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);
    printf("Winsock Initialized.\n");

    // 2️⃣ Create TCP socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created.\n");

    // 3️⃣ Bind server to port 8888
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // any IP
    serv_addr.sin_port = htons(8888);
    bind(server, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Bind done.\n");

    // 4️⃣ Listen and accept
    listen(server, 3);
    addr_len = sizeof(client_addr);
    client = accept(server, (struct sockaddr*)&client_addr, &addr_len);

    printf("Client connected!\n");

    // 5️⃣ Simple chat loop
    while (1) {
        int r = recv(client, msg, sizeof(msg), 0);
        msg[r] = '\0';
        printf("Client: %s\n", msg);

        if(strcmp(msg,"exit")==0) break;

        printf("Server: ");
        gets(msg);
        send(client, msg, strlen(msg), 0);
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
}
