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


ostream& operator << (ostream& lhs, const pair<int, int>& rhs){
    return lhs << "(" << rhs.first << "," << rhs.second << ")"; }
    

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
                /**
                 * Checks if two vertex_iterators are equal.
                 * @param rhs first vertex_iterator
                 * @param lhs second vertex_iterator
                 * @return true if equal, false if not
                 */
                friend bool operator == (const vertex_iterator& rhs, const vertex_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i);
                }
            private:
                Graph* _g;
                vertex_descriptor _i;
            public:
                /**
                 * Constructor for vertex_iteator
                 * @param g pointer to graph being itearted on.
                 * @param i vertex position to start at.
                 */
                vertex_iterator(Graph* g, const vertex_descriptor& i) :
                    _g(g),
                    _i(i)
                    {}
                /**
                 * Dereferences vertex_iterator
                 * @return const reference to vertex
                 */
                const vertex_descriptor& operator * () {
                    return _i;
                }
                /**
                 * Pre-increment on iterator.
                 * @return reference to self (*this)
                 */
                vertex_iterator& operator ++ () {
                    ++_i;
                    return *this;
                }
                /**
                 * Post-increment on iterator.
                 * @return copy of this iterator before increment
                 */
                vertex_iterator operator ++ (int) {
                    vertex_iterator temp = *this;
                    ++_i;
                    return temp;
                }
                /**
                 * Pre-decrement on iterator.
                 * @return reference to self (*this)
                 */
                vertex_iterator& operator -- () {
                    --_i;
                    return *this;
                }
                /**
                 * Post-decrement on iterator.
                 * @return copy of this iterator before decrement
                 */
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
                /**
                 * Checks if two adjacency_iterators are equal.
                 * @param rhs first adjacency_iterator
                 * @param lhs second adjacency_iterator
                 * @return true if equal, false if not
                 */
                friend bool operator == (const adjacency_iterator& rhs, const adjacency_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i);
                }
            private:
                Graph* _g;
                edge_set::iterator _i;
            public:
                /**
                 * Constructor for adjacency_iterator
                 * @param g pointer to graph being itearted on.
                 * @param i an edge_set iterator pointing to set of edges for this vertex
                 */
                adjacency_iterator(Graph* g, const edge_set::iterator& i) :
                    _g(g),
                    _i(i)
                    {}
                /**
                 * Dereferences adjacency_iterator
                 * @return const reference to a vertex adjacent to this vertex
                 */
                const vertex_descriptor& operator * () {
                    return (*_i).second;
                }
                /**
                 * Pre-increment on iterator.
                 * @return reference to self (*this)
                 */
                adjacency_iterator& operator ++ () {
                    ++_i;
                    return *this;
                }
                /**
                 * Post-increment on iterator.
                 * @return copy of this iterator before increment
                 */
                adjacency_iterator operator ++ (int) {
                    adjacency_iterator temp = *this;
                    ++_i;
                    return temp;
                }
                /**
                 * Pre-decrement on iterator.
                 * @return reference to self (*this)
                 */
                adjacency_iterator& operator -- () {
                    --_i;
                    return *this;
                }
                /**
                 * Post-decrement on iterator.
                 * @return copy of this iterator before decrement
                 */
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
                /**
                 * Checks if two edge_iterators are equal.
                 * @param rhs first edge_iterator
                 * @param lhs second edge_iterator
                 * @return true if equal, false if not
                 */
                friend bool operator == (const edge_iterator& rhs, const edge_iterator& lhs) {
                    return (rhs._g == lhs._g) && (rhs._i == lhs._i) && (rhs._e == lhs._e);
                }
            private:
                /**
                 * moves the state of the iterator forward.  Used by post and pre-increment
                 * @return void
                 */
                void next() {
                    if((unsigned int)_i == _g->_g.size()-1 && (_e == _g->_g[_g->_g.size()-1].end())) { //|| _e == --_g->_g[_g->_g.size()-1].end())) {
                        return; //_e = _g->_g[_g->_g.size()-1].end();
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
                 /**
                 * Constructor for edge_iterator
                 * @param g pointer to graph being itearted on.
                 * @param i the starting vertex.
                 * @param e starting edge to begin iteration on.
                 */
                edge_iterator(Graph* g, const vertex_descriptor& i, const edge_set::iterator& e) :
                    _g(g),
                    _i(i),
                    _e(e)
                    {}
                /**
                 * Dereferences edge_iterator
                 * @return const reference to an edge_descriptor
                 */
                const edge_descriptor& operator * () {
                    return *_e;
                }
                /**
                 * Pre-increment on iterator.
                 * @return reference to self (*this)
                 */
                edge_iterator& operator ++ () {
                    next();
                    return *this;
                }
                /**
                 * Post-increment on iterator.
                 * @return copy of this iterator before increment
                 */
                edge_iterator operator ++ (int) {
                    edge_iterator temp = *this;
                    next();
                    return temp;
                }

                // edge_descriptor& operator -> () const {
                //     return *_e;}

                /**
                 * Pre-decrement on iterator.
                 * @return reference to self (*this)
                 */
                edge_iterator& operator -- () {
                    next();
                    return *this;
                }
                /**
                 * Post-decrement on iterator.
                 * @return copy of this iterator before decrement
                 */
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
         * @param a vertex_descriptor to the first vertex
         * @param b vertex_descriptor to the second vertex
         * @param g the graph for which to add the edge
         * @return returns a pair of an edge_descriptor and a boolean for successful or not
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
         * @param g graph for which to add the vertex
         * @return returns the vertex_descriptor for the new vertex
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            g._g.push_back(set<edge_descriptor>());
            return g._g.size()-1;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param v vertex_descriptor for which you want the adjacent vertices of
         * @param g the graph for which to get the adjacent vertices from
         * @return returns a pair of adjacency iterators for the beginning and end
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
         * @param a vertex_descriptor of the main vertex
         * @param b vertex_descriptor of the secondary vertex
         * @param g graph for which to get the edge from 
         * @return returns a pair of an edge_descriptor and a boolean
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor a, vertex_descriptor b, const Graph& g) {
            edge_descriptor e(a, b);
            return make_pair(e, g._g[a].find(e) != g._g[a].end());
        }

        // -----
        // edges
        // -----

        /**
         * @param g the graph for which to get the iterator over edges from 
         * @return returns a pair of edge_iterators for the beginning and the end
         */
        friend std::pair<edge_iterator, edge_iterator> edges (Graph& g) {
            unsigned int i = 0;
            while(g._g[i].empty() && i < g._g.size()) { i++; }
            edge_iterator b(&g, i, g._g[i].begin());
            edge_iterator e(&g, g._g.size()-1, g._g[g._g.size()-1].end());
            if(g._numEdges == 0){
                return make_pair(e, e);
            }
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param g the graph for which to get the number of edges from 
         * @return returns the number of edges in the graph
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g._numEdges;}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param g the graph for which to get the number of vertices from 
         * @return returns the number of vertices in the graph
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g._g.size();}

        // ------
        // source
        // ------

        /**
         * @param e edge_descriptor from which to get the source
         * @param g the graph for which to get the source from
         * @return returns the main vertex in an edge
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {
            return e.first;}

        // ------
        // target
        // ------

        /**
         * @param e edge_descriptor from which to get the target
         * @param g the graph for which to get the target from 
         * @return returns the secondary vertex in an edge
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {
            return e.second;}

        // ------
        // vertex
        // ------

        /**
         * @param i index of the graph to get the vertex_descriptor from 
         * @param g graph from which to get the vertex_descriptor from 
         * @return returns the vertex_descriptor at index i
         */
        friend vertex_descriptor vertex (vertices_size_type i, const Graph& g) {
            return i;}

        // --------
        // vertices
        // --------

        /**
         * @param g graph form which to get the vertex iterators from 
         * @return returns a pair of vertex iterators which are the beginning and the end of the graph's vertices
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
         * @return returns a boolean stating whether the condition is valid. This is when the graph is empty
         */
        bool valid () const {
            return _g.size() == 0 && _numEdges == 0;}

    public:

        // ------------
        // constructors
        // ------------

        /**
         * initializes the graph and calls valid to ensure this
         */
        Graph () : _g(), _numEdges() {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
