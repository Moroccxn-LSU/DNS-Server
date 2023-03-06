/*
    Adam Elkhanoufi
    Simple DNS Server in C
    12/02/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 53 // port for the DNS server
#define MAX_REQUESTS 10 // maximum number of requests the server can handle simultaneously

int main(){

    int sockfd, clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    char buffer[1024];
    int bytes_received, bytes_sent;
    struct hostent *host;

    // create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1){
        perror("Error creating socket");
        return 1;
    }

    // set the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1){
        perror("Error binding socket to server address");
        return 1;
    }

    // set the maximum number of requests the server can handle simultaneously
    if (listen(sockfd, MAX_REQUESTS) == -1){
        perror("Error setting maximum number of requests");
        return 1;
    }

    // accept incoming requests
    while (1){
        client_addr_size = sizeof(client_addr);
        clientfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_size);
        if (clientfd == -1){
            perror("Error accepting incoming request");
            return 1;
        }

        // receive the DNS query
        bytes_received = recv(clientfd, buffer, sizeof(buffer), 0);
        if (bytes_received == -1){
            perror("Error receiving DNS query");
            return 1;
        }

        // resolve the domain name
        host = gethostbyname(buffer);
        if (host == NULL){
            perror("Error resolving domain name");
            return 1;
        }

        // send the DNS response
        bytes_sent = sendto(clientfd, host->h_addr, host->h_length, 0, (struct sockaddr*) &client_addr, client_addr_size);
        if (bytes_sent == -1){
            perror("Error sending DNS response");
            return 1;
        }

        // close the client socket
        close(clientfd);
    }

    // close the server socket
    close(sockfd);

    return 0;
}
