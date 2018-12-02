/*
Function：在客户端创建Socket_IP Domin，用于发送数据（一次4个）并接收服务器接收成功返回的标志Ack。数据格式为：	
    SV_CHAR CODE[64];
	SV_CHAR STATE[64];
	SV_U16 u16X, u16Y;
    测试用数据为，"abcdef","xyz!",123,45 ，
    发往的IP：127.0.0.1
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


#define MAX_MSG_SIZE 256
#define SERVER_PORT 9987


int GetServerAddr(char * addrname) {
	printf("please input server addrs (for example--127.0.0.1(localhost))_._._._:\n");
	scanf("%s", addrname);
	return 1;
}

struct SNDDATA snddata = { "abcdef","xyz!",123,45 };

int main() {
	int cli_sockfd;/*客户端SOCKET */
	int addrlen;
	char seraddr[14];
	struct sockaddr_in ser_addr,/* 服务器的地址*/
		cli_addr;/* 客户端的地址*/
	char msg[MAX_MSG_SIZE];/* 缓冲区*/
	memset(msg, 0, BUF_SIZE);
//    struct SNDDATA snddata = { "abcdef","xyz!",123,45 };
	struct SNDDATA *p = &snddata;

	GetServerAddr(seraddr);

	cli_sockfd = socket(AF_INET, SOCK_STREAM, 0);/*创建连接的SOCKET */

	if (cli_sockfd<0) {/*创建失败 */
		fprintf(stderr, "socker Error:%s\n", strerror(errno));
		exit(1);
	}
	/* 初始化客户端地址*/
	addrlen = sizeof(struct sockaddr_in);
	bzero(&ser_addr, addrlen);
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = 0;
	if (bind(cli_sockfd, (struct sockaddr*)&cli_addr, addrlen)<0) {
		/*绑定失败 */
		fprintf(stderr, "Bind Error:%s\n", strerror(errno));
		exit(1);
	}
	/* 初始化服务器地址*/
	addrlen = sizeof(struct sockaddr_in);
	bzero(&ser_addr, addrlen);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(seraddr);
	ser_addr.sin_port = htons(SERVER_PORT);
	if (connect(cli_sockfd, (struct sockaddr*)&ser_addr, addrlen) != 0) /*请求连接*/
	{
		/*连接失败 */
		fprintf(stderr, "Connect Error:%s\n", strerror(errno));
		close(cli_sockfd);
		exit(1);
	}
    

    if (setdata(msg, p)!=0) {
		perror("can not send data to serever !");
		return -1;
	};

/*发送数据*/  
	send(cli_sockfd, msg, sizeof(msg), 0);
        printf("The Data have been sent to server and wating for the ack from server\n");
        
	recv(cli_sockfd, msg, MAX_MSG_SIZE, 0) ;
        printf("%s\n", msg);
       
	
	close(cli_sockfd);

	return 0;
}



int setdata(char * Buffer, const struct SNDDATA  *p) {
	//对待发送数据进行赋值
	printf("The size of struct SNDDATA is %d \n", sizeof(*p));
	printf("The data sending to Server is : %s  %s  %d  %d \n", p->CODE, p->STATE, p->u16X, p->u16Y);
	char * pbuffer = Buffer;
	char * structmember = &(p->CODE);
    int i;
	for (i = 0 ; i != sizeof(p->CODE);  i++) {
		pbuffer[i] =structmember[i];		
	}

	structmember = &(p->STATE);
	for ( i =0 ; i != sizeof(p->STATE); i++) {
		pbuffer[i+sizeof(p->CODE)] = structmember[i];
	}

	pbuffer[sizeof(p->CODE)+ sizeof(p->STATE)+2] =(char)(p->u16X);
	pbuffer[sizeof(p->CODE) + sizeof(p->STATE)+3] =(char)(p->u16Y);
	return 0;
}

