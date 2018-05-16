//
// Created by Luca Santonastasi on 30/10/16.
//
#include "src/simulator/FactoryBN.h"
#include <time.h>
#include "src/utils/ThreadPool.h"

#include "src/utils/TaskFitness.h"
//#include "src/utils/TaskQueue.h"


using namespace BNCore;
using namespace BNSimulator;

string convertToBinary(int n, string s){
    if (n / 2 != 0) {
        return convertToBinary(n / 2, to_string(n%2)+s);
    }
    return to_string(n%2)+s;
}


int main(){

    int nNodes              =   20 ;
    int inputsPerNode       =   3   ;
    //float bias              =   0.788675 ;
    float bias              =   0.5 ;
    int stepN               =   0   ;
    int nThread             =   1   ;
    int hd                  =   0   ;

    //TaskQueue<BNUtils::TaskFitness> *queue;

    FactoryBN factory = FactoryBN();
    BooleanNetwork rbn = factory.createClassicalRandomBooleanNetwork(inputsPerNode,bias,nNodes,nThread);
    States initialStates = States();
    initialStates.generateRandomStates(rbn.getNodes());
    rbn.setInitialState(initialStates);
    const clock_t single_time = clock();

    BNOutput gen1 = rbn.start(stepN,true);
    cout << "Execution time of state  is: " << float( clock () - single_time ) /  CLOCKS_PER_SEC << " seconds "<< endl;

    cout << "Attractor" <<endl;

    Attractor a = gen1.getSuccession().getAttractor();
    for(int i = 0 ; i < a.getAttractors().size(); i++){
        a.getAttractors().at(i).print();
    }



    cout << "****************** Test *************************" << endl;
    double fit = 0.0;

    vector<States> trainingSet = vector<States>();
    //BNUtils::ThreadPool threadPool(nThread);
    //queue = new TaskQueue<BNUtils::TaskFitness>(nThread);
    for (int k = 0; k < nNodes; k++) {
        string zeros = "";
        for (int ii = 0; ii < nNodes; ii++) {
            //ones = ones + "1";
            zeros = zeros + "0";
        }
        for (int i = 0; i < nNodes; i++) {

            States s = States();
            //ones[i]='0';
            zeros[i] = '1';
            vector<int> positionUsed = vector<int>();
            positionUsed.push_back(i);
            for(int y = 0 ; y < k ; y++){
                bool found = false;
                int randomNum = rand() % nNodes;

                for(int yy = 0 ; yy < positionUsed.size(); yy++){
                    if (randomNum == positionUsed.at(yy)){
                        found = true;
                    }
                }
                if(found) {
                    int tries = 0;
                    while (found){
                        for (int ff = 0; ff < positionUsed.size() ; ff++){
                            if (tries != positionUsed.at(ff)) {
                                randomNum = tries;
                                found = false;
                            }
                        }
                        tries ++;

                    }

                }
                positionUsed.push_back(randomNum);
                zeros[randomNum] = '1';

            }

            for(int y = 0; y < zeros.size(); y++) {
                int a = 0;
                if(zeros.at(y) == '1'){
                    a = 1;
                }
                s.addState(State("x"+to_string(y),a));
            }


            trainingSet.push_back(s);
            for (int zz = 0 ; zz < positionUsed.size(); zz++){
                zeros[positionUsed.at(zz)] = '0';
            }
        }

    }
    /*for(int i = 0 ; i < pow(2,nNodes); i++) {
        States s = States();

        string fu = convertToBinary(i,"");//prova1.csv
        if(fu.size() < nNodes) {
            int diff = nNodes - fu.size();
            for (int k = 0 ; k < diff; k++){
                fu = "0"+fu;
            }
        }
        for(int i = 0; i < fu.size(); i++) {
            int a = 0;
            if(fu.at(i) == '1'){
                a = 1;
            }
            //cout << "x"+to_string(i) << "=" << a <<endl;
            s.addState(State("x"+to_string(i),a));
        }

        trainingSet.push_back(s);


    }*/

    cout << trainingSet.size() << " == " << (nNodes*(nNodes+1)) << endl;


    //std::vector< std::future<int> > results;
    const clock_t begin_time_tries_cicle = clock();
    /*for (int no = 0; no < trainingSet.size(); no++) {
        States s = trainingSet.at(no);
        queue->QueueTask(BNUtils::TaskFitness(rbn,s));

    }

    //hd = hdTot;

    while (queue->TasksCompleted()){
        BNUtils::TaskFitnessResult result = queue->GetCompletedTaskResult();
        hd += result.hammingDistance;
        while (queue->NumPendingTasks()){
            //cout << "All tasks submitted, waiting for last tasks to complete..."<<endl;
            //boost::this_thread::sleep(boost::posix_time::milliseconds(10));


        }
    }*/
    for (int no = 0; no < trainingSet.size(); no++) {
        States states = trainingSet.at(no);

        const clock_t single_time = clock();



        //int hdTot = 0;

       /* vector<double> binaryV = vector<double>();
        binaryV.clear();
        for(int is = 0; is < states.getStates().size(); is++){
            binaryV.push_back(0.0);
        }

        int counterOne = 0;

        for(int is = 0 ; is < states.getStates().size(); is++) {
            if(states.getStates().at(is).getValue() == 1) {
                counterOne ++;
            }
        }*/

        rbn.setInitialState(states);
        BNCore::BNOutput output = rbn.start(0,false);

        /*vector<States> vS = output.getSuccession().getAttractor().getAttractors();

        for(int k = 0; k < vS.size(); k++){
            States attr = vS.at(k);
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

        }*/

        cout << "Execution time of state " << states.toString() <<" is: " << float( clock () - single_time ) /  CLOCKS_PER_SEC << " seconds - Analyzed "<< output.getSuccessionStates().size() <<" states"<< endl;

        //hd += hdTot;
    }
    cout << "[RBN - DCP fitness function] Complexive Hamming Distance for RBN is: "<< (hd) ;
    fit = (1/(1 +((double)hd)));


    cout << " and its fitness value is: "<< fit <<endl;

    cout << "Execution of "<< trainingSet.size() << " tries: " << float( clock () - begin_time_tries_cicle ) /  CLOCKS_PER_SEC << " seconds "<< endl;


    return 0;
}