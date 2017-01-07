#ifndef IDISTANCE_METHOD_HPP
#define IDISTANCE_METHOD_HPP

#include <string>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <exception>
#include <stdexcept>

namespace cpp
{
namespace waes
{

/*!
 * @class IDistanceMethodException
 * @brief Custom exception when input data does not have valid sizes
 */
class
IDistanceMethodException : public std::runtime_error
{
public:
    /*!
     * @brief IDistanceMethodException ctor
     * @param [in] inputASize Size value for inputA
     * @param [in] inputBSize Size value for inputB
     */
    IDistanceMethodException(const size_t inputASize, const size_t inputBSize) :
        std::runtime_error("Incompatible input sizes"),
        m_inputASize(inputASize),
        m_inputBSize(inputBSize),
        m_message(buildMessage())
    {
    }

    /*!
     * @brief Request exception details
     * @return Exception message
     */
    virtual const char* what() const throw()
    {
        return m_message.c_str();
    }

private:
    size_t m_inputASize; /*!< Size value for inputA */
    size_t m_inputBSize; /*!< Size value for inputB */
    std::string m_message; /*!< Message details */

    /*!
     * @brief Build exception message using all available information
     * @return Built message 
     */
    std::string buildMessage()
    {
        std::stringstream ss;
        ss << std::string(std::runtime_error::what());
        ss << ": input A size (" << m_inputASize << ") != input B size ("<< m_inputBSize << ")";
        return ss.str();
    }
};

/*!
 * @class IDistanceMethod
 * @brief Abstract class for any other distance method calculation
 */
template <class T>
class
IDistanceMethod
{
public:
    /*!
     * @brief Default ctor
     */
    IDistanceMethod() {}

    /*!
     * @brief Default dtor
     */
    virtual ~IDistanceMethod() {}

    /*!
     * @brief Pure virtual method to be called for distance 
     * computation algorithm
     * @return Computed distance
     */
    virtual size_t run()=0;

    /*!
     * @brief Set input value
     */
    void setInputA(const T& inputA);

    /*!
     * @brief Set input value
     */
    void setInputB(const T& inputB);

public:
    typedef std::shared_ptr<IDistanceMethod>
        IDistanceMethodPtr; /*!< Smart pointer for IDistanceMethod */


protected:
    T m_inputA; /*!< First input value */
    T m_inputB; /*!< Second input value */

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

}
}
#endif //IDISTANCE_METHOD_HPP
