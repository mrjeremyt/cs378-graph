// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h



// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream> // cout, endl

using namespace std;
using std::rel_ops::operator!=;

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef pair<vertex_descriptor, vertex_descriptor> edge_descriptor;


        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
        typedef set<edge_descriptor> edge_set;

         // ------------
        // vertex_iterator class
        // ------------
        class vertex_iterator : public iterator<bidirectional_iterator_tag, vertex_descriptor>
        {
            public:
                friend bool operator == (const vertex_iterator& rhs, const vertex_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i);
                }
            private:
                Graph* _g;
                vertex_descriptor _i;
            public:
                vertex_iterator(Graph* g, const vertex_descriptor& i) :
                    _g(g),
                    _i(i)
                    {}

                const vertex_descriptor& operator * () {
                    return _i;
                }
                vertex_iterator& operator ++ () {
                    ++_i;
                    return *this;
                }
                vertex_iterator operator ++ (int) {
                    vertex_iterator temp = *this;
                    ++_i;
                    return temp;
                }
                vertex_iterator& operator -- () {
                    --_i;
                    return *this;
                }
                vertex_iterator operator -- (int) {
                    vertex_iterator temp = *this;
                    --_i;
                    return temp;
                }

        };

        // ------------
        // adjacency_iterator class
        // ------------
        class adjacency_iterator : public iterator<bidirectional_iterator_tag, vertex_descriptor>
        {
            public:
                friend bool operator == (const adjacency_iterator& rhs, const adjacency_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i);
                }
            private:
                Graph* _g;
                edge_set::iterator _i;
            public:
                adjacency_iterator(Graph* g, const edge_set::iterator& i) :
                    _g(g),
                    _i(i)
                    {}

                const vertex_descriptor& operator * () {
                    return (*_i).second;
                }
                adjacency_iterator& operator ++ () {
                    ++_i;
                    return *this;
                }
                adjacency_iterator operator ++ (int) {
                    adjacency_iterator temp = *this;
                    ++_i;
                    return temp;
                }
                adjacency_iterator& operator -- () {
                    --_i;
                    return *this;
                }
                adjacency_iterator operator -- (int) {
                    adjacency_iterator temp = *this;
                    --_i;
                    return temp;
                }

        };

        // ------------
        // edge_iterator class
        // ------------
        class edge_iterator : public iterator<bidirectional_iterator_tag, edge_descriptor>
        {
            public:
                friend bool operator == (const edge_iterator& rhs, const edge_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i) && (rhs._e == lhs._e);
                }
            private:

                void next() {
                    if((unsigned int)_i >= _g->_g.size()) {
                        _e = _g->_g[_g->_g.size()-1].end();
                    }else if((_e != _g->_g[_i].end())) {
                        ++_e;
                        if((_e == _g->_g[_i].end())) next();
                    }else{
                        ++_i;
                        _e = _g->_g[_i].begin();
                        if(_g->_g[_i].empty()) next();
                    }
                }


                Graph* _g;
                vertex_descriptor _i;
                edge_set::iterator _e;
            public:
                edge_iterator(Graph* g, const vertex_descriptor& i, const edge_set::iterator& e) :
                    _g(g),
                    _i(i),
                    _e(e)
                    {}

                const edge_descriptor& operator * () {
                    return *_e;
                }
                edge_iterator& operator ++ () {
                    next();
                    return *this;
                }
                edge_iterator operator ++ (int) {
                    edge_iterator temp = *this;
                    next();
                    return temp;
                }
                edge_iterator& operator -- () {
                    next();
                    return *this;
                }
                edge_iterator operator -- (int) {
                    edge_iterator temp = *this;
                    next();
                    return temp;
                }

        };

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor a, vertex_descriptor b, Graph& g) {
            edge_descriptor e(a, b);
            if(g._g[a].find(e) == g._g[a].end()){  g._g[a].insert(e); ++g._numEdges; return make_pair(e, true); }
            else return make_pair(e, false);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            g._g.push_back(set<edge_descriptor>());
            return g._g.size()-1;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, Graph& g) {
            adjacency_iterator b(&g, g._g[v].begin());
            adjacency_iterator e(&g, g._g[v].end());
            return std::make_pair(b, e);
        }

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor a, vertex_descriptor b, const Graph& g) {
            edge_descriptor e(a, b);
            return make_pair(e, g._g[a].find(e) != g._g[a].end());
        }

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (Graph& g) {
            unsigned int i = 0;
            while(g._g[i].empty() && i < g._g.size()) { i++; }
            edge_iterator b(&g, i, g._g[i].begin());
            edge_iterator e(&g, g._g.size(), g._g[g._g.size()-1].end());
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g._numEdges;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g._g.size();}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {
            return e.first;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {
            return e.second;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type i, const Graph& g) {
            return i;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (Graph& g) {
            return make_pair(vertex_iterator(&g, 0), vertex_iterator(&g, g._g.size()));}

    private:
        // ----
        // data
        // ----

        vector< edge_set > _g; // something like this
        edges_size_type _numEdges;
        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:

        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () : _g(), _numEdges() {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
