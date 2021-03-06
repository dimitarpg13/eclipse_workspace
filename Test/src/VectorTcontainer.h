/*
 * VectorTcontainer.h
 *
 *  Created on: Oct 6, 2014
 *      Author: root
 */

#ifndef VECTORTCONTAINER_H_
#define VECTORTCONTAINER_H_

#include "ContainerT.h"
#include "VectorT.h"

namespace Algorithms {

template <typename T>
class VectorT_container : public ContainerT<T> {
public:
	VectorT_container(int s) : v(s) {};
	virtual ~VectorT_container();
	T& operator[] (int i) { return v[i]; };
	int size() const { return this->v.size(); };

private:
	VectorT<T> v;

};

} /* namespace Algorithms */

#endif /* VECTORTCONTAINER_H_ */
