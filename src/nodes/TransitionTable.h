//
// Created by lsantonastasi on 21/09/16.
//

#ifndef BN_SIMULATOR_LOOKUPTABLE_H
#define BN_SIMULATOR_LOOKUPTABLE_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "InputTable.h"

using namespace std;

namespace BNCore {

    /**!
     * \author Luca Santonastasi
     *
     * Class that represent an instance of Transition Table for Node
     *
     */
    class TransitionTable {

    public:

        /**!
         * Empty constructor
         */
        TransitionTable();


        /**!
         * Constructor
         *
         * @param K inputs per node
         * @param p bias
         */
        TransitionTable(int K, float p);


        /**!
         * Get the related inputs per node of the RBN
         *
         * \return inputs per node for current LookupTable instance
         */
        int getInputsPerNode();


        /**!
         * Get actual value of the bias
         *
         * \return bias actual value
         */
        float getBias();

        /**!
         *
         * \return
         */
        vector<int> getListResult();

        /**!
         *
         * @param l
         */
        void setListResult(vector<int> l);

        /**!
         * \param res
         */
        void addAResult(int res);


        /**!
         * Get the associated result ti a string input searched inside the map
         *
         * \param input key of the map
         * \return value sassociated to input
         */
        int getResult(string input);

        /**!
         * Function which set a new value in map for a fixed key
         *
         * \param key : position to be changed
         * \param res : value to be setted
         * \param isListToBeChanged : parameter that modifies list at position if true, otherwise doesn't change
         * \return if key is present true, false otherwise
         */
        bool setResultForKey(int key, int res, bool isListToBeChanged);
        bool setResultForKey(string s, int res, bool isListToBeChanged);

        /**!
         * Function that resets current instance of Transition Table
         */
        void reset();

    private:

        /**!
         * Map that represent the lookup table instance
         */
        unordered_map<string,int> lookup;

        /**!
         * List that contains all result of current instance
         */
        vector<int> listResult;

        /**!
         * Number of inputs per node of the RBN
         */
        int inputsPerNode;

        /**!
         * Instance that keeps the input part of the transition table
         */
        InputTable t;


        /**!
         * Bias of the net
         */
        float bias;


        /**!
         * Function for init LookupTable instance
         */
        void init();


    };
}


#endif //BN_SIMULATOR_LOOKUPTABLE_H
