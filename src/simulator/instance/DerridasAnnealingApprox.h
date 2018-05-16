//
// Created by lsantonastasi on 22/09/16.
//

#ifndef BN_SIMULATOR_DERRIDASANNEALINGAPPROX_H
#define BN_SIMULATOR_DERRIDASANNEALINGAPPROX_H

#include <vector>
#include <string>
#include "BooleanNetwork.h"

using namespace BNCore;


namespace BNSimulator {

    /**!
     * \author Luca Santonastasi
     *
     * This simulator is inspired to article:
     *
     * "Perturbation Propagation in random and evolved Boolean Network"
     * Christoph Fretter, Agnes Szejka, Barbara Drossel
     *
     */
    class DerridasAnnealingApprox {


    public:

        /**!
         * Constructor
         *
         * \param N
         * \param times
         */
        DerridasAnnealingApprox(int N,int times);

        /**!
         *
         */
        void start();

    private:

        /**!
         *
         */
        vector<int> inputs;

        /**!
         *
         */
        int times=0;

        /**!
         *
         */
        vector<float> av0_list = vector<float> ();

        /**!
         *
         */
        vector<float> av1_list = vector<float> ();

        /**!
         *
         * \return
         */
        int hammingDistance(string,string);

        /**!
         *
         */
        int numberOfNodes;

        /**!
         * Function that parametrize the computation fro computing Derrida's plot
         *
         * \param N number of nodes
         * \param K inputs per node
         * \param p bias of the network
         * \param it number of iteration
         */
        void k(int N,int K,float p, int it);
    };

}
#endif //BN_SIMULATOR_DERRIDASANNEALINGAPPROX_H
