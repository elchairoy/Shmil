#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "p2p.h"
#include "server_details.h"

int get_other_peer_addr(struct sockaddr_in *peer_addr)
{
    int our_socket = 0;
    struct sockaddr_in server_addr;

    if ((our_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return -1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(our_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        return -1;

    if (!read(our_socket, peer_addr, sizeof(*peer_addr)))
        return -1;

    return 0;
}
