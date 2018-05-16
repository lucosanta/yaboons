
//#include "src/simulator/BooleanNetwork.h"


//#include "src/operator/BooleanExpr.h"
#include "src/simulator/FactoryBN.h"
#include "src/simulator/instance/AllAttractorsBooleanNetwork.h"
#include "src/utils/ThreadPool.h"

using namespace BNCore;
using namespace BNSimulator;

string convertToBinary(int n, string s){
    if (n / 2 != 0) {
        return convertToBinary(n / 2, to_string(n%2)+s);
    }
    return to_string(n%2)+s;
}

int main() {
    srand(time(NULL));

    bool generateRandomParam = true;


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

    Node x5 = Node("x5",2,0.5);

    Node x6 = Node("x6",2,0.5);

    Node x7 = Node("x7",2,0.5);

    Node x8 = Node("x8",2,0.5);

    Node x9 = Node("x9",2,0.5);

    x1.addConnection(x2);
    x1.addConnection(x4);

    x2.addConnection(x1);
    x2.addConnection(x3);

    x3.addConnection(x2);
    x3.addConnection(x4);

    x4.addConnection(x3);
    x4.addConnection(x1);

    x5.addConnection(x4);
    x5.addConnection(x6);

    x6.addConnection(x5);
    x6.addConnection(x7);

    x7.addConnection(x6);
    x7.addConnection(x8);

    x8.addConnection(x7);
    x8.addConnection(x9);

    x9.addConnection(x8);
    x9.addConnection(x1);

    n.addNode(x1);
    n.addNode(x2);
    n.addNode(x3);
    n.addNode(x4);
    n.addNode(x5);
    n.addNode(x6);
    n.addNode(x7);
    n.addNode(x8);
    n.addNode(x9);


    BooleanNetwork network = factory.createSimpleBooleanInstance(2,4);
    network.setNodes(n);

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

    BNOutput gen = network.start(100,true);
    gen.print();

    cout << "****************** TRANSIENT *********************" <<endl;
    Transient t = gen.getSuccession().getTransient();

    for (int i = 0 ; i < t.getTransient().size(); i++) {
        t.getTransient().at(i).print();
    }
    cout << "****************** ATTRACTOR *********************" <<endl;

    Attractor a = gen.getSuccession().getAttractor();
    for (int i = 0 ; i < a.getAttractors().size(); i++) {
        a.getAttractors().at(i).print();
    }




    return 0;
}





