#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080 // Server port
#define BUFFER_SIZE 1024 // Message size

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Error initializing Winsock");
        return 1;
    }

    // Create the UDP socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("Error creating the socket");
        return 1;
    }
    
    char SERVER_IP[16]; // Changed the data type to an array of characters

    printf("Enter the Server IP Address: ");
    scanf("%s", SERVER_IP);

    // Configure the server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (1) {
        printf("Enter the message to send (or 'exit' to quit): ");
        gets(message);

        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Send the message to the server
        sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    // Close the socket and release resources
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
