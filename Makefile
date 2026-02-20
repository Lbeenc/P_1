CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = main.o buildTree.o traversals.o
TARGET = P1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp node.h buildTree.h traversals.h
	$(CC) $(CFLAGS) -c main.cpp

buildTree.o: buildTree.cpp buildTree.h node.h
	$(CC) $(CFLAGS) -c buildTree.cpp

traversals.o: traversals.cpp traversals.h node.h
	$(CC) $(CFLAGS) -c traversals.cpp

clean:
	rm -f $(OBJS) $(TARGET)
