//
// Created by lsantonastasi on 05/09/16.
//

#ifndef BN_SIMULATOR_NODES_H
#define BN_SIMULATOR_NODES_H

#include "Node.h"
#include <vector>
#include <stdlib.h>

namespace BNCore {

    /**!
     *
     * \author Luca Santonastasi
     *
     * Class that deserves as an aggregator of nodes
     *
     */
    class Nodes {

    public:

        /**!
         *  Default Constructor
         */
        Nodes() ;

        /**!
         *  Constructor for a fixed number of Node
         *
         *  \param N number of nodes of the network
         */
        Nodes(int N);

        /**!
         *  Constructor for a BN with fixed K and fixed number of Node
         *
         *  \param K inputs per each node
         *  \param N number of nodes of the network
         */
        Nodes(int K, int N);

        /**!
         *  Constructor for a RBN
         *
         *  \param K inputs per each node
         *  \param p bias of the nodes
         *  \param N total number of the nodes
         *  \param generate true if you want to generate in constructor, false otherwise
         */
        Nodes(int K, float p, int N, bool generate);

        /**!
         * Add a new node to nodesList
         *
         * @param n node to be added
         */
        void addNode(Node n);


        /**!
         * Get the vector of BN nodes
         *
         * \return List of nodes
         */
        vector<Node> getNodes() ;

        /**!
         *  Set a new vector as the new node list
         *
         * \param newVector new list to be setted
         */
        void setNodes(vector<Node> newVector) ;


        /**!
         * Set a node at a fixed position
         *
         * \param n node to be setted
         * \param position where to set the node
         */
        void setNodeAtPosition(Node n, int position);


        /**!
         * Function for generate a RBN node list and connection
         *
         * \return parameters instance of generated parameter
         */
        void generateNodesAndConnections();

        /**!
         *
         * \return
         */
        vector<string> getNetworkAsVectorString();

        Nodes getInputNodes();

        Nodes getOutputNodes();

    private:

        /**!
         * List of nodes
         */
        vector<Node> nodesList;

        /**!
         * Support vector for list of connection
         */
        vector<string> connection;

        int actualNodeNumbers= 0;

        /**!
         * Number of nodes
         */
        int numberOfNodes;


        /**!
         * Number of inputs for each node
         */
        int inputsPerNode;


        /**!
         * bias of each node
         */
        float bias;


        /**!
         * Support function for setting node connection
         *
         * \param node
         * \param i
         */
        void setNodeConnection(Node node, int i);

        /**!
         * Support function for check if a connection already exists and created for following
         * Kauffman directive upon connection between nodes in a classical RBN
         *
         * \param v Vector with all identificator not permitted
         * \param y Times recalling checkId
         *
         * \return allowed position for a connection
         */
        int checkId(vector<string> v, int y);

    };
}


#endif //BN_SIMULATOR_NODES_H
