CC = g++
CFLAGS = -Wall -g -fPIC

EXE = app

OBJ = build/app.o build/main.o

$(EXE): build $(OBJ)
	$(CC) -o $@ $(OBJ) -L../logbook -llogbook -Wl,-rpath=../logbook -pthread

build:
	mkdir build

build/app.o: src/app.cpp include/app.h
	$(CC) $(CFLAGS) -I../logbook/include -Iinclude -o $@ -c $<

build/main.o: src/main.cpp include/app.h
	$(CC) $(CFLAGS) -I../logbook/include -Iinclude -o $@ -c $<

clean:
	rm -rf build
