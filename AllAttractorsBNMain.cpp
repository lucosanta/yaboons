//
// Created by Luca Santonastasi on 03/11/16.
//
#include "src/simulator/FactoryBN.h"
#include "src/simulator/instance/AllAttractorsBooleanNetwork.h"

using namespace BNCore;
using namespace BNSimulator;


int main(int argc, char**argv){
    FactoryBN factory = FactoryBN();

    Nodes n = Nodes();

    Node x1 = Node("x1");

    vector<int> v = vector<int>();
    v.push_back(1);
    v.push_back(0);
    v.push_back(0);
    v.push_back(1);
    x1.setTransitionTableResult(v);

    Node x2 = Node("x2");
    v.clear();
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
    v.push_back(1);
    x2.setTransitionTableResult(v);

    Node x3 = Node("x3");
    v.clear();
    v.push_back(0);
    v.push_back(1);
    v.push_back(1);
    v.push_back(0);
    x3.setTransitionTableResult(v);

    Node x4 = Node("x4");
    v.clear();
    v.push_back(0);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    x4.setTransitionTableResult(v);

    Node x5 = Node("x5",2,0.5,NodeType::OUTPUT);

    Node x6 = Node("x6",NodeType::INPUT);

    Node x7 = Node("x7",NodeType::INPUT);

    Node x8 = Node("x8",NodeType::INPUT);

    Node x9 = Node("x9",NodeType::INPUT);

    x1.addConnection(x2);
    x1.addConnection(x4);

    x2.addConnection(x1);
    x2.addConnection(x3);

    x3.addConnection(x2);
    x3.addConnection(x4);

    x4.addConnection(x3);
    x4.addConnection(x5);

    x5.addConnection(x1);
    x5.addConnection(x4);

    n.addNode(x1);
    n.addNode(x2);
    n.addNode(x3);
    n.addNode(x4);
    n.addNode(x5);
    n.addNode(x6);
    n.addNode(x7);
    n.addNode(x8);
    n.addNode(x9);


    BooleanNetwork network = factory.createSimpleBooleanInstance(2,1);
    network.setNodes(n);
    Nodes nodInput = network.getNodes();
    for(int i = 0; i < nodInput.getNodes().size(); i++){
        cout << nodInput.getNodes().at(i).getNodeAsAString()<<endl;
    }

    States initialStates = States();

    initialStates.addState(State("x1", 1));
    initialStates.addState(State("x2", 0));
    initialStates.addState(State("x3", 1));
    initialStates.addState(State("x4", 1));
    initialStates.addState(State("x5", 0));
    initialStates.addState(State("x6", 1));
    initialStates.addState(State("x7", 1));
    initialStates.addState(State("x8", 1));
    initialStates.addState(State("x9", 1));

    network.setInitialState(initialStates);

    network.setInitialState(initialStates);

    network.start(0,true);

    return 0;
}