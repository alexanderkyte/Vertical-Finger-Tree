#include <iostream>
#include <cassert>
#include "test.h"
#include "../src/finger_node.h"

struct ArrayMeasurer : Measurer <void *, int> {
	public:
		int
		combine (int first, int second) override 
		{
			return first + second;
		};

		int
		compare (int first, int second) override
		{
			return second - first;
		};

		int
		compute (void *elem) override
		{
			return 1;
		};
};

void test_finger_node (void) {
	Measurer <void *, int> *arry = new ArrayMeasurer ();
	int one = 1;
	int two = 2;
	int three = 3;
	// 3 elements
	auto measure = 3;

	auto finger = new FingerLeafNode<void *, int> (&one, &two, &three, measure);
	std::cout << "Test run";
	assert (0);
}
