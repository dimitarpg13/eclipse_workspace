/*
 * String.h
 *
 *  Created on: Oct 21, 2014
 *      Author: root
 */

#ifndef STRING_H_
#define STRING_H_

namespace Algorithms {

template<typename C>
class String {
public:
	String() : sz{0}, ptr{ch}
	{
		ch[0] = {}; // terminating 0 of the appropriate character type
	};

	//String();

	C& operator[] (int n) { return ptr[n]; }
	// unchecked element access
	String& operator+=(C c); // add c at the end
	virtual ~String() {};
private:
	static const int short_max = 15;
	int sz;
	char* ptr;
	union {
		int space; // unused allocated space
		C ch[short_max+1];  // leave space for terminating 0
	};


};

} /* namespace Algorithms */

#endif /* STRING_H_ */
