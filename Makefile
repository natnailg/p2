CC       = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P2
OBJS    = main.o Parser.o scanner.o BuildTree.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) -c scanner.cpp

Parser.o: scanner.cpp scanner.h
	$(CC) $(CFLAGS) -c Parser.cpp

BuildTree.o: BuildTree.cpp BuildTree.h
	$(CC) $(CFLAGS) -c BuildTree.cpp

clean:
	/bin/rm -f *.o $(TARGET)

