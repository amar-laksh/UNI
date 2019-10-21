#ifndef HELPER_H
#define HELPER_H

#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFERLENGTH 256

void error(char* msg)
{
    perror(msg);
    exit(1);
}

void check_port(char* port_no, int* portno)
{
    *portno = atoi(port_no);
    if ((*portno < 0) || (*portno > 65535)) {
	fprintf(stderr, "%s: Illegal port number, exiting!\n", port_no);
	exit(1);
    }
}

void create_and_bind_socket(int* sockfd, int* port_no, struct sockaddr_in6* addr)
{
    *sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (*sockfd < 0)
	error("ERROR opening socket");
    bzero((char*)addr, sizeof(*addr));
    addr->sin6_family = AF_INET6;
    addr->sin6_addr = in6addr_any;
    addr->sin6_port = htons(*port_no);

    if (bind(*sockfd, (struct sockaddr*)addr,
	    sizeof(*addr))
	< 0)
	error("ERROR on binding");
}

void accept_con(int* sockfd, struct sockaddr_in6* addr, socklen_t* len, int* newsockfd)
{

    *newsockfd = accept(*sockfd,
	(struct sockaddr*)addr,
	len);
    if (*newsockfd < 0)
	error("ERROR on accept");
}

#endif /* ifndef HELPER_H */
