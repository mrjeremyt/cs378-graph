// ----------------------------
// TestGraph.c++
// Copyright (C) 2014
// Omar Lalani
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestGraph

To obtain coverage of the test:
    % gcov-4.7 -b Graph.h TestGraph.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef testing::Types< 
			boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>
			, Graph
			> 
			my_types;

TYPED_TEST_CASE(TestGraph, my_types);

// ---------------
// Edge_Descriptor
// ---------------

TYPED_TEST(TestGraph, Edge_Descriptor_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
	

    edge_descriptor a;
    edge_descriptor b(a);
    edge_descriptor c = a;
    edge_descriptor d = edge(vdC, vdD, g).first;
}

// ---------------
// Vertex_Iterator
// ---------------

//Four Vertices Forward
TYPED_TEST(TestGraph, Vertex_Iterator_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
	
    std::pair<vertex_iterator, vertex_iterator> it = vertices(g);
    vertex_iterator b = it.first;
    vertex_iterator e = it.second;
    if(b != e){
    	ASSERT_EQ(vdA, *b);
    }
    ++b;
    if(b != e){
    	ASSERT_EQ(vdB, *b);
    }
    b++;
    if(b != e){
    	ASSERT_EQ(vdC, *b);
    }
    ++b;
    if(b != e){
    	ASSERT_EQ(vdD, *b);
    }
    b++;
    ASSERT_EQ(b,e);
}

//Four Vertices Reverse
TYPED_TEST(TestGraph, Vertex_Iterator_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
	
    std::pair<vertex_iterator, vertex_iterator> it = vertices(g);
    vertex_iterator b = it.first;
    vertex_iterator e = it.second;
    e--;
    if(b != e){
    	ASSERT_EQ(vdD, *e);
    }
    --e;
    if(b != e){
    	ASSERT_EQ(vdC, *e);
    }
    e--;
    if(b != e){
    	ASSERT_EQ(vdB, *e);
    }
    --e;
    if(b != e){
    	ASSERT_EQ(vdA, *e);
    }
    ASSERT_EQ(b,e);
}

//No Vertices
TYPED_TEST(TestGraph, Vertex_Iterator_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
	
    std::pair<vertex_iterator, vertex_iterator> it = vertices(g);
    vertex_iterator b = it.first;
    vertex_iterator e = it.second;
    ASSERT_EQ(b,e);
}

// -------------
// Edge_Iterator
// -------------

//A points to B, C, and D Forward
TYPED_TEST(TestGraph, Edge_Iterator_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edAD = add_edge(vdA, vdD, g).first;
	
    std::pair<edge_iterator, edge_iterator> it = edges(g);
    edge_iterator b = it.first;
    edge_iterator e = it.second;
    if(b != e){
    	ASSERT_EQ(edAB, *b);
    }
    ++b;
    if(b != e){
    	ASSERT_EQ(edAC, *b);
    }
    b++;
    if(b != e){
    	ASSERT_EQ(edAD, *b);
    }
    ++b;
    ASSERT_EQ(b,e);
}

//A points to B, B points to C, and C points to A
TYPED_TEST(TestGraph, Edge_Iterator_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;
	
    std::pair<edge_iterator, edge_iterator> it = edges(g);
    edge_iterator b = it.first;
    edge_iterator e = it.second;
    if(b != e){
    	ASSERT_EQ(edAB, *b);
    }
    ++b;
    if(b != e){
    	ASSERT_EQ(edBC, *b);
    }
    b++;
    if(b != e){
    	ASSERT_EQ(edCA, *b);
    }
    ++b;
    ASSERT_EQ(b,e);
}

//D points to A, B, and C
TYPED_TEST(TestGraph, Edge_Iterator_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edDA = add_edge(vdD, vdA, g).first;
    edge_descriptor edDB = add_edge(vdD, vdB, g).first;
    edge_descriptor edDC = add_edge(vdD, vdC, g).first;
	
    std::pair<edge_iterator, edge_iterator> it = edges(g);
    edge_iterator b = it.first;
    edge_iterator e = it.second;
    if(b != e){
    	ASSERT_EQ(edDA, *b);
    }
    ++b;
    if(b != e){
    	ASSERT_EQ(edDB, *b);
    }
    b++;
    if(b != e){
    	ASSERT_EQ(edDC, *b);
    }
    ++b;
    ASSERT_EQ(b,e);
}

//No Edges
TYPED_TEST(TestGraph, Edge_Iterator_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
	
    std::pair<edge_iterator, edge_iterator> it = edges(g);
    edge_iterator b = it.first;
    edge_iterator e = it.second;
    ASSERT_EQ(b,e);
}

// --------
// Add_Edge
// --------

//Standard Single Edge between two points
TYPED_TEST(TestGraph, Add_Edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB = edge(vdA, vdB, g).first;
    ASSERT_EQ(p1.first, edAB);
    ASSERT_EQ(p1.second, true);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

//Two edges between two points pointing in opposite directions
TYPED_TEST(TestGraph, Add_Edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB = edge(vdA, vdB, g).first;
    ASSERT_EQ(p1.first, edAB);
    ASSERT_EQ(true, p1.second);

    std::pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
    edge_descriptor edBA = edge(vdB, vdA, g).first;
    ASSERT_EQ(p2.first, edBA);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd3 = source(edBA, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd4 = target(edBA, g);
    ASSERT_EQ(vdA, vd1);
}

//Two edges between two points pointing in same directions
TYPED_TEST(TestGraph, Add_Edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB = edge(vdA, vdB, g).first;
    ASSERT_EQ(p1.first, edAB);
    ASSERT_EQ(true, p1.second);

    std::pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    ASSERT_EQ(p2.first, edAB);
    ASSERT_EQ(false, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

//Vertex with edge pointing to itself
TYPED_TEST(TestGraph, Add_Edge_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdA, g);
    edge_descriptor edAA = edge(vdA, vdA, g).first;
    ASSERT_EQ(p1.first, edAA);
    ASSERT_EQ(true, p1.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAA, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAA, g);
    ASSERT_EQ(vdA, vd2);
}

// ----------
// Add_Vertex
// ----------

//Add Vertex to empty graph
TYPED_TEST(TestGraph, Add_Vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(vertex(0,g), vdA);

    edges_size_type es = num_vertices(g);
    ASSERT_EQ(1, es);
}

//Add vertices to growing graph
TYPED_TEST(TestGraph, Add_Vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    for(int i = 0; i < 5000; ++i){
    	vertex_descriptor newVertex = add_vertex(g);
    	ASSERT_EQ(vertex(i,g), newVertex);
    	ASSERT_EQ(num_vertices(g), i + 1);
    }
}

// -----------------
// Adjacent_Vertices
// -----------------

//A points to B, then C, and then D
TYPED_TEST(TestGraph, Adjacent_Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdD, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);
    }
    ++b;
    ASSERT_EQ(e, b);
}

//A points to itself and then B, B points to A and then itself
TYPED_TEST(TestGraph, Adjacent_Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdA, g);
    add_edge(vdA, vdB, g);
    add_edge(vdB, vdA, g);
    add_edge(vdB, vdB, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);
    }
    ++b;
    ASSERT_EQ(e, b);

    p = adjacent_vertices(vdB, g);
    b = p.first;
    e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);
    }
    ++b;
    ASSERT_EQ(e, b);
}

//A points to itself and then B, B points to itself and then A
TYPED_TEST(TestGraph, Adjacent_Vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdA, g);
    add_edge(vdA, vdB, g);
    add_edge(vdB, vdB, g);
    add_edge(vdB, vdA, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);
    }
    ++b;
    ASSERT_EQ(e, b);

    p = adjacent_vertices(vdB, g);
    b = p.first;
    e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);
    }
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);
    }
    ++b;
    ASSERT_EQ(e, b);
}

//B points to A, then C points to A, then D points to A
TYPED_TEST(TestGraph, Adjacent_Vertices_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdB, vdA, g);
    add_edge(vdC, vdA, g);
    add_edge(vdD, vdA, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    ASSERT_EQ(e, b);
}

// ----
// Edge
// ----

//Standard Single Edge between two points
TYPED_TEST(TestGraph, Edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB = p1.first;

    /*
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(true, p0.first);
    ASSERT_EQ(false, p1.second);
	*/

    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

//Two edges between two points pointing in opposite directions
TYPED_TEST(TestGraph, Edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    edge_descriptor edAB = p1.first;
    ASSERT_EQ(true, p1.second);

    std::pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
    edge_descriptor edBA = p2.first;
    ASSERT_EQ(true, p2.second);

    std::pair<edge_descriptor, bool> p3 = edge(vdA, vdB, g);
    ASSERT_EQ(p3.first, edAB);
    ASSERT_EQ(p3.second, true);

    std::pair<edge_descriptor, bool> p4 = edge(vdB, vdA, g);
    ASSERT_EQ(p4.first, edBA);
    ASSERT_EQ(p4.second, true);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd3 = source(edBA, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd4 = target(edBA, g);
    ASSERT_EQ(vdA, vd1);
}

//No edges exist
TYPED_TEST(TestGraph, Edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(p1.second, false);

    std::pair<edge_descriptor, bool> p2 = edge(vdB, vdA, g);
    ASSERT_EQ(p2.second, false);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);
}

//Vertex with edge pointing to itself
TYPED_TEST(TestGraph, Edge_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdA, g);
    
   	std::pair<edge_descriptor, bool> p2 = edge(vdA, vdA, g);
    ASSERT_EQ(p1.first, p2.first);
    ASSERT_EQ(true, p1.second);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(p2.first, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(p2.first, g);
    ASSERT_EQ(vdA, vd2);
}

// -----
// Edges
// -----

//A points to B, then C, and then D
TYPED_TEST(TestGraph, Edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edAD = add_edge(vdA, vdD, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAD, ed);}
    ++b;
    ASSERT_EQ(e, b);
}

//A points to itself and then B, B points to A and then itself
TYPED_TEST(TestGraph, Edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

	edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;
    edge_descriptor edBB = add_edge(vdB, vdB, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAA, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBA, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBB, ed);
    }
    ++b;
    ASSERT_EQ(e, b);
}

//A points to itself and then B, B points to itself and then A
TYPED_TEST(TestGraph, Edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

	edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBB = add_edge(vdB, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAA, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBA, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBB, ed);
    }
    ++b;
    ASSERT_EQ(e, b);
}

//B points to A, then C points to A, then D points to A
TYPED_TEST(TestGraph, Edges_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edBA = add_edge(vdB, vdA, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;
    edge_descriptor edDA = add_edge(vdD, vdA, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBA, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edCA, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edDA, ed);}
    ++b;
    ASSERT_EQ(e, b);
}

//B points to C, C points to A, A points to B
TYPED_TEST(TestGraph, Edges_5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edCA, ed);}
    ++b;
    ASSERT_EQ(e, b);
}

// ---------
// Num_Edges
// ---------

//A points to B, then C, and then D
TYPED_TEST(TestGraph, Num_Edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edAD = add_edge(vdA, vdD, g).first;
    ASSERT_EQ(num_edges(g), 3);
}

//A points to B, then C, and then D
TYPED_TEST(TestGraph, Num_Edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

	edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;
    edge_descriptor edBB = add_edge(vdB, vdB, g).first;

    ASSERT_EQ(num_edges(g), 4);
}

//A points to B 500 times
TYPED_TEST(TestGraph, Num_Edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> e1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(e1.second, true);
    
    for(int i = 0; i < 500; ++i){
		std::pair<edge_descriptor, bool> e2 = add_edge(vdA, vdB, g);
		ASSERT_EQ(e2.first, e1.first);
		ASSERT_EQ(e2.second, false);
    }

    ASSERT_EQ(num_edges(g), 1);
}

//A points to B, B points to C, C points to A
TYPED_TEST(TestGraph, Num_Edges_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;

    ASSERT_EQ(num_edges(g), 3);
}

//A points to itself
TYPED_TEST(TestGraph, Num_Edges_5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;

    ASSERT_EQ(num_edges(g), 1);
}

//A points to B, B points to A
TYPED_TEST(TestGraph, Num_Edges_6) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAA = add_edge(vdA, vdB, g).first;
    edge_descriptor edAB = add_edge(vdB, vdA, g).first;

    ASSERT_EQ(num_edges(g), 2);
}

//No Edges
TYPED_TEST(TestGraph, Num_Edges_7) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    ASSERT_EQ(num_edges(g), 0);
}

// ------------
// Num_Vertices
// ------------

//Three Vertices
TYPED_TEST(TestGraph, Num_Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    ASSERT_EQ(num_vertices(g), 3);
}

//No Vertices
TYPED_TEST(TestGraph, Num_Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    ASSERT_EQ(num_vertices(g), 0);
}

// ------
// Source
// ------

//B points to C, C points to A, A points to B
TYPED_TEST(TestGraph, Source_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = source(edBC, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd3 = source(edCA, g);
    ASSERT_EQ(vdC, vd3);
}

//A Points to itself
TYPED_TEST(TestGraph, Source_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;

    vertex_descriptor vd1 = source(edAA, g);
    ASSERT_EQ(vdA, vd1);
}

// ------
// Target
// ------

//B points to C, C points to A, A points to B
TYPED_TEST(TestGraph, Target_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    vertex_descriptor vd1 = target(edAB, g);
    ASSERT_EQ(vdB, vd1);

    vertex_descriptor vd2 = target(edBC, g);
    ASSERT_EQ(vdC, vd2);

    vertex_descriptor vd3 = target(edCA, g);
    ASSERT_EQ(vdA, vd3);
}

//A Points to itself
TYPED_TEST(TestGraph, Target_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;

    vertex_descriptor vd1 = target(edAA, g);
    ASSERT_EQ(vdA, vd1);
}

// ------
// Vertex
// ------

//Add single vertex
TYPED_TEST(TestGraph, Vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

//Add 5000 Vertices
TYPED_TEST(TestGraph, Vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

	graph_type g;

    for(int i = 0; i < 5000; ++i){
    	vertex_descriptor newVertex = add_vertex(g);
    	ASSERT_EQ(vertex(i,g), newVertex);
    	ASSERT_EQ(num_vertices(g), i + 1);
    }

    ASSERT_EQ(num_vertices(g), 5000);
}

//No vertices
TYPED_TEST(TestGraph, Vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

	graph_type g;

    ASSERT_EQ(num_vertices(g), 0);
}

// --------
// Vertices
// --------

//Two Vertices
TYPED_TEST(TestGraph, Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

//No Vertices
TYPED_TEST(TestGraph, Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;

    ASSERT_EQ(e, b);
}
