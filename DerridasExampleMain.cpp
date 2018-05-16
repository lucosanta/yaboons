//
// Created by Luca Santonastasi on 30/10/16.
//

#include "src/simulator/FactoryBN.h"

using namespace BNCore;
using namespace BNSimulator;

int main(){

    FactoryBN factory = FactoryBN();

    DerridasAnnealingApprox approx = factory.createDerridasAnnealingApproximationTest(60,200);
    approx.start();


    return 0;
}