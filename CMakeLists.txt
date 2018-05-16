cmake_minimum_required(VERSION 3.0)
project(YABooNS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ARGOS3_HEADERS_PLUGINS_YABOONS

        src/nodes/InputTable.h
        src/nodes/TransitionTable.h
        src/nodes/Node.h
        src/nodes/Nodes.h
        src/state/State.h
        src/state/States.h
        src/state/Attractor.h
        src/state/StateSuccession.h
        src/evaluation/Updater.h
        src/simulator/instance/BooleanNetwork.h
        src/simulator/instance/DerridasAnnealingApprox.h
        src/simulator/FactoryBN.h
        src/simulator/BNTypes.h
        src/utils/ThreadPool.h
        src/simulator/instance/AllAttractorsBooleanNetwork.h
        src/output/BNOutput.h
        src/exceptions/Exception.h

        )


set(ARGOS3_SOURCES_PLUGINS_YABOONS_NODES
        src/nodes/InputTable.cpp
        src/nodes/TransitionTable.cpp
        src/nodes/Node.cpp
        src/nodes/Nodes.cpp
        src/nodes/InputTable.h
        src/nodes/TransitionTable.h
        src/nodes/Node.h
        src/nodes/Nodes.h
        src/nodes/NodeType.h)

set(ARGOS3_SOURCES_PLUGINS_YABOONS_STATE
        src/state/State.cpp
        src/state/States.cpp
        src/state/Attractor.cpp
        src/state/Transient.cpp
        src/state/Transient.h
        src/state/StateSuccession.cpp
        src/state/State.h
        src/state/States.h
        src/state/Attractor.h
        src/state/StateSuccession.h
        )

set(ARGOS3_SOURCES_PLUGINS_YABOONS_SIMULATOR_INSTANCE
        src/simulator/instance/BooleanNetwork.h
        src/simulator/instance/DerridasAnnealingApprox.h
        src/simulator/instance/AllAttractorsBooleanNetwork.h
        src/simulator/instance/BooleanNetwork.cpp
        src/simulator/instance/DerridasAnnealingApprox.cpp
        src/simulator/instance/AllAttractorsBooleanNetwork.cpp
        )
set(ARGOS3_SOURCES_PLUGINS_YABOONS_SIMULATOR
        src/simulator/FactoryBN.cpp
        src/simulator/FactoryBN.h
        src/simulator/BNTypes.h
        src/evaluation/Updater.h

        )
set(ARGOS3_SOURCES_PLUGINS_YABOONS_OUTPUT
        src/output/BNOutput.h
        src/output/BNOutput.cpp
        )
set(ARGOS3_SOURCES_PLUGINS_YABOONS_EXCEPTION
        src/exceptions/Exception.cpp
        src/exceptions/Exception.h
        )

set(ARGOS3_SOURCES_PLUGINS_YABOONS_UTILS
        src/utils/ThreadPool.h
        #src/utils/TaskQueue.h
        #src/utils/TaskFitness.h
        #src/utils/TaskEvaluation.h
        )


set(ARGOS3_SOURCES_PLUGINS_YABOONS

        ${ARGOS3_SOURCES_PLUGINS_YABOONS_STATE}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_SIMULATOR_INSTANCE}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_SIMULATOR}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_OUTPUT}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_EXCEPTION}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_NODES}
        ${ARGOS3_SOURCES_PLUGINS_YABOONS_UTILS}

        )




##########################################################

add_library(yaboons STATIC ${ARGOS3_SOURCES_PLUGINS_YABOONS})
target_link_libraries(yaboons pthread)
install(TARGETS yaboons ARCHIVE DESTINATION lib COMPONENT libraries)


add_executable(BNSimulator BooleanNetworkMain.cpp)
target_link_libraries(BNSimulator yaboons)

add_executable(RBNSimulator RandomBooleanNetworkMain.cpp)
target_link_libraries(RBNSimulator yaboons)

add_executable(DerridaAnnealedApprox DerridasExampleMain.cpp ${ARGOS3_SOURCES_PLUGINS_YABOONS})
target_link_libraries(DerridaAnnealedApprox yaboons)

add_executable(AllAttractorsBN AllAttractorsBNMain.cpp ${ARGOS3_SOURCES_PLUGINS_YABOONS})
target_link_libraries(AllAttractorsBN yaboons)

#add_executable(BNFromFile FileConfigBNMain.cpp ${ARGOS3_SOURCES_PLUGINS_YABOONS})
#target_link_libraries(BNFromFile yaboons)

#add_executable(FissionYeastCell FissionYeastCellMain.cpp ${ARGOS3_SOURCES_PLUGINS_YABOONS})
#target_link_libraries(FissionYeastCell yaboons)

#add_executable(ArabThaliana ThalianaBNMain.cpp ${ARGOS3_SOURCES_PLUGINS_YABOONS})
#target_link_libraries(ArabThaliana yaboons)

#add_executable(Robot RobotMain.cpp src/pi/GPIO.cpp src/pi/GPIO.h ${ARGOS3_SOURCES_PLUGINS_YABOONS})
