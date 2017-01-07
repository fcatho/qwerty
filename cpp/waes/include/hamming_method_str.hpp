#ifndef HAMMING_METHOD_STR_HPP
#define HAMMING_METHOD_STR_HPP

#include <hamming_method.hpp>
#include <iostream>
#include <memory>

/*!
 * @class HammingMethodStr
 * @brief This class derives from HammingMethod and overrides
 * byteHammingDistance method, to make a computation based on byte comparison
 */
class
HammingMethodStr : public HammingMethod
{
public:
    /*!
     * @brief Default ctor
     */
    HammingMethodStr();

    /*!
     * @brief Default dtor
     */
    virtual ~HammingMethodStr();

public:
    typedef std::shared_ptr<HammingMethodStr>
        HammingMethodStrPtr; /*!< Smart pointer for HammingMethodStr */

protected:
    /*!
     * @brief Computes if two bytes are equal or not
     * @param [in] a First value for comparison
     * @param [in] b Second value for comparison
     * @return 0 for equal values, 1 otherwise
     */
    virtual uint8_t byteHammingDistance(const uint8_t a, const uint8_t b);
};

#endif //HAMMING_METHOD_STR_HPP
