//============================================================================
// Name        : BoostFileDependency.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

using namespace std;

enum files_e {
	dax_h, yow_h, boz_h, zow_h, foo_cpp,
	foo_o, bar_cpp, bar_o, libfoobar_a,
	zig_cpp, zig_o, zag_cpp, zag_o,
	libzigzag_a, killerapp, N };

const char* name[] = { "dax_h", "yow_h", "boz_h", "zow_h", "foo.cpp",
					   "foo.o", "bar.cpp", "bar.o", "libfoobar.a",
					   "zig.cpp", "zig.o", "zag.cpp", "zag.o",
					   "libzigzag.a", "killerapp" };

typedef std::pair<int, int> Edge;
Edge used_by[] = {
		Edge(dax_h,foo_cpp), Edge(dax_h, bar_cpp), Edge(dax_h, yow_h),
		Edge(yow_h, bar_cpp), Edge(yow_h, zag_cpp),
		Edge(boz_h, bar_cpp), Edge(boz_h, zig_cpp), Edge(boz_h, zag_cpp),
		Edge(zow_h, foo_cpp),
		Edge(foo_cpp, foo_o),
		Edge(foo_o, libfoobar_a),
		Edge(bar_cpp, bar_o),
		Edge(bar_o, libfoobar_a),
		Edge(libfoobar_a, libzigzag_a),
		Edge(zig_cpp, zig_o),
		Edge(zig_o, libzigzag_a),
		Edge(libzigzag_a, killerapp)
};

using namespace boost;



int main() {
	cout << "File Dependency Example" << endl; // prints File Dependency Example

	typedef adjacency_list<vecS, vecS, bidirectionalS, property<vertex_color_t, default_color_type>> Graph;
	Graph g(used_by, used_by + sizeof(used_by) / sizeof(Edge), N);
	typedef graph_traits<Graph>::vertex_descriptor Vertex;

	typedef std::list<Vertex> MakeOrder;
	MakeOrder make_order;
	boost::topological_sort(g, std::front_inserter(make_order));

	std::cout << "make ordering: ";
	for (MakeOrder::iterator i = make_order.begin();
			i != make_order.end(); ++i )
		std::cout << name[*i] << " ";
	std::cout << endl;



	return 0;
}
