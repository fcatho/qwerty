#pragma once

#include <string>
#include <cstdint>

struct CpaRecordDetails
{
    std::string sessionDate;
    std::string instrument;
    uint8_t orderSide;
    uint32_t orderNumber;
    uint32_t orderId;
    uint8_t executionType;
    std::string priorityTime;
    uint32_t priorityIndicator;
    uint64_t orderPriceInt;
    uint64_t orderPriceDec;
    uint64_t totalQuantity;
    uint64_t tradedQuantity;
    std::string orderDate;
    std::string orderDatetime;
    char orderStatus;
    uint8_t aggressor;
    uint32_t member;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar & sessionDate;
        ar & instrument;
        ar & orderSide;
        ar & orderNumber;
        ar & orderId;
        ar & executionType;
        ar & priorityTime;
        ar & priorityIndicator;
        ar & orderPriceInt;
        ar & orderPriceDec;
        ar & totalQuantity;
        ar & tradedQuantity;
        ar & orderDate;
        ar & orderDatetime;
        ar & orderStatus;
        ar & aggressor;
        ar & member;
    }
};

class CpaRecord
{
public:
    CpaRecord();
    ~CpaRecord();
    bool loadDetails(const std::string& raw);
    std::string str();

private:
    CpaRecordDetails m_details;
};
