#ifndef DUMMY_METHOD_HPP
#define DUMMY_METHOD_HPP

#include <idistance_method.hpp>
#include <iostream>
#include <memory>

/*!
 * @class DummyMethod
 * @brief This class is just an example to show how to build
 * a new distance method from IDistanceMethod interface
 */
class
DummyMethod : public IDistanceMethod<int>
{
public:
    /*!
     * @brief Default ctor
     */
    DummyMethod();

    /*!
     * @brief Default dtor
     */
    virtual ~DummyMethod();

    /*!
     * @brief Return 0 is previously set inputs are equal, 1 otherwise
     * @return Computed distance as described before
     */
    virtual size_t run();

public:
    typedef std::shared_ptr<DummyMethod>
        DummyMethodPtr; /*!< Smart pointer for DummyMethodPtr */

};

#endif //DUMMY_METHOD_HPP
