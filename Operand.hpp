//
// Created by aloha on 21.06.18.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <sstream>
#include <limits>
#include <iomanip>
#include "AvmExcept.hpp"
#include "OperandFactory.hpp"

template <class T>
class Operand :public IOperand{
public:
    Operand();
    Operand(eOperandType type, int precision, std::string const &str, const OperandFactory *op) : _type(type),
                                                          _precision(precision),
                                                          _op(op){
        std::stringstream ss;

        try {
            if (type < Float) {
                long long val = std::stoll(str);
                isOverFlow<long long>(val);
                _value = static_cast<T>(val);
                ss << std::setprecision(_precision) << val;
                _str = ss.str();

            }
            else {
                long double val = std::stold(str);
                isOverFlow<long double>(val);
                _value = static_cast<T>(val);
                ss << std::setprecision(_precision) << val;
                _str = ss.str();

            }
        }
        catch (AvmExcept &e) {
            std::cerr << e.what() << std::endl;
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
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::stringstream ss;
        if (type < Float) {
            long long val = std::stoll(_str) + std::stoll(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        else {
            long double val = std::stold(_str) + std::stold(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        return (_op->createOperand(type, ss.str()));
    }

    IOperand const * operator-( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::stringstream ss;
        if (type < Float) {
            long long val = std::stoll(_str) - std::stoll(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        else {
            long double val = std::stold(_str) - std::stold(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        return (_op->createOperand(type, ss.str()));
    }

    IOperand const * operator*( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::stringstream ss;
        if (type < Float) {
            long long val = std::stoll(_str) * std::stoll(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        else {
            long double val = std::stold(_str) * std::stold(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        return (_op->createOperand(type, ss.str()));
    }

    IOperand const * operator/( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::stringstream ss;
        if (type < Float) {
            long long val = std::stoll(_str) / std::stoll(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        else {
            long double val = std::stold(_str) / std::stold(rhs.toString());
            ss << std::setprecision(precision) << val;
        }
        return (_op->createOperand(type, ss.str()));
    }

    IOperand const * operator%( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        if (type > Int32)
            throw AvmExcept("ERROR: mod with fp value");
        std::stringstream ss;
        long long val = std::stoll(_str) % std::stoll(rhs.toString());
        ss << std::setprecision(precision) << val;

        return (_op->createOperand(type, ss.str()));
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
            throw AvmExcept("ERROR: OVERFLOW");
        if (val < min)
            throw AvmExcept("ERROR: UNDERFLOW");
    }

private:
    eOperandType            _type;
    int                     _precision;
    std::string             _str;
    const OperandFactory    *_op;
    T                       _value;
};

#endif //AVM_OPERAND_HPP
