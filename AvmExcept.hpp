//
// Created by aloha on 6/14/18.
//

#ifndef AVM_AVMEXCEPT_HPP
#define AVM_AVMEXCEPT_HPP

#include <exception>
#include <string>

class AvmExcept : std::exception {
public:
    AvmExcept(const std::string &);
    ~AvmExcept() throw();
    AvmExcept(const AvmExcept&);
    const AvmExcept&operator=(const AvmExcept&);
    virtual const char* what() const throw();

private:
    std::string _msg;
};

#endif //AVM_AVMEXCEPT_HPP
