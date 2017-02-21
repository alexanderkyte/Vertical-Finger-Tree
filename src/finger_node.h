#include <memory>

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
};

template <class Value, class MeasureClass>
struct FingerNode
{
	using myMeasurer = Measurer<Value, MeasureClass> *;

	public:
		const int depth;
		const MeasureClass measure;
		// implement filter and map with
		//std::shared_ptr<FingerNode>
		//foldr ((Value)(*)(Value));

		Value
		find (MeasureClass threshold, myMeasurer executor);

		FingerNode (int depth, MeasureClass measure) : depth(depth), measure(measure)
		{};
};

template <class Value, class Measure>
struct FingerInnerNode : FingerNode<Value, Measure> {
	using ref = std::shared_ptr<FingerNode<Value, Measure> >;

	public:
		const ref left;
		const ref middle;
		const ref right;
		FingerInnerNode (ref left, ref middle, ref right, Measure m): 
			FingerNode<Value, Measure>(0, m), left(left), middle(middle), right(right) {};
};

template <class Value, class Measure>
struct FingerLeafNode : FingerNode<Value, Measure> {

	public:
		const Value left;
		const Value middle;
		const Value right;
		FingerLeafNode (Value left, Value middle, Value right, Measure m): 
			FingerNode<Value, Measure>(0, m), left(left), middle(middle), right(right) {};
};
