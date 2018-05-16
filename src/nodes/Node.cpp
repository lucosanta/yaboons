//
// Created by lsantonastasi on 05/09/16.
//

#include "Node.h"
#include "../exceptions/Exception.h"


namespace BNCore {


    Node::Node(string id){
        identificator = id;
        isTransitionTableToBeSet= true;
        inputsPerNode = 2;
        transitionTable = TransitionTable(2,0);
        nodeType = NodeType::GENERIC;
    }

    Node::Node(string id, NodeType t){
        identificator = id;
        isTransitionTableToBeSet= true;
        inputsPerNode = 2;
        transitionTable = TransitionTable(2,0);
        nodeType = t;
    }

    Node::Node(string id, int K){
        identificator = id;
        isTransitionTableToBeSet = true;
        inputsPerNode = K;
        transitionTable = TransitionTable(K,0);
        nodeType = NodeType::GENERIC;
    }

    Node::Node(string id, int K, NodeType t){
        identificator = id;
        isTransitionTableToBeSet = true;
        inputsPerNode = K;
        transitionTable = TransitionTable(K,0);
        nodeType = t;
    }


    Node::Node(string id, int K, float p) {
        identificator = id;
        isTransitionTableToBeSet = false;
        inputsPerNode = K;
        bias = p;
        transitionTable = TransitionTable(K,p);
        nodeType = NodeType::GENERIC;
    }


    Node::Node(string id,int K,float p,NodeType t) {
        identificator = id;
        isTransitionTableToBeSet = false;
        inputsPerNode = K;
        bias = p;
        transitionTable = TransitionTable(K,p);
        nodeType = t;
    }



    void Node::setIdentificator(string id) {
        identificator = id;
    }


    string Node::getIdentificator() {
        return identificator;
    }

    void Node::addConnection(Node n){
        connections.push_back(n);
    }


    NodeType Node::getNodeType(){
        return nodeType;
    }

    void Node::setNodeType(NodeType t){
        nodeType = t;


        if(t == NodeType::INPUT){
            isTransitionTableToBeSet= false;
            transitionTable = TransitionTable(1,0);
            inputsPerNode = 1;
            vector<int> v = vector<int>();
            v.push_back(0);
            v.push_back(1);
            setTransitionTableResult(v);
            resetConnection();
            addConnection(*this);

        }






    }

    vector<Node> Node::getConnections(){
        if(!isTransitionTableSet()){
            throw TransitionTableToBeSetException("Transition table for Node "+identificator+ " has not been set! Please set it!");
        }


        return connections;
    }


    void Node::resetConnection() {
        connections = vector<Node>();
    }



    /*void Node::printConnectionNode(States p) {
        string conn = ""+identificator+" => ";
        for(int i = 0 ; i < p.getParameters().size(); i++){
            conn+=p.getParameters().at(i).getIdentificator();
        }
        cout << conn << endl;
    }*/


    void Node::setTransitionTableResult(vector<int> tVectorAfter) {
        transitionTable.reset();
        int length =  pow(2,transitionTable.getInputsPerNode());
        //cout << length <<endl;
        //cout << tVectorAfter.size() <<endl;
        if(tVectorAfter.size() != length){
            string s =  (tVectorAfter.size() > length ?"more": "less");
            int howMany = (tVectorAfter.size() > length ? tVectorAfter.size() - length : length -tVectorAfter.size());
            throw DifferentVectorSizeException("[Node "+identificator+"] Vector passed as argument contains "+to_string(howMany)+" "+ s +" argument than needed");
        }

        for(int i = 0; i < length ; i ++ ){
            transitionTable.addAResult(tVectorAfter.at(i));
            transitionTable.setResultForKey(i, tVectorAfter.at(i),false);
        }
        isTransitionTableToBeSet = false;

    }

    bool Node::isTransitionTableSet() {
        return !isTransitionTableToBeSet;
    }


    string Node::convertToBinary(int n, string s){
        if (n / 2 != 0) {
            return convertToBinary(n / 2, to_string(n%2)+s);
        }
        return to_string(n%2)+s;
    }


    TransitionTable Node::getTransitionTable() {
        return transitionTable;
    }


    void Node::setTransitionTable(TransitionTable t) {
        transitionTable = t;
    }


    vector<string> Node::getStringVectorConnection() {
        vector<string> s =vector<string>();
        for(int i = 0; i  < connections.size(); i++ ){
            s.push_back(identificator+" -> "+connections.at(i).getIdentificator());
        }

        return s;
    }


    string Node::getNodeAsAString() {
        string s = "";

        s+= identificator+";";

        for(int j = 0 ; j < getConnections().size(); j++) {
            s+= getConnections().at(j).getIdentificator()+ ";";
        }


        for(int k = 0; k< getTransitionTable().getListResult().size(); k++ ){
            //cout << instanceBN.getNodes().at(i).getLookupTable().getListResult().at(k)<< endl;
            s+= to_string(getTransitionTable().getListResult().at(k));
        }

        s+=";";

        return s;
    }

    /*int Node::step(States p) {
        string s = "";
        //cout << connections.size() << endl;
        for(int i = 0; i < connections.size(); i++){
            string id = connections.at(i).getIdentificator();

            for(int j = 0; j < p.getParameters().size(); j++){
                if(p.getParameters().at(j).getIdentificator() == id){
                    s = to_string(p.getParameters().at(j).getValue())+s;
                }
            }
        }
        //cout << s << endl;
        //if (s == "" || s.length() < inputsPerNode){
            //throw SomeParameterMissingException("Some state is missing for "+identificator+" node! Please check!");
        //}
        return transitionTable.getResult(s);
    }*/


    void Node::setNumber(int n){
        this->number = n ;
    }

    int Node::getNumber(){
        return this->number;
    }

}