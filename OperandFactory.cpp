//
// Created by aloha on 21.06.18.
//

#include <stdexcept>
#include "OperandFactory.hpp"
#include "Operand.hpp"


OperandFactory::OperandFactory() {
    _createFunc[Int8] = &OperandFactory::createInt8;
    _createFunc[Int16] = &OperandFactory::createInt16;
    _createFunc[Int32] = &OperandFactory::createInt32;
    _createFunc[Float] = &OperandFactory::createFloat;
    _createFunc[Double] = &OperandFactory::createDouble;
}

OperandFactory::~OperandFactory() {}

IOperand const* OperandFactory::createOperand(eOperandType type, std::string const &value) const {
    IOperand const* (OperandFactory::*func)(std::string const & value) const;
    func = _createFunc.at(type);
    return (this->*func)(value);
}

IOperand const* OperandFactory::createInt8(std::string const &value) const {
    return new Operand<char>(Int8, 0, value, this);
}

IOperand const* OperandFactory::createInt16(std::string const &value) const {
    return (new Operand<short>(Int16, 0, value, this));
}

IOperand const* OperandFactory::createInt32(std::string const &value) const {
    return (new Operand<int>(Int32, 0, value, this));
}

IOperand const* OperandFactory::createFloat(std::string const &value) const {
    return (new Operand<float>(Float, 7, value, this));
}

IOperand const* OperandFactory::createDouble(std::string const &value) const {
    return new Operand<double>(Double, 14, value, this);
}