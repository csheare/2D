CC = g++

CFLAGS = -g Wall

BINS= init_order static_function assign leastpriv Pokemon pointandref

all: $(BINS)

pointandref: pointandref.cpp
	$(CC) -o pointandref $^

init_order: init_order.cpp
	$(CC) -o init_order $^

static_function: static_function.cpp
	$(CC) -o static_function $^

assign: assign.cpp
	$(CC) -o assign $^

leastpriv: leastpriv.cpp
	$(CC) -o leastpriv $^

Pokemon: Pokemon.cpp
	$(CC) -o Pokemon $^

%: %.c
	$(CC) -o $@ $< -g

clean:
	rm $(BINS)
