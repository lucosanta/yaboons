//
// Created by lsantonastasi on 21/09/16.
//

#include <iostream>
#include "TransitionTable.h"
#include "InputTable.h"


namespace BNCore{

    TransitionTable::TransitionTable() {
        inputsPerNode = 2;
        bias = 0.5;
        t = InputTable(inputsPerNode);
    }

    TransitionTable::TransitionTable(int K, float p){
        inputsPerNode=K;
        bias = p;
        lookup = unordered_map<string,int>();
        listResult = vector<int>();
        t = InputTable(inputsPerNode);
        init();
    }

    void TransitionTable::init() {

        vector<string> k = t.getInputsCombination();

        for(int i = 0 ; i < k.size() ; i++){

            float t = rand() % 100;
            int v = 0;

            if(t < bias*100 ){ v= 1; }

            lookup[k.at(i)] = v;
            if(bias > 0) {
                listResult.push_back(v);
            }
            //cout << k.at(i) << " => " << v << " with rand value = " << to_string(t) << " and bias = "<< bias <<endl;
        }
    }

    void TransitionTable::reset() {
        listResult.clear();
        init();
    }

    vector<int> TransitionTable::getListResult(){
        return listResult;
    }

    void TransitionTable::setListResult(vector<int> l){
        listResult = l;
    }

    int TransitionTable::getInputsPerNode(){
        return inputsPerNode;
    }

    void TransitionTable::addAResult(int res) {
        listResult.push_back(res);
    }


    float TransitionTable::getBias(){
        return bias;
    }


    int TransitionTable::getResult(string input){
        return lookup[input];
    }

    bool TransitionTable::setResultForKey(int key, int res, bool isListToBeChanged) {
        string s = t.convertToBinary(key,"");
        if(key > listResult.size() || key < 0){
            return false;
        }

        if(isListToBeChanged) {
            listResult[key] = res;
        }

        return setResultForKey(s,res,isListToBeChanged);
    }

    bool TransitionTable::setResultForKey(string s,int res, bool isListToBeChanged) {

        if(s.size() != inputsPerNode){
            int diff = inputsPerNode - (int)s.size();
            for (int i = 0 ; i < diff; i++){
                s = "0"+s;
            }
        }

        lookup[s] = res;
        return true;
    }



}