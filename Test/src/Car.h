/*
 * Car.h
 *
 *  Created on: Oct 12, 2014
 *      Author: root
 */

#ifndef CAR_H_
#define CAR_H_

#include <iostream>
#include <string>

using namespace std;

namespace Algorithms {

class Car {
public:
	Car(string brand);
	virtual ~Car();
	int getPassengerCount();
	void setPassengerCount(int);
	string getLicensePlate();
	void setLicensePlate(string);
	string getBrand();
protected:
	int m_iPassengerCount;
	string m_sLicensePlate;
	string m_sBrand;
};

} /* namespace Algorithms */

#endif /* CAR_H_ */
