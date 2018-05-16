//
// Created by lsantonastasi on 15/10/16.
//

#include "AllAttractorsBooleanNetwork.h"
#include "../../nodes/InputTable.h"


namespace BNSimulator {


    AllAttractorsBooleanNetwork::AllAttractorsBooleanNetwork(BooleanNetwork n) {
        bn= n;
        createGraphvizFile = true;
    }

    AllAttractorsBooleanNetwork::AllAttractorsBooleanNetwork(BooleanNetwork n,bool wantFile) {
        bn= n;
        createGraphvizFile = wantFile;

    }

    vector< StateSuccession> AllAttractorsBooleanNetwork::start(){
        int l = (int) bn.getNodes().getNodes().size();
        Nodes nodes;

        nodes = bn.getNodes();

        InputTable inputTable = InputTable(l);
        BNOutput final = BNOutput();
        attractors = vector< StateSuccession > ();
        vector<vector<States>> statesListList = vector<vector<States>>();
        for(int i = 0 ; i < inputTable.getInputsCombination().size(); i++){
            cout << i << "/" << inputTable.getInputsCombination().size()<< " - States = "<<inputTable.getInputsCombination().at(i) << endl;
            States states;
            BNOutput tmp ;

            states = convertToStates(nodes,inputTable.getInputsCombination().at(i));
            bn.setInitialState(states);
            tmp = bn.start(0, false);
            StateSuccession vS = tmp.getSuccession();

            statesListList.push_back(tmp.getSuccessionStates());
            attractors.push_back(vS);
        }

        if(createGraphvizFile) {
            cout << "Creating Graphviz file for representing all the state space of the BN and their connections" << endl;
            final.printGraphvizFileAll(statesListList);
        }

        return attractors;
    }


    States AllAttractorsBooleanNetwork::convertToStates(Nodes n, string s){
        States st = States();
        for(int i  = 0; i < s.size(); i++) {
            int a = 1;
            if(s.at(i) == '0'){
                a = 0;
            }
            State state = State();
            state.setIdentificator(n.getNodes().at(i).getIdentificator());
            state.setValue(a);
            st.addState(state);
        }
        return st;

    }


};