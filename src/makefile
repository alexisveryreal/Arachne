OBJS = deMain.o test.o
CC = g++ -g -Wall -pedantic -std=c++11
DEPS = test.h

all: deMain

test: $(OBJS)
	$(CC) -Wall -g -o test $(OBJS)

test.o: test.cpp
	$(CC) -Wall -g -c test.cpp

deMain: $(OBJS)
	$(CC) -Wall -g -o deMain $(OBJS)

deMain.o: deMain.cpp $(DEPS)
	$(CC) -Wall -g -c deMain.cpp


clean:
	rm $(OBJS)