//
// Created by lsantonastasi on 21/09/16.
//

#ifndef BN_SIMULATOR_INPUTTABLE_H
#define BN_SIMULATOR_INPUTTABLE_H

#include <string>
#include <vector>

using namespace std;


namespace BNCore {

    /**!
     * \author Luca Santonastasi
     *
     * Class that creates a list with every combination related to inputs per node
     * defined in RBN constructor.
     *
     */
    class InputTable {

    public:

        /**!
         * Constructor
         */
        InputTable();

        /**!
         * Constructor
         *
         * \param K inputs per node of RBN
         */
        InputTable(int K);


        /**!
         * Gets inputs per node of actual instance
         *
         * \return inputs per node setted  in constructor
         */
        int getInputPerNode();


        /**!
         * Gets list of input combination for LookupTable
         *
         * \return list of all combination of binary defined by K
         */
        vector <string> getInputsCombination();

        /**
         * Utility function for converting an integer to a representation of binary value in string
         * It uses recursion
         *
         * \param s : integer to be converted
         * \param v : actual string version of the conversion
         * \return string :representation of binary value in string
         */
        string convertToBinary(int s,string v);

    private:


        /**!
         * Inputs per node
         */
        int K;


        /**!
         * length of the vector;
         */
        int length;


        /**!
         * List of all combination in binary form
         */
        vector <string> inputs;


        /**
         *  Initialization init function
         */
        void init();


    };
}

#endif //BN_SIMULATOR_INPUTTABLE_H
