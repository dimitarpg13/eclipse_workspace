//============================================================================
// Name        : BoostTest03.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
#include <boost/property_map/property_map.hpp>

using namespace std;

template <typename AddressMap>
void foo(AddressMap address)
{
	typedef typename boost::property_traits<AddressMap>::value_type value_type;
	typedef typename boost::property_traits<AddressMap>::key_type key_type;

	value_type old_address, new_address;
	key_type fred = "Fred";
	old_address = get(address,fred);
	new_address = "384 Fitzpatrick Street";
	put(address, fred, new_address);

	key_type joe = "Joe";
	value_type& joes_address = address[joe];
	joes_address = "325 Cushing Avenue";
}

int main() {

	map<string,string> name2address;
	boost::associative_property_map< map<string,string> > address_map(name2address);

	name2address.insert(make_pair<string,string>(string("Fred"),string("710 West 13th Street")));
	name2address.insert(make_pair<string,string>(string("Joe"),string("710 West 13th Street")));

	foo(address_map);

	for (map<string,string>::iterator i = name2address.begin(); i != name2address.end(); ++i)
		cout << i->first << ": " << i->second << "\n";

	return 0;
}
