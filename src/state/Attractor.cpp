//
// Created by lsantonastasi on 11/10/16.
//

#include "Attractor.h"


namespace BNCore{

    Attractor::Attractor() {
        attractorList = vector<States>();
    }

    void Attractor::setAttractors(vector<States> n) {
        attractorList = n;
    }

    vector<States> Attractor::getAttractors() {
        return attractorList;
    }

    void Attractor::addStatesToAttractorList(States s){
        attractorList.push_back(s);
    }


    bool Attractor::operator==(Attractor attractor) {

        if(attractorList.size() != attractor.getAttractors().size()){
            return false;
        }


        for( int i =  0; i < attractorList.size() ; i++) {
            if(attractorList.at(i).toString() != attractor.getAttractors().at(i).toString() ){
                return false;
            }
        }


        return true;
    }
}