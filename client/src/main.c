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
    int our_socket = 0;
    char *message = "Hello peer";
    char buffer[300];
    socklen_t size;

    struct sockaddr_in peer_addr;
    if (get_other_peer_addr(&peer_addr) < 0)
    {
        printf("Network error when trying to get other's peer address");
        return -1;
    }
    printf("peer: %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

    if (udp_hole_punching(peer_addr) < 0)
    {
        printf("Network error when trying to hole punch");
        return -1;
    }

    if ((our_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) /* Creates the socket */
        return -1;

    /* Setup an entry for the peer on MY nat */
    if (sendto(our_socket, (const char *)&message, strlen(message),
               MSG_CONFIRM, (const struct sockaddr *)&peer_addr,
               sizeof(peer_addr)) /* Sends the massage to the server */
        < 0)
        return -1;

    size = sizeof(peer_addr);
    if (recvfrom(our_socket, buffer, 300, MSG_WAITALL, (struct sockaddr *)&peer_addr,
                 &size) /* Gets the other peer's address from the server */
        < 0)
        return -1;

    printf("Got: %s\n", buffer);

    return 0;
}
