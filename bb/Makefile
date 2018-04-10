CC = clang++

CFLAGS = -g -std=c++11 -W -Wall -Weffc++ -Wextra -pedantic -O0

BINS= init_order static_function assign leastpriv Pokemon pointandref number

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

number: number.cpp
	$(CC) $(CFLAGS) -o number $^

%: %.c
	$(CC) -o $@ $< -g

clean:
	rm $(BINS)
