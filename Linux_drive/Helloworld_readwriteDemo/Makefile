
obj-m := demo.o            #要生成的模块名     

modules-objs:= demo.o         #生成这个模块名所需要的目标文件

 

KDIR := /lib/modules/`uname -r`/build

PWD := $(shell pwd)

 

default:

	make -C $(KDIR) M=$(PWD) modules

 

clean:

	rm -rf *.o *.cmd *.ko *.mod.c *.order *.symvers
