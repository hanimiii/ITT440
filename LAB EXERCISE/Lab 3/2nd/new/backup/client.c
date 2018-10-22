#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH 512

void sendFile(int sockfd);
void recvFile(int connfd, int sockfd);

int main(int argc,char *argv[])
{
	int sockfd, connfd;
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
    int success = 0;
    char op;

    while(success == 0){
        printf("1. Send File\n");
		printf("2. Receive File\n");
		printf("Enter your choice...\n\n");
		scanf("%c", &op);

		if(op == '1'){
            sendFile(sockfd);
		}else if(op == '2'){
			recvFile(connfd, sockfd);
		}
    }

    close(connfd);
    printf("[Client] Connection with Server closed.\n");
    return(0);
}

void sendFile(int sockfd){
	char* fs_name = "clientRead.txt";
	char sdbuf[LENGTH]; //send buffer
	printf("[Client] Sending %s to the Server...\n", fs_name);
	FILE *fs = fopen(fs_name, "r");

	if(fs == NULL){
		printf("ERROR: File %s not found on client.\n", fs_name);
		exit(1);
	}else{
		bzero(sdbuf, LENGTH);
		int fs_block_sz = 0;
		int success = 0;
		while(success == 0){
			while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) >0){
				if(send(sockfd, sdbuf, fs_block_sz, 0) <0){
					printf("ERROR: Failed to send file %s.\n", fs_name);
					exit(1);
				}
				bzero(sdbuf, LENGTH);
			}
			sleep(5);
			printf("[Server] Send Done!\n\n");
			success = 1;
			fclose(fs);
		}
	}
}

void recvFile(int connfd, int sockfd){
    char revbuf[LENGTH];
    char* fr_name = "clientWrite.txt";
    printf("[Client] Receiving file from server and saving as clientWrite.txt\n");
    FILE *fr = fopen(fr_name, "a");
    
    if(fr == NULL){
        printf("File %s cannot be opened.\n", fr_name);
    }else{
        bzero(revbuf, LENGTH);
        int fr_block_sz = 0;
        int success= 0;
        while(success == 0){
            while(fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)){
                if(fr_block_sz < 0){
                    error("Receive file error.\n");
                }

                int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
                if(write_sz < fr_block_sz){
                    error("File write failed.\n");
                }else if(fr_block_sz){
                    break;
                }
                bzero(revbuf, LENGTH);
            }
            sleep(5);
            printf("[Client] Received from server!\n\n");
            success=1;
            fclose(fr);
        }
    }
}