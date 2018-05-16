//
// Created by lsantonastasi on 12/09/16.
//

#ifndef BN_SIMULATOR_PARAMETER_H
#define BN_SIMULATOR_PARAMETER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace BNCore {

    /**!
      * \author Luca Santonastasi
      */
    class State {


    public:
        /**!
         * Constructor
         */
        State();

        /**!
         * Constructor
         *
         * \param id name of the parameter
         * \param v boolean value of the identificator
         */
        State(string id,int v);

        /**!
         * Constructor
         *
         * \param id name of the parameter
         * \param v boolean value of the identificator
         */
        State(string id,int v,int pos);

        /**!
         *  Get identificator name value
         *
         * \return identificator name
         */
        string getIdentificator();

        /**!
         *  Set the new identificator name value
         *
         *  \param newIdentificator identificator string to be setted
         */
        void setIdentificator(string newIdentificator);

        /**!
         *  Get the current value of the parameter
         *
         * \return value of the parameter
         */
        int getValue();

        /**!
         *  Set the new parameter's value
         *
         *  \param newValue value to be setted
         */
        void setValue(int newValue);

        /**!
         * Get current position of the current instance of the State
         *
         * \return
         */
        int getPosition();

        /**!
         * Set the new position for current instance of the State
         *
         * \param pos new position for current state
         */
        void setPosition(int pos);

        /**!
         * Print id and value of current State
         */
        void print() ;

    private:

        /**!
         * name of the parameter
         */
        string identificator;

        /**!
         * boolean value of the identificator
         */
        int value;

        /**!
         * position of current state inside States
         */
        int position;
    };

}

#endif //BN_SIMULATOR_PARAMETER_H
