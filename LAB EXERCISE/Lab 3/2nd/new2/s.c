#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>


#define LENGTH 256

int main()
{
	int sockfd, connfd;
    char revbuf[LENGTH];
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
	printf("[Server] Connection Established!\n\n");
    

    //Receive file
    char* fr_name = "Sreceive.txt";
    FILE *fr = fopen(fr_name, "a");
    if(fr == NULL){
        printf("File %s cannot be open on server.\n", fr_name);
    }else{
        bzero(revbuf, LENGTH);
        int fr_block_sz = 0;
        while((fr_block_sz = recv(connfd, revbuf, LENGTH, 0)) > 0) 
		{
			int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
			if(write_sz < fr_block_sz)
			{
			    error("File write failed on server.\n");
			}
			bzero(revbuf, LENGTH);
			if (fr_block_sz == 0 || fr_block_sz != 512) 
			{
				break;
			}
		}
        if(fr_block_sz < 0){
            if(errno == EAGAIN){
                printf("recv() timed out.\n");
            }else{
                fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                exit(1);
            }
        }
        printf("[Server] Received from client!\n");
        fclose(fr);
    }

    //Send File
    char* fs_name = "Ssend.txt";
    char sdbuf[LENGTH];
    printf("[Server] Sending %s to Client...\n", fs_name);
    FILE *fs = fopen(fs_name, "r");
    if(fs == NULL)
	{
		fprintf(stderr, "ERROR: File %s not found on server. (errno = %d)\n", fs_name, errno);
		exit(1);
	}

    bzero(sdbuf, LENGTH);
    int fs_block_sz;
    while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
	{
		if(send(connfd, sdbuf, fs_block_sz, 0) < 0)
		{
		    fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
		    exit(1);
		}
		bzero(sdbuf, LENGTH);
	}
	printf("[Server] Sent to client!\n");

	close(connfd);
	printf("\n[Server] Connection with Client closed. Server will wait now...\n");
	return(0);
}

