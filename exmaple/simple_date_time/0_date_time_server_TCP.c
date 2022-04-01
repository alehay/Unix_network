#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include    <sys/errno.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <signal.h>
#include    <unistd.h>
#include    <netinet/in.h>
#include    <netinet/ip.h>
#include    <stdlib.h>
#include    <stdio.h>
#include	<time.h>		/* timespec{} for pselect() */

#define MAXLINE 50 

int terminate = 0;

void signal_handler (int signum) {
    terminate = 1;
        /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

}


int main (int argc, char * argv [] ) 
{

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t tics;

    if ((listenfd = socket (AF_INET, SOCK_STREAM,0)) < 0) {
        printf("socet error " );
        exit (1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(65501);


    if (bind(listenfd, &servaddr, sizeof(servaddr)) < 0) {
        printf ("error bind ");
        exit (1);
    }

    listen(listenfd, 0); 

    while ( terminate <= 0) {
        connfd = accept(listenfd,NULL, NULL);
        tics = time(NULL);
        snprintf(buff, sizeof(buff), "%24s\er\en", ctime(&tics));
        write(connfd, buff, strlen(buff));

        close(connfd);

    }

}