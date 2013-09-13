obj-m += testsyscall.o
obj-m += listprocess.o
obj-m += hello_world.o
obj-m += hello.o

all:
	make -C /home/victor/goldfish M=$(PWD) modules

clean:
	make -C /home/victor/goldfish M=$(PWD) clean