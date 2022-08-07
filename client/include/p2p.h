#ifndef __P2P_H__
#define __P2P_H__

#include <netinet/in.h>

/**
 * @brief Gets from server the address of the other peer.
 * 
 * @param our_socket A socket to talk with.
 * @param peer_addr A pointer to an address object.
 * @return int 0 on success, -1 on error.
 */
int get_other_peer_addr(int our_socket, struct sockaddr_in *peer_addr);

/**
 * @brief Setups a P2P connection using the UDP Hole Punching method.
 * @param our_socket A socket to talk with.
 * @param peer_addr The address of the other peer.
 * @return int 0 on success, -1 on error.
 */
int udp_hole_punching(int our_socket, struct sockaddr_in peer_addr);

#endif