#include "helper.h"

int main(int argc, char* argv[])
{
    socklen_t clilen;
    int sockfd, newsockfd, port_no;
    char buffer[BUFFERLENGTH];
    struct sockaddr_in6 serv_addr, cli_addr;
    int n;
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }
    /* check port number */
    check_port(argv[1], &port_no);
    /* create and bind socket */
    create_and_bind_socket(&sockfd, &port_no, &serv_addr);
    /* ready to accept connections */
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    while (1) {
	/* waiting for connections */
	accept_con(&sockfd, &cli_addr, &clilen, &newsockfd);
	bzero(buffer, BUFFERLENGTH);
	/* read the data */
	n = read(newsockfd, buffer, BUFFERLENGTH - 1);
	if (n < 0)
	    error("ERROR reading from socket");
	printf("Here is the message: %s\n", buffer);
	/* send the reply back */
	n = write(newsockfd, "I got your message", 18);
	if (n < 0)
	    error("ERROR writing to socket");
	close(newsockfd); /* important to avoid memory leak */
	return 0;
    }
}
