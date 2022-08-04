#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <netinet/in.h>

#include "p2p.h"

int main(void)
{
    struct sockaddr_in peer_addr;
    if (get_other_peer_addr(&peer_addr) < 0)
    {
        printf("Network error when trying to get other's peer address");
        return -1;  
    }
    printf("peer: %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

    return 0;
}