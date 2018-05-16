//
// Created by lsantonastasi on 12/09/16.
//

#include "States.h"



namespace BNCore{


    States::States() {
        stateList = unordered_map<int,State>();
        statesToString = "";
    }

    States::States(int nStates) {
        stateList = unordered_map<int,State>();
        statesToString = "";
        //stateList = vector<State>(nStates);
    }



    void States::addState(State param)  {
        param.setPosition(nextPositionNumber);
        stateList[nextPositionNumber] = param;
        nextPositionNumber++;

    }


    unordered_map<int,State> States::getStates()  {
        return stateList;
    }


    void States::setStates(unordered_map<int,State> pList) {
        nextPositionNumber = (int)pList.size();
        stateList = pList;
    }

    string States::toString() {
        if(statesToString == "") {
            string s = "";
            for (int k = 0; k < stateList.size(); k++) {
                s += to_string(stateList[k].getValue());
            }
            statesToString = s;
            return s;
        } else {
            return statesToString;
        }

    }


    void States::print() {
        cout << toString() <<endl;
    }


    void States::generateRandomStates(Nodes nodes) {
        for (int i = 0; i < nodes.getNodes().size(); i++) {
            State p = State();
            p.setIdentificator(nodes.getNodes().at(i).getIdentificator());
            p.setValue((rand() % 2));
            p.setPosition(i);
            stateList[i]=p;
        }
    }


    void States::setStateAtPosition(State par, int position)  {
        stateList[position] = par;
    }


    //void States::appendListStates(vector<State> p) {
    //    stateList.insert(end(stateList),p.begin(),p.end());
    //}

}