CC = gcc
CFLAGS = -Wall -g
LIBS = -lSDL2 -lSDL2_gfx -lm

all: 
	$(CC) main.c -o calculator $(CFLAGS) $(LIBS)

clean:
	rm calculator
