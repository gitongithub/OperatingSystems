default:
	@gcc shell.c -o shell
	@gcc delete.c -o rm
	@gcc mkdir.c -o mkdir
	@gcc date.c -o date
	@gcc ls.c -o ls
	@gcc cat.c -o cat
	@./shell
preprocess:
	@gcc -E shell.c -o shell.i
	@gcc -E delete.c -o rm.i
	@gcc -E mkdir.c -o mkdir.i
	@gcc -E date.c -o date.i
	@gcc -E ls.c -o ls.i
	@gcc -E cat.c -o cat.i
compile:
	@gcc -S shell.i -o shell.s
	@gcc -S rm.i -o rm.s
	@gcc -S mkdir.i -o mkdir.s
	@gcc -S date.i -o date.s
	@gcc -S ls.i -o ls.s
	@gcc -S cat.i -o cat.s
assemble:
	@gcc -c shell.s -o shell.o
	@gcc -c rm.s -o rm.o
	@gcc -c mkdir.s -o mkdir.o
	@gcc -c date.s -o date.o
	@gcc -c ls.s -o ls.o
	@gcc -c cat.s -o cat.o
link:
	@gcc shell.o -o shell
	@gcc rm.o -o rm
	@gcc mkdir.o -o mkdir
	@gcc date.o -o date
	@gcc ls.o -o ls
	@gcc cat.o -o cat
run:
	@./shell
clean:
	@rm -rf *.i *.s *.o shell
	@rm -rf *.i *.s *.o rm
	@rm -rf *.i *.s *.o cat
	@rm -rf *.i *.s *.o mkdir
	@rm -rf *.i *.s *.o ls
	@rm -rf *.i *.s *.o date
