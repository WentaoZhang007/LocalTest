/*
Function：用于在服务器端创建监听服务，用于接收客户端数据（一次4个），接收成功后将成功接收标志返回给客户端。
Version：V1.0
Author: MDVR_张文涛
*/
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <errno.h>
#include "snddata.h"
  
  
#define MAX_MSG_SIZE  BUF_SIZE
#define SERVER_PORT  9987  
  
  
#define BACKLOG 2  
  
  
int GetServerAddr(char * addrname){  
    printf("please input server addr:");  
    scanf("%s",addrname);  
    return 1;   
}  
  
  
int main(){    
    int sock_fd,client_fd; /*sock_fd：监听socket；client_fd：数据传输socket */    
    struct sockaddr_in ser_addr; /* 本机地址信息 */    
    struct sockaddr_in cli_addr; /* 客户端地址信息 */    
    char msg[MAX_MSG_SIZE];/* 缓冲区*/   
    struct SNDDATA recvddata = {"0","0",0,0};
	struct SNDDATA *precv = &recvddata;
    
    int ser_sockfd=socket(AF_INET,SOCK_STREAM,0);/*创建连接的SOCKET */    
    if(ser_sockfd<0)    
           {/*创建失败 */    
                  fprintf(stderr,"socker Error:%s\n",strerror(errno));    
                  exit(1);    
          }    
    /* 初始化服务器地址*/    
    socklen_t  addrlen=sizeof(struct sockaddr_in);    
    bzero(&ser_addr,addrlen);    
    ser_addr.sin_family=AF_INET;    
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);    
    ser_addr.sin_port=htons(SERVER_PORT);    
    if(bind(ser_sockfd,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_in))<0){ /*绑定失败 */    
            fprintf(stderr,"Bind Error:%s\n",strerror(errno));    
            exit(1);    
    }    
    /*侦听客户端请求*/    
    if(listen(ser_sockfd,BACKLOG)<0){    
        fprintf(stderr,"Listen Error:%s\n",strerror(errno));    
        close(ser_sockfd);    
        exit(1);    
    }  
    printf("I'm wating for connecting from Client............\n " );
    while(1){/* 等待接收客户连接请求*/    
        int cli_sockfd=accept(ser_sockfd,(struct sockaddr*) &cli_addr, &addrlen); 

        if(cli_sockfd<=0){    
            fprintf(stderr,"Accept Error:%s\n",strerror(errno));    
        }else{/*开始服务*/    
            recv(cli_sockfd, msg, (size_t)MAX_MSG_SIZE, 0); /* 接受数据*/    
            printf("received a connection from %s\n", inet_ntoa(cli_addr.sin_addr));

            if (buffer2data(precv, msg) != 0) {
                perror("The Server can not read  the data sened from Client !\n");
                return -2;	
            } 

        /*在屏幕上把接收到的数据打印出来 */ 
            printf("This Server  Recv Data from Client is : %s  %s  %d  %d \n", precv->CODE, precv->STATE, precv->u16X, precv->u16Y);
            
         /*成功接收数据后，向客户端返回成功接收数据的标记*/                                  
            strcpy(msg,"This is Ack respondng from server ---Data from Client have been recvied ");   
            send(cli_sockfd, msg, sizeof(msg),0) ;           
            printf("The Ack have been resend to client");
            /*发送的数据*/ 
            
            
            close(cli_sockfd);    
        }    
    }    
    close(ser_sockfd);    
    return 0;    
 }    

int buffer2data(struct SNDDATA *precv,const char * Buffer) {

	
	char * pbuffer = Buffer;
	char * structmember = &(precv->CODE);
    int i;
	for (i = 0; i != sizeof(precv->CODE); i++) {
		structmember[i]= pbuffer[i];
	}
	structmember = &(precv->STATE);
	for (i = 0; i != sizeof(precv->STATE); i++) {
		structmember[i]= pbuffer[i + sizeof(precv->CODE)];
	}
	precv->u16X= (char)pbuffer[sizeof(precv->CODE) + sizeof(precv->STATE)+2] ;
	(precv->u16Y)= (char)pbuffer[sizeof(precv->CODE) + sizeof(precv->STATE) + 3] ;	
//	printf("This Server  Recv Data from Client is : %s  %s  %d  %d \n", precv->CODE, precv->STATE, precv->u16X, precv->u16Y);

	return 0;
}