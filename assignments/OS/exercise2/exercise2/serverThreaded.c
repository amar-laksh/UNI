#include "helper.h"

pthread_mutex_t mut;

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

void* processRequest(void* args)
{
    int length = 0;
    char* message = NULL;
    int n;
    request* req = (request*)args;
    int* newsockfd = req->sockfd;
    /* read the message length */
    char temp[BUFFERLENGTH];
    while (1) {
	n = read(*newsockfd, temp, BUFFERLENGTH);
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
	    n = read(*newsockfd, message, length);
	    if (n < 0)
		error("ERROR reading from socket");
	    debug_print("\nrecieved message:\n%s", message);
	    /** write or append to logfile based on context */
	    pthread_mutex_lock(&mut);
	    write_or_append((const char*)req->filename, message);
	    pthread_mutex_unlock(&mut);
	    /** Freeing the allocated memory of the message buffer */
	    free(message);
	} else {
	    /** if EOF, close the socket and start accepting new connections */
	    close(*newsockfd);
	    free(newsockfd);
	    break;
	}
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    socklen_t clilen;
    int sockfd, port_no;
    struct sockaddr_in6 serv_addr, cli_addr;
    request req;
    int result = 0;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <logfile>\n", argv[0]);
	exit(1);
    }
    /** Setting our filename pointer from input */
    req.filename = (const char*)argv[2];
    /** return fd if file exists else create and return fd*/
    /* check port number */
    check_port(argv[1], &port_no);
    /* create and bind socket*/
    create_and_bind_socket(&sockfd, &port_no, &serv_addr);

    /* ready to accept connections */
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    while (1) {
	pthread_attr_t pthread_attr;
	pthread_t server_thread;
	int* newsockfd;

	/** Allocating memory for each instance of socket */
	newsockfd = (int*)malloc(sizeof(int));
	if (!newsockfd)
	    error("Memory Allocation for socket failed!\n");

	accept_con(&sockfd, &cli_addr, &clilen, newsockfd);

	/* create separate thread for processing */
	if (pthread_attr_init(&pthread_attr))
	    error("Creating initial thread attributes failed!\n");

	if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED))
	    error("Setting thread attributes failed!\n");

	req.sockfd = newsockfd;
	result = pthread_create(&server_thread, &pthread_attr, processRequest, (void*)&req);
	if (result != 0)
	    error("Thread creation failed!\n");
    }
    close(sockfd);
    return 0;
}
