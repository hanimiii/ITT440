#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define LENGTH 512

void sendFile(int connfd);
void recvFile(int connfd, int sockfd);

int main()
{
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
	printf("[Server] Connection Established!\n\n");
    int success = 0;
	char op;

	while(success == 0){
		printf("1. Send File\n");
		printf("2. Receive File\n");
		printf("Enter your choice...\n\n");
		scanf("%c", &op);

		if(op == '1'){
			sendFile(connfd);
		}else if(op == '2'){
			recvFile(connfd, sockfd);
		}
	}

	close(connfd);
	printf("[Server] Connection with Client closed. Server will wait now...\n");
	return(0);
}

void sendFile(int connfd){
	char* fs_name = "serverRead.txt";
	char sdbuf[LENGTH]; //send buffer
	printf("[Server] Sending %s to the Client...\n", fs_name);
	FILE *fs = fopen(fs_name, "r");

	if(fs == NULL){
		printf("ERROR: File %s not found on server.\n", fs_name);
		exit(1);
	}else{
		bzero(sdbuf, LENGTH);
		int fs_block_sz = 0;
		int success = 0;
		while(success == 0){
			while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) >0){
				if(send(connfd, sdbuf, fs_block_sz, 0) <0){
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
    char* fr_name = "serverWrite.txt";
    printf("[Server] Receiving file from client and saving as serverWrite.txt\n");
    FILE *fr = fopen(fr_name, "a");
    
    if(fr == NULL){
        printf("File %s cannot be opened.\n", fr_name);
    }else{
        bzero(revbuf, LENGTH);
        int fr_block_sz = 0;
        int success= 0;
        while(success == 0){
            while(fr_block_sz = recv(connfd, revbuf, LENGTH, 0)){
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
            printf("[Server] Received from client!\n\n");
            success=1;
            fclose(fr);
        }
    }
}