#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	int sockfd, connfd;
	char sendline[100];
	char recvline[100];
	struct sockaddr_in servaddr;

    //Check user input for IP address
    if(argc != 2){
        fprintf(stderr, "Usage: client hostname\n");
        exit(1);
    }

    //Socket Function
	sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Socket failed: ");
        exit(1);
    }

	bzero(&servaddr,sizeof servaddr);

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);

    //Connect Function
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	while(1)
	{
        //Reset the variable
		bzero( sendline, 100);
		bzero( recvline, 100);

        //User input
        printf("Client: ");
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */

        //Write Function
        send(sockfd, sendline, sizeof(sendline), 0);

        //Read Function
        recv(sockfd, recvline, sizeof(recvline), 0);
        printf("Server: %s",recvline);
	}

    //Close Function
    close(sockfd);
    return 0;
}
