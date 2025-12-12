#include <stdio.h>
#include <winsock2.h>
#include <string.h>

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;
    char client_msg[2000], server_msg[2000];

    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Winsock Initialized.\n");

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("Bind done.\n");

    // Listen
    listen(server_socket, 3);
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);

    client_socket = accept(server_socket, (struct sockaddr *)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed with error code : %d", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Connection accepted.\n");

    while (1) {
        int recv_size = recv(client_socket, client_msg, 2000, 0);
        if (recv_size == SOCKET_ERROR) {
            printf("Recv failed.\n");
            break;
        }
        client_msg[recv_size] = '\0';
        printf("\nClient: %s\n", client_msg);

        if (strcmp(client_msg, "exit") == 0)
            break;

        printf("Server: ");
        gets(server_msg);

        send(client_socket, server_msg, strlen(server_msg), 0);

        if (strcmp(server_msg, "exit") == 0)
            break;
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    printf("\nChat ended.\n");
    return 0;
}

