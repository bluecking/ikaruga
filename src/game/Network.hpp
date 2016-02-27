/*
 * Network.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#ifndef SRC_NETWORK_HPP_
#define SRC_NETWORK_HPP_

#include "StaticRenderable.hpp"
#include "Vector.hpp"

#include <string>
#include <tuple>
#include <vector>

using std::string;
using std::pair;
using std::vector;

namespace jumper {

    /**
     * A class to store and render a network of paths and
     * nodes (i.e. a graph)
     */
    class Network : public StaticRenderable {
    public:
        /***
         * Constructor.
         *
         * @param renderer		A SDL renderer to render the graph
         * @param graphFile		A file containing the graph definition
         */
        Network(SDL_Renderer *renderer, string graphFile);

        /// Renders the graph
        virtual void render();

        /// Destructor.
        virtual ~Network();

        /// Returns the nodes
        const vector<Vector2i> &getNodes() { return m_nodes; }

        /// Returns the edges
        const vector<pair<unsigned int, unsigned int> > &getEdges() { return m_edges; }

        /// Returns the index of the goal node
        unsigned int getGoal() const {
            return m_goal;
        }

        /// Sets the index of the goal node
        void setGoal(unsigned int goal) {
            m_goal = goal;
        }

        /// Returns the index of the start node
        unsigned int getStart() const {
            return m_start;
        }

        /// Sets the index of the start node
        void setStart(unsigned int start) {
            m_start = start;
        }

    private:

        /// Parse the graph file and fill up m_nodes and m_edges
        void parseGraphFile(string file);

        /// The graph nodes
        vector<Vector2i> m_nodes;

        /// The connections
        vector<pair<unsigned int, unsigned int> > m_edges;

        /// The index of the start vertex
        unsigned int m_start;

        /// The index of the goal vertex
        unsigned int m_goal;

    };

} /* namespace jumper */

#endif /* SRC_NETWORK_HPP_ */
