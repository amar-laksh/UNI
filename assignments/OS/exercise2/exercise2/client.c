#include "helper.h"

int main(int argc, char* argv[])
{
    size_t bufsize = 256;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sockfd, s;
    char* buffer;
    int n, chars;
    if (argc != 3) {
	fprintf(stderr, "usage %s hostname port\n", argv[0]);
	exit(1);
    }
    buffer = (char*)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
	error("ERROR allocating memory");
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
    }
    /* getaddrinfo() returns a list of address structures.
	     *        Try each address until we successfully connect(2).
	     *               If socket(2) (or connect(2)) fails, we (close the socket
	     *                      and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
	sockfd = socket(rp->ai_family, rp->ai_socktype,
	    rp->ai_protocol);
	if (sockfd == -1)
	    continue;
	if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)
	    break; /* Success */
	close(sockfd);
    }
    if (rp == NULL) { /* No address succeeded */
	fprintf(stderr, "Could not connect\n");
	exit(EXIT_FAILURE);
    }
    freeaddrinfo(result); /* No longer needed */
    /** Getting message from input */
    while ((chars = getdelim(&buffer, &bufsize, '\n', stdin)) >= 0) {
	/** send message length */
	char length[BUFFERLENGTH];
	itoa(chars, length, 10);
	printf("\nsending message: %s\n", length);
	n = write(sockfd, length, BUFFERLENGTH);
	if (n < 0)
	    error("ERROR writing to socket");
	/* send message */

	printf("\nsending message: %s\n", buffer);
	n = write(sockfd, buffer, chars);
	if (n < 0)
	    error("ERROR writing to socket");
    }
    free(buffer);
    return 0;
}
