//
// Created by lsantonastasi on 05/09/16.
//

#include "Nodes.h"

namespace  BNCore {


    Nodes::Nodes() {
        nodesList = vector<Node>();
        inputsPerNode = 0;
        bias = 0.0;
        //numberOfNodes = 10;
        connection = vector<string>();
    }

    Nodes::Nodes(int N) {
        nodesList = vector<Node>();
        inputsPerNode = 0;
        bias = 0.0;
        numberOfNodes = N;
        connection = vector<string>();
    }

    Nodes::Nodes(int K,int N) {
        nodesList = vector<Node>();
        inputsPerNode = K;
        bias = 0.0;
        numberOfNodes = N;
        connection = vector<string>();
    }




    Nodes::Nodes(int K, float p,int N, bool generate) {
        nodesList = vector<Node>();
        inputsPerNode = K;
        bias = p;
        numberOfNodes = N;
        connection = vector<string>();
        if(generate) {
            generateNodesAndConnections();
        }
    }


    void Nodes::addNode(Node n)  {
        n.setNumber(actualNodeNumbers++);
        nodesList.push_back(n);
    }


    vector<Node> Nodes::getNodes() {
        return nodesList;
    }


    void Nodes::setNodes(vector<Node> newVector) {
        nodesList = newVector;
    }


    void Nodes::setNodeAtPosition(Node n, int position)  {
        nodesList[position] = n;
    }

    void Nodes::generateNodesAndConnections() {

        for(int i = 0 ; i < numberOfNodes; i++) {
            Node n = Node("x" + to_string(i), inputsPerNode, bias);
            n.setNumber(i);
            nodesList.push_back(n);
        }

        for(int i = 0; i < nodesList.size(); i++){
            setNodeConnection(nodesList.at(i), i);
        }
    }


    void Nodes::setNodeConnection(Node node, int i) {
        //cout << "Set connection node!" << endl;
        node.resetConnection();
        vector <string> taboo = vector<string>();
        connection = vector<string>();

        string conn = "";
        if(inputsPerNode != numberOfNodes) {
            taboo.push_back(node.getIdentificator());
        }
        for(int k = 0 ; k < inputsPerNode; k++){
            int t =  checkId(taboo,0);//rand() % nodesList.size();
            taboo.push_back(nodesList.at(t).getIdentificator());

            node.addConnection(nodesList.at(t));
            conn = conn +" "+nodesList.at(t).getIdentificator();
        }



        for(int q = 0 ; q < connection.size(); q++){
            if(conn == connection.at(i)){
                setNodeConnection(node,i);
                return;
            }
        }
        connection.push_back(conn);

        //cout << node.getIdentificator() << " => "<< conn << endl;
        setNodeAtPosition(node,i);
    }


    int Nodes::checkId(vector<string> v, int y) {
        int t = rand() % nodesList.size();

        for(int a = 0 ; a < v.size(); a++){
            //cout << "Vector: " << v.at(a) << endl;
            if(nodesList.at(t).getIdentificator() == v.at(a)){
                return checkId(v,y+1);

            }
        }
        return t;
    }

    vector<string> Nodes::getNetworkAsVectorString() {
        vector<string> list = vector<string>();

        for(int i = 0; i< nodesList.size(); i++){
            list.push_back(nodesList.at(i).getNodeAsAString());
        }

        return list;

    }


    Nodes Nodes::getInputNodes() {

        Nodes input = Nodes();

        bool allGeneric = true;
        for (int  i = 0 ; i < nodesList.size(); i++) {

            NodeType t = nodesList.at(i).getNodeType();

            switch (t) {
                case NodeType::INPUT:
                    allGeneric = false;
                    input.addNode(nodesList.at(i));
                    break;

                case NodeType::OUTPUT:
                    allGeneric = false;
                case NodeType::GENERIC:

                    break;
            }


        }

        if(allGeneric) return *this;

        return input;

    }

    Nodes Nodes::getOutputNodes() {
        Nodes output = Nodes();
        bool allGeneric = true;
        for (int  i = 0 ; i < nodesList.size(); i++) {
            NodeType t = nodesList.at(i).getNodeType();
            switch (t) {
                case NodeType::OUTPUT:
                    allGeneric = false;
                    output.addNode(nodesList.at(i));
                    break;

                case NodeType::INPUT:
                    allGeneric = false;

                case NodeType::GENERIC:

                    break;
            }


        }

        if(allGeneric) return *this;

        return output;

    }

}