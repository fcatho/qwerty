#ifndef HAMMING_METHOD_HPP
#define HAMMING_METHOD_HPP

#include <idistance_method.hpp>
#include <iostream>
#include <memory>
#include <vector>

namespace cpp
{
namespace waes
{
/*!
 * @class HammingMethod
 * @brief This class computes hamming distance bitwise using as input two strings
 * that can be built from byte arrays using provided static cast functions
 */
class
HammingMethod : public IDistanceMethod<std::string>
{
public:
    HammingMethod();
    virtual ~HammingMethod();

    /*!
     * @brief Return distance between to previously set blob inputs
     */
    virtual size_t run();

    /*!
     * @brief Static function to convert a given byte to string
     * @param [in] byte Input byte as uint8_t type
     * @return Value of byte variable as string
     */
    static std::string byte2str(const uint8_t byte);

    /*!
     * @brief Static function to convert a given array of byte to string
     * @param [in] blob Input array byte as uint8_t type
     * @return Value of array byte variable as string
     */
    static std::string blob2str(const std::vector<uint8_t>& blob);

public:
    typedef std::shared_ptr<HammingMethod>
        HammingMethodPtr; /*!< Smart pointer for HammingMethod */

protected:
    /*!
     * @brief Compute hamming distance bitwise using a small lookup table
     * @param [in] a First byte input
     * @param [in] b Second byte input
     * @return Computed distance
     */
    virtual uint8_t byteHammingDistance(const uint8_t a, const uint8_t b);
};

}
}

#endif //HAMMING_METHOD_HPP
