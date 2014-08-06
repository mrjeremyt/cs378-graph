// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2014
// Glenn P. Downing
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
    % gcov-4.7 -b Graph.c++ TestGraph.c++
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

typedef testing::Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        my_types;

TYPED_TEST_CASE(TestGraph, my_types);

/* source */
TYPED_TEST(TestGraph, source1) 
{
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

    edge_descriptor ed = add_edge(vdA, vdB, g).first;

    vertex_descriptor vA = source(ed, g);

    ASSERT_EQ(vA, 0);
    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, source2) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    vertex_descriptor vA = source(ed, g);

    ASSERT_EQ(vA, 18);
    ASSERT_EQ(num_edges(g), 10);
    ASSERT_EQ(num_vertices(g), 20);
}

TYPED_TEST(TestGraph, source3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    vertex_descriptor vA = source(ed, g);

    ASSERT_EQ(vA, 38);
    ASSERT_EQ(num_edges(g), 20);
    ASSERT_EQ(num_vertices(g), 40);
}

/* target */
TYPED_TEST(TestGraph, target1) 
{
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

    edge_descriptor ed = add_edge(vdA, vdB, g).first;

    vertex_descriptor vA = target(ed, g);

    ASSERT_EQ(vA, 1);
    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, target2) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    vertex_descriptor vA = target(ed, g);

    ASSERT_EQ(vA, 19);
    ASSERT_EQ(num_edges(g), 10);
    ASSERT_EQ(num_vertices(g), 20);
}

TYPED_TEST(TestGraph, target3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    vertex_descriptor vA = target(ed, g);

    ASSERT_EQ(vA, 39);
    ASSERT_EQ(num_edges(g), 20);
    ASSERT_EQ(num_vertices(g), 40);
}

/* vertex */
TYPED_TEST(TestGraph, vertex1) 
{
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

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertex_descriptor ve = vertex(1, g);
    ASSERT_EQ(vdB, ve);
}

TYPED_TEST(TestGraph, vertex2) 
{
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

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertex_descriptor ve = vertex(1, g);
    ASSERT_EQ(vdB, ve);

    vertex_descriptor vf = vertex(2, g);
    ASSERT_EQ(vdC, vf);
}

TYPED_TEST(TestGraph, vertex3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA;

    for(int i = 0; i < 25; ++i)
        vdA = add_vertex(g);

    vertex_descriptor vd = vertex(24, g);
    ASSERT_EQ(vdA, vd);
}

/* add_vertex */
TYPED_TEST(TestGraph, add_vertex1) 
{
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

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertex_descriptor ve = vertex(1, g);
    ASSERT_EQ(vdB, ve);
}

TYPED_TEST(TestGraph, add_vertex2) 
{
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

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertex_descriptor ve = vertex(1, g);
    ASSERT_EQ(vdB, ve);

    vertex_descriptor vf = vertex(2, g);
    ASSERT_EQ(vdC, vf);
}

TYPED_TEST(TestGraph, add_vertex3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA;

    for(int i = 0; i < 25; ++i)
        vdA = add_vertex(g);

    vertex_descriptor vd = vertex(24, g);
    ASSERT_EQ(vdA, vd);
}

/* num_vertices */
TYPED_TEST(TestGraph, num_vertices1) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(0, vs);
}

TYPED_TEST(TestGraph, num_vertices2) 
{
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

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertex_descriptor ve = vertex(1, g);
    ASSERT_EQ(vdB, ve);

    vertex_descriptor vf = vertex(2, g);
    ASSERT_EQ(vdC, vf);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(3, vs);
}

TYPED_TEST(TestGraph, num_vertices3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA;

    for(int i = 0; i < 25; ++i)
        vdA = add_vertex(g);

    vertex_descriptor vd = vertex(24, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(25, vs);
}

/* add_edge */
TYPED_TEST(TestGraph, add_edge1) 
{
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

    edge_descriptor ed = add_edge(vdA, vdB, g).first;
    edge_descriptor ed2 = add_edge(vdA, vdB, g).first;

    ASSERT_EQ(ed, ed2);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, add_edge2) 
{
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

    std::pair<edge_descriptor, bool> temp = add_edge(vdA, vdB, g);
    edge_descriptor ed = temp.first;

    std::pair<edge_descriptor, bool> temp2 = add_edge(vdA, vdB, g);
    bool result = temp2.second;

    ASSERT_FALSE(result);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, add_edge3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    ASSERT_EQ(num_edges(g), 20);
    ASSERT_EQ(num_vertices(g), 40);
}

/* edge */
TYPED_TEST(TestGraph, edge1) 
{
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

    edge_descriptor ed = add_edge(vdA, vdB, g).first;
    edge_descriptor ed2 = edge(vdA, vdB, g).first;

    ASSERT_EQ(ed, ed2);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, edge2) 
{
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

    add_edge(vdA, vdB, g);

    bool result = edge(vdB, vdA, g).second;

    ASSERT_FALSE(result);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, edge3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    bool test = edge(18, 19, g).second;

    ASSERT_TRUE(test);
    ASSERT_EQ(num_edges(g), 20);
    ASSERT_EQ(num_vertices(g), 40);
}

/* num_edges */
TYPED_TEST(TestGraph, num_edges1) 
{
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

    edge_descriptor ed = add_edge(vdA, vdB, g).first;

    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, num_edges2) 
{
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

    std::pair<edge_descriptor, bool> temp = add_edge(vdA, vdB, g);
    edge_descriptor ed = temp.first;

    std::pair<edge_descriptor, bool> temp2 = add_edge(vdA, vdB, g);
    bool result = temp2.second;

    ASSERT_FALSE(result);
    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 2);
}

TYPED_TEST(TestGraph, num_edges3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 5; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 5; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 5; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    ASSERT_EQ(num_edges(g), 15);
    ASSERT_EQ(num_vertices(g), 30);
}

/* edge_iterator(edges) */
TYPED_TEST(TestGraph, edge_iterator1) 
{
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

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;

    ASSERT_EQ(*b, edAB);
    ++b;

    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, edge_iterator2) 
{
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
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

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
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, edge_iterator3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vdA;
    vertex_descriptor vdB;
    edge_descriptor ed;

    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }
    for(int i = 0; i < 10; ++i)
    {
        vdA = add_vertex(g);
        vdB = add_vertex(g);
        ed = add_edge(vdA, vdB, g).first;
    }

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;

    edge_iterator temp = b;
    for(int i = 0; i < 20; ++i)
        ++temp;
    ASSERT_EQ(temp, e);    

    ASSERT_EQ(num_edges(g), 20);
    ASSERT_EQ(num_vertices(g), 40);
}

/* vertex_iterator */
TYPED_TEST(TestGraph, vertex_iterator1) 
{
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

TYPED_TEST(TestGraph, vertex_iterator2) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA;

    for(int i = 0; i < 25; ++i)
        vdA = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;

    while(b != e){
        ++b;
    }

    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, vertex_iterator3) 
{
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA;

    for(int i = 0; i < 22; ++i)
        vdA = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;

    vertex_iterator temp = b + 21;
    vertex_descriptor vd = *temp;

    ASSERT_EQ(vd, 21);
}

/* adjacent_vertices */
TYPED_TEST(TestGraph, adjacent_vertices1) 
{
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

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, adjacent_vertices2) 
{
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
    
    for(int i = 0; i < 11; ++i)
    {
        vertex_descriptor temp = add_vertex(g);
        edge_descriptor temp2 = add_edge(vdA, temp, g).first;
    }

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    adjacency_iterator test = b;
    for(int i = 0; i < 11; ++i)
        ++test;

    ASSERT_EQ(test, e);
}

TYPED_TEST(TestGraph, adjacent_vertices3) 
{
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
    
    for(int i = 0; i < 20; ++i)
    {
        vertex_descriptor temp = add_vertex(g);
        edge_descriptor temp2 = add_edge(vdA, temp, g).first;
    }

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    adjacency_iterator test = b;
    for(int i = 0; i < 20; ++i)
        ++test;
    
    ASSERT_EQ(test, e);
}

TYPED_TEST(TestGraph, adjacent_vertices4) 
{
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
    edge_descriptor edD = add_edge(vdA, vdD, g).first;
    edge_descriptor edB = add_edge(vdA, vdB, g).first;
    edge_descriptor edA = add_edge(vdA, vdA, g).first;
    edge_descriptor edC = add_edge(vdA, vdC, g).first;

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_EQ(*b, vdA);
    ++b;
    ASSERT_EQ(*b, vdB);
    ++b;
    ASSERT_EQ(*b, vdC);
    ++b;
    ASSERT_EQ(*b, vdD);
    ++b;
    ASSERT_EQ(b, e);
}
