CC = g++
CFLAGS = -Wall -g -fPIC
LDFLAGS = -shared

LIB_NAME = liblogbook.so
EXE = tests/test

OBJ = build/logbook.o
TOBJ = build/test.o

$(EXE): build $(TOBJ) $(LIB_NAME)
	$(CC) -o $@ $(TOBJ) -L. -llogbook -Wl,-rpath=.

build:
	mkdir build

$(LIB_NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

build/logbook.o: src/logbook.cpp include/logbook.h
	$(CC) $(CFLAGS) -Iinclude -o $@ -c $<


build/test.o: tests/test.cpp include/logbook.h
	$(CC) $(CFLAGS) -Iinclude -o $@ -c $<

clean:
	rm -rf build
