//
// Created by lsantonastasi on 12/09/16.
//

#include "State.h"


namespace BNCore {

    State::State() {}


    State::State(string id, int v) {
        identificator = id;
        value = v;
    }

    State::State(string id, int v, int pos) {
        identificator = id;
        value = v;
        position = pos;
    }



    string State::getIdentificator() {
        return identificator;
    }



    void State::setIdentificator(string newIdentificator) {
        identificator = newIdentificator;
    }



    int State::getValue() {
        return value;
    }



    void State::setValue(int newValue) {
        if(newValue > 1){
            newValue = 1;
        }
        value = newValue;
    }

    int State::getPosition() {
        return position;
    }

    void State::setPosition(int pos) {
        position = pos;
    }

    void State::print() {
        cout << identificator << " => " << value << endl;
    }



}