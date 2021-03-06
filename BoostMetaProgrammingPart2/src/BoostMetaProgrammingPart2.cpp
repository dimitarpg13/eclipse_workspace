//============================================================================
// Name        : BoostMetaProgrammingPart2.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <typeinfo>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/fusion/support/deduce_sequence.hpp>
#include <boost/mpl/equal.hpp>

using namespace std;

namespace mpl = boost::mpl;
static int const five = mpl::int_<5>::value;

typedef mpl::vector<
		mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>,
        mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > mass_dim_old;

typedef mpl::vector<
		mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>,
		mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > length_dim_old;

typedef mpl::vector_c<long,1,0,0,0,0,0,0> mass_dim; //using integral sequence wrappers
typedef mpl::vector_c<long,0,1,0,0,0,0,0> length_dim;
typedef mpl::vector_c<long,0,0,1,0,0,0,0> time_dim;
typedef mpl::vector_c<long,0,0,0,1,0,0,0> charge_dim;
typedef mpl::vector_c<long,0,0,0,0,1,0,0> temperature_dim;
typedef mpl::vector_c<long,0,0,0,0,0,1,0> intensity_dim;
typedef mpl::vector_c<long,0,0,0,0,0,0,1> quantity_dim; // amount of substance
// base dimension m l t q theta I qty
typedef mpl::vector_c<long,0,1,-1,0,0,0,0> velocity_dim;
typedef mpl::vector_c<long,0,1,-2,0,0,0,0> acceleration_dim; // l/(t^2)
typedef mpl::vector_c<long,1,1,-1,0,0,0,0> momentum_dim; // ml/t
typedef mpl::vector_c<long,1,1,-2,0,0,0,0> force_dim; // ml/(t^2)
typedef mpl::vector_c<long,0,0,0,0,0,0,0> scalar_dim;
//typedef mpl::vector_c<long,1,1,-2,0,0,0,0> force_dim2; // ml/(t^2)


template<class T, class Dimensions>
struct quantity
{
	explicit quantity(T x) : m_value(x) {}
	T value() const { return m_value; }
	template <class OtherDimensions>
	quantity(quantity<T, OtherDimensions> const& rhs) : m_value(rhs.value())
	{
		BOOST_STATIC_ASSERT((
				mpl::equal<Dimensions,OtherDimensions>::type::value));
	}
private :
	T m_value;
};

template<class T, class D>
quantity<T,D>
operator+(quantity<T,D> x, quantity<T,D> y)
{
	return quantity<T,D>(x.value() + y.value());
};

template<class T, class D>
quantity<T,D>
operator-(quantity<T,D> x, quantity<T,D> y)
{
	return quantity<T,D>(x.value() - y.value());
};

struct plus_f
{
	template<class T1, class T2>
	struct apply
	{
		typedef typename mpl::plus<T1,T2>::type type;
	};
};

struct noop_f
{
	template<class T>
	struct apply
	{
		typedef T type;
	};
};


template<class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type > // new dimensions
                               operator*(quantity<T,D1> x, quantity<T,D2> y)
{

	typedef typename mpl::transform<D1,D2,plus_f>::type dim;
	return quantity<T, dim >( x.value() * y.value() );
};


int main() {
	cout << "Boost : Template Metaprogramming Part 2" << endl; // prints Boost : Template Metaprogramming Part 2
    cout << "Print five: " << five << endl;
    quantity<float,length_dim> l(1.0f);
    quantity<float,mass_dim> m(1.0f);

    quantity<float, length_dim> len1(1.0f);
    quantity<float, length_dim> len2(2.0f);
    len1 = len1 + len2;
    std::cout << "len1 + len2 = " << len1.value() << std::endl;

    quantity<float, mass_dim> m1(5.0f);
    quantity<float, acceleration_dim> a1(9.8f);

    std::cout << "force = " << (m1 * a1).value() << std::endl;

    // the statment below will fail to compile
    // because transform builds an entirely new sequence with different underlying type
    quantity<float, force_dim > f1 = m1 * a1;

    // here is an attempt to figure out what transform does with the input types
    // and how to fix the new sequence
    //
    typedef boost::fusion::traits::deduce_sequence<force_dim>::type exp_force_dim;
    typedef mpl::reverse_transform<mass_dim,force_dim, plus_f>::type acc_type;
    acc_type t1;
    cout << typeid(t1).name() << std::endl;

    typedef mpl::transform<
    		mpl::range_c<int,0,10> ,
    		mpl::plus<mpl::_1,mpl::_1> ,
    		mpl::back_inserter< mpl::vector0<> >
    		>::type result;
    cout << typeid(result).name() << std::endl;




	return 0;
}
