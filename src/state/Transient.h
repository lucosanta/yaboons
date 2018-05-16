//
// Created by Luca Santonastasi on 29/10/16.
//

#ifndef BN_SIMULATOR_TRANSIENT_H
#define BN_SIMULATOR_TRANSIENT_H

#include <algorithm>
#include "States.h"

namespace BNCore {
    /**!
     * \author Luca Santonastasi
     *
     *
     */
    class Transient {

    public:

        /**!
         * Constructor
         *
         */
        Transient();

        /**!
         * Set current list of States that represent transient to a new one
         *
         * \param n new Attractor
         */
        void setTransient(vector <States> n);

        /**!
         * Obtain current list of States that represent transient
         *
         * \return
         */
        vector <States> getTransient();

        /**!
         * Add a states to current list of this transient
         *
         * \param s
         */
        void addStatesToTransientList(States s);


        /**!
         * Methods that delete an item from current list
         *
         * \param i position of the item to be deleted
         */
        void removeStatesFromTransientList(States s);


    private:
        vector <States> transientList;
    };
}

#endif //BN_SIMULATOR_TRANSIENT_H
