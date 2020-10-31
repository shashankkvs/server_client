#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/wait.h>
int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		perror("socket error:");
		exit(1);
	}

	struct sockaddr_in sa,ca;
	sa.sin_family=AF_INET;
	sa.sin_port=htons(3005);
	sa.sin_addr.s_addr=INADDR_ANY;
	memset(&(sa.sin_zero),0,8);


	if(bind(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0){
		perror("bind error");
		exit(1);
	}

	listen(sockfd,5);

	int newsock;
	int length=sizeof(ca);
	
	while(1){	
	if((newsock=accept(sockfd,(struct sockaddr*)&ca,&length))<0){
		perror("accept error");
		exit(1);
	}
	int cpid=fork();

	if(cpid==0){
	printf("\n\n************CONNECTION ESTABLISHED*************\n\n");
	
	char snd[256]={'\0'},rcv[256]={'\0'};
	while(1){
		recv(newsock,&rcv,sizeof(rcv),0);
		printf("recieved:%s",rcv);
		if(strncmp(rcv,"BYE",3)==0) break;
	}
	close(newsock);
	}
	}
	int status;
	waitpid(-1,&status,0);
	
	close(sockfd);
}

		
