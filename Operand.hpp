//
// Created by aloha on 21.06.18.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include "IOperand.hpp"
#include <sstream>
#include <limits>
#include "AvmExcept.hpp"

template <class T>
class Operand :public IOperand{
public:
    Operand();
    Operand(eOperandType type, int precision, std::string const &str) : _type(type),
                                                          _precision(precision),
                                                          _str(str) {
        if (_precision > Int32)
            _str = removeZerosInString(_str);
        if (type < Float) {
            try {
                long long val = std::stoll(_str);
                isOverFlow<long long>(val);
                _value = static_cast<T>(val);
            }
            catch (...) {
                std::cerr << "OVERFLOW" << std::endl;
            }

        }
        else {
            long double val = std::stold(_str);
            isOverFlow<long double>(val);
            _value = static_cast<T>(val);
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
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value + right;
        std::string ss = std::to_string(res);

        return (new Operand(type, precision, ss));
    }

    IOperand const * operator-( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value - right;
        std::string ss = std::to_string(res);
        return (new Operand(type, precision, ss));
    }

    IOperand const * operator*( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value * right;
        std::string ss = std::to_string(res);
        return (new Operand(type, precision, ss));
    }

    IOperand const * operator/( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        T right;
        iss >> right;
        T res = _value / right;
        std::string ss = std::to_string(res);
        return (new Operand(type, precision, ss));
    }

    IOperand const * operator%( IOperand const & rhs ) const {
        eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
        if (type > Int32)
            throw AvmExcept("ERROR: mod with fp value");
        int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
        std::istringstream iss(rhs.toString());
        int right;
        iss >> right;
        int res = static_cast<int>(_value) % right;
        std::string ss = std::to_string(res);
        return (new Operand(type, precision, ss));
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
        T max = std::numeric_limits<T>::max();
        T min = std::numeric_limits<T>::min();
        if (val > max || val < min)
            throw std::range_error("ERROR: OVERFLOW");
    }

private:
    eOperandType    _type;
    int             _precision;
    std::string     _str;
    T               _value; // value which will be added to stack
};

#endif //AVM_OPERAND_HPP
