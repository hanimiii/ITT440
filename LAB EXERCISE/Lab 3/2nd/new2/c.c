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

int main(int argc,char *argv[])
{
	int sockfd, connfd;
    char revbuf[LENGTH];
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
	connfd = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    printf("[Client] Connection Established!\n\n");
    
    //Send file
    char* fs_name = "cSend.txt";
    char sdbuf[LENGTH];
    printf("[Client] Sending %s to the server... \n", fs_name);
    FILE *fs = fopen(fs_name, "r");
    if(fs == NULL){
        printf("ERROR: File %s not found.\n", fs_name);
        exit(1);
    }

    bzero(sdbuf, LENGTH);
    int fs_block_sz;
    while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
	{
		if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
		{
		    fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
		    break;
		}
		bzero(sdbuf, LENGTH);
	}
	printf("[Client] File %s sent!\n", fs_name);
	
    //Receive file
    printf("[Client] Receiving file from server and save as cReceived.txt\n");
    char* fr_name = "cReceived.txt";
    FILE *fr = fopen(fr_name, "a");
    if(fr == NULL)
		printf("File %s Cannot be opened.\n", fr_name);
	else
	{
		bzero(revbuf, LENGTH); 
		int fr_block_sz = 0;
	    while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
	    {
			int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
	        if(write_sz < fr_block_sz)
			{
	            error("File write failed.\n");
	        }
			bzero(revbuf, LENGTH);
			if (fr_block_sz == 0 || fr_block_sz != 512) 
			{
				break;
			}
		}
		if(fr_block_sz < 0)
        {
			if (errno == EAGAIN)
			{
				printf("recv() timed out.\n");
			}
			else
			{
				fprintf(stderr, "recv() failed due to errno = %d\n", errno);
			}
		}
	    printf("[Client] received from server!\n");
	    fclose(fr);
	}

    close(connfd);
    printf("\n[Client] Connection with Server closed.\n");
    return(0);
}
