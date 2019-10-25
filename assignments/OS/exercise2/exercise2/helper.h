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
#define BUFFERLENGTH 20

//debug prints: set DEBUG to 0 to remove the debug prints from the output
#define DEBUG 1
#define debug_print(...)                  \
    do {                                  \
	if (DEBUG)                        \
	    fprintf(stderr, __VA_ARGS__); \
    } while (0)

void swap(char* x, char* y)
{
    char t = *x;
    *x = *y;
    *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char* buffer, int i, int j)
{
    while (i < j)
	swap(&buffer[i++], &buffer[j--]);
    return buffer;
}

// Iterative function to implement itoa() function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
	return buffer;
    // consider absolute value of number
    int n = abs(value);
    int i = 0;
    while (n) {
	int r = n % base;

	if (r >= 10)
	    buffer[i++] = 65 + (r - 10);
	else
	    buffer[i++] = 48 + r;
	n = n / base;
    }
    // if number is 0
    if (i == 0)
	buffer[i++] = '0';
    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
	buffer[i++] = '-';
    buffer[i] = '\0'; // null terminate string
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

/* long atoi(const char* S, int n) */
// {
// // base case - we have reached end of the string or
// // current character is non-numeric
// if (n < 0 || (S[n] < '0' || S[n] > '9'))
// return 0;
//
// // recur for remaining digits and append current digit
// // to result of recusion multiply by 10
// return (10 * atoi(S, n - 1) + (S[n] - '0'));
// }
/*  */
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

void create_file(const char* filename, FILE* filefd)
{
    filefd = fopen(filename, "a+");
    if (filefd == NULL)
	error("Failed to open file\n");
}

void write_or_append(FILE* filefd, char* buffer, int flag)
{
}

#endif /* ifndef HELPER_H */
