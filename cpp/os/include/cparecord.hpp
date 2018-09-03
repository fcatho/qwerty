#pragma once

#include <iostream>
#include <string>
#include <cstdint>

struct CpaRecordDetails
{
    std::string sessionDate;
    std::string instrument;
    uint8_t orderSide;
    uint64_t orderNumber;
    uint64_t orderId;
    uint16_t executionType;
    std::string priorityTime;
    uint64_t priorityIndicator;
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

    void print()
    {
        std::cout << "sessionDate: " << sessionDate << std::endl;
        std::cout << "instrument: " << instrument << std::endl;
        std::cout << "orderSide: " << orderSide << std::endl;
        std::cout << "orderNumber: " << orderNumber << std::endl;
        std::cout << "orderId: " << orderId << std::endl;
        std::cout << "executionType: " << executionType << std::endl;
        std::cout << "priorityTime: " << priorityTime << std::endl;
        std::cout << "priorityIndicator: " << priorityIndicator << std::endl;
        std::cout << "orderPriceInt: " << orderPriceInt << std::endl;
        std::cout << "orderPriceDec: " << orderPriceDec << std::endl;
        std::cout << "totalQuantity: " << totalQuantity << std::endl;
        std::cout << "tradedQuantity: " << tradedQuantity << std::endl;
        std::cout << "orderDate: " << orderDate << std::endl;
        std::cout << "orderDatetime: " << orderDatetime << std::endl;
        std::cout << "orderStatus: " << orderStatus << std::endl;
        std::cout << "aggressor: " << aggressor << std::endl;
        std::cout << "member: " << member << std::endl;
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
