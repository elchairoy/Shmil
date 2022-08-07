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
int get_other_peer_addr(struct sockaddr_in *peer_addr)
{
    int our_socket = 0;
    char *hello = "Hello from client"; /* The message to send to the server (could be any massage) */
    unsigned int len;                  /* The length of server_addr (needed for recvfrom) */
    struct sockaddr_in server_addr;

    if ((our_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) /* Creates the socket */
        return -1;

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
    close(our_socket);
    return 0;
}
