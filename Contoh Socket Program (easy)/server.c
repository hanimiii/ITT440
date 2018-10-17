#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char str[100];
	int sockfd, connfd;
	struct sockaddr_in servaddr;

    //Socket Function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero( &servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY); //Allow any ip to connect
	servaddr.sin_port = htons(22000); //listen on port 22000

    //Bind Function
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    //Listen Function
	listen(sockfd, 10); //Starts listening for connections request waiting, if more than 10 the 11th will fail

    //Accept Function
	connfd = accept(sockfd, (struct sockaddr*) NULL, NULL);

	while(1)
	{

		bzero( str, 100);

        //Read function
        recv(connfd, str, sizeof(str), 0);

		printf("Echoing back - %s",str);

        //Write Function
        send(connfd, str, sizeof(str), 0);
	}

    //Close Function
    close(sockfd);
}