//
// Created by aloha on 6/14/18.
//

#include "AvmExcept.hpp"

AvmExcept::AvmExcept(const std::string &str) :_msg(str) {}

AvmExcept::AvmExcept(const AvmExcept &) {}

AvmExcept::~AvmExcept() throw(){}

const AvmExcept& AvmExcept::operator=(const AvmExcept &) {}

const char* AvmExcept::what() const throw(){
    return _msg.c_str();
}