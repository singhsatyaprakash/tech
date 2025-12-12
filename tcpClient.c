#include <stdio.h>
#include <winsock2.h>
#include <string.h>

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    int recv_size;

    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Winsock Initialized.\n");

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed.\n");
        return 1;
    }

    printf("Connected to server.\n");

    while (1) {
        printf("Client: ");
        gets(message);
        send(s, message, strlen(message), 0);

        if (strcmp(message, "exit") == 0)
            break;

        recv_size = recv(s, server_reply, 2000, 0);
        if (recv_size == SOCKET_ERROR) {
            printf("Recv failed.\n");
            break;
        }

        server_reply[recv_size] = '\0';
        printf("Server: %s\n", server_reply);

        if (strcmp(server_reply, "exit") == 0)
            break;
    }

    closesocket(s);
    WSACleanup();
    printf("\nChat ended.\n");
    return 0;
}
