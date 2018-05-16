//
// Created by lsantonastasi on 15/10/16.
//

#ifndef BN_SIMULATOR_EVALUATOR_H
#define BN_SIMULATOR_EVALUATOR_H

#include "../nodes/Nodes.h"
#include "../simulator/BNTypes.h"
#include "../state/State.h"
#include "../utils/ThreadPool.h"
//#include "TaskEval.h"
//#include "../utils/TaskFitness.h"
//#include "../utils/TaskQueue.h"

//#define BOOST_THREAD_PROVIDES_FUTURE

#include <future>
#include <atomic>
#include <mutex>

using namespace BNCore ;
using namespace BNSimulator ;
using namespace std ;

namespace BNSimulator {

    /**!
     *
     */
    class Updater {

    public:

        /**!
         *
         */
        Updater(){
            n=  Nodes();
            s=  States();
            bnTypes = BNTypes::BN;
            nThread= 1;
            //queue = new TaskQueue<TaskEvaluation>(nThread);
        }

        /**!
         * Constructor
         *
         * \param nodes
         * \param states
         * \param t
         */
        Updater(Nodes nodes, States states, BNTypes t){
            n = nodes;
            s = states;
            bnTypes = t;
            nThread = 1;
            size = (int)n.getNodes().size();
            //queue = new TaskQueue<TaskEvaluation>(nThread);
        }

        /**!
         * Constructor
         *
         * \param nodes
         * \param states
         * \param t
         * \param nThr
         */
        Updater(Nodes nodes, States states, BNTypes t, int nThr){
            n = nodes;
            s = states;
            bnTypes = t;
            nThread = nThr;
            size = (int)n.getNodes().size();
            //queue = new TaskQueue<TaskEvaluation>(nThread);
            //thList = vector<boost::thread>();
            mtx = new std::mutex();
            if(nThread <= 0){
                throw LessThanZeroThreadPoolException("Thread pool cannot have zero thread! Please give a number greater than 0.");
            }


        }

        Updater(Nodes nodes, States states, BNTypes t, bool fromFile){
            n = nodes;
            s = states;
            bnTypes = t;
            nThread = 1;
            size = (int)n.getNodes().size();
            isFromFile = fromFile;
            //queue = new TaskQueue<TaskEvaluation>(nThread);
            //thList = vector<boost::thread>();
            mtx = new std::mutex();
            if(nThread <= 0){
                throw LessThanZeroThreadPoolException("Thread pool cannot have zero thread! Please give a number greater than 0.");
            }


        }


        Updater(Nodes nodes, States states, BNTypes t,int nThr, bool fromFile){
            n = nodes;
            s = states;
            bnTypes = t;
            nThread = nThr;
            isFromFile = fromFile;
            size = (int)n.getNodes().size();
            //queue = new TaskQueue<TaskEvaluation>(nThread);
            //thList = vector<boost::thread>();
            mtx = new std::mutex();
            if(nThread <= 0){
                throw LessThanZeroThreadPoolException("Thread pool cannot have zero thread! Please give a number greater than 0.");
            }


        }

        //vector<boost::thread> thList;

        /**!
         * Function that set current value of states for evaluation
         *
         * \param states
         */
        void setStates(States states){
            this->s = states;
        }


        /**!
         * Operator that evaluate a generation of States
         *
         * \param numberGen
         * \param showMeGen
         */
        States operator()(int numberGen, bool showMeGen){

            const clock_t eval_time1 = clock();

            //boost::xtime start;
            //boost::xtime_get(&start, boost::TIME_UTC_);
            nextGen= States();


            vector<Node> listN = n.getNodes();
            float sum = 0;
            //for (int no = 0; no < size; ++no) {
            int no = 0;
            while(no<size){

                //const clock_t eval_time = clock();
                Node node1 = listN[no];
                int conn_s =(int)node1.getConnections().size();

                str ="";

                for (int i = 0; i < conn_s; i++) {

                    int n = node1.getConnections()[i].getNumber();
                    str = str+to_string(s.getStates()[n].getValue());

                }
                //cout << node1.getIdentificator() << " - " << node1.getTransitionTable().getResult(str) << " - " << node1.getNumber()<< endl;
                nextGen.setStateAtPosition(BNCore::State(node1.getIdentificator(), node1.getTransitionTable().getResult(str)),node1.getNumber());
                ++no;
            }

            if(showMeGen) {
                cout << "Generation #" <<numberGen << ": " << nextGen.toString() <<  " - Computed in "<< 1000*( float( clock () - eval_time1 ) /  CLOCKS_PER_SEC) << " ms."<<endl;
            }


            return nextGen;
        }




    private:

        /**!
         * Structure of the network
         */
        Nodes n;

        /**!
         * Current states of the network
         */
        States s;

        /**!
         * Number of thread for thread evaluator
         */
        int nThread;

        /**!
         * type of BN we are using
         */
        BNTypes bnTypes;

        /**!
         * States to be computed
         */
        States nextGen;

        /**!
         * Flag to enable one type of evaluation versus another
         */
        bool isFromFile = false;

        /**!
         * Semaphore for multithreading
         */
        std::mutex *mtx;

        int size;

        string str = "";
    };

}

#endif //BN_SIMULATOR_EVALUATOR_H
