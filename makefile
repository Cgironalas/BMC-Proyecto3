CC = gcc
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`
WARN = -Wall

all:
	$(CC) -o ecvsel ECvsEL.c $(WARN) $(GTKLIB) -export-dynamic
