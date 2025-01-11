obj-m := processtestmod.o
processtestmod-objs := main.o gdb-debug.o wait-queue.o process-state.o
SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	rm -rf *.o
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
