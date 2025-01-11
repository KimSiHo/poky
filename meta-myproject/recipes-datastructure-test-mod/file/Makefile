obj-m := datastructuretestmod.o
datastructuretestmod-objs := double-linked-list.o single-linked-list.o queue.o idr.o rbtree.o main.o
SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	rm -rf *.o
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
