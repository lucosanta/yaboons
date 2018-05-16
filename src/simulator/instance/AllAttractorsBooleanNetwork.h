//
// Created by lsantonastasi on 15/10/16.
//

#ifndef BN_SIMULATOR_ALLATTRACTORSBOOLEANNETWORK_H
#define BN_SIMULATOR_ALLATTRACTORSBOOLEANNETWORK_H

#include "BooleanNetwork.h"
#include "BooleanNetwork.h"

using namespace BNCore;

namespace BNSimulator {

    /**!
     * \author Luca Santonastasi
     *
     */
    class AllAttractorsBooleanNetwork {

    public:
        /**!
         *
         * \param n
         */
        AllAttractorsBooleanNetwork(BooleanNetwork n);

        /**!
         *
         * \param n
         */
        AllAttractorsBooleanNetwork(BooleanNetwork n, bool wantFile);

        /**!
         *
         */
        vector< StateSuccession> start();

    private:

        /**!
         *
         */
        vector< StateSuccession> attractors;

        /**!
         *
         */
        BooleanNetwork bn;


        bool createGraphvizFile = true;
        /**!
         *
         *
         * \param n
         * \param s
         * \return
         */
        States convertToStates(Nodes n,string s);

    };

}
#endif //BN_SIMULATOR_ALLATTRACTORSBOOLEANNETWORK_H
