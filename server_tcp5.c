#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 100

main()
{
	int sockfd, newsockfd, retval;
	socklen_t actuallen;
	int recedbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;
	char recvdchar, buff[MAXSIZE];	

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd == -1)
	{
		printf("\nSocket creation error");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(3388);
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);//wildcard
	retval = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	if(retval == -1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval = listen(sockfd,5);//Size of queue changed to 5 from 1 -Samar and Rahul
	if(retval == -1)
	{
		close(sockfd);
	}

	actuallen = sizeof(clientaddr);
	newsockfd = accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);

	if(newsockfd == -1)
	{
		printf("Cannot connect\n");//printf added -Samar
		close(sockfd);
	}
	//start
	while(1)
	{
 		recedbytes = recv(newsockfd,&recvdchar,sizeof(recvdchar),0);
		if(recedbytes == -1)//local error
		{
		  	close(newsockfd);
		  	close(sockfd);		  	
		}
		else if(recvdchar == '~')//end found
		{
	    	sentbytes = send(newsockfd,&recvdchar,sizeof(recvdchar),0);
			if(sentbytes == -1)
			{
				close(newsockfd);
				close(sockfd);				
			}
			continue;
		}		
		else
		{			
			printf("%s\n",recvdchar);
			sentbytes = send(newsockfd,&recvdchar,sizeof(recvdchar),0);
			if(sentbytes == -1)
	  		{
				close(newsockfd);
				close(sockfd);
   	  		}
		}					
	}
	close(newsockfd);//order of close switched -Sa
	close(sockfd);
}