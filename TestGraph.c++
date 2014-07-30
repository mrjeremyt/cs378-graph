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
    % gcov-4.7 -b Graph.h TestGraph.c++


To configure Doxygen:
    % doxygen -g
    That creates the file "Doxyfile".
    Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile

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

#include <vector>

using namespace std;




#define ALL_TYPEDEF     typedef typename TestFixture::graph_type         graph_type;\
                        typedef typename TestFixture::vertex_descriptor  vertex_descriptor;\
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
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> >
            my_types;

TYPED_TEST_CASE(TestGraph, my_types);

TYPED_TEST(TestGraph, Add_Vertex_1) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, Add_Vertex_2) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    vertex_descriptor vd = vertex(1, g);
    ASSERT_EQ(vdB, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(2, vs);
}

TYPED_TEST(TestGraph, Add_Vertex_3) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    vertex_descriptor vd = vertex(3, g);
    ASSERT_EQ(vdD, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(4, vs);
}

TYPED_TEST(TestGraph, Num_Vertices_1){
    ALL_TYPEDEF

    graph_type g;    

    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
}

TYPED_TEST(TestGraph, Num_Vertices_2){
    ALL_TYPEDEF

    graph_type g;    

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    ASSERT_EQ(5, num_vertices(g));
}

TYPED_TEST(TestGraph, Num_Vertices_3){
    ALL_TYPEDEF

    graph_type g;    

    for(int i = 0; i < 5000; i++){
        vertex_descriptor vdA = add_vertex(g);    
    }
    ASSERT_EQ(5000, num_vertices(g));
}


TYPED_TEST(TestGraph, Add_Edge_1) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, Add_Edge_2) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, Add_Edge_3) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, Num_Edges_1){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    ASSERT_EQ(1, num_edges(g));
}

TYPED_TEST(TestGraph, Num_Edges_2){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edBB = add_edge(vdB, vdB, g).first;
    ASSERT_EQ(3, num_edges(g));
}

TYPED_TEST(TestGraph, Num_Edges_3){
    ALL_TYPEDEF

    graph_type g;

    for(int i = 0; i < 500; i++){
        
        vertex_descriptor vdA = add_vertex(g);
        vertex_descriptor vdB = add_vertex(g);
        for(int j = 0; j < 10; j++){
            edge_descriptor edAB = add_edge(vdA, vdB, g).first;
            edge_descriptor edAA = add_edge(vdA, vdA, g).first;
            edge_descriptor edBB = add_edge(vdB, vdB, g).first;
        }
    }

    ASSERT_EQ(1500, num_edges(g));
}


TYPED_TEST(TestGraph, Adjacent_Vertices_1) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
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

TYPED_TEST(TestGraph, Adjacent_Vertices_2) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdA, g);
    add_edge(vdA, vdE, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, Adjacent_Vertices_3) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
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

TYPED_TEST(TestGraph, Edge_1){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(true, p1.second);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;

    pair<edge_descriptor, bool> p2 = edge(vdA, vdA, g);
    ASSERT_EQ(edAA, p2.first);
    ASSERT_EQ(true, p2.second);
}

TYPED_TEST(TestGraph, Edge_2){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);    

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(true, p1.second);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;

    pair<edge_descriptor, bool> p2 = edge(vdA, vdA, g);
    ASSERT_EQ(edAA, p2.first);
    ASSERT_EQ(true, p2.second);

    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    pair<edge_descriptor, bool> p3 = edge(vdA, vdC, g);
    ASSERT_EQ(edAC, p3.first);
    ASSERT_EQ(true, p3.second);

}

TYPED_TEST(TestGraph, Edge_3){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);    

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(true, p1.second);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    pair<edge_descriptor, bool> p2 = edge(vdA, vdA, g);
    ASSERT_EQ(edAA, p2.first);
    ASSERT_EQ(true, p2.second);

    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    pair<edge_descriptor, bool> p3 = edge(vdA, vdC, g);
    ASSERT_EQ(edAC, p3.first);
    ASSERT_EQ(true, p3.second);

    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    pair<edge_descriptor, bool> p4 = edge(vdB, vdC, g);
    ASSERT_EQ(edBC, p4.first);
    ASSERT_EQ(true, p4.second);
}

TYPED_TEST(TestGraph, Edge_4){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);    
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(true, p1.second);

    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    pair<edge_descriptor, bool> p2 = edge(vdA, vdA, g);
    ASSERT_EQ(edAA, p2.first);
    ASSERT_EQ(true, p2.second);

    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    pair<edge_descriptor, bool> p3 = edge(vdA, vdC, g);
    ASSERT_EQ(edAC, p3.first);
    ASSERT_EQ(true, p3.second);

    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    pair<edge_descriptor, bool> p4 = edge(vdB, vdC, g);
    ASSERT_EQ(edBC, p4.first);
    ASSERT_EQ(true, p4.second);

    pair<edge_descriptor, bool> p5 = edge(vdD, vdC, g);
    ASSERT_NE(edBC, p5.first);
    ASSERT_EQ(false, p5.second);    
}

TYPED_TEST(TestGraph, Edges_1) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;
    edge_descriptor edCB = add_edge(vdC, vdB, g).first;
    edge_descriptor edEA = add_edge(vdE, vdA, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;

    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAA, ed);}
    ++b;
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
        ASSERT_EQ(edBA, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edCB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edEA, ed);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, Edges_2) {
    ALL_TYPEDEF

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

TYPED_TEST(TestGraph, Edges_3) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);
    }
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);
    }
    ++b;
    if(b != e){
        edge_descriptor ed = *b;
        ASSERT_EQ(edBC, ed);
    }
    ++b;
    ASSERT_EQ(e, b);

}

TYPED_TEST(TestGraph, Source_1){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    vertex_descriptor sAB = source(edAB, g);
    ASSERT_EQ(0, sAB);
}

TYPED_TEST(TestGraph, Source_2){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    vertex_descriptor sAB = source(edAB, g);
    vertex_descriptor sAC = source(edAC, g);

    ASSERT_EQ(0, sAB);
    ASSERT_EQ(0, sAC);
}

TYPED_TEST(TestGraph, Source_3){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;

    vertex_descriptor sAB = source(edAB, g);
    vertex_descriptor sAC = source(edAC, g);
    vertex_descriptor sAA = source(edAA, g);
    vertex_descriptor sBC = source(edBC, g);

    ASSERT_EQ(0, sAB);
    ASSERT_EQ(0, sAC);
    ASSERT_EQ(0, sAA);
    ASSERT_EQ(1, sBC);
}

TYPED_TEST(TestGraph, Target_1){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    vertex_descriptor sAB = target(edAB, g);
    ASSERT_EQ(1, sAB);
}

TYPED_TEST(TestGraph, Target_2){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    vertex_descriptor sAB = target(edAB, g);
    vertex_descriptor sAC = target(edAC, g);

    ASSERT_EQ(1, sAB);
    ASSERT_EQ(2, sAC);
}

TYPED_TEST(TestGraph, Target_3){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;

    vertex_descriptor sAB = target(edAB, g);
    vertex_descriptor sAC = target(edAC, g);
    vertex_descriptor sAA = target(edAA, g);
    vertex_descriptor sBC = target(edBC, g);

    ASSERT_EQ(1, sAB);
    ASSERT_EQ(2, sAC);
    ASSERT_EQ(0, sAA);
    ASSERT_EQ(2, sBC);
}

TYPED_TEST(TestGraph, Vertex_1){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);

    ASSERT_EQ(vdA, vd);
}

TYPED_TEST(TestGraph, Vertex_2){
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    vertex_descriptor vda = vertex(0, g);
    vertex_descriptor vdb = vertex(1, g);
    vertex_descriptor vdc = vertex(2, g);

    ASSERT_EQ(vdA, vda);
    ASSERT_EQ(vdB, vdb);
    ASSERT_EQ(vdC, vdc);
}

TYPED_TEST(TestGraph, Vertex_3){
    ALL_TYPEDEF

    graph_type g;

    vector<vertex_descriptor> v;

    int num_vertices = 100;

    for(int i = 0; i < num_vertices; i++){ v.push_back(add_vertex(g)); }


    for(int i = 0; i < num_vertices; i++){
        ASSERT_EQ(vertex(i, g), v[i]);
    }
}

TYPED_TEST(TestGraph, Vertices_1) {
    ALL_TYPEDEF

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

TYPED_TEST(TestGraph, Vertices_2) {
    ALL_TYPEDEF

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
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, Vertices_3) {
    ALL_TYPEDEF

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);    
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

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
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdF, vd);}
    ++b;
    ASSERT_EQ(e, b);
}


