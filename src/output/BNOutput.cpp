//
// Created by lsantonastasi on 12/09/16.
//

#include "BNOutput.h"


namespace BNCore {

    BNOutput::BNOutput() {
        statesList = vector<States>();
    }


    Nodes BNOutput::getStructure() {
        return instanceBN;
    }

    void BNOutput::setStructure(Nodes n) {
        instanceBN = n;
    }

    StateSuccession BNOutput::getSuccession() {
        return succession;
    }

    void BNOutput::setSuccession(StateSuccession newSucc) {
        succession = newSucc;

        Transient t = succession.getTransient();
        Attractor a = succession.getAttractor();

        statesList.push_back(succession.getInitialState());

        for(int i = 0; i < t.getTransient().size(); i++ ){
            statesList.push_back(t.getTransient()[i]);
        }

        for(int i = 0; i < a.getAttractors().size(); i++ ){
            statesList.push_back(a.getAttractors()[i]);
        }

        if(a.getAttractors().size() != 0) {
            statesList.push_back(a.getAttractors()[0]);
        }
    }

    void BNOutput::print()  {
        for (int i = 0; i < statesList.size(); i++) {
            string s = "Generation #";
            if(i<10) {
                s+="0";
            }
            s+=to_string(i)+": ";
            for(int k = 0 ; k < statesList.at(i).getStates().size(); k++){

                s += to_string(statesList.at(i).getStates().at(k).getValue());


            }
            cout << s <<endl;
        }
    }

    vector<string> BNOutput::getListGeneration() {
        vector<string> str = vector<string>();
        for (int i = 0; i < statesList.size(); i++) {
            string s ="";
            for(int k = 0 ; k < statesList.at(i).getStates().size(); k++){

                s += to_string(statesList.at(i).getStates().at(k).getValue());


            }
            str.push_back(s);
        }
        return str;
    }

    void BNOutput::printGraphvizFile() {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        string time = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1)+ to_string(now->tm_mday)+
                      to_string(now->tm_hour) + to_string(now->tm_min)+ to_string(now->tm_sec);

        filebuf fb1;
        fb1.open ("graphviz"+time+".dot",std::ios::out);
        ostream os(&fb1);

        vector <string> arcs = vector<string>();
        os << "digraph G {" << endl;
        for (int i = 0 ; i < statesList.size() - 1; i++){

            string current="";
            string next ="";
            for(int k = 0 ; k < statesList.at(i).getStates().size(); k++){
                current += to_string(statesList.at(i).getStates().at(k).getValue());
                next += to_string(statesList.at(i+1).getStates().at(k).getValue());
            }
            bool isPresent = false;
            string arc = current+" -> "+next;

            for(int j = 0 ; j < arcs.size(); j++) {
                if(arcs .at(j) == arc) {
                    isPresent = true;
                }
            }
            if(!isPresent) {
                arcs.push_back(arc);
                os << arc << endl;
            }
        }
        os << "}" << endl;
        fb1.close();
    }

    string BNOutput::printConfigurationFileActualBooleanNetwork() {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        string time = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1)+ to_string(now->tm_mday)+
                      to_string(now->tm_hour) + to_string(now->tm_min)+ to_string(now->tm_sec);

        filebuf fb1;
        string filename = "BN-"+time+".csv";
        fb1.open (filename,std::ios::out);
        ostream os(&fb1);
        os << "K;"<< to_string(instanceBN.getNodes().at(0).getConnections().size())<< ";" << endl;

        vector<string> v = instanceBN.getNetworkAsVectorString();
        for(int i = 0; i< v.size(); i++) {
            os << v.at(i) << endl;
        }

        fb1.close();

        return filename;

    }


    void BNOutput::printGraphvizBooleanNodes() {
        if(instanceBN.getNodes().size() == 0 ) {
            throw NetworkNotSetException("Please provide a valid instance of Network in Boolean Network Generation instance!");
        } else if(instanceBN.getNodes().size() != 0) {


            time_t t = time(0);   // get time now
            struct tm * now = localtime( & t );
            string time = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1)+ to_string(now->tm_mday)+
                          to_string(now->tm_hour) + to_string(now->tm_min)+ to_string(now->tm_sec);

            filebuf fb1;
            fb1.open ("graphviz-BN-"+time+".dot",std::ios::out);
            ostream os(&fb1);

            vector <string> arcs = vector<string>();
            os << "digraph G {" << endl;
            for (int i = 0 ; i < instanceBN.getNodes().size() ; i++){

                vector<string> arcN = instanceBN.getNodes().at(i).getStringVectorConnection();
                arcs.insert(arcs.end(),arcN.begin(),arcN.end());


            }

            for(int i = 0; i < arcs.size(); i++ ){
                os << arcs.at(i) << endl;
            }

            os << "}" << endl;


        }
    }

    void BNOutput::printGraphvizFileAll(vector< vector<BNCore::States> > vvS) {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        string time = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1)+ to_string(now->tm_mday)+
                      to_string(now->tm_hour) + to_string(now->tm_min)+ to_string(now->tm_sec);

        filebuf fb1;
        fb1.open ("graphviz"+time+".dot",std::ios::out);
        ostream os(&fb1);

        vector <string> arcs = vector<string>();
        os << "digraph G {" << endl;

        for (int i = 0 ; i < vvS.size(); i++){

            for(int j = 0; j < vvS.at(i).size() -1; j++) {
                string current="";
                string next ="";

                current = vvS.at(i).at(j).toString();
                next = vvS.at(i).at(j+1).toString();

                bool isPresent = false;
                string arc = current+" -> "+next;

                for(int j = 0 ; j < arcs.size(); j++) {
                    if(arcs .at(j) == arc) {
                        isPresent = true;
                    }
                }
                if(!isPresent || i == 0) {
                    arcs.push_back(arc);
                    os << arc << endl;
                }
            }
        }
        os << "}" << endl;

    }


    vector <States> BNOutput::getSuccessionStates() {
        return statesList;
    }

    void BNOutput::setSuccessionList(vector <States> newSucc) {
        statesList = newSucc;
    }






}