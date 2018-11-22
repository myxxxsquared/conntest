
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

    if(inet_pton(AF_INET, DSTADDR, &serv_addr.sin_addr) != 1)
        printerror("inet_pton(AF_INET, DSTADDR, &serv_addr.sin_addr)", errno);

    if(connect(sockfd_tcp, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        printerror("connect(sockfd_tcp, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))", errno);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "TCP: This is client.");
    ssize_t transmitted = send(sockfd_tcp, buffer, strlen(buffer) + 1, 0);
    if(transmitted == (ssize_t)-1)
        printerror("send(sockfd_tcp, buffer, strlen(buffer) + 1, 0)", errno);

    ssize_t received = recv(sockfd_tcp, buffer, sizeof(buffer) - 1, 0);
    if(received == (ssize_t)-1)
        printerror("recv(sockfd_tcp, buffer, sizeof(buffer) - 1, 0)", errno);
    buffer[received] = 0;
    printf("received: %s\n", buffer);

    close(sockfd_tcp);

    strcpy(buffer, "UDP: This is client.");
    transmitted = sendto(sockfd_udp, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(transmitted == (ssize_t)-1)
        printerror("sendto(sockfd_udp, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr))", errno);

    received = recvfrom(sockfd_udp, buffer, sizeof(buffer) - 1, 0, 0, 0);
    if(received == (ssize_t)-1)
        printerror("recvfrom(sockfd_udp, buffer, sizeof(buffer) - 1, 0, 0, 0)", errno);
    buffer[received] = 0;
    printf("received: %s\n", buffer);

    close(sockfd_udp);
}
