//============================================================================
// Name        : BoostGraphLibraryTour.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;

void create_graph()
{
	// create a typedef for the Graph type
	typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

	// make convenient labels for the vertices
    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const char * name = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
    {
       Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
       Edge(C,E), Edge(B,D), Edge(D,E)
    };

    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
    // declare a graph object
    Graph g(num_vertices);

    // add the edges to the graph object
    for (int i = 0; i < num_edges; i++)
    {
    	add_edge(edge_array[i].first, edge_array[i].second, g);
    }



}

int main(int, char *[]) {
	std::cout << "Boost Graph Library Tour" << std::endl; // prints Boost Graph Library Tour



	return 0;
}
