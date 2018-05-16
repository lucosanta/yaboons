//
// Created by lsantonastasi on 03/10/16.
//

#ifndef BN_SIMULATOR_FACTORYBN_H
#define BN_SIMULATOR_FACTORYBN_H

#include "instance/BooleanNetwork.h"
#include "instance/BooleanNetwork.h"
#include "instance/DerridasAnnealingApprox.h"

namespace BNSimulator {

    class FactoryBN {

    public:

        /**!
         * Constructor
         */
        FactoryBN();

        /**!
         * Method for create a new instance of BooleanNetwork class.
         *
         * \par K inputs per each node
         * \return new instance of a Boolean Network
         */
        static BooleanNetwork createSimpleBooleanInstance(int K);

        /**!
         * Method for create a new instance of BooleanNetwork class.
         *
         * \par K inputs per each node
         * \par nThread number of thread for pool of evaluation
         * \return new instance of a Boolean Network
         */
        static BooleanNetwork createSimpleBooleanInstance(int K, int nThread);

        /**!
         * Method for create a new instance of BooleanNetwork class starting from a file
         *
         * \par path absolute path to the files
         * \par sep separtor of the CSV
         * \return a new boolean network instance
         */
        static BooleanNetwork createSimpleBooleanInstanceFromFile(string path, char sep, BNTypes t, int nThread);

        /**!
         * Method for create a new instance of a Classical Random Boolean Network
         *
         * \par K inputs per node
         * \par p bias of the node
         * \par N number of nodes
         * \return a new CRBN
         */
        static BooleanNetwork createClassicalRandomBooleanNetwork(int K,float p, int N, int nThreadInPool);

        /**!
         * Method for create a new instance of annealing approximation test
         *
         * \param N number of nodes
         * \param times number of tries for each K
         * \return a new instance of DerridasAnnealingApprox class
         */
        static DerridasAnnealingApprox createDerridasAnnealingApproximationTest(int N, int times);

        /**!
         * Method for create a new instance of a Random Boolean Maps
         * which are CRBN with N=K;
         *
         * \par K inputs per node
         * \par p bias of the node
         * \return a new random boolean maps
         */
        static BooleanNetwork createRandomBooleanMaps(int K, int p);

        /**!
         * Method for create a new instance of an Asynchronous Random Boolean Network
         *
         * \par K inputs per node
         * \par p bias of the node
         * \return a new asynchronous random boolean network
         */
        static BooleanNetwork createAsynchronousRandomBooleanMaps(int K, int p);

        /**!
         * Method for create a new instance of a Deterministic Asynchronous RBN
         *
         * \par K inputs per node
         * \par p bias of the node
         * \par N number of nodes
         *
         * \return a new deterministic asynchronous random boolean network
         */
        static BooleanNetwork createDeterministicAsyncRandomBooleanNetwork(int K, float p, int N);
    };

}
#endif //BN_SIMULATOR_FACTORYBN_H
