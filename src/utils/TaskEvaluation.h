//
// Created by Luca Santonastasi on 04/01/17.
//

#ifndef YABOONS_TASK_H
#define YABOONS_TASK_H

#include <string>
#include "../state/State.h"
#include "../state/States.h"
#include "../simulator/instance/BooleanNetwork.h"

namespace BNSimulator {

    struct TaskEvaluationResult {
        BNCore::State state;
    };

    struct TaskEvaluation {
        typedef TaskEvaluationResult result_type;

        TaskEvaluation(BNCore::Node n, BNCore::States ss, Evaluator current) :
                node(n),
                s1(ss),
                ev(current){
        }

        void operator()() {
            result_type result;

            string str = "";
            for (int i = 0; i < node.getConnections().size(); i++) {
                string id = node.getConnections().at(i).getIdentificator();
                for (int j = 0; j < s1.getStates().size(); j++) {
                    if (s1.getStates().at(j).getIdentificator() == id) {
                        str = to_string(s1.getStates().at(j).getValue()) + str;
                    }
                }
            }
            result.state = BNCore::State(node.getIdentificator(), node.getTransitionTable().getResult(str));

            ev.addState(result.state);

            //return result;

        }

        BNCore::Node node;
        BNCore::States s1;
        Evaluator ev;
    };
}
#endif //YABOONS_TASK_H
