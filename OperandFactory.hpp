//
// Created by aloha on 21.06.18.
//

#ifndef AVM_OPERANDFACTORY_HPP
#define AVM_OPERANDFACTORY_HPP

#include "IOperand.hpp"
#include <string>
#include <map>

class OperandFactory {
public:
    OperandFactory();
    ~OperandFactory();
    OperandFactory(const OperandFactory&);

    OperandFactory&operator=(const OperandFactory&);

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

    std::map<eOperandType, IOperand const* (OperandFactory::*)(std::string const & value) const>    _createFunc;
};


#endif //AVM_OPERANDFACTORY_HPP
