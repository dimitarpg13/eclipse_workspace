//============================================================================
// Name        : BoostCityVisitor.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp> // for boost::make_list

/*
 * Example of using a visitor with breadth_first_search and deapth_first_search algorithms
 *
 * Sacramento ---- Reno ---- Salt Lake City
 * 		|
 * San Fransisco
 * 		|
 * San Jose ---- Fresno
 * 		|
 * Los Angeles  ----  Las Vegas ---- Phoenix
 * 		|
 * San Diego
 *
 * The visitor has three main functions:
 *
 * discover_vertex(u,g) is invoked when the algorithm first arrives at vertex u.
 * 	This will happen on the depth first or breadth first order depending on which
 * 	algorithm is used.
 *
 * examine_edge(e,g) is invoked when the algorithm first checks an edge to see
 * 	whether it has been already there. Whether using BFS or DFS, all the edges of
 * 	vertex u are examined immediately after the call to visit(u).
 *
 * finish_vertex(u, g) is called after all vertices reachable from u have been visited
 */


using namespace std;
using namespace boost;

struct city_arrival : public base_visitor<city_arrival>
{
   city_arrival(string * n) : names(n) {};
   typedef on_discover_vertex event_filter;
   template <class Vertex, class Graph>
   inline void operator() (Vertex u, Graph& g) {
	 cout << endl << "arriving at " << names[u] << endl
	    		  << " neighboring cities are: ";
   }
   string* names;
};

struct neighbor_cities : public base_visitor<neighbor_cities>
{
	neighbor_cities(string * n) : names(n) {};
	typedef on_examine_edge event_filter;
	template<class Edge, class Graph>
	inline void operator() (Edge e, Graph& g) {
		cout << names[ target(e,g) ] << ", ";
	}
	string* names;

};

struct finish_city : public base_visitor<finish_city>
{
	finish_city(string * n) : names(n) {};
	typedef on_finish_vertex event_filter;
	template<class Vertex, class Graph>
	inline void operator() (Vertex u, Graph& g) {
		cout << endl << "finished with " << names[u] << endl;
	}
	string* names;
};

int main() {
  enum { SanJose, SanFran, LA, SanDiego, Fresno, LasVegas, Reno,
  	  	  Sacramento, SaltLake, Phoenix, N };

  string names[] = { "San Jose", "San Francisco", "Los Angeles", "San Diego",
					"Fresno", "Las Vegas", "Reno", "Sacramento", "Salt Lake City", "Phoenix" };

  typedef std::pair<int,int> E;
  E edge_array[] = { E(Sacramento,Reno), E(Sacramento,SanFran),
					E(Reno,SaltLake), E(SanFran,SanJose), E(SanJose,Fresno), E(SanJose, LA),
					E(LA, LasVegas), E(LA, SanDiego), E(LasVegas, Phoenix) };

  typedef adjacency_list<vecS, vecS, undirectedS> Graph;

  Graph G(edge_array, edge_array + sizeof(edge_array)/sizeof(E), N);

  cout << "**** Depth First ****" << endl;
  depth_first_search
  	  (G,
  	   visitor(make_dfs_visitor(boost::make_list(city_arrival(names),
  			   	   	   	   	   					 neighbor_cities(names),
  			   	   	   	   	   					 finish_city(names)))));

  cout << endl;

  /* get source vertex */
  boost::graph_traits<Graph>::vertex_descriptor s = vertex(SanJose,G);

  cout << "**** Breadth First ****"<< endl;
  breadth_first_search
  	  (G,s, visitor(make_bfs_visitor(boost::make_list(city_arrival(names),
  			  	  	  	  	  	  	  	  	  	  	  neighbor_cities(names),
  			  	  	  	  	  	  	  	  	  	  	  finish_city(names)))));


  return 0;
}
