//
// Created by lsantonastasi on 05/09/16.
//

#ifndef BN_SIMULATOR_NODE_H
#define BN_SIMULATOR_NODE_H

#include <string>
#include <vector>
#include "TransitionTable.h"
#include "NodeType.h"
#include <cmath>

using namespace std;


namespace BNCore {


    /**!
     * \author Luca Santonastasi
     *
     * Class that represent a single Node of the Boolean Network
     */
    class Node{

    public:

        /**!
         * Constructor
         * \param id identificator of Node
         */
        Node(string id);

        /**!
         * Constructor
         * \param id identificator of Node
         * \param t object of node type
         */
        Node(string id, NodeType t);

        /**!
         * Constructor
         *
         * \param id identificator of Node
         * \param K number of inputs this node has
         */
        Node(string id,int K);

        /**!
         * Constructor
         *
         * \param id identificator of Node
         * \param K number of inputs this node has
         */
        Node(string id,int K, NodeType t);

        /**!
         * Constructor
         *
         * \param id identificator of Node
         * \param K number of inputs this node has
         * \param p probability that an entry of Node's transition table has 1
         */
        Node(string id,int K,float p);

        /**!
         * Constructor
         *
         * \param id identificator of Node
         * \param K number of inputs this node has
         * \param p probability that an entry of Node's transition table has 1
         */
        Node(string id,int K,float p, NodeType t);


        /**!
         * Set the current identificator value
         *
         * \param id identificator value
         */
        void setIdentificator(string id) ;

        /**!
         * Get the current identificator values
         *
         * \return identificator's value
         */
        string getIdentificator() ;

        /**!
         * Add a new connection to the Node
         *
         * \param n New node connection
         */
        void addConnection(Node n);

        /**!
         * Reset connection fro the actual node
         */
        void resetConnection();

        /**!
         * Gets the actual list of connections of RBNode
         *
         * \return list of connections
         */
        vector<Node> getConnections();

        /**!
         * Check whether transition table is set or not
         * @return
         */
        bool isTransitionTableSet();

        /**!
         * Method that set transition result inside TransitionTable instance of current node
         *
         * \param tVectorAfter vector that contains result of the transition table
         */
        void setTransitionTableResult(vector <int> tVectorAfter);

        /**!
         * Function that retrieves current instance of TransitionTable
         *
         * \return TransitionTable instance
         */
        TransitionTable getTransitionTable();

        /**!
         * Function that set the TransitionTable instance to a new one
         *
         * \param t new TransitionTable instance for current node
         */
        void setTransitionTable(TransitionTable t);

        /**!
         * Support function that gives a list of string containing a Graphviz version of connection
         *
         * \return list of string
         */
        vector<string> getStringVectorConnection() ;

        /**!
         * Returns a string that consist in the representation of current Node
         * instance for saving in a configuration file
         *
         * \return
         */
        string getNodeAsAString();

        /**!
         * Function that return the type of the current node
         *
         * \return
         */
        NodeType getNodeType();

        /**!
         * Function that set the type of the function
         *
         * \param t
         */
        void setNodeType(NodeType t);

        int getNumber();

        void setNumber(int n);




    private:

        /**!
         * Number of inputs this node has
         */
        int inputsPerNode;

        /**!
         * Instance of TransitionTable
         */
        TransitionTable transitionTable;

        /**!
         *
         */
        float bias;

        /**!
         * Boolean flag that points out if this node has a transition table set
         */
        bool isTransitionTableToBeSet;

        /**!
         * Identificator of the parameter modified
         */
        string identificator;

        /**!
         * Point out if the node is a input node or an output node
         * If generic it can be used for both scopes
         */
         NodeType nodeType;

        /**!
         * List of connections
         */
        vector<Node> connections;

        int number;

        /**!
         * Support function that converts an integer to a string in binary form
         *
         * \param n current int value
         * \param s current binary string value
         * \return string binary version of integer passed
         */
        string convertToBinary(int n, string s);

    };
}

#endif //BN_SIMULATOR_NODE_H
