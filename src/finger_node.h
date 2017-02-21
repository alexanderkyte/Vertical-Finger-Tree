#include <memory>

struct FingerNode
{
	int depth;
};

struct FingerInnerNode : FingerNode {
	public:
		const std::shared_ptr<FingerNode> left;
		const std::shared_ptr<FingerNode> middle;
		const std::shared_ptr<FingerNode> right;
};

template <class Value>
struct FingerLeafNode : FingerNode {
	public:
		const Value left;
		const Value middle;
		const Value right;
};
