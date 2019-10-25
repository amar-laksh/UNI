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
    int sockfd, newsockfd, port_no;
    char* message;
    struct sockaddr_in6 serv_addr, cli_addr;
    int n;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <logfile>\n", argv[0]);
	exit(1);
    }
    /** return fd if file exists else create and return fd*/
    /* check port number */
    check_port(argv[1], &port_no);
    /* create and bind socket */
    create_and_bind_socket(&sockfd, &port_no, &serv_addr);
    /* ready to accept connections */
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    /* waiting for connections */
    accept_con(&sockfd, &cli_addr, &clilen, &newsockfd);
    while (1) {
	/* read the message length */
	char temp[BUFFERLENGTH] = { '\0' };
	n = read(newsockfd, temp, BUFFERLENGTH);
	if (n < 0)
	    error("ERROR reading from socket");

	if (strcmp(temp, "\0") == 0) {
	    /** if no message, close the socket and start accepting new connections */
	    close(newsockfd);
	    accept_con(&sockfd, &cli_addr, &clilen, &newsockfd);
	    continue;
	}
	int length = atoi(temp);
	printf("\nrecieved length:\n%d", length);

	if (length > 0) {
	    /** if I have any message then write it to file */
	    /** read the message */
	    message = (char*)malloc((length * sizeof(char)));
	    bzero(message, (length * sizeof(char)));
	    if (message == NULL)
		error("ERROR allocating memory");
	    n = read(newsockfd, message, length);
	    if (n < 0)
		error("ERROR reading from socket");
	    printf("\nrecieved message:\n%s", message);
	    /** write or append to logfile based on context */
	    /** write_or_append((const char*)argv[2], message); */
	    free(message);
	}
    }
    return 0;
}
