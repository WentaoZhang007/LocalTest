/*
Function：该进程用于服务器端，监控侦听进程 "socketwatchser"是否存在，并对侦听进程进行kill和启动(后台运行，不受Shell终端影响）。
Attention：!启动socketwatchserver进程采用的方式是 system shell 指令，
        ！！@该指令当中含有相对路径。@！！绝对路径的位置在第111行。
Version：V1.0
Author: MDVR_张文涛
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm/ioctls.h>
#include"lookoutServerPS.h"



int  main (void){
    printf("\n");
    printf("----------watchser:-----------\n");
    socketwatchser_has_exist( );
    printf("\n");
    
    printf("--------startwatchser:---------\n");    
    watchstartsocketwatchser();
    printf("\n");
    
    printf("---------killwatchser:---------\n");
    killsocketwatchser();
    printf("\n");
    
    printf("--------startwatchser:---------\n");
    watchstartsocketwatchser();
    printf("\n");

    printf("---------killwatchser:---------\n");
    killsocketwatchser();
    printf("\n");
    
    printf("----------watchser:-----------\n");
    socketwatchser_has_exist( );
    printf("\n");

    printf("--------startwatchser:---------\n");
    watchstartsocketwatchser();
    printf("\n");

    return 0;
}

 
  int socketwatchser_has_exist( ){
 FILE           *pstr;
 char            cmd[128], buff[512];
 pid_t           pID;
 int             pidnum;
 char           *name = "socketwatchser";   /*进程名 */
 char           *p = NULL;
 int             ret = 3;
 
 memset(cmd, 0, sizeof(cmd));
 sprintf(cmd, "ps -ef|grep -w %s", name);
 pstr = popen(cmd, "r");
 if (pstr == NULL) {
     return 0;
 }
 
 memset(buff, 0, sizeof(buff));
 fgets(buff, 512, pstr);
 
 p = strtok(buff, " ");
 p = strtok(NULL, " ");
 pclose(pstr);
 
 if (p == NULL) {
     return 0;
 }
 //printf( "pid:%s\n",p);
 if (strlen(p) == 0) {
     return 0;
 }
 if ((pidnum = atoi(p)) == 0) {
     return 0;
 }
 //printf("pidnum: %d\n", pidnum);
 
 pID = (pid_t) pidnum;
 ret = kill(pID, 0);
 
   if (0 == ret) {
     printf("process: %s  PID %d exist! \n", name, pID);
     return 1;
     } 
     else {
         printf("process: %s not exist!\n", name);
         return 0;
     }
 
 }

 int watchstartsocketwatchser(){
      switch (socketwatchser_has_exist())
     {
          case 1 :{
            break;
            }
          case 0:{ 
            int code;
            code=system("nohup /mnt/hgfs/Code/Debug/debug/socketwatchser & "); //服务器监听进程文件的位置。注意含有绝对路径
             if(code==0){
                printf("start process socketwatchser\n ");
                socketwatchser_has_exist();
            }      
            else {
                printf("can not start process socketwatchser\n ");
                return -1;
            }
            break;
          }
      }//end of switch
}

 int killsocketwatchser(){
     if (socketwatchser_has_exist()){
       if(0!=system("pkill -9  socketwatchser")) {
        printf("Can not kill the process of socketwatchser\n"); 
        return 0;
       } else {
        printf("has killed the process of socketwatchser\n");
        return -1;
       }
     }
 }

