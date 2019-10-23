#include "helper.h"

int main(int argc, char* argv[])
{
    socklen_t clilen;
    int sockfd, newsockfd, port_no, filefd;
    char* buffer;
    struct sockaddr_in6 serv_addr, cli_addr;
    int n;
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }
    /** return fd if file exists else create and return fd*/
    create_file(argv[2], &filefd);
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
	/* read the message length */
	char temp[BUFFERLENGTH];
	n = read(newsockfd, temp, BUFFERLENGTH);
	if (n < 0)
	    error("ERROR reading from socket");
	printf("\nrecieved message:\n%s", temp);
	/** read the message */
	int length = atoi(temp);
	buffer = (char*)malloc(length * sizeof(char));
	if (buffer == NULL)
	    error("ERROR allocating memory");
	n = read(newsockfd, buffer, length);
	if (n < 0)
	    error("ERROR reading from socket");
	printf("\nrecieved message:\n%s", buffer);
	/** write or append to logfile based on context */
	write_or_append(&filefd, buffer, 1);
    }

    close(newsockfd);
    free(buffer);
    return 0;
}
