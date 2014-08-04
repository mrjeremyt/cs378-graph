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
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Graph.c++ TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

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
#define TEST_TYPES  typedef typename TestFixture::graph_type         graph_type; \
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
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        my_types;

TYPED_TEST_CASE(TestGraph, my_types);

// --------
// Add Edge
// --------
TYPED_TEST(TestGraph, add_edge_1) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    ASSERT_EQ(num_edges(g), 2);
    ASSERT_EQ(num_vertices(g) , 3);
}
TYPED_TEST(TestGraph, add_edge_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    ASSERT_EQ(num_edges(g), 2);
    ASSERT_EQ(num_vertices(g) , 3);

    edge_descriptor edT = add_edge(vdA, vdB, g).first;
    ASSERT_EQ(num_edges(g), 2);
}
TYPED_TEST(TestGraph, add_edge_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdA, g).first;

    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g) , 1);
}

// ----------
// Add Vertex
// ----------

TYPED_TEST(TestGraph, add_vertex_1) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    ASSERT_EQ(num_vertices(g) , 1);
}
TYPED_TEST(TestGraph, add_vertex_2) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    graph_type g2(g);
    vertex_descriptor vdB = add_vertex(g2);

    ASSERT_EQ(num_vertices(g2) , 2);
}

TYPED_TEST(TestGraph, add_vertex_3) {
    TEST_TYPES

    graph_type g;

    for(int i = 0; i < 1000; i++)
        add_vertex(g);

    ASSERT_EQ(num_vertices(g) , 1000);
}

// -----------------
// Adjacent Vertices
// -----------------

TYPED_TEST(TestGraph, adjacent_vertices_1) {
    TEST_TYPES

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

TYPED_TEST(TestGraph, adjacent_vertices_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    add_edge(vdA, vdA, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    
    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 1);
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    ASSERT_EQ(e, b);

}
TYPED_TEST(TestGraph, adjacent_vertices_3) {
    TEST_TYPES

    graph_type g;
  
    vertex_descriptor vdA = add_vertex(g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    
    ASSERT_EQ(num_vertices(g), 1);
    ASSERT_EQ(num_edges(g), 0);
    ASSERT_EQ(b,e);

}

// ----
// Edge
// ----

TYPED_TEST(TestGraph, edge_1) {
    TEST_TYPES

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

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}
TYPED_TEST(TestGraph, edge_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdB, vdA, g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);

}
TYPED_TEST(TestGraph, edge_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    add_edge(vdA, vdA, g);
    add_edge(vdA, vdA, g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);
}

// -----
// Edges
// -----

TYPED_TEST(TestGraph, edges_1) {
    TEST_TYPES

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
TYPED_TEST(TestGraph, edges_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edge_descriptor ed = add_edge(vdA, vdA, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    ASSERT_EQ(num_edges(g), 1);
    ASSERT_EQ(num_vertices(g), 1);
    if (b != e) {
        edge_descriptor edt = *b;
        ASSERT_EQ(ed, edt);}
    ++b;
    ASSERT_EQ(e, b);

}
TYPED_TEST(TestGraph, edges_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator b = p.first;
    edge_iterator e = p.second;

    ASSERT_EQ(num_edges(g), 0);
    ASSERT_EQ(num_vertices(g), 1);
    ASSERT_EQ(e,b);


}

// ---------
// Num Edges
// ---------

TYPED_TEST(TestGraph, num_edges_1) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdB, g); //Redundant on purpose

    add_edge(vdB, vdA, g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);

}
TYPED_TEST(TestGraph, num_edges_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(0, es);

}
TYPED_TEST(TestGraph, num_edges_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdB, vdC, g);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);

}

// ------------
// Num Vertices
// ------------

TYPED_TEST(TestGraph, num_vertices_1) {
    TEST_TYPES

    graph_type g;

    ASSERT_EQ(num_vertices(g) , 0);

}
TYPED_TEST(TestGraph, num_vertices_2) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(num_vertices(g) , 1);

}
TYPED_TEST(TestGraph, num_vertices_3) {
    TEST_TYPES

    graph_type g;

    for(int i = 0; i < 100; i++)
            add_vertex(g);

    ASSERT_EQ(num_vertices(g) , 100);

}

// ------
// Source
// ------

TYPED_TEST(TestGraph, source_1) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);

    std::pair<edge_descriptor, bool> epair = add_edge(vdA, vdA, g);

    ASSERT_EQ(source(epair.first, g) , vdA);

}
TYPED_TEST(TestGraph, source_2) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> epair = add_edge(vdB, vdA, g);

    ASSERT_EQ(source(epair.first, g) , vdB);

}
TYPED_TEST(TestGraph, source_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> epair = add_edge(vdC, vdA, g);

    ASSERT_EQ(source(epair.first, g) , vdC);
}

// ------
// Target
// ------

TYPED_TEST(TestGraph, target_1) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);

    std::pair<edge_descriptor, bool> epair = add_edge(vdA, vdA, g);

    ASSERT_EQ(target(epair.first, g) , vdA);

}
TYPED_TEST(TestGraph, target_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<edge_descriptor, bool> epair = add_edge(vdA, vdB, g);

    ASSERT_EQ(target(epair.first, g) , vdB);

}
TYPED_TEST(TestGraph, target_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> epair = add_edge(vdC, vdA, g);

    ASSERT_EQ(target(epair.first, g) , vdA);

}

// ------
// Vertex
// ------

TYPED_TEST(TestGraph, vertex_1) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, vertex_2) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(3, vs);

}
TYPED_TEST(TestGraph, vertex_3) {
    TEST_TYPES

    graph_type g;
    graph_type h(g);

    vertex_descriptor vdA = add_vertex(h);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(0, vs);
}

// --------
// Vertices
// --------

TYPED_TEST(TestGraph, vertices_1) {
    TEST_TYPES

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
TYPED_TEST(TestGraph, vertices_2) {
    TEST_TYPES

    graph_type g;

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;

    ASSERT_EQ(num_vertices(g), 0);
    ASSERT_EQ(e,b);
}
TYPED_TEST(TestGraph, vertices_3) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    ASSERT_EQ(e,b);
}

// -------------------
// Default Constructor
// -------------------

TYPED_TEST(TestGraph, default_constructor_1) {
    TEST_TYPES

    graph_type g;
    ASSERT_EQ(num_vertices(g) , 0);

}
TYPED_TEST(TestGraph, default_constructor_2) {
    TEST_TYPES

    graph_type g;
    ASSERT_EQ(num_edges(g) , 0);

}
TYPED_TEST(TestGraph, default_constructor_3) {
    TEST_TYPES

    graph_type g;
    graph_type h;


    ASSERT_EQ(num_vertices(h) , num_vertices(g));

}

// ----------------
// Copy Constructor
// ----------------

TYPED_TEST(TestGraph, copy_constructor_1) {
    TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);

    graph_type h(g);

    ASSERT_EQ(num_vertices(h) , 1);

}
TYPED_TEST(TestGraph, copy_constructor_2) {
    TEST_TYPES

    graph_type g;
    graph_type h(g);

    vertex_descriptor vdA = add_vertex(g);

    ASSERT_EQ(num_vertices(h) , 0);
}
TYPED_TEST(TestGraph, copy_constructor_3) {
   TEST_TYPES

    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    graph_type h(g);
    vertex_descriptor vdC = add_vertex(h);
    graph_type z(h);

    ASSERT_EQ(num_vertices(z) , 3);
}

// ----------
// Destructor
// ----------

TYPED_TEST(TestGraph, destructor_1) {
    TEST_TYPES

    graph_type g;
}
TYPED_TEST(TestGraph, destructor_2) {
   TEST_TYPES

    {
    graph_type g;
    }
}

TYPED_TEST(TestGraph, destructor_3) {
    TEST_TYPES

    {
    graph_type g;
    graph_type h(g);
    graph_type z = g;
    }
}

// ----------
// Assignment
// ----------

TYPED_TEST(TestGraph, assignment_1) {
    TEST_TYPES

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdB, vdA, g);

    graph_type h = g;

    ASSERT_EQ(num_edges(g), num_edges(h));
    ASSERT_EQ(num_vertices(g) , num_vertices(h));

}
TYPED_TEST(TestGraph, assignment_2) {
    TEST_TYPES

    graph_type g;
    graph_type h = g;

    vertex_descriptor vdA = add_vertex(g);
    add_edge(vdA, vdA, g);

    ASSERT_EQ(num_edges(h), 0);
    ASSERT_EQ(num_vertices(h) , 0);


}
TYPED_TEST(TestGraph, assignment_3) {
    TEST_TYPES

    graph_type g;
    graph_type h = g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(h);

    ASSERT_EQ(num_vertices(g) , 1);
    ASSERT_EQ(num_vertices(h) , 1);

}
