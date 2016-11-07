CC = gcc
CFLAGS = -g -Wall -std=c99
LIBFILE = game.o
CPPFLAGS = -I ../include/


SOURCE = hashi_text.c display.c node.c
OBJS = $(SOURCE:.c=.o)
TEST_SRC = ./tests/test_game1.c ./tests/test_toolbox.c node.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: libhashi.a hashi_text

libhashi.a:
	ar rvs libhashi.a $(LIBFILE)

hashi_text: $(OBJS)
	$(CC) -o $@ $(CPPFLAGS) $^ -l hashi -L ./

.PHONY: test
test: tests/test

tests/test: $(TEST_OBJ)
	ar rvs libhashi.a $(LIBFILE)
	$(CC) -o $@ $(CFLAGS) $^ libhashi.a 

include depends.txt

.PHONY : clean
clean:
	rm libhashi.a depends.txt hashi_text display.o hashi_text.o node.o

.PHONY : cleanTest
cleanTest:
	rm ./tests/test ./tests/test_game1.o ./tests/test_toolbox.o libhashi.a depends.txt node.o


depends.txt : $(SOURCE)
	$(CC) $(CFLAGS) -M $(CPPFLAGS) $(SOURCE) > depends.txt
