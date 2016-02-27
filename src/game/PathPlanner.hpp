#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>

#include "Network.hpp"
#include "Vector.hpp"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/astar_search.hpp>


namespace jumper {

    using namespace boost;
    using namespace std;

/// We are using floats to represent costs in the graph
    typedef float CostT;

// The graph is represented with an undirected adjacency list without
// vertex costs and CostT for edge costs
    typedef adjacency_list<listS, vecS, undirectedS, no_property, property<edge_weight_t, CostT> > MutableGraph;

// A suitable property map for edge weights (given our parameterization of the
// graph structure
    typedef property_map<MutableGraph, edge_weight_t>::type WeightMap;

// The vertex descriptor type for our graph
    typedef MutableGraph::vertex_descriptor VertexDescriptor;

// The edge descriptor for our graph
    typedef MutableGraph::edge_descriptor EdgeDescriptor;


    /**
     * @brief A class to plan shortest paths in a graph using the A* algorithm
     */
    class PathPlanner {
    public:

        /**
         * Creates a path planner instance for the given graph
         *
         * @param net the network
         */
        PathPlanner(Network *net);

        /**
         * @brief plans a path
         * @description Plans a path from \ref startIndex to \ref endIndex.
         *              The generated path can by extracted with \ref getSolution().
         *
         * @param startIndex the start index
         * @param endIndex the end index
         */
        void planPath(int startIndex, int endIndex);

        /**
         * the computed solution path
         *
         * @returns the computed solution path
         */
        const std::list<Vector2f> &getSolution() { return m_solutionpath; };

    private:

        /// The shortest path (series of vertex positions)
        std::list<Vector2f> m_solutionpath;

        /// The vertex position array
        Vector2f *m_nodes;

        /// The graph structure
        MutableGraph m_graph;

        /// A weight map
        WeightMap m_weightmap = get(edge_weight, m_graph);

    };


}

#endif
