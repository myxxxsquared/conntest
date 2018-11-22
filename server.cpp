
#include "conntest.h"

int main()
{
    int sockfd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd_tcp < 0)
        printerror("socket(AF_INET, SOCK_STREAM, 0)", errno);

    int sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_udp < 0)
        printerror("socket(AF_INET, SOCK_DGRAM, 0)", errno);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DSTPORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd_tcp, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        printerror("bind(sockfd_tcp, (const struct sockaddr*)&serv_addr, sizeof(serv_addr))", errno);
    if(bind(sockfd_udp, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        printerror("bind(sockfd_udp, (const struct sockaddr*)&serv_addr, sizeof(serv_addr))", errno);

    listen(sockfd_tcp, 1);

    struct sockaddr_in cli_addr;
    socklen_t cli_addr_len;
    int newfd_tcp = accept(sockfd_tcp, (struct sockaddr*)&cli_addr, &cli_addr_len);
    if(newfd_tcp < 0)
        printerror("accept(sockfd_tcp, (struct sockaddr*)&cli_addr, &cli_addr_len)", errno);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t received = recv(newfd_tcp, buffer, sizeof(buffer) - 1, 0);
    if(received == (ssize_t)-1)
        printerror("recv(newfd_tcp, buffer, sizeof(buffer) - 1, 0)", errno);
    buffer[received] = 0;
    printf("received: %s\n", buffer);

    strcpy(buffer, "TCP: This is server.");
    ssize_t transmitted = send(newfd_tcp, buffer, strlen(buffer) + 1, 0);
    if(transmitted == (ssize_t)-1)
        printerror("send(newfd_tcp, buffer, strlen(buffer) + 1, 0)", errno);

    close(newfd_tcp);
    close(sockfd_tcp);

    received = recvfrom(sockfd_udp, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&cli_addr, &cli_addr_len);
    if(received == (ssize_t)-1)
        printerror("recvfrom(sockfd_udp, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&cli_addr, &cli_addr_len)", errno);
    buffer[received] = 0;
    printf("received: %s\n", buffer);

    strcpy(buffer, "UDP: This is server.");
    transmitted = sendto(sockfd_udp, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&cli_addr, cli_addr_len);
    if(transmitted == (ssize_t)-1)
        printerror("sendto(sockfd_udp, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&cli_addr, cli_addr_len)", errno);

    close(sockfd_udp);
}
