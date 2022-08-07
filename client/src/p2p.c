#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "p2p.h"
#include "server_details.h"

#define MAX_MASSAGE_LEN 1024

#define HOLE_PUNCHING 0x1234 /* The message to send to the other peer when I want to start hole-punching */

int get_other_peer_addr(int our_socket, struct sockaddr_in *peer_addr)
{
    char *hello = "Hello from client"; /* The message to send to the server (could be any massage) */
    unsigned int len;                  /* The length of server_addr (needed for recvfrom) */
    struct sockaddr_in server_addr;

    /* Inserts the server_address (family, port and IP) to server_addr: */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (sendto(our_socket, (const char *)hello, strlen(hello),
               MSG_CONFIRM, (const struct sockaddr *)&server_addr,
               sizeof(server_addr)) /* Sends the massage to the server */
        < 0)
        return -1;
    printf("Hello message sent.\n");

    len = sizeof(&server_addr);
    if (recvfrom(our_socket, peer_addr, MAX_MASSAGE_LEN,
                 MSG_WAITALL, (struct sockaddr *)&server_addr,
                 &len) /* Gets the other peer's address from the server */
        < 0)
        return -1;

    return 0;
}

int udp_hole_punching(int our_socket, struct sockaddr_in peer_addr)
{
    /* We just need to send a message to the client */

    int message = HOLE_PUNCHING;

    /* Setup an entry for the peer on MY nat */
    if (sendto(our_socket, (const char *)&message, sizeof(message),
               MSG_CONFIRM, (const struct sockaddr *)&peer_addr,
               sizeof(peer_addr)) /* Sends the massage to the server */
        < 0)
        return -1;

    return 0;
}
