CC = g++

CFLAGS = -g Wall
TARGET = myprog

init_order: init_order.cpp 
	$(CC) -o $(TARGET) $^

static_function: static_function.cpp
	$(CC) -o $(TARGET) $^

assign: assign.cpp
	$(CC) -o $(TARGET) $^

leastpriv: leastpriv.cpp
	$(CC) -o $(TARGET) $^

clean:
	rm $(TARGET)
run:
	./$(TARGET)
