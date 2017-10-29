#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 100

main()
{
	int sockfd, retval;
	int recedbytes, sentbytes;
	int i, choice=1;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE], endchar, recvdchar;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("\nSocket Creation Error");
	}

	//printf("%i",sockfd); Commented out by Samar
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(3388);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//loopback
	retval = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	if(retval == -1)
	{
		printf("Connection error");
	}
	//start
	while(choice)
	{
	 	printf("Enter the text\n");
	 	gets(buff);	
	 	int n = strlen(buff);
	 	for(i = 0; i < n; i++)
	 	{
			sentbytes = send(sockfd,&buff[i],sizeof(buff[i]),0);
			if(sentbytes == -1)
			{
				printf("Local server error\n");
				close(sockfd);
			}
			if(i == n-1)
			{	
				endchar = '~';
		 		sentbytes = send(sockfd,&endchar,sizeof(endchar),0);
			}
	 	}	 	 		 
	  	while(1)
	  	{
	    	recedbytes = recv(sockfd,&recvdchar,sizeof(recvdchar),0);	    	 
	    	if(recvdchar == '~')
 		 	{
 		 		break;
 		 	}
	    	putchar(recvdchar);
	    	printf("\n");
	  	}
	 	printf("Wish to continue?(1 for yes/anything else for no)\n");
	 	scanf("%d",&choice);
	}
}