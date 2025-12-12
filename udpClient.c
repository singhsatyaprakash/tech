#include <stdio.h>
#include <winsock2.h>
#include <string.h>

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server, client;
    int client_len, recv_size;
    char recv_msg[1024], send_msg[1024];

    // Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Winsock Initialized.\n");

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d", WSAGetLastError());
        return 1;
    }
    printf("Server started. Waiting for client...\n");

    client_len = sizeof(client);

    // Chat loop
    while (1) {
        memset(recv_msg, 0, sizeof(recv_msg));

        // Receive message from client
        recv_size = recvfrom(sock, recv_msg, sizeof(recv_msg), 0, (struct sockaddr *)&client, &client_len);
        if (recv_size == SOCKET_ERROR) {
            printf("recvfrom() failed: %d", WSAGetLastError());
            break;
        }

        recv_msg[recv_size] = '\0';
        printf("\nClient: %s\n", recv_msg);

        // Exit condition
        if (strcmp(recv_msg, "exit") == 0)
            break;

        // Send reply
        printf("Server: ");
        gets(send_msg);
        sendto(sock, send_msg, strlen(send_msg), 0, (struct sockaddr *)&client, client_len);

        if (strcmp(send_msg, "exit") == 0)
            break;
    }

    closesocket(sock);
    WSACleanup();
    printf("Chat ended.\n");
    return 0;
}
