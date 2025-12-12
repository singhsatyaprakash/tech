// Simple UDP Server (easy)
// Steps: Init → Socket → Bind → recvfrom/sendto

#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA w;
    SOCKET server;
    struct sockaddr_in serv_addr, client_addr;
    int cli_len, r;
    char msg[1000];

    WSAStartup(MAKEWORD(2,2), &w);

    // 1️⃣ Create UDP socket
    server = socket(AF_INET, SOCK_DGRAM, 0);

    // 2️⃣ Bind server to port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8888);
    bind(server, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("UDP Server ready...\n");
    cli_len = sizeof(client_addr);

    // 3️⃣ Chat loop
    while (1) {
        r = recvfrom(server, msg, sizeof(msg), 0, (struct sockaddr*)&client_addr, &cli_len);
        msg[r] = '\0';
        printf("Client: %s\n", msg);

        if(strcmp(msg,"exit")==0) break;

        printf("Server: ");
        gets(msg);
        sendto(server, msg, strlen(msg), 0, (struct sockaddr*)&client_addr, cli_len);

        if(strcmp(msg,"exit")==0) break;
    }

    closesocket(server);
    WSACleanup();
}
