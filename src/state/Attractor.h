//
// Created by lsantonastasi on 11/10/16.
//

#ifndef BN_SIMULATOR_ATTRACTORS_H
#define BN_SIMULATOR_ATTRACTORS_H

#include "States.h"

namespace BNCore {

    /**!
     * \author Luca Santonastasi
     *
     * After a transient, some states will be repeated and this repetition is called Attractor of the BN
     * and it can be classified as a Cycle attractor with a period tau > 1 and Point attractor with tau = 1, called also Fixpoint.
     * The set of initial state that flow to an attractor is named \textit{basins of attraction}.
     * An \textit{attractor} is considered \textit{stable} if, mantaining the connections fixed between nodes and perturbing the value of a node, after some updates  most of the nodes
     * assume the same values as before the perturbation.In biology this phenomenon is named \textit{homeostasis}.
     */
    class Attractor {

    public:

        /**!
         * Constructor
         *
         */
        Attractor();

        /**!
         * Set current list of States that represent attractor to a new one
         *
         * \param n new Attractor
         */
        void setAttractors(vector<States> n);

        /**!
         * Obtain current list of States that represent attractor
         *
         * \return
         */
        vector<States> getAttractors();

        /**!
         * Add a states to current list of this attractor
         *
         * \param s
         */
        void addStatesToAttractorList(States s);


        /**!
         * Operator for checking the equivalence between Attractors
         *
         * \param attr Attractor to be checked
         * \return if are equals returns true, false otherwise
         */
        bool operator==(Attractor attr);


    private:
        vector<States> attractorList;
    };
}

#endif //BN_SIMULATOR_ATTRACTORS_H
