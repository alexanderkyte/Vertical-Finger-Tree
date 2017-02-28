
#ifndef __FINGER_NODE_HDR
#define __FINGER_NODE_HDR 1

#include <memory>

#include <cassert>

template <class Value, class Measure>
struct Measurer
{
	public:
		virtual Measure
		combine (Measure first, Measure second) = 0;

		virtual int
		compare (Measure first, Measure second) = 0;

		virtual Measure
		compute (Value val) = 0;

		virtual Measure
		base (void) = 0;
};

template <class Value, class MeasureClass>
struct FingerNode
{
	public:
		const int depth;
		// implement filter and map with
		//std::shared_ptr<FingerNode>
		//foldr ((Value)(*)(Value));

		Value
		find (MeasureClass threshold, Measurer<Value, MeasureClass> *executor);

		FingerNode (int depth) : depth(depth) {};
};

template <class Value, class MeasureClass>
struct FingerInnerNode : FingerNode<Value, MeasureClass> {
	using ref = std::shared_ptr<FingerNode<Value, MeasureClass> >;

	public:
		const MeasureClass measure;
		const ref left;
		const ref middle;
		const ref right;
		FingerInnerNode (ref left, ref middle, ref right, MeasureClass m): 
			FingerNode<Value, MeasureClass>(0), left(left), middle(middle), right(right), measure(m) {};
};

template <class Value, class Measure>
struct FingerLeafNode : FingerNode<Value, Measure> {
	public:
		const Value left;
		const Value middle;
		const Value right;
		FingerLeafNode (Value left, Value middle, Value right): 
			FingerNode<Value, Measure>(0), left(left), middle(middle), right(right) {};
};

template <class Value, class Measure>
Value
FingerNode<Value, Measure>::find (Measure threshold, Measurer<Value, Measure> *executor)
{
	Measure accum = executor->base ();

	if (this->depth == 0) {
		auto handle = (FingerLeafNode<Value, Measure> *) this;
		accum = executor->combine (accum, executor->compute(handle->left));
		if (executor->compare(threshold, accum) > 0)
			return handle->left;

		accum = executor->combine (accum, executor->compute(handle->middle));
		if (executor->compare(threshold, accum) > 0)
			return handle->middle;

		accum = executor->combine (accum, executor->compute(handle->right));
		if (executor->compare(threshold, accum) > 0)
			return handle->right;
	} else {
		assert(0);
		return NULL;
	}

	return NULL;
}

#endif
