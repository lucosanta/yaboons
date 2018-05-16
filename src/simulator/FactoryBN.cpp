//
// Created by lsantonastasi on 03/10/16.
//

#include "FactoryBN.h"



namespace BNSimulator {


    FactoryBN::FactoryBN() {}

    BooleanNetwork FactoryBN::createSimpleBooleanInstance(int K) {
        return BooleanNetwork(K);
    }

    BooleanNetwork FactoryBN::createSimpleBooleanInstance(int K,int nThread) {
        return BooleanNetwork(K,0.0,20,BNTypes::BN,nThread);
    }


    BooleanNetwork FactoryBN::createSimpleBooleanInstanceFromFile(string path, char sep, BNTypes t, int nThread) {
        return BooleanNetwork(path,sep,t,nThread);
    }



    BooleanNetwork FactoryBN::createClassicalRandomBooleanNetwork(int K, float p, int N, int nThreadInPool) {
        return BooleanNetwork(K,p,N,BNTypes::CRBN, nThreadInPool);
    }

    DerridasAnnealingApprox FactoryBN::createDerridasAnnealingApproximationTest(int N,int times) {
        return DerridasAnnealingApprox(N,times);
    }

    BooleanNetwork FactoryBN::createRandomBooleanMaps(int K, int p) {
        return BooleanNetwork(K,p,K,BNTypes::CRBN);
    }

    BooleanNetwork FactoryBN::createAsynchronousRandomBooleanMaps(int K, int p) {
        return BooleanNetwork(K,p,K,BNTypes::ARBN);
    }

    BooleanNetwork FactoryBN::createDeterministicAsyncRandomBooleanNetwork(int K, float p, int N){
        return BooleanNetwork(K,p,N,BNTypes::DARBN);
    }
}