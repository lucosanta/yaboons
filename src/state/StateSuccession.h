//
// Created by Luca Santonastasi on 29/10/16.
//

#ifndef BN_SIMULATOR_STATESUCCESSION_H
#define BN_SIMULATOR_STATESUCCESSION_H

#include "Attractor.h"
#include "Transient.h"

namespace BNCore {

    /**!
     * \author Luca Santonastasi
     *
     * Class that represent the state succession of a network evaluation
     */
    class StateSuccession {

    public:
        /**!
         * Constructor
         */
        StateSuccession();

        /**!
         * Constructor
         */
        StateSuccession(States i,Transient t,Attractor a);

        /**!
         * Get initial state for current instance
         *
         * @return States
         */
        States getInitialState();

        /**!
         * Get transient of the current instance
         * @return
         */
        Transient getTransient();

        /**!
         *  Get attractor of the current instance
         *
         * @return Attractor of the state succession
         */
        Attractor getAttractor();

    private:

        /**!
         * Initial State for current succession
         */
        States initialState;

        /**!
         * Transient part before reaching an attractor
         */
        Transient t;


        /**!
         * Attractor of current state succession of Network
         */
        Attractor a;


    };

}
#endif //BN_SIMULATOR_STATESUCCESSION_H
