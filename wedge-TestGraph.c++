// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2014
// Glenn P. Downing
// Daniel Durbin
// K.C. Hawes-Domingue
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
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -ggdb3 -Wall TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

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
using namespace std;

#define FIXTURES    typedef typename TestFixture::graph_type         graph_type; \
                    typedef typename TestFixture::vertex_descriptor  vertex_descriptor; \
                    typedef typename TestFixture::edge_descriptor    edge_descriptor;\
                    typedef typename TestFixture::vertex_iterator    vertex_iterator;\
                    typedef typename TestFixture::edge_iterator      edge_iterator;\
                    typedef typename TestFixture::adjacency_iterator adjacency_iterator;\
                    typedef typename TestFixture::vertices_size_type vertices_size_type;\
                    typedef typename TestFixture::edges_size_type    edges_size_type;

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
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>, Graph>
        my_types;

TYPED_TEST_CASE(TestGraph, my_types);

TYPED_TEST(TestGraph, add_edge_one_edge)
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    assert(va == 0);
    vertex_descriptor vb = add_vertex(g);
    assert(vb == 1);

    add_edge(va, vb, g);
    ASSERT_TRUE(edge(va, vb, g).second);
}

TYPED_TEST(TestGraph, add_edge_both_ways)
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    assert(va == 0);
    vertex_descriptor vb = add_vertex(g);
    assert(vb == 1);

    add_edge(va, vb, g);
    bool edge_added = add_edge(vb, va, g).second;
    ASSERT_TRUE(edge_added);
}

TYPED_TEST(TestGraph, add_edge_3)
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    assert(va == 0);
    vertex_descriptor vb = add_vertex(g);
    assert(vb == 1);
    vertex_descriptor vc = add_vertex(g);
    assert(vc == 2);
    vertex_descriptor vd = add_vertex(g);
    assert(vd == 3);
    edge_descriptor e1 = add_edge(va, vc, g).first;
    edge_descriptor e2 = add_edge(vb, vd, g).first;
    ASSERT_FALSE(edge(vb, vc, g).second);
    ASSERT_FALSE(edge(va, vd, g).second);
}

TYPED_TEST(TestGraph, add_vertex_one_vertex)
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    assert(va == 0);
}

TYPED_TEST(TestGraph, add_vertex_3_vertices)
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    assert(va == 0);
    vertex_descriptor vb = add_vertex(g);
    assert(vb == 1);
    vertex_descriptor vc = add_vertex(g);
    ASSERT_EQ(vertex(2,g), 2);
}

TYPED_TEST(TestGraph, add_vertex_51_vertices)
{
    FIXTURES

    graph_type g;

    for (int i = 0; i < 50; ++i) {
        add_vertex(g);
    }

    vertex_descriptor v1 = add_vertex(g);
    ASSERT_EQ(vertex(50,g), 50);
}

TYPED_TEST(TestGraph, adjacent_vertices_0) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    vertex_descriptor vb = add_vertex(g);
    vertex_descriptor vc = add_vertex(g);
    vertex_descriptor vd = add_vertex(g);

    add_edge(va, vd, g);
    add_edge(vb, vc, g);
    add_edge(vc, vd, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vd, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, adjacent_vertices_1) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor va = add_vertex(g);
    vertex_descriptor vb = add_vertex(g);
    vertex_descriptor vc = add_vertex(g);
    vertex_descriptor vd = add_vertex(g);

    add_edge(va, vc, g);
    add_edge(vb, vc, g);
    add_edge(vc, vd, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vc, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;

    ASSERT_EQ(++b, e);
}

TYPED_TEST(TestGraph, Adjacent_Vertices_The_Sequel) 
{
    FIXTURES

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

TYPED_TEST(TestGraph, adjacency_iterator_test) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdD, g);
    add_edge(vdA, vdE, g);
    add_edge(vdA, vdF, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);

    adjacency_iterator it = p.first;
    adjacency_iterator end = p.second;

    ++it;
    ++it;
    it++;
    it++;
    ASSERT_EQ(it, --end);
}

TYPED_TEST(TestGraph, edge) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g); 
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
}

TYPED_TEST(TestGraph, edge_no_edge) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    std::pair<edge_descriptor, bool> p = edge(vdA, vdA, g);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestGraph, edge_loop) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    edge_descriptor ed = add_edge(vdA, vdA, g).first;

    std::pair<edge_descriptor, bool> p = edge(vdA, vdA, g);
    ASSERT_EQ(ed, p.first);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, edges) {
    FIXTURES

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

TYPED_TEST(TestGraph, no_edges) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, edges_fully_connected) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor ed0 = add_edge(vdA, vdB, g).first;
    edge_descriptor ed1 = add_edge(vdA, vdC, g).first;
    edge_descriptor ed2 = add_edge(vdA, vdD, g).first;
    edge_descriptor ed3 = add_edge(vdB, vdA, g).first;
    edge_descriptor ed4 = add_edge(vdB, vdC, g).first;
    edge_descriptor ed5 = add_edge(vdB, vdD, g).first;
    edge_descriptor ed6 = add_edge(vdC, vdA, g).first;
    edge_descriptor ed7 = add_edge(vdC, vdB, g).first;
    edge_descriptor ed8 = add_edge(vdC, vdD, g).first;
    edge_descriptor ed9 = add_edge(vdD, vdA, g).first;
    edge_descriptor ed10 = add_edge(vdD, vdB, g).first;
    edge_descriptor ed11 = add_edge(vdD, vdC, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    vector<edge_descriptor> locke = {ed0, ed1, ed2, ed3, ed4, ed5, ed6, ed7, ed8, ed9, ed10, ed11};
    auto itl = locke.begin();

    ASSERT_NE(b, e);
    while (b != e) {
        ASSERT_EQ(*b, *itl);
        ++b;
        ++itl;
    }
}

TYPED_TEST(TestGraph, edge_iterator_test) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdD, g);
    add_edge(vdA, vdE, g);
    add_edge(vdA, vdF, g);

    std::pair<edge_iterator, edge_iterator> p = edges(g);

    edge_iterator it = p.first;
    edge_iterator end = p.second;

    ++it;
    ++it;
    *it = add_edge(vdA, vdA, g).first;

    ASSERT_TRUE(edge(vdA, vdA, g).second);
}

TYPED_TEST(TestGraph, num_edges_0) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);
}

TYPED_TEST(TestGraph, num_edges_1) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    add_edge(vdA, vdB, g); 

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);
}

TYPED_TEST(TestGraph, num_edges_2) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    add_edge(vdA, vdB, g); 

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdC, vdD, g);

    es = num_edges(g);
    ASSERT_EQ(2, es);
}

TYPED_TEST(TestGraph, num_vertices_the_first) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    assert(vdA == 0);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, num_vertices_none) {
    FIXTURES

    graph_type g;

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(0, vs);
}

TYPED_TEST(TestGraph, num_vertices_a_bunch) {
    FIXTURES

    graph_type g;

    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(16, vs);
}

TYPED_TEST(TestGraph, source_1) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);
}

TYPED_TEST(TestGraph, source_2) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;

    vertex_descriptor va = source(edAB, g);
    ASSERT_EQ(vdA, va);
    vertex_descriptor vb = source(edBA, g);
    ASSERT_EQ(vdB, vb);
}

TYPED_TEST(TestGraph, source_cycle) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vA = add_vertex(g);

    edge_descriptor eAA = add_edge(vA, vA, g).first;

    vertex_descriptor v1 = source(eAA, g);
    ASSERT_EQ(vA, v1);
}

TYPED_TEST(TestGraph, target_1)
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g); 
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, target_2) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;

    vertex_descriptor v1 = target(edAB, g);
    ASSERT_EQ(vdB, v1);
    vertex_descriptor v2 = target(edBA, g);
    ASSERT_EQ(vdA, v2);
}

TYPED_TEST(TestGraph, target_cycle) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vA = add_vertex(g);

    edge_descriptor eAA = add_edge(vA, vA, g).first;

    vertex_descriptor v1 = target(eAA, g);
    ASSERT_EQ(vA, v1);
}

TYPED_TEST(TestGraph, vertex_a_bunch) {
    FIXTURES

    graph_type g;

    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    vertex_descriptor v15 = add_vertex(g);

    vertex_descriptor vd = vertex(15, g);
    ASSERT_EQ(vd, v15);
}

TYPED_TEST(TestGraph, vertex_end) {
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    assert(vdA == 0);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);
}

TYPED_TEST(TestGraph, vertex_none) {
    FIXTURES

    graph_type g;

    vertex_descriptor vd = vertex(0, g);

    ASSERT_EQ(0, vd);
}

TYPED_TEST(TestGraph, vertex_iterator) 
{
    FIXTURES

    graph_type g;

    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g); 
    vertex_iterator it = p.first;
    vertex_iterator end = p.second;

    it += 5;
    ASSERT_EQ(it, end);

    --it;
    it -= 2;
    ASSERT_EQ(it, end - 3);
}

TYPED_TEST(TestGraph, vertices) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

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
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, vertices_no_vertices) 
{
    FIXTURES

    graph_type g;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g); 
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, vertices_one_vertex) 
{
    FIXTURES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g); 
    vertex_iterator b = p.first;
    vertex_iterator e = p.second;
    ++b;
    ASSERT_EQ(b, e);
}

TYPED_TEST(TestGraph, Big_Graph)
{
    FIXTURES

    graph_type g;

    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    vertex_descriptor v2 = add_vertex(g);
    edge_descriptor e0 = add_edge(v0, v1, g).first;
    edge_descriptor e2 = add_edge(v2, v2, g).first;
    vertex_descriptor v3 = add_vertex(g);
    edge_descriptor e1 = add_edge(v1, v2, g).first;
    vertex_descriptor v4 = add_vertex(g);
    edge_descriptor e3 = add_edge(v2, v3, g).first;
    edge_descriptor e5 = add_edge(v4, v0, g).first;
    edge_descriptor e4 = add_edge(v0, v4, g).first;
    edge_descriptor e6 = add_edge(v0, v3, g).first;
    vertex_descriptor v5 = add_vertex(g);
    vertex_descriptor v6 = add_vertex(g);

    ASSERT_EQ(7, num_edges(g));
    ASSERT_EQ(7, num_vertices(g));

    std::pair<vertex_iterator, vertex_iterator> vertex_range = vertices(g);
    vertex_iterator itv = vertex_range.first;
    vertex_descriptor v = 0;
    while (itv != vertex_range.second) {
        ASSERT_EQ(v++, *itv++);
    }

    std::pair<edge_iterator, edge_iterator> edge_range = edges(g);

    vector<edge_descriptor> celes {e0, e6, e4, e1, e2, e3, e5};

    edge_iterator ite = edge_range.first;
    auto ites = celes.begin();
    ASSERT_NE(ite, edge_range.second);
    while (ite != edge_range.second) {
       ASSERT_EQ(*ites, *ite);
       ites++;
       ite++;
    }

    itv = vertex_range.first;
    while (itv != vertex_range.second) {
        pair<adjacency_iterator, adjacency_iterator> adjacency_range = adjacent_vertices(*itv, g);
        adjacency_iterator itar = adjacency_range.first;
        while(itar != adjacency_range.second) {
            ASSERT_TRUE(edge(*itv, *itar++, g).second); 
        }
        itv++;
    }
}

TYPED_TEST(TestGraph, edge_with_no_vertex)
{
    FIXTURES

    graph_type g;

    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = 42;

    std::pair<edge_descriptor, bool> p2 = edge(v0, v1, g);

    ASSERT_FALSE(p2.second);
    ASSERT_EQ(num_vertices(g), 1);
    ASSERT_EQ(num_edges(g),0);
}
