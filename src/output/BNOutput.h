//
// Created by lsantonastasi on 12/09/16.
//

#ifndef BN_SIMULATOR_BNGENERATION_H
#define BN_SIMULATOR_BNGENERATION_H

#include <fstream>
#include "../state/States.h"
#include "../state/Attractor.h"
#include "../state/StateSuccession.h"

namespace BNCore {

    /**!
     * \author Luca Santonastasi
     *
     * Class that gives multiple ways to print output
     *
     */
    class BNOutput {


    public:

        /**!
         * Constructor
         */
        BNOutput();

        /**!
         * Get current instance of state succession
         *
         * \return state succession
         */
        StateSuccession getSuccession();

        /**!
         * Set instance of state succession
         *
         * \param newSucc new instance set
         */
        void setSuccession(StateSuccession newSucc);

        /**!
         * Get structure of the network
         *
         * \return structure of the network
         */
        Nodes getStructure();

        /**!
         * Set structure of the network
         *
         * \param s new structure of the network
         */
        void setStructure(Nodes s);


        /**!
         * Print all parameters id and values
         */
        void print();

        /**!
         * Gets the list of states
         *
         * \return list of states succession
         */
        vector<string> getListGeneration();

        /**!
         * Save a Graphviz file in output folder with State Succession Graph
         */
        void printGraphvizFile();

        /**!
         *
         */
        void printGraphvizFileAll(vector< vector<BNCore::States> > vvS);

        /**!
         * Save a CSV file for configuration of a BN
         *
         * \return filename of the configuration file for BN
         */
        string printConfigurationFileActualBooleanNetwork();


        /**!
         * Save a Graphviz file with the structure of BN
         */
        void printGraphvizBooleanNodes();

        /**!
         * Return list of States of current succession
         *
         * \return list of States
         */
        vector <States> getSuccessionStates();

        /**!
         * Set a new succession list.
         * Warning: if you set the list with this method, StateSuccession instance will not be updated
         * Use only for graph purpose
         *
         * @param newSucc
         */
        void setSuccessionList(vector <States> newSucc);



    private:

        /**!
         * List of parameter
         */
        vector <States> statesList;

        /**!
         * Structure of the network
         */
        Nodes instanceBN;

        /**!
         * State succession of the network
         */
        StateSuccession succession;



    };
}


#endif //BN_SIMULATOR_BNGENERATION_H
