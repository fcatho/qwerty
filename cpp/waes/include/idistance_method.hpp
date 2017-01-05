#ifndef IDISTANCE_METHOD_HPP
#define IDISTANCE_METHOD_HPP

#include <string>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <exception>
#include <stdexcept>


class
IDistanceMethodException : public std::runtime_error
{
public:
    IDistanceMethodException(const size_t inputASize, const size_t inputBSize) : 
        std::runtime_error("Incompatible input sizes"),
        m_inputASize(inputASize),
        m_inputBSize(inputBSize),
        m_message(buildMessage())
    {
    }

    virtual const char* what() const throw()
    {
        return m_message.c_str();
    }

private:
    size_t m_inputASize;
    size_t m_inputBSize;
    std::string m_message;

    std::string buildMessage()
    {
        std::stringstream ss;
        ss << std::string(std::runtime_error::what());
        ss << ": input A size (" << m_inputASize << ") != input B size ("<< m_inputBSize << ")";
        return ss.str();
    }
};

class
IDistanceMethod
{
public:
    IDistanceMethod() {}
    virtual ~IDistanceMethod() {}

    virtual size_t run(const std::string& inputA, const std::string& inputB) = 0;

public:
    typedef std::shared_ptr<IDistanceMethod> IDistanceMethodPtr;

};

#endif //IDISTANCE_METHOD_HPP
