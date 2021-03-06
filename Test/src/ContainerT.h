/*
 * ContainerT.h
 *
 *  Created on: Oct 8, 2014
 *      Author: root
 */

#ifndef CONTAINERT_H_
#define CONTAINERT_H_

namespace Algorithms {

template <typename T>
class ContainerT {
public:
	virtual T& operator[](int) = 0; // pure virtual function
	virtual int size() const = 0; // const member function
	virtual ~ContainerT() {};
};

} /* namespace Algorithms */

#endif /* CONTAINERT_H_ */
