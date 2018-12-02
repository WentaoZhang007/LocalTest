Linux中epoll模型学习
2015年04月21日 21:14:57
阅读数：381
epoll是Linux2.6及以后版本中的一种IO复用技术。可以非常高效的处理数以百万计的socket句柄，今天学习一下它为何能高速处理这么多并发连接。学习epoll之前，先介绍一下Linux中其它处理并发的模型的缺点，包括PPC/TPC，select IO复用，poll IO复用。IO复用就是同时监听多个描述符。

 

一、常用模型的缺点

1、 PPC/TPC模型

Process PerConnection简称PPC，Thread Per Connection简称TPC，这两种模型思想类似，就是让每一个连接自己做事，只是PPC为它开了一个进程，而TPC开了一个线程。这是需要时间和空间代价的，连接多了之后，进程/线程切换开销很大。因此这类模型能接受的最大连接数都不高，一般几百个。

2、 select模型

(1)   最大并发数限制。一个进程打开的文件描述符数量是有限的，由FD_SETSIZE设置，默认值为1024/2048，因此select模型最大并发数被限制。增加FD_SETSIZE可提高并发数，但是效率会线性下降。

(2)   效率问题。select每次调用都会扫描全部fd集合，效率随并发数线性下降。IO事件到了后，select通知应用程序有事件到需要处理，而应用程序必须轮询所有fd集合，测试每个fd是否有事件发生，并处理事件。

(3)   内核/用户空间内存拷贝。内核把fd消息通知用户空间，使用了内存拷贝。

总结：连接数受限、查找配对速度慢、内存拷贝

3、 poll模型

效率基本与select相同，select缺点(2)(3)它同样具有。

 

二、epoll的优点

1、 epoll没有最大连接限制；

2、 效率提升，它只关注”活跃”的连接，而跟连接总数无关，实际网络中效率远高于select。

3、 epoll使用共享内存，不需拷贝。

 

三、epoll实现原理

epoll总共有三个系统调用：

(1)   int epoll_create(int size);

(2)   int epoll_ctl(int epfd, int op,int fd, struct epoll_event* event);

(3)   int epoll_wait(int epfd, structepoll_events, int maxevents, int timeout);

epoll_create建立一个epoll对象。size是内核保证能够正确处理的最大句柄数，多于这个最大数时内核不保证效果。

epoll_ctl可以操纵上述epoll对象，例如将socket加入epoll让其监控或者移除socket，不再监控等。

epoll_wait调用时，在给定的timeout时间内，当监控的所有句柄中有事件发生时，返回到用户态进程。

select和poll中，每次都要传递要监控的socket给select/poll调用，也就是需要将用户态socket列表拷贝到内核，效率很低。而调用epoll_wait就不用传递socket句柄给内核，因为内核已经在epoll_ctl时拿到了要监控的句柄列表。epoll_create后，内核就在内核态开始准备存储要监控的句柄了。每次调用epoll_ctl只是往内核数据结构加入新的socket句柄。

epoll在被内核初始化时(操作系统启动)，同时会开辟出epoll自己的内核高速cache区，用于安置每一个要监控的socket，这些socket以红黑树的形式保存在内核cache中，以支持快速查找插入删除。这个内核高速cache区，就是连续的物理内存页，然后在之上建立slab层，简单说就是物理上分配好想要的size的内存对象，每次使用时使用空闲的已分配好的对象。

即使有数百万的socket句柄，epoll_wait仍然可以快速返回发生事件的句柄。这是由于epoll_create时，内核还建立了一个list链表，用于存储准备就绪的事件。当epoll_wait调用时，仅仅观察这个list链表有没有数据即可。有数据就返回，没数据就sleep，等到timeout时间到后没数据也返回。所以，epoll_wait非常高效。通常情况下大量句柄中仅有少量活动的句柄。这个list链表是如何维护的呢？当我们执行epoll_ctl时，除了把socket放到epoll红黑树上之外，还给内核中断处理程序注册了一个回调函数，告诉内核，如果这个句柄的中断到了，就把它放到准备就绪list链表里。

一棵红黑树，一张准备就绪list链表，少量内核cache，就帮我们解决了大并发下socket处理问题。执行epoll_create创建红黑树和就绪链表，执行epoll_ctl增加socket句柄，检查是否在红黑树中存在，存在立即返回，不存在添加到红黑树并向内核注册回调函数，用于当中断事件到来时向就绪链表插入数据。执行epoll_wait时立刻返回准备就绪链表的数据即可。

epoll有两种工作模式LT(默认)和ET。区别是，LT模式下，只要一个句柄上的事件一次没有处理完，会在以后调用epoll_wait时次次返回这个句柄，而ET模式下仅在第一次返回。这是怎么实现的呢？当一个socket句柄上有事件时，内核会把该句柄插入到就绪list链表，我们调用epoll_wait，会把就绪socket拷贝到用户态内存，然后清空list链表。最后，epoll_wait检查这些socket，如果不是ET模式且socket确实有未处理的事件时，又把该句柄放回就绪链表。所以非ET句柄只要它上面有事件，epoll_wait每次都要返回，而ET模式的句柄，除非有新中断到来，即使socket上的事件没有处理完，也不会次次从epoll_wait返回。



个人分类： 互联网-服务器编程