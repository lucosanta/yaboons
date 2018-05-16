//
// Created by lsantonastasi on 12/09/16.
//

#ifndef BN_SIMULATOR_PARAMETERS_H
#define BN_SIMULATOR_PARAMETERS_H

//#include <vector>

#include "State.h"
#include "../exceptions/Exception.h"

#include "../nodes/Nodes.h"

#include <unordered_map>

using namespace std;


namespace BNCore {


    /**!
     *
     * \author Luca Santonastasi
     *
     * Class that represent the entire set of State
     *
     */
    class States {


    public:

        /**!
         * Constructor
         */
        States();

        /**!
         * Constructor
         *
         * \param nStates number of states to instantiate
         */
        //TODO check if useful
        States(int nStates);

        /**!
         * Function for adding a parameter to the list
         *
         * \param s State to be added to list
         */
        void addState(State s);


        /**!
         * Get the current list of parameters
         *
         * \return list of parameter
         */
        unordered_map<int,State> getStates();

        /**!
         * Set a new parameters list
         *
         * \param pList new list to be setted
         */
        void setStates(unordered_map<int,State> pList) ;

        /**!
         * Print all parameters id and values
         */
        void print() ;

        /**!
         * Function to generate random parameters
         *
         * \param nParameters number of how many parameters to create and add to list
         */
        void generateRandomStates(Nodes n) ;

        /**!
         * Changing a parameter at a fixed position
         *
         * \param par PArameter to be setted at fixed position
         * \param position position inside the list
         */
        void setStateAtPosition(State par, int position);

        /**!
         * Utility function for appending a vector of parameter to current parameter vector
         *
         * \param p Vector to append
         */
         //TODO check if useful
        //void appendListStates(vector<State> p);


        /**!
         * Support function that returns entire set of current state which belong to list
         * as a unique string
         *
         * \return entire set of current state which belong to list as a unique string
         */
        string toString();

        /**!
         * Operator to check if two different states are equals
         *
         * @param s States that has to be checked
         * @return true if equals, false otherwise
         */
        bool operator==(States s) {
            if (toString() == s.toString()) {
                return true;
            }
            return false;
        }


    protected:

    private:

        /**!
         * List of parameter
         */
        unordered_map <int,State> stateList;

        //TODO check if useful
        int nextPositionNumber = 0;

        string statesToString = "";

    };


}


#endif //BN_SIMULATOR_PARAMETERS_H
