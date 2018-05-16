//
// Created by Luca Santonastasi on 29/10/16.
//

#include "StateSuccession.h"


namespace BNCore{

    StateSuccession::StateSuccession() {
        initialState = States();
        t = Transient();
        a = Attractor();
    }

    StateSuccession::StateSuccession(States i, Transient transient, Attractor attractor) {
        initialState = i;
        t = transient;
        a = attractor;
    }

    States StateSuccession::getInitialState() {
        return initialState;
    }

    Attractor StateSuccession::getAttractor() {
        return a;
    }


    Transient StateSuccession::getTransient() {
        return t;
    }





}