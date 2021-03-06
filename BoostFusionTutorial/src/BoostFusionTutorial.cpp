//============================================================================
// Name        : BoostFusionTutorial.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <typeinfo>

#include <boost/mpl/assert.hpp>

#include <boost/fusion/sequence.hpp>

#include <boost/fusion/container/vector.hpp>

#include <boost/fusion/algorithm.hpp>

#include <boost/type_traits/is_pointer.hpp>

#include <boost/fusion/support/is_sequence.hpp>

#include <boost/fusion/view/single_view.hpp>

#include <boost/fusion/view/iterator_range.hpp>

#include <boost/mpl/vector_c.hpp>

#include <boost/fusion/view/nview.hpp>

#include <boost/fusion/view/repetitive_view.hpp>

#include <boost/fusion/view/flatten_view.hpp>

#include <boost/fusion/support/tag_of.hpp>

#include <boost/fusion/iterator/key_of.hpp>

#include <boost/fusion/container/map.hpp>

#include <boost/fusion/sequence/intrinsic/begin.hpp>


//using namespace std;
using namespace boost;

using boost::mpl::_;
using boost::mpl::not_;
using boost::is_class;

struct print_xml
{
	template <typename T>
	void operator()(T const & x) const
	{
		std::cout
		 << '<' << typeid(x).name() << '>'
		 << x
		 << "</" << typeid(x).name() << '>';
	}
};

template<typename Sequence>
void xml_print_pointers(Sequence const& seq)
{
   for_each(fusion::filter_if<boost::is_pointer<mpl::_> >(seq), print_xml());
}

template< typename T, typename U > struct bmpan_my
{
	BOOST_MPL_ASSERT_NOT(( is_same< T,U > ));
};

struct tv_square
{
	template<typename Sig>
	struct result;

	template<typename U>
	struct result<tv_square(U)>
	: remove_reference<U>
	{};

	template<typename T>
	T operator()(T x) const
	{
		return x*x;
	}
};

struct aw_f0
{
	template< typename T = int > struct apply
	{
	   typedef char type;
	};
};

struct aw_g0
{
	struct apply { typedef char type; };
};

struct aw_f2
{
	template< typename T1, typename T2 > struct apply
	{
		typedef T2 type;
	};
};

template< typename N1, typename N2 > struct int_plus
    : mpl::int_<( N1::value + N2::value )>
{

};

int main() {
	std::cout << "Boost Fusion Tutorial" << std::endl; // prints Boost Fusion Tutorial


	// fusion::at_c example
    fusion::vector<int, char, std::string> at_stuff(1, 'x', "howdy");
    int at_i = fusion::at_c<0>(at_stuff);
    char at_ch = fusion::at_c<1>(at_stuff);
    std::string at_s = fusion::at_c<2>(at_stuff);
    std::cout << "at_i=" << at_i << ", at_ch=" << at_ch << ", at_s=" << at_s << std::endl;
    for_each(at_stuff, print_xml());

    // BOOST_MPL_ASSERT_NOT example
    BOOST_MPL_ASSERT_NOT(( fusion::traits::is_sequence< std::vector<int> > ));

    bmpan_my<int,long> test;

    // fusion::single_view example
    fusion::single_view<int> sview(3);
    std::cout << sview << std::endl;

    // fusion::filter_view example
    typedef fusion::vector<std::string, char, long, bool, double> fv_vector_type;

    fv_vector_type v("a-string",'@',987654,true,6.6);

    fusion::filter_view<fv_vector_type const, mpl::not_<boost::is_class<mpl::_> > > fv_view(v);
    std::cout << fv_view << std::endl;

    // iterator_range example
    char const* ir_s = "Ruby";
    typedef fusion::vector<int, char, double, char const*> ir_vector_type;
    ir_vector_type ir_vec(1,'x',3.3,ir_s);

    typedef fusion::result_of::begin<ir_vector_type>::type A;
    typedef fusion::result_of::end<ir_vector_type>::type B;
    typedef fusion::result_of::next<A>::type C;
    typedef fusion::result_of::prior<B>::type D;

    C c(ir_vec);
    D d(ir_vec);

    fusion::iterator_range<C,D> ir_range(c,d);
    std::cout << ir_range << std::endl;

    // joint_view example
    fusion::vector<int, char> jv_v1(3, 'x');
    fusion::vector<std::string,int> jv_v2("hello",123);
    fusion::joint_view<
        fusion::vector<int, char>,
        fusion::vector<std::string, int>
    > jv_view(jv_v1, jv_v2);
    std::cout << jv_view << std::endl;

    //zip_view example
    typedef fusion::vector<int,int> zv_vec1;
    typedef fusion::vector<char,char> zv_vec2;
    zv_vec1 zv_v1(1,2);
    zv_vec2 zv_v2('a','b');
    typedef fusion::vector<zv_vec1&,zv_vec2&> zv_sequences;
    std::cout << fusion::zip_view<zv_sequences>(zv_sequences(zv_v1,zv_v2)) << std::endl;

    //transform_view example
    typedef fusion::vector<int,short,double> tv_vector_type;
    tv_vector_type tv_vec(2, 5, 3.3);
    fusion::transform_view<tv_vector_type,tv_square> tv_transform(tv_vec, tv_square());
    std::cout << tv_transform << std::endl;

    //reverse_view example
    typedef fusion::vector<int,short,double> rv_vector_type;
    rv_vector_type rv_vec (2, 5, 3.3);
    fusion::reverse_view<rv_vector_type> rv_reverse(rv_vec);
    std::cout << rv_reverse << std::endl;

    //nview example
    typedef fusion::vector<int, char, double> nv_vec;
    typedef mpl::vector_c<int, 2, 1, 0, 2, 0> nv_indices;

    nv_vec nv_v1(1,'c',2.0);

    std::cout << fusion::nview<nv_vec, nv_indices>(nv_v1) << std::endl; //2.0 c 1 2.0 1

    //repetitive_view example
    typedef fusion::vector<int, char, double> rv_vec1;
    typedef fusion::vector<int, char, double, int, char> rv_vec2;

    rv_vec1 rv_v1(1,'c',2.0);
    rv_vec2 rv_v2(fusion::repetitive_view<rv_vec1>(rv_v1));


    std::cout << rv_v2 << std::endl; // 1, 'c', 2.0, 1, 'c'

    //tag_of example
    typedef fusion::traits::tag_of<fusion::list<> >::type to_tag1;
    typedef fusion::traits::tag_of<fusion::list<int> >::type to_tag2;
    typedef fusion::traits::tag_of<fusion::vector<> >::type to_tag3;
    typedef fusion::traits::tag_of<fusion::vector<int> >::type to_tag4;

    BOOST_MPL_ASSERT((boost::is_same<to_tag1, to_tag2>));
    BOOST_MPL_ASSERT((boost::is_same<to_tag3, to_tag4>));

    //begin example
    typedef fusion::vector<int> be_vec;
    typedef fusion::result_of::begin<be_vec>::type be_it;
    BOOST_MPL_ASSERT((boost::is_same<fusion::result_of::deref<be_it>::type, int&>));

    //key_of example
    typedef fusion::map<mpl::pair<float,int> > ko_vec;
    typedef fusion::result_of::begin<ko_vec>::type ko_first;

    // this is supposed to be BOOST_MPL_ASSERT but that fails!
    //BOOST_MPL_ASSERT((boost::is_same<fusion::result_of::key_of<ko_first>::type, float>));

    //MPL apply_wrap and arg example
    typedef mpl::apply_wrap5< mpl::arg<1>, bool, char, short, int, long >::type aw_t1;
    typedef mpl::apply_wrap5< mpl::arg<3>, bool, char, short, int, long >::type aw_t3;

    BOOST_MPL_ASSERT(( boost::is_same< aw_t1, bool > ));
    BOOST_MPL_ASSERT(( boost::is_same< aw_t3, short > ));

    typedef mpl::apply_wrap0< aw_f0 >::type aw_r1;
    typedef mpl::apply_wrap0< aw_g0 >::type aw_r2;
    typedef mpl::apply_wrap2< aw_f2,int,char >::type aw_r3;

    BOOST_MPL_ASSERT(( boost::is_same< aw_r1, char > ));
    BOOST_MPL_ASSERT(( boost::is_same< aw_r2, char > ));
    BOOST_MPL_ASSERT(( boost::is_same< aw_r3, char > ));

    //MPL apply example
    typedef mpl::apply< int_plus<mpl::_1,mpl::_2>, mpl::int_<2>, mpl::int_<3> >::type a_r1;
    typedef mpl::apply< mpl::quote2<int_plus>, mpl::int_<2>, mpl::int_<3> >::type a_r2;

    BOOST_MPL_ASSERT_RELATION( a_r1::value, ==, 5 );
    BOOST_MPL_ASSERT_RELATION( a_r2::value, ==, 5 );

    //MPL integral wrapper int_ example
    typedef mpl::int_<8> iw_eight;
    BOOST_MPL_ASSERT(( boost::is_same< iw_eight::value_type, int > ));
    BOOST_MPL_ASSERT(( boost::is_same< iw_eight::type, iw_eight > ));
    BOOST_MPL_ASSERT(( boost::is_same< mpl::next< iw_eight >::type, mpl::int_<9> > ));


	return 0;
}
