//
// Created by aloha on 6/14/18.
//

#include "Lexer.hpp"
#include "AvmExcept.hpp"
#include <regex>
#include <istream>

Lexer::Lexer(int ac, char **av) {
    if (ac > 2)
        throw AvmExcept("ERROR: invalid input");
    else if (ac == 2) {
        _ifs.open(av[1]);
        _isFile = true;
    } else
        _isInput = true;
}

Lexer::Lexer(const Lexer &) {}

Lexer& Lexer::operator=(const Lexer &) {}

Lexer::~Lexer() {}

void Lexer::start() {
    if (_isFile) {
        std::string str;

        while (getline(_ifs, str)) {
                eachLine(str);
        }
    }
    if (_isInput) {
        std::string str;

        while (getline(std::cin, str)) {
            if (str == ";;")
                break;
            eachLine(str);
        }
    }
}

void Lexer::eachLine(std::string &str) {
    size_t found = str.find(';');
    if (found != std::string::npos) {
        if (found == 0)
            return ;
        str = str.substr(0, found);
        size_t space = 0;
        for (auto &it : str) {
            if (it == ' ')
                space++;
        }
        if (found != space)
            space--;
        str.resize(found - space);
    }

    std::istringstream iss(str);
    std::string s;
    int cnt = 0;

    while (getline(iss, s, ' ')) {
        Token token;
        cnt++;

        if (cnt == 1)
            token = isInst(cnt, s, iss);
        if (cnt == 2)
            token = isValue(cnt, s);
        if (cnt > 2)
            throw AvmExcept("ERROR: LEXER3");
        _tokens.push_back(token);
    }
}

Token Lexer::isInst(int &cnt, std::string &str, std::istringstream &iss) {
    std::map<std::string, tokenType> instr = {std::make_pair("push", PUSH),
                                              std::make_pair("pop", POP),
                                              std::make_pair("dump", DUMP),
                                              std::make_pair("assert", ASSERT),
                                              std::make_pair("add", ADD),
                                              std::make_pair("sub", SUB),
                                              std::make_pair("mul", MUL),
                                              std::make_pair("div", DIV),
                                              std::make_pair("mod", MOD),
                                              std::make_pair("print", PRINT),
                                              std::make_pair("exit", EXIT)};
    Token token;

    if ((str == "push" || str == "assert") && iss.peek() == EOF)
        throw AvmExcept("ERROR: LEXER0");
    std::map<std::string, tokenType>::iterator it;
    it = instr.find(str);
    if (it == instr.end())
        throw AvmExcept("ERROR: LEXER ");
    token._type = it->second;
    token._value = it->first;
    if (str != "push" && str != "assert")
        cnt = 0;
    return token;
}

Token Lexer::isValue(int &cnt, std::string &str) {
    std::map<std::string, tokenType> typeValue = {std::make_pair("int8", INT8),
                                                  std::make_pair("int16", INT16),
                                                  std::make_pair("int32", INT32),
                                                  std::make_pair("float", FLOAT),
                                                  std::make_pair("double", DOUBLE)};
    std::regex value(R"((\w*\()([-]?[0-9]+|[-]?[0-9]+.[0-9]+)(\)))");
    Token token;

    if (std::regex_match(str, value)) {
        size_t found = 0;
        for (const auto &i : typeValue) {
            found = str.find(i.first);
            if (found != std::string::npos) {
                token._value = str;
                token._type = i.second;
                break;
            }
        }
        if (found == std::string::npos)
            throw AvmExcept("ERROR: LEXER1");
    }
    else
        throw AvmExcept("ERROR: LEXER2");
    return token;
}

std::list<Token>& Lexer::getTokens() {
    return _tokens;
}