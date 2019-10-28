#include "helper.h"

void write_or_append(const char* filename, char* message)
{
    FILE* fp = NULL;
    char c = 0;
    int lines = 0;
    fp = fopen(filename, "a+");
    if (fp == (FILE*)NULL)
	error("Failed to open file\n");
    while (!feof(fp)) {
	c = fgetc(fp);
	if (c == '\n') {
	    lines++;
	}
    }
    /** Writing the message to file */
    fprintf(fp, "%d %s", lines, message);

    fclose(fp);
}

int main(int argc, char* argv[])
{
    socklen_t clilen;
    int sockfd, newsockfd, port_no, length = 0;
    char* message = NULL;
    struct sockaddr_in6 serv_addr, cli_addr;
    int n;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <logfile>\n", argv[0]);
	exit(1);
    }
    /** return fd if file exists else create and return fd*/
    /* check port number */
    check_port(argv[1], &port_no);
    /* create socket */
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0)
	error("ERROR opening socket");
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_addr = in6addr_any;
    serv_addr.sin6_port = htons(port_no);
    /* bind it */
    if (bind(sockfd, (struct sockaddr*)&serv_addr,
	    sizeof(serv_addr))
	< 0)
	error("ERROR on binding");
    /* ready to accept connections */
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    /* waiting for connections */
    newsockfd = accept(sockfd,
	(struct sockaddr*)&cli_addr,
	&clilen);
    if (newsockfd < 0)
	error("ERROR on accept");
    while (1) {
	/* read the message length */
	char temp[BUFFERLENGTH];
	n = read(newsockfd, temp, BUFFERLENGTH);
	if (n < 0)
	    error("ERROR reading from socket");
	length = atoi(temp);
	if (strcmp(temp, "\0\0\0") != 0) {
	    /** if I have any message then write it to file */
	    debug_print("\nrecieved length:\n%d", length);

	    /** read the message */
	    message = (char*)malloc((length * sizeof(char) + 1));
	    if (message == NULL)
		error("ERROR allocating memory");
	    bzero(message, (length * sizeof(char)));
	    n = read(newsockfd, message, length);
	    if (n < 0)
		error("ERROR reading from socket");
	    debug_print("\nrecieved message:\n%s", message);
	    /** write or append to logfile based on context */
	    write_or_append((const char*)argv[2], message);
	    free(message);
	} else {
	    /** if EOF, close the socket and start accepting new connections */
	    close(newsockfd);
	    /**   waiting for connections ***/
	    newsockfd = accept(sockfd,
		(struct sockaddr*)&cli_addr,
		&clilen);
	    if (newsockfd < 0)
		error("ERROR on accept");
	    continue;
	}
    }
    close(sockfd);
    return 0;
}
