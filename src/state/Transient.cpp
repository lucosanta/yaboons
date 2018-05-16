//
// Created by Luca Santonastasi on 29/10/16.
//

#include "Transient.h"


namespace BNCore{


    Transient::Transient(){
        transientList = vector<States>();
    }

    void Transient::setTransient(vector <States> n){
        transientList = n;
    }

    vector <States> Transient::getTransient(){
        return transientList;
    }

    void Transient::addStatesToTransientList(States s){
        transientList.push_back(s);
    }


    void Transient::removeStatesFromTransientList(States s){
        string t = s.toString();

        transientList.erase(
                std::remove_if(
                        transientList.begin(),
                        transientList.end(),
                        [t](States element) -> bool {
                            // Do "some stuff", then return true if element should be removed.
                            return t == element.toString();
                        }
                ),
                transientList.end()
        );
    }



}