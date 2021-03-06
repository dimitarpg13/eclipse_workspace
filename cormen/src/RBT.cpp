/*
 * RBT.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: root
 */

#include "RBT.h"

namespace Algorithms {

RBT::RBT(int cmp(const void* p, const void* q)) {
    _cmp = cmp;
    _root = nullptr;

}

RBT::~RBT() {
	if (_root != nullptr)
	   delete _root;
}

// find the infimum node which is the node with the largest
// value among those smaller than "val"
RBTNode * RBT::find_inf(RBTNode * nd)
{
	RBTNode * res = nullptr;

	if (nd != nullptr)
	{
	   if (nd->p != nullptr)
	   {
		   if (nd->p->right == nd)
		   {
		   	  res = nd->p;
		   }

	   }
	   else if (nd == _root)
	   {
		   res = nd->left;
		   if (res != nullptr)
		   {
		      RBTNode * parent = nullptr;
		      while (res != nullptr)
		      {
			    parent = res;
			    res=res->right;
		      }
		   }

	   }
	}

	return res;
}




// find the supremum node which is the node with the smallest value among those
// larger than "val"
RBTNode * RBT::find_sup(RBTNode * nd)
{
	RBTNode * res = nullptr;

	return res;
}

bool RBT::add(const void* val)
{
	bool res = true;

	if (_root == nullptr)
	{
		_root = new RBTNode(val,Color::Black);
	}
	else
	{
		RBTNode * cur = _root, * parent = nullptr;
        while (cur != nullptr)
        {
           parent = cur;
           if (_cmp(cur->value, val) > 0)
              cur = cur->left;
           else
        	  cur = cur->right;
        }


        RBTNode * vnd = new RBTNode(val);
        vnd->p = parent;

        if (parent == nullptr)
        	_root = vnd;
        else if (_cmp(val,parent->value) < 0)
            parent->left = vnd;
        else
        	parent->right = vnd;

        vnd->left = nullptr;
        vnd->right = nullptr;
        vnd->color = Color::Red;

	}

	return res;
}




RBTNode::RBTNode()
{
	value = nullptr;
	p = nullptr;
	left = nullptr;
	right = nullptr;
	color = Color::Black;
}

RBTNode::RBTNode(const void* pdata)
{
	value = pdata;
	p = nullptr;
	left = nullptr;
	right = nullptr;
	color = Color::Black;
}

RBTNode::RBTNode(const void* pdata, Color col)
{
	value = pdata;
	p = nullptr;
	left = nullptr;
	right = nullptr;
	color = col;
}

} /* namespace Algorithms */

