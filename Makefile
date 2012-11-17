# Esto es un comentario. 
# La variable CC se utiliza para especificar el compilador a utilizar
CC=g++
# La variable CFLAGS se utiliza para pasarle opciones al compilador 
CFLAGS=-c -Wall -o
CLIBS=-Lsource/bpp/lib
CINLC=-Isource/bpp/include

all: main

main: bpp_main.o instancia.o solucion.o bpp.o
	$(CC) compiled/o/instancia.o compiled/o/solucion.o compiled/o/bpp.o compiled/o/bpp_main.o -o compiled/bpp_main

bpp_main.o: source/main/bpp_main.cpp
	$(CC) $(CFLAGS) compiled/o/bpp_main.o source/main/bpp_main.cpp

instancia.o: source/bpp/lib/instancia.cpp
	$(CC) $(CFLAGS) compiled/o/instancia.o source/bpp/lib/instancia.cpp

solucion.o: source/bpp/lib/solucion.cpp
	$(CC) $(CFLAGS) compiled/o/solucion.o source/bpp/lib/solucion.cpp

bpp.o: source/bpp/lib/bpp.cpp
	$(CC) $(CFLAGS) compiled/o/bpp.o source/bpp/lib/bpp.cpp

clean:
	rm -rf compiled/o/*o compiled/bpp_main

