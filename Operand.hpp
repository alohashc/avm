//
// Created by aloha on 21.06.18.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <sstream>
#include <limits>
#include "AvmExcept.hpp"
#include "OperandFactory.hpp"

template <class T>
class Operand :public IOperand{
public:
    Operand();
    Operand(eOperandType type, int precision, std::string const &str, const OperandFactory *op) : _type(type),
                                                          _precision(precision),
                                                          _str(str), _op(op){
        if (_precision > Int32)
            _str = removeZerosInString(_str);
        if (type < Float) {
            try {
                size_t pos = str.find('.');
                _str = str.substr(0, pos);
                long long val = std::stoll(_str);
                isOverFlow<long long>(val);
                _value = static_cast<T>(val);
            }
            catch (std::exception) {
                throw AvmExcept("OVERFLOW");
            }

        }
        else {
            try {
                long double val = std::stold(_str);
                isOverFlow<long double>(val);
                _value = static_cast<T>(val);
            }
            catch (std::exception) {
                throw AvmExcept("OVERFLOW");
            }

        }
    }
    Operand(const Operand& src);
    ~Operand() {}

    Operand&operator=(const Operand* rhs) {
        this->_value = rhs->_value;
        this->_type = rhs->_type;
        this->_precision = rhs->_precision;
        this->_str = rhs->_str;
    }

    IOperand const * operator+( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
//        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value + right;
        std::string ss = std::to_string(res);

        return (_op->createOperand(type, ss));
    }

    IOperand const * operator-( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
//        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value - right;
        std::string ss = std::to_string(res);
        return (_op->createOperand(type, ss));
    }

    IOperand const * operator*( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
//        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value * right;
        std::string ss = std::to_string(res);
        return (_op->createOperand(type, ss));
    }

    IOperand const * operator/( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
//        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value / right;
        std::string ss = std::to_string(res);
        return (_op->createOperand(type, ss));
    }

    IOperand const * operator%( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        if (type > Int32)
            throw AvmExcept("ERROR: mod with fp value");
//        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        int right;
        iss >> right;
        int res = static_cast<int>(_value) % right;
        std::string ss = std::to_string(res);
        return (_op->createOperand(type, ss));
    }

    std::string const & toString() const {
        return _str;
    }
    int getPrecision() const {
        return _precision;
    }
    eOperandType getType() const {
        return _type;
    }

    std::string removeZerosInString(std::string &str) {
        for (int i = str.size() - 1; i > 0; i--) {
            if (str.at(i) == '0')
                str.erase(str.end() - 1);
            else
                break;
        }
        return str;
    }

    template <typename Type>
    void isOverFlow(Type &val) {
        Type max = std::numeric_limits<T>::max();
        Type min = std::numeric_limits<T>::lowest();
        if (val > max)
            throw std::range_error("ERROR: OVERFLOW");
        if (val < min)
            throw std::range_error("ERROR: UNDERFLOW");
    }

private:
    eOperandType    _type;
    int             _precision;
    std::string     _str;
    const OperandFactory  *_op;
    T               _value;
};

#endif //AVM_OPERAND_HPP
