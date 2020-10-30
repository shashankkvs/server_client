#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

void perr(void){
	perror("error");
	exit(1);
}

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1) perr();

	struct sockaddr_in sa;
	sa.sin_family=AF_INET;
	sa.sin_port=htons(3005);
	sa.sin_addr.s_addr=INADDR_ANY;
	memset(&(sa.sin_zero),0,8);

	if(connect(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0) perr();

	printf("\n\n*****************CONNNECTION ESTABLISHED***************\n\n");


	char snd[256]={'\0'},rcv[256]={'\0'};

	while(1){
		printf("send:");
		fgets(snd,25,stdin);
		write(sockfd,&snd,sizeof(snd));
		if(strncmp(snd,"BYE",3)==0) break;

	}
	printf("\n\n******************CONNECTION TERMINATED*****************\n\n");
	close(sockfd);
}



