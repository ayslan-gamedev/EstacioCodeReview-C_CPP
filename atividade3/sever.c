#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080 // Port to receive messages
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Error initializing Winsock");
        return 1;
    }

    // Create the UDP socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("Error creating the socket");
        return 1;
    }

    // Configure the server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        perror("Error binding the socket to the port");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server waiting for messages on port %d...\n", PORT);

    while (1) {
        // Receive the message from the client
        int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == SOCKET_ERROR) {
            perror("Error receiving message");
            break;
        }

        // Add a null terminator to display the message
        buffer[bytesReceived] = '\0';

        printf("Message received from the client: %s\n", buffer);
    }

    // Close the socket and release resources
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
