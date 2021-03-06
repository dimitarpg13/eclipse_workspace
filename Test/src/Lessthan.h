/*
 * Lessthan.h
 *
 *  Created on: Oct 8, 2014
 *      Author: root
 */

#ifndef LESSTHAN_H_
#define LESSTHAN_H_

namespace Algorithms {

template <typename T>
class Less_than {
public:
	Less_than(const T& v) : val(v) {};
	bool operator() (const T& x) const { return x < val; }
	virtual ~Less_than() {};
private:
	const T val;
};

} /* namespace Algorithms */

#endif /* LESSTHAN_H_ */
