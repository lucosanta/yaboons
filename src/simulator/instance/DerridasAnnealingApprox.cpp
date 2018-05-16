//
// Created by lsantonastasi on 22/09/16.
//

#include <fstream>
#include "DerridasAnnealingApprox.h"


namespace BNSimulator {

    DerridasAnnealingApprox::DerridasAnnealingApprox(int N, int tim) {
        numberOfNodes = N;
        times=tim;
    }


    int DerridasAnnealingApprox::hammingDistance(string fs, string ss) {
        int hm_distance = 0;
        if ((fs.length() == ss.length())) {

            for (int i = 0; i < fs.length(); i++) {
                if (fs[i] != ss[i]) {
                    hm_distance++;
                }
            }

        } else {
            hm_distance = -1;
        }
        return hm_distance;
    }



    void DerridasAnnealingApprox::start(){
        float p = 0.5;
        int  it = 1;
        int K = 0;
        int numberOfNodes= 0;
        //ordered
        K =1 ;
        numberOfNodes = 60;
        k(numberOfNodes,K,p,it);

        //critical
        K =2 ;
        numberOfNodes = 60;
        k(numberOfNodes,K,p,it);

        //chaotic
        K = 4 ;
        numberOfNodes = 60;
        k(numberOfNodes,K,p,it);

        //maximally chaotic
        K = 8 ;
        numberOfNodes = 8;
        k(numberOfNodes,K,p,it);

    }

    void DerridasAnnealingApprox::k(int N,int K, float p, int nIterationStart) {
        filebuf fb;
        fb.open ("derridaK="+to_string(K)+".txt",std::ios::out);
        ostream os(&fb);

        if(K==N ){
            os << " =============== Random Boolean Maps (K=N="<< K <<") =============== " << endl;
            os << "Maximally Chaotic RBN "<< endl;
        } else {
            os << " =============== K = "<< K <<" =============== " << endl;

            float criticalK = 1/(2*p*(1-p));

            if(criticalK == K) {
                os << "Critical RBN" << endl;
            } else if(criticalK > K){
                os << "Ordered/Frozen RBN"<< endl;
            } else if (criticalK < K) {
                os << "Chaotic RBN "<< endl;
            }

        }
        os << "I'm going to try this RBN for " << times << " tries"<< endl;

        const clock_t begin_time_tries_cicle = clock();

        for (int m = 0 ; m < times; m++) {
            os << "=======> Tries #" << (m+1) << endl;

            int hd = 0;
            vector<int> h0_list = vector<int> ();
            vector<int> hd_list = vector<int> ();
            for(int  i = 0 ; i < N; i++) {
                const clock_t begin_time_rbn_cicle = clock();

                os << " =============== # " << (m+1) << " // "<< (i+1) << "/" << N << " =============== " << endl;
                cout << " =============== # " << (m+1) << " // "<< (i+1) << "/" << N << " =============== " << endl;
                //CREATION RBN
                const clock_t begin_time_creation_rbn_cicle = clock();
                BooleanNetwork net1 = BooleanNetwork(K,p,N,BNTypes::CRBN,4);
                BooleanNetwork net2 = net1;

                States states = States();
                states.generateRandomStates(net1.getNodes());

                net1.setInitialState(states);
                net2.setInitialState(states);

                net2.flip(i);
                float creation_time = float( clock () - begin_time_creation_rbn_cicle ) /  1000;
                os << "Creation and inversion time = "<< creation_time << endl;

                //START
                const clock_t begin_time_start_rbn_cicle = clock();

                BNOutput bn1 = net1.start(nIterationStart,false);

                BNOutput bn2 = net2.start(nIterationStart,false);

                float start_time = float( clock () - begin_time_start_rbn_cicle ) /  1000;
                os << "Start time = "<< start_time << endl;


                h0_list.push_back( hammingDistance(bn1.getListGeneration().at(0), bn2.getListGeneration().at(0)));

                hd_list.push_back(hammingDistance(bn1.getListGeneration().at(nIterationStart), bn2.getListGeneration().at(nIterationStart)));

                float endtime = float( clock () - begin_time_rbn_cicle );

                os << "Execution of "<< (i+1) << " cycle: " << endtime << " nanoseconds "<< endl;
            }
            os << " =============== End tries =============== " << endl;

            if(av0_list.size() == 0) {

                for (int k = 0 ; k < hd_list.size(); k++){
                    av0_list.push_back(h0_list.at(k));
                    av1_list.push_back(hd_list.at(k)/times);
                }

            } else {
                vector<float> tmp1_list = vector<float> ();

                for(int k = 0; k < hd_list.size(); k++){
                    tmp1_list.push_back((av1_list.at(k)*(m)+hd_list.at(k))/(m+1));
                }

                av1_list = tmp1_list;
            }
        }

        os << "Execution of "<< times << " tries: " << float( clock () - begin_time_tries_cicle ) /  CLOCKS_PER_SEC << " seconds "<< endl;
        os << "Execution of "<< times << " tries: " << float( clock () - begin_time_tries_cicle ) << " nanoseconds "<< endl;

        os << "Printing average data to export in a csv" << endl;

        filebuf fbcsv;
        fbcsv.open ("derridaK="+to_string(K)+".csv",std::ios::out);
        ostream oscsv(&fbcsv);

        for(int i = 0; i < av1_list.size(); i++) {
            oscsv << av0_list.at(i) << ";" << av1_list.at(i)  << ";" << endl;
        }

        fbcsv.close();
        fb.close();

    };


}