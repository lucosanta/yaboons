//
// Created by Luca Santonastasi on 04/01/17.
//

#ifndef YABOONS_TASKFITNESS_H
#define YABOONS_TASKFITNESS_H


#include <string>
#include "../state/State.h"
#include "../state/States.h"
#include "../output/BNOutput.h"
#include "../simulator/instance/BooleanNetwork.h"


namespace BNUtils {

    struct TaskFitnessResult {
        int hammingDistance;
    };

    struct TaskFitness {
        typedef TaskFitnessResult result_type;

        TaskFitness(BNSimulator::BooleanNetwork _bn, BNCore::States ss) :
                bn(_bn),
                states(ss) {
            nNodes = (int)bn.getNodes().getNodes().size();
        }

        result_type operator()() {
            result_type result;

            const clock_t single_time = clock();

            int hdTot = 0;

            vector<double> binaryV = vector<double>();
            binaryV.clear();
            for(int is = 0; is < states.getStates().size(); is++){
                binaryV.push_back(0.0);
            }

            int counterOne = 0;

            for(int is = 0 ; is < states.getStates().size(); is++) {
                if(states.getStates().at(is).getValue() == 1) {
                    counterOne ++;
                }
            }

            bn.setInitialState(states);

            //const clock_t only_RBN = clock();
            BNCore::BNOutput output = bn.start(0,false);
            //cout << "Execution time of RBN with " << states.toString() <<" is: " << float( clock () - only_RBN ) /  CLOCKS_PER_SEC << " seconds "<< endl;


            vector<BNCore::States> vS = output.getSuccession().getAttractor().getAttractors();

            for(int k = 0; k < vS.size(); k++){
                BNCore::States attr = vS.at(k);
                for(int z = 0; z < attr.getStates().size(); z++) {
                    binaryV[z] += (((double)attr.getStates().at(z).getValue())/vS.size());
                }
            }

            for(int l = 0 ; l< binaryV.size(); l++){
                double v = binaryV[l]+0.5;
                int val = (int)v;

                if(counterOne <= nNodes/2) {
                    if (val != 0) {
                        hdTot++;
                    }
                } else {
                    if (val != 1) {
                        hdTot++;
                    }
                }

            }
            binaryV.clear();

            cout << "Execution time of state " << states.toString() <<" is: " << float( clock () - single_time ) /  CLOCKS_PER_SEC << " seconds "<< endl;

            result.hammingDistance = hdTot;

            return result;

        }

        BNSimulator::BooleanNetwork bn;
        BNCore::States states;
        int nNodes;
    };
}


#endif //YABOONS_TASKFITNESS_H
