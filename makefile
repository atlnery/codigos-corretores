all: 
	gcc -g -c crc.c 
	gcc -g -c enviar.c
	gcc -g -c spc.c
	gcc -g -c aux.c
	gcc -g crc.o enviar.o spc.o aux.o -o enviar
	