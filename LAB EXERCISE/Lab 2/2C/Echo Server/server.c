#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490" //the port users will be connecting t
#define MAXDATASIZE 100 //tambah dkt sini
#define BACKLOG 10 //how many pending connections queue 

void signchld_handler(int s){
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

//get sockaddr, IPV4 or IPV6:
void *get_in_addr(struct sockaddr *sa){
	if (sa->sa_family == AF_INET){
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int numbytes; //tambah dkt sinis
	int sockfd, new_fd, check;
	char buf[MAXDATASIZE], client_reply[MAXDATASIZE]; //tambah dkt sini
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	socklen_t sinsize;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo))!=0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	} 

	for(p = servinfo; p !=NULL;p = p->ai_next){
	    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
	        perror("server: socket");
	        continue;
        }	
	    
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1){
	        perror("setsockopt");
	        exit(1);	
        }

	    if (bind(sockfd, p->ai_addr, p->ai_addrlen)== -1){
	        close(sockfd);
	        perror("server:bind");
	        continue;	
	    }
        break;
    }

	if (p == NULL){
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	
	freeaddrinfo(servinfo);

	if (listen(sockfd, BACKLOG)==-1){
		perror("listen");
		exit(1);
	}

	sa.sa_handler = signchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &sa, NULL)==-1){
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections....\n");

	sinsize = sizeof their_addr;
	new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sinsize);
    if (new_fd == -1){
		perror("accept");
		//continue;
	}

	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
	printf("server: got connection from %s\n", s);

	while(1){
		bzero(client_reply, sizeof(client_reply));

		numbytes = recv(new_fd, client_reply, MAXDATASIZE-1, 0);
		if(numbytes < 0){
			perror("Recv Failed");
		}else{
			numbytes = send(new_fd, client_reply, MAXDATASIZE-1, 0);
			if(numbytes < 0){
				perror("Send failed");
				return 1;
			}
		}	
	}
	close(new_fd);
	return 0;
}