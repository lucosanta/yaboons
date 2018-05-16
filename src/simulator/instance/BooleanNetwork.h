//
// Created by lsantonastasi on 12/09/16.
//

#ifndef BN_SIMULATOR_RANDOMBOOLEANNETWORK_H
#define BN_SIMULATOR_RANDOMBOOLEANNETWORK_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "../../state/States.h"
#include "../../output/BNOutput.h"
#include "../../exceptions/Exception.h"
#include "../BNTypes.h"
#include "../../evaluation/Updater.h"

using namespace BNCore ;


namespace BNSimulator {


    struct Tuple{
    public:
        int occurences;
        int position;

        Tuple()
        {
            occurences = 0;
            position = -1;
        }

        Tuple(int x, int y){
            occurences = x;
            position = y;
        }

    };

    /**!
     * \author Luca Santonastasi
     */
    class BooleanNetwork {

    public:
        /**!
         * Default constructor
         */
        BooleanNetwork();

        /**!
         * Default constructor
         */
        BooleanNetwork(int K);

        /**!
         * Constructor
         *
         * \param path where to find the file (absolute path)
         * \param sep char version separator for CSV file configuration
         */
        BooleanNetwork(string path, char sep, BNTypes t, int nThread);

        /**!
         * Constructor
         *
         * \param K inputs per node
         * \param p bias
         */
        BooleanNetwork(int K, float p, int N, BNTypes type);

        /**!
         * Constructor which will be used in case of you want to set the value
         * of the number of thread in pool
         *
         * \param K inputs per node
         * \param p bias
         * \param N number of nodes
         * \param type network type
         * \param nThreadInPool number of thread in pool
         */
        BooleanNetwork(int K,float p, int N,BNTypes type,int nThreadInPool);

        /**!
         * Function mandatory for start a new boolean network
         *
         * \param s initial state for current BNSimulator instance
         */
        void setInitialState(States s);

        /**!
         * Method for start the evaluation of Boolean Network
         *
         * \param nIteration
         * \return output of the network
         */
        BNOutput start(int nIteration,  bool showMeGen);

        /**!
         *
         * \param h how many state has to change
         */
        void flip(int h);

        /**!
         * Function for getting information about structure of the network
         *
         * \return the structure of the nodes
         */
        Nodes getNodes();

        /**!
         * Function for set information about structure of the network
         *
         * \param rbn new RBN to be set
         */
        void setNodes(Nodes rbn) ;


        /**!
         * Set current name of the Boolean Network instance
         *
         * \param name
         */
        void setName(string name);

        /**!
         * Get current name of the Boolean Network instance
         *
         * \return
         */
        string getName();

    private:

        /**!
         *
         */
         string name;

        /**!
         * field that let the start method run when called
         */
        bool isInitialStateSet;

        /**!
         * field that check if the topology if set or not
         */
        bool isTopologyDefined;

        /**!
         *
         */
        int nIteration;

        /**!
         * Number of inputs for every node of the Random Boolean Network
         */
        int inputsPerNode;

        /**!
         *
         */
        BNTypes types;

        /**!
         * Probability that an entry as 1 or 0 in the truth table
         */
        float bias;

        /**!
         *
         */
        bool set = false;

        /**!
         * Aggregator of all parameters of Boolean Network
         */
        States pars;

        /**!
         * Aggregator of all nodes of Boolean Network
         */
        Nodes nodes;

        /**!
         * Number of attractors after current execution of RBN.
         */
        int attractorsLength;

        /**!
         *
         */
        int numberOfNodes;

        /**!
         *
         */
        int nThreadForEvaluation;

        /**!
         * string for identificate the char for separate string in CSV file
         */
        char CSVseparator;

        /**!
         *
         */
         Updater e;

        /**!
         *
         */
         bool isFromFile = false;


        /**!
         * Function for init Boolean network
         *
         * \param file
         */
        void initBNSimulator(string path);

        /**!
         *
         * @param s
         * @param delim
         * @param elems
         */
        void split(const string &s, char delim, vector<string> &elems);

        /**!
         *
         * @param s
         * @param delim
         * @return
         */
        //TODO
        vector<string> splits(const string &s, char delim);



        /**!
         *
         */
        map<string,Tuple> attractorsChecker;

        /**!
         * Function for init RBN
         */
        void init();

        /**!
         * Function used for evaluation result of current RBN
         *
         * \par currentIt
         * \return next generation of parameters
         */
        States eval(int currentIt, bool showMeGen);

    };

}



#endif //BN_SIMULATOR_RANDOMBOOLEANNETWORK_H
