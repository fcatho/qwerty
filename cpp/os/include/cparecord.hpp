#pragma once

#include <iostream>
#include <cstring>
#include <cstdint>

struct CpaRecordDetails
{
    //static const CPA_SESSION_DATE_LEN = 10;
    //static const CPA_INSTRUMENT_LEN = 50;
    //static const CPA_PRIORITY_TIME_LEN = 15;
    //static const CPA_ORDER_DATE_LEN = 10;
    //static const CPA_ORDER_DATE_TIME_LEN = 19;

    char sessionDate[11];
    char instrument[51];
    uint8_t orderSide = 0;
    uint64_t orderNumber = 0;
    uint64_t orderId = 0;
    uint16_t executionType = 0;
    char priorityTime[16];
    uint64_t priorityIndicator = 0;
    uint64_t orderPriceInt = 0;
    uint64_t orderPriceDec = 0;
    uint64_t totalQuantity = 0;
    uint64_t tradedQuantity = 0;
    char orderDate[11];
    char orderDatetime[20];
    char orderStatus = 0;
    uint8_t aggressor = 0;
    uint32_t member = 0;

    void print()
    {
        std::cout << sessionDate << ";"
                  << instrument << ";"
                  << (int)orderSide << ";"
                  << orderNumber << ";"
                  << orderId << ";"
                  << executionType << ";"
                  << priorityTime << ";"
                  << priorityIndicator << ";"
                  << orderPriceInt << "."
                  << orderPriceDec << ";"
                  << totalQuantity << ";"
                  << tradedQuantity << ";"
                  << orderDate << ";"
                  << orderDatetime << ";"
                  << orderStatus << ";"
                  << (int) aggressor << ";"
                  << member << std::endl;

    }
};

class CpaRecord
{
public:
    CpaRecord();
    ~CpaRecord();

    bool loadDetails(const std::string& raw);
    std::string pack();
    bool unpack(const std::string& str);
    void print();

private:
    CpaRecordDetails m_details;

    template<class T>
    void packValue(unsigned char** p, T t, const int n)
    {
        for (int i = 0; i < n; ++i)
        {
            **p = 0xFF & (t >> (8*i));
            (*p)++;
        }
    }

    void packValue(unsigned char** p, char* c, const int n)
    {
        std::memcpy(*p, c, n);
        (*p) += n;
    }


    template<class T>
    void unpackValue(unsigned char** p, T& t, const int n)
    {
        for (int i = 0; i < n; ++i)
        {
            t |= (((T)(**p)) << (8*i));
            (*p)++;
        }
    }

    void unpackValue(unsigned char** p, char* c, const int n)
    {
        std::memcpy(c, *p, n);
        (*p) += n;
    }

    //static const std::size_t CPA_DETAILS_LEN = 200;
};
