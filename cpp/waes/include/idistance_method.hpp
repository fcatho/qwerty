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

template <class T>
class
IDistanceMethod
{
public:
    IDistanceMethod() {}
    virtual ~IDistanceMethod() {}

    virtual size_t run()=0;//const T& inputA, const T& inputB) = 0;
    void setInputA(const T& inputA);
    void setInputB(const T& inputB);

public:
    typedef std::shared_ptr<IDistanceMethod> IDistanceMethodPtr;

protected:
    T m_inputB;
    T m_inputA;

};

template <class T>
void IDistanceMethod<T>::setInputA(const T& input)
{
    m_inputA = input;
}

template <class T>
void IDistanceMethod<T>::setInputB(const T& input)
{
    m_inputB = input;
}

#endif //IDISTANCE_METHOD_HPP
