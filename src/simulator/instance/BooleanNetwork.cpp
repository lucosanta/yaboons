//
// Created by lsantonastasi on 12/09/16.
//

#include "BooleanNetwork.h"
#include "../../csv/CSVIterator.h"
#include "../../state/StateSuccession.h"
#include "../../state/Transient.h"
//#include "../../nodes/darbn/DARBNNodes.h"


namespace BNSimulator{


    BooleanNetwork::BooleanNetwork() {
        bias = 0.5;
        inputsPerNode = 2;
        numberOfNodes = 20;
        nIteration = 0;
        isInitialStateSet = false;
        types = BNTypes::BN;
        attractorsChecker = map<string,Tuple>();
        nThreadForEvaluation = 1;
        init();
    }

    BooleanNetwork::BooleanNetwork(int K) {
        bias = 0.0;
        inputsPerNode = K;
        numberOfNodes = 20;
        nIteration = 0;
        isInitialStateSet = false;
        types = BNTypes::BN;
        attractorsChecker = map<string,Tuple>();
        nThreadForEvaluation = 1;
        //
        init();
    }

    BooleanNetwork::BooleanNetwork(string path, char sep, BNTypes t, int nThread) {
        CSVseparator = sep;
        isInitialStateSet = false;
        types = t;
        nIteration = 0;
        attractorsChecker = map<string,Tuple>();
        nThreadForEvaluation = nThread;
        isFromFile = true;
        initBNSimulator(path);
    }

    BooleanNetwork::BooleanNetwork(int K, float p, int N, BNTypes t) {
        bias = p;
        inputsPerNode = K;
        numberOfNodes = N;
        isInitialStateSet = false;
        types = t;
        nIteration = 0;
        attractorsChecker = map<string,Tuple>();
        nThreadForEvaluation = 1;
        init();
    }

    BooleanNetwork::BooleanNetwork(int K, float p, int N, BNTypes t,int nThreadInPool) {
        bias = p;
        inputsPerNode = K;
        numberOfNodes = N;
        isInitialStateSet = false;
        nIteration = 0;
        types = t;
        attractorsChecker = map<string,Tuple>();
        nThreadForEvaluation = nThreadInPool;
        init();
    }

    void BooleanNetwork::setInitialState(States s) {
        isInitialStateSet = true;
        pars = s;
    }

    BNOutput BooleanNetwork::start(int nIteration, bool showMeGen) {
        if(!isInitialStateSet) {
            throw MissingInitialStateSetException("You have to provide an initial state to BN Simulator before start! Please set initial state!");
        }

        this->nIteration = nIteration;



        BNOutput bn = BNOutput();
        bn.setStructure(nodes);
        //bn.addParameters(pars);

        if(nIteration < 0 ){
            throw NegativeIterationException("Error! Iteration cannot be less or equal than 0. Setted value = "+to_string(nIteration));
        }

        if(showMeGen){
            cout << "Initial state: " << pars.toString() << endl;
        }

        bool stopped = false;
        int nIt = 0;

        States init = pars;
        Attractor a;
        Transient t;
        t.addStatesToTransientList(pars);
        attractorsChecker.clear();
        vector<States> statesL = vector<States>();
        //TOFIX: Non evaluator!
        e = Updater(nodes,pars,types,nThreadForEvaluation,isFromFile);

        while(!stopped){

            //const clock_t single_time = clock();
            States nextGenerationParam = e(nIt,showMeGen);
            nIt++;
            //nextGenerationParam.print();
            pars = nextGenerationParam;

            e.setStates(pars);

            string s = pars.toString();


            if(attractorsChecker[s].occurences == 0){
                t.addStatesToTransientList(pars);
                statesL.push_back(pars);
                //a.addStatesToAttractorList(pars);
                //t.removeStatesFromTransientList(pars);
                attractorsChecker[s].position = nIt;
                attractorsChecker[s].occurences++;
            } else if(attractorsChecker[s].occurences == 1){
                //a.addStatesToAttractorList(pars);
                //t.removeStatesFromTransientList(pars);
                if(showMeGen) {
                    cout << "Attractor found! Exiting!" << endl;
                }
                stopped = true;
                //attractorsChecker[s].occurences++;
            }


            //bn.addParameters(nextGenerationParam);

            if(nIt == nIteration && nIteration != 0){
                stopped = true;
            }
            //cout << "Execution time loop is: " << float( clock () - single_time ) /  CLOCKS_PER_SEC << " seconds "<< endl;

            if(stopped)
            {

                for(int i =attractorsChecker[s].position-1; i < statesL.size(); i++ ){
                    a.addStatesToAttractorList(statesL.at(i));
                    t.removeStatesFromTransientList(statesL.at(i));
                }




            }
        }

        /*
        for(int i = 0; i < t.getTransient().size(); i++) {
            cout << "Transient # "<< i << ": "<<t.getTransient().at(i).toString() << endl;
        }

        for(int i = 0; i < a.getAttractors().size(); i++) {
            cout << "Attractor # "<< i << ": "<<a.getAttractors().at(i).toString() << endl;
        }
        */

        StateSuccession stateSuccession(init,t,a);

        bn.setSuccession(stateSuccession);
        //attractorsLength = (int)bn.getAttractorFromBN().getAttractors().size();

        return bn;
    }

    void BooleanNetwork::flip(int h) {
        h %= numberOfNodes;
        for(int i = 0 ; i < h ; i ++) {
            State p = pars.getStates().at(i);
            p.setValue(((p.getValue()) + 1) % 2);
            pars.setStateAtPosition(p, i);
        }
    }

    void BooleanNetwork::init() {

        switch (types) {

            case BNTypes ::CRBN:{
                nodes = Nodes(inputsPerNode,bias,numberOfNodes,true);
            }
                break;
            case BNTypes::ARBN:
            case BNTypes::DARBN:{
                throw NotYetImplementedException("[SIMULATOR] --> ARBN, DARBN");
            }
            default:
                break;

        }

    }


    States BooleanNetwork::eval(int currentIt,bool showMeGen) {
        //Updater ev(nodes,pars,types,nThreadForEvaluation);
        e.setStates(pars);
        return e(currentIt,showMeGen);
    }


    Nodes BooleanNetwork::getNodes() {
        return nodes;
    }

    void BooleanNetwork::setNodes(Nodes rbn) {
        nodes = rbn;
    }

    void BooleanNetwork::initBNSimulator(string path) {
        //cout << "Init " << path << endl;
        vector<string> splitted;
        nodes = Nodes();
        //pars = States();
        ifstream file(path);
        if (file.good()) {
            //cout << "File is ok "  << endl;
            int iter = 0;
            int numN = 0 ;
            for (CSVIterator iterator(file); iterator != CSVIterator(); ++iterator) {
                splitted = splits((*iterator)[0], CSVseparator);
                string identificator = (splitted)[0];
                string value = (splitted)[1];
                if(iter == 0 && identificator == "K") {
                    cout << value << endl;
                    if(value=="ND"){
                        inputsPerNode = 0;
                    } else {
                        inputsPerNode = stoi(value);
                    }
                } else if(iter != 0 && identificator != "K") {
                    int length = (int)splitted.size()-1;
                    string function = (splitted)[splitted.size()-1];
                    vector<int> transTable = vector<int>();
                    for(int i = 0; i < function.size(); i++) {

                        int a = 0;
                        if(function.at(i) == '1'){
                            a = 1;
                        }

                        transTable.push_back(a);
                    }

                    cout << length << endl;

                    Node n = Node(identificator,length-1);
                    n.setNumber(numN);
                    n.setTransitionTableResult(transTable);
                    for(int i = 1; i  < length ; i++){
                        n.addConnection(Node(splitted[i]));
                    }
                    nodes.addNode(n);
                    numN++;

                } else {
                    throw new TokenWrongException("There was an error while trying to compute tokens: "+identificator + " - "+value);
                }

                iter++;
            }

            if(nodes.getNodes().size() != 0) {
                isTopologyDefined = true;
            }

        }else {
            throw new InvalidFileException("The file you are trying to open is not good");
            return;
        }


    }

    void BooleanNetwork::split(const string &s, char delim, vector<string> &elems)  {
        stringstream ss;
        ss.str(s);
        string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
    }



    vector<string> BooleanNetwork::splits(const string &s, char delim) {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }

    string BooleanNetwork::getName() {
        return name;
    }

    void BooleanNetwork::setName(string n){
        this->name = n;
    }



}