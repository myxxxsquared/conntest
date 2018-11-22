
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


const uint16_t DSTPORT = 8888;
const char * const DSTADDR = "192.168.2.15";

void printerror(const char* desc, int e)
{
    fprintf(stderr, "ERROR: %s(%d). %s\n", strerror(e), e, desc);
    exit(e);
}
