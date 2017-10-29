#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define MAXSIZE 5500

int main()
{
    pid_t pid;
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE], sendmsg[MAXSIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)         
        printf("\nSocket Creation Error");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3333);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.43.147");
    retval = connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    if (retval == -1) 
        printf("Connection error");

    pid = fork();
    if (pid == 0) 
    {
        while (1)
        {            
            gets(sendmsg);
            send(sockfd, sendmsg, sizeof(sendmsg), 0);
            if(sentbytes == -1)
            {
                printf("Error\n");
                close(sockfd);
            }
        }
    }
    else if (pid > 0)
    {
        while (1)
        {
            recedbytes = recv(sockfd, buff, sizeof(buff), 0);
            if(recedbytes == -1)
            {
                printf("Error\n");
                close(sockfd);
            }
            puts(buff);
        }
    }
}