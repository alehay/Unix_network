#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include    <sys/errno.h>
#include    <netinet/in.h>
#include    <netinet/ip.h>
#include    <stdlib.h>
#include    <stdio.h>
#include	<time.h>		/* timespec{} for pselect() */

#define MAXLINE 50 

int main(int argc, char * argv []) 
{
    int sockfd;
    int n;
    char recvline [MAXLINE+1];
    struct sockaddr_in servaddr;



    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        printf("socket error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(65501);

    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        printf("eroor socket " );
    }

    if(connect(sockfd, &servaddr, sizeof(servaddr)) < 0) {
        printf ("connect error");
        exit (1);
    }

    int cycles_coutn = 0; 
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		++cycles_coutn;
        recvline[n] = 0;	/* null terminate */
		printf("%d bytes: %s", n, recvline);
	}
    printf ("cycles is %d", cycles_coutn);
	exit(0);


}