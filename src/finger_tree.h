
#ifndef __FINGER_TREES_HDR
#define __FINGER_TREES_HDR 1

#include "finger_node.h"
#include <vector>

#define BITMASK int32_t
#define BITMASK_NULL 0

const static inline int
bit_set (BITMASK mask, int index)
{
	return (1 & (mask >> index)) != 0;
}

const static inline int
get_row (BITMASK mask, int level)
{
	return __builtin_popcount ((mask >> level * 4) & 0xf);
}

const static inline BITMASK
set_row (BITMASK mask, int level, int state)
{
	// The way the state with (index) bits looks in our bitmask
	const int mappings [] = {0, 0x1, 0x2, 0x8, 0x9};
	const int new_state = mappings [state];
	const int bits = level + 4;
	const BITMASK without = mask & (~0xf << bits);
	return without | (new_state << bits);
}


template <class Value, class Measure>
class FingerTree {
	private:
		const BITMASK left_bitmask;
		const BITMASK right_bitmask;
		const std::shared_ptr<std::vector<Value>> left_side;
		const std::shared_ptr<std::vector<Value>> right_side;

		const Measurer<Value, Measure> *measurer;

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		push (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side,
		          Value added) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		};

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		pop (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		};

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		create (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side) const
		{
			if (left_near)
				return std::make_shared <FingerTree<Value, Measure> > (measurer, near_bitmask, far_bitmask, near_side, far_side);
			else
				return std::make_shared <FingerTree<Value, Measure> > (measurer, far_bitmask, near_bitmask, far_side, near_side);
		};

		const inline size_t
		measure_bitmask (BITMASK mask) const
		{
			// The 0th index holds 3 items, the Nth holds 3 ** (N - 1) items
			int size = 3;
			int accum = 0;
			for (int i=0; i < sizeof (mask) * CHAR_BIT; i += 4) {
				if (bit_set (mask, i))
					accum += size;
				size = size * size;
			}
			return accum;
		};

	public:
		FingerTree (const Measurer<Value, Measure> *measurer, const BITMASK left_bitmask, const BITMASK right_bitmask,
		    const std::shared_ptr<std::vector<Value>> left_side, const std::shared_ptr<std::vector<Value>> right_side) :
		    left_bitmask (left_bitmask), right_bitmask (right_bitmask), left_side (left_side), right_side (right_side)
		{};

		// FIXME: get measurer from subclass, no indirection
		FingerTree (Measurer<Value, Measure> *measurer) : left_bitmask (BITMASK_NULL), right_bitmask (BITMASK_NULL), left_side (nullptr), right_side (nullptr)
		{};

		//const std::shared_ptr<FingerTree <Value, Measure>>
		//add (Value v)
		//{
		
		//}

		//const Value
		//find (Measure threshold)
		//{
		
		//}

		//const std::shared_ptr<FingerTree <Value, Measure>>
		//concat (FingerTree *ftree) 
		//{
			//return nullptr;
		//}

		const size_t 
		size (void) const
		{
			return measure_bitmask (this->left_bitmask) + measure_bitmask (this->right_bitmask);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		pushLeft (Value v) const
		{
			return push (true, left_bitmask, right_bitmask, left_side, right_side, v);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		pushRight (Value v) const
		{
			return push (false, right_bitmask, left_bitmask, right_side, left_side, v);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		popLeft (Value v) const
		{
			return pop (true, left_bitmask, right_bitmask, left_side, right_side);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		popRight (Value v) const
		{
			return pop (false, right_bitmask, left_bitmask, right_side, left_side);
		};
};


#endif



