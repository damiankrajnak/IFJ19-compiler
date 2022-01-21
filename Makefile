 CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra



interpret: main.c main.h dl_list.c dl_list.h parser.c parser.h precanalysis.c precanalysis.h scanner.c scanner.h stack.c stack.h symstack.c symstack.h symtable.c symtable.h generator.h linked_list.h linked_list.c
	gcc $(CFLAGS) dl_list.c parser.c precanalysis.c scanner.c stack.c symstack.c symtable.c main.c generator.c linked_list.c
	

clean:
	rm -f intepret

test:
	./run_tests.sh