/*
 * RBT.h
 *
 *  Created on: Dec 1, 2014
 *      Author: root
 */

#ifndef RBT_H_
#define RBT_H_

namespace Algorithms {

enum class Color
{
	Red=1,
	Black=2
};

struct RBTNode
{
	RBTNode();
	RBTNode(const void*);
    RBTNode(const void*,Color);
    const void* value;
    Color color;
	RBTNode * p;
	RBTNode * left;
	RBTNode * right;
};

class RBT {
public:
	RBT(int (*)(const void*, const void*) );
    bool add(const void*);
	virtual ~RBT();
private:
	RBTNode * _root;
	int (*_cmp)(const void*, const void*);

	// restore blackness property after insertion
	void add_fixup(RBTNode *);

	// find infimum
	RBTNode * find_inf(RBTNode * );

	// find supremum
	RBTNode * find_sup(RBTNode *);

};
} /* namespace Algorithms */

#endif /* RBT_H_ */
