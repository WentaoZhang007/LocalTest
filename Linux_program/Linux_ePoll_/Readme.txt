高级I/O复用技术：Epoll的使用及一个完整的C实例
2014年04月03日 12:21:37
阅读数：7224
高性能的网络服务器需要同时并发处理大量的客户端，而采用以前的那种对每个连接使用一个分开的线程或进程方法效率不高，因为处理大量客户端的时候，资源的使用及进程上下文的切换将会影响服务器的性能。一个可替代的方法是在一个单一的线程中使用非阻塞的I/O（non-blocking I/O）。
        这篇文章主要介绍linux下的epoll(7)方法，其有着良好的就绪事件通知机制。我们将会使用C来展现一个完整的TCP服务器实现代码。Epoll是被linux2.6开始引进的，但是不被其他的类UNIX系统支持，它提供了一种类似select或poll函数的机制：

   1.Select(2)只能够同时管理FD_SETSIZE数目的文件描述符

       2. poll(2)没有固定的描述符上限这一限制，但是每次必须遍历所有的描述符来检查就绪的描述符，这个过程的时间复杂度为O(N)。

      epoll没有select这样对文件描述符上限的限制，也不会像poll那样进行线性的遍历。因此epoll处理大并发连接有着更高的性能。

    Epoll相关操作函数介绍：

     1. epoll_create(2) or epoll_create1(2)（有着不同的参数值）用来创建epoll实例。

[cpp] view plain copy
/usr/include/sys/epoll.h  
extern int epoll_create (int __size) ;  
RETURN：>0, 成功；-1, 出错  
函数描述：

       (1) epoll_create返回的是一个文件描述符，也就是说epoll是以特殊文件的方式体现给用户

       (2) __size提示操作系统，用户可能要使用多少个文件描述符，该参数已经废弃，填写一个大于0的正整数

      2.  epoll_ctl(2)用来增加或移除被epoll所监听的文件描述符。

[cpp] view plain copy
int epoll_ctl(int epfd, int op, int fd, struct  epoll_event *event);  
RETURN：0，成功；-1，出错  
函数描述：

        (1) epfd为epoll_create创建的epoll描述符

        (2) epoll_ctl函数对epoll进行op类型的操作，op选项为

              EPOLL_CTL_ADD，对fd描述符注册event事件

              EPOLL_CTL_MOD，对fd描述符的event事件进行修改

              EPOLL_CTL_DEL，删除已注册的event事件

      3. epoll_wait(2)用来等待发生在监听描述符上的事件。它会一直阻塞直到事件发生。

[cpp] view plain copy
#include <sys/epoll.h>  
int epoll_wait(int epfd, struct epoll_event *events,  
                int maxevents, int timeout);  
RETURN:>0，发生事件个数；=0，时间到；-1，出错  
函数描述：

           epoll_wait与select函数类似，同步地等待事件发生

           (1) epfd，标识epoll的文件描述符

           (2) events，指向传入操作系统的一个epoll_event数组

           (3) maxevents，表示传入数组的大小，必须大于0

          当有事件发生，Linux会填写events结构，返回给应用程序。由于epoll_wait同步等待，有可能被信号中断，返回EINTR错误

      更多的函数介绍请参照man。  

Epoll的两种模式：

      1. 水平触发（LT）：使用此种模式，当数据可读的时候，epoll_wait()将会一直返回就绪事件。如果你没有处理完全部数据，并且再次在该epoll实例上调用epoll_wait()才监听描述符的时候，它将会再次返回就绪事件，因为有数据可读。ET只支持非阻塞socket。

      2. 边缘触发（ET）：使用此种模式，只能获取一次就绪通知，如果没有处理完全部数据，并且再次调用epoll_wait()的时候，它将会阻塞，因为就绪事件已经释放出来了。

ET的效能更高，但是对程序员的要求也更高。在ET模式下，我们必须一次干净而彻底地处理完所有事件。LT两种模式的socket都支持。

     传递给epoll_ctl(2)的Epoll事件结构体如下所示：

[cpp] view plain copy
typedef union epoll_data  
{  
void* ptr;  
int fd;  
  __uint32_t   u32;  
  __uint64_t   u64;  
}epoll_data_t;  
  
struct epoll_event  
{  
  __uint32_t   events;/* Epoll events */  
epoll_data_t data;/* User data variable */  
};  

对于每一个监听的描述符，能够关联一个整形数据或指向用户数据的指针。
      epoll的事件类型：

[cpp] view plain copy
enum EPOLL_EVENTS  
  {  
    EPOLLIN = 0x001,  
#define EPOLLIN EPOLLIN  
    EPOLLPRI = 0x002,  
#define EPOLLPRI EPOLLPRI  
    EPOLLOUT = 0x004,  
#define EPOLLOUT EPOLLOUT  
    EPOLLRDNORM = 0x040,  
#define EPOLLRDNORM EPOLLRDNORM  
    EPOLLRDBAND = 0x080,  
#define EPOLLRDBAND EPOLLRDBAND  
    EPOLLWRNORM = 0x100,  
#define EPOLLWRNORM EPOLLWRNORM  
    EPOLLWRBAND = 0x200,  
#define EPOLLWRBAND EPOLLWRBAND  
    EPOLLMSG = 0x400,  
#define EPOLLMSG EPOLLMSG  
    EPOLLERR = 0x008,  
#define EPOLLERR EPOLLERR  
    EPOLLHUP = 0x010,  
#define EPOLLHUP EPOLLHUP  
    EPOLLRDHUP = 0x2000,  
#define EPOLLRDHUP EPOLLRDHUP  
    EPOLLONESHOT = (1 << 30),  
#define EPOLLONESHOT EPOLLONESHOT  
    EPOLLET = (1 << 31)  
#define EPOLLET EPOLLET  
  };  

– EPOLLIN，读事件

– EPOLLOUT，写事件

– EPOLLPRI，带外数据，与select的异常事件集合对应

– EPOLLRDHUP，TCP连接对端至少写写半关闭

– EPOLLERR，错误事件

– EPOLLET，设置事件为边沿触发

– EPOLLONESHOT，只触发一次，事件自动被删除

      epoll在一个文件描述符上只能有一个事件，在一个描述符上添加多个事件，会产生EEXIST的错误。同样，删除epoll的事件，只需描述符就够了

      epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);

      这里有一个比较重要的问题：从epoll_wait返回的events中，该如何知道是哪个描述符上的事件：在注册epoll事件的时候，一定要填写epoll_data，否则我们将分不清触发的是哪个描述符上的事件。

     下面我们将实现一个轻型TCP服务器，功能是在标准输出中打印发送给套接字的一切数据。