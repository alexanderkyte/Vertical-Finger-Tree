TEST_SRC = \
	test/test.cpp \
	test/finger_node.cpp

CFLAGS=-ggdb -O0 -std=c++11

.PHONY: all
all: check 

check: test/runner
	./test/runner

test/runner: src/finger_tree.o $(TEST_SRC)
	c++ -I ./src $(CFLAGS) $(TEST_SRC) src/finger_tree.o -o test/runner

src/finger_tree.o: src/finger_tree.cpp src/finger_node.cpp
	c++ $(CFLAGS) src/finger_tree.cpp -c -o src/finger_tree.o
	c++ $(CFLAGS) src/finger_node.cpp -c -o src/finger_node.o

clean:
	rm -rf src/*.o test/runner

