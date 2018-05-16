//
// Created by lsantonastasi on 21/09/16.
//

#include <cmath>
#include <iostream>
#include "InputTable.h"

namespace  BNCore {

    InputTable::InputTable() {
        K=10;
    }

    InputTable::InputTable(int i) {
        K = i;
        inputs = vector<string>();
        length = pow(2,K);
        init();
    }

    void InputTable::init() {
        for (int i = 0 ; i < length ; i++) {
            string s = convertToBinary(i, "");
            if(s.size() < K) {
                int diff = K - s.size();
                for (int i = 0 ; i < diff; i++){
                    s = "0"+s;
                }
            }
            inputs.push_back(s);
            //cout << s << endl;
        }
    }


    string InputTable::convertToBinary(int n, string s){
        if (n / 2 != 0) {
            return convertToBinary(n / 2, to_string(n%2)+s);
        }
        return to_string(n%2)+s;
    }


    int InputTable::getInputPerNode() {
        return K;
    }

    vector<string> InputTable::getInputsCombination() {
        return inputs;
    }

}