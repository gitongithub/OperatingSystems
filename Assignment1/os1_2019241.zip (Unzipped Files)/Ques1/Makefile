default:
	@gcc P1.c -o P1
	@./P1
preprocess:
	@gcc -E P1.c -o P1.i
compile:
	@gcc -S P1.i -o P1.s
assemble:
	@gcc -c P1.s -o P1.o
link:
	@gcc P1.o -o P1
run:
	@./P1
clean:
	@rm -rf *.i *.s *.o p1


