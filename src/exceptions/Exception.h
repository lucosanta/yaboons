//
// Created by lsantonastasi on 08/09/16.
//

#ifndef BN_SIMULATOR_EXCEPTION_H
#define BN_SIMULATOR_EXCEPTION_H

#include <iostream>

using namespace std;

namespace BNCore {

    class Exception : public runtime_error {
    public:
        Exception(std::string const &msg) :std::runtime_error(msg) {}
    };

    class ParsingException : public Exception {
    public:
        ParsingException(string msg) : Exception("[PARSING] " + msg) {}
    };

    class LexerException : public Exception {
    public:
        LexerException(string msg) : Exception("[PARSING] " + msg) {}
    };

    class MissingParameterException : public Exception {
    public:
        MissingParameterException(string msg) : Exception("[EVALUATION] " + msg) {}
    };

    class NegativeIterationException : public Exception {
    public:
        NegativeIterationException(string msg) : Exception("[EVALUATION] " + msg) {}
    };

    class IdentificatorNotFoundException : public Exception {
    public:
        IdentificatorNotFoundException(string msg) : Exception("[PARAMETERS] " + msg) {}
    };

    class SomeParameterMissingException : public Exception {
    public:
        SomeParameterMissingException(string msg) : Exception("[SIMULATOR] " + msg) {}
    };

    class MissingInitialStateSetException : public Exception {
    public:
        MissingInitialStateSetException(string msg) : Exception("[SIMULATOR] " + msg) {}
    };

    class MissingNodesDefinitionException: public Exception {
    public:
        MissingNodesDefinitionException(string msg) : Exception("[SIMULATOR] " + msg) {}
    };

    class DifferentInputsPerNodesException: public Exception {
    public:
        DifferentInputsPerNodesException(string msg) : Exception("[SIMULATOR] " + msg) {}
    };


    class DifferentVectorSizeException: public Exception {
    public:
        DifferentVectorSizeException(string msg) : Exception("[NODE] " + msg) {}
    };

    class TransitionTableToBeSetException: public Exception {
    public:
        TransitionTableToBeSetException(string msg) : Exception("[NODE] " + msg) {}
    };

    class NotYetImplementedException: public Exception {
    public:
        NotYetImplementedException(string msg) : Exception("[Not Yet Implemented] " + msg) {}
    };

    class NetworkNotSetException: public Exception {
    public:
        NetworkNotSetException(string msg) : Exception("[GENERATION] " + msg) {}
    };

    class CSVReadingException: public Exception {
    public:
        CSVReadingException(string msg) : Exception("[SIMULATOR] " + msg) {}
    };

    class LessThanZeroThreadPoolException: public Exception {
    public:
        LessThanZeroThreadPoolException(string msg) : Exception("[EVALUATOR] " + msg) {}
    };

    class InvalidFileException: public Exception {
    public:
        InvalidFileException(string msg) : Exception("[MAIN] " + msg) {}
    };

    class TokenWrongException: public Exception {
    public:
        TokenWrongException(string msg) : Exception("[BN] " + msg) {}
    };


}

#endif //BN_SIMULATOR_EXCEPTION_H
