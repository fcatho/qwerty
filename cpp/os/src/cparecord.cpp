#include <cparecord.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include <sstream>

CpaRecord::CpaRecord()
{
}

CpaRecord::~CpaRecord()
{
}

bool CpaRecord::loadDetails(const std::string& raw)
{
    boost::char_separator<char> sep(";");
    boost::tokenizer<boost::char_separator<char>> tokens(raw, sep);

    if (std::distance(tokens.begin(), tokens.end()) != 16)
    {
        return false;
    }

    auto token = tokens.begin();

    if ((*token).size() != 10) return false;
    strcpy(m_details.sessionDate, (*token).c_str());
    //m_details.sessionDate = *token;

    if ((*(++token)).size() != 50) return false;
    strcpy(m_details.instrument, (*token).c_str());

    if ((*(++token)).size() != 1) return false;
    m_details.orderSide = boost::numeric_cast<uint8_t>(boost::lexical_cast<int>(*token) & 0xFF);

    if ((*(++token)).size() != 15) return false;
    m_details.orderNumber = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 15) return false;
    m_details.orderId = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 3) return false;
    m_details.executionType = boost::lexical_cast<uint16_t>(*token);

    if ((*(++token)).size() != 15) return false;
    strcpy(m_details.priorityTime, (*token).c_str());
    //m_details.priorityTime = *token;

    if ((*(++token)).size() != 10) return false;
    m_details.priorityIndicator = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 20) return false;

    std::size_t dotPos = (*token).find('.');
    if (dotPos == std::string::npos) return false;

    std::string first  = (*token).substr(0, dotPos);
    std::string second =  (*token).substr(dotPos + 1);
    boost::algorithm::trim(first);
    boost::algorithm::trim(second);
    m_details.orderPriceInt = boost::lexical_cast<uint64_t>(first);
    m_details.orderPriceDec = boost::lexical_cast<uint64_t>(second);

    if ((*(++token)).size() != 18) return false;
    m_details.totalQuantity = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 18) return false;
    m_details.tradedQuantity = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 10) return false;
    strcpy(m_details.orderDate, (*token).c_str());
    //m_details.orderDate = *token;

    if ((*(++token)).size() != 19) return false;
    strcpy(m_details.orderDatetime, (*token).c_str());
    //m_details.orderDatetime = *token;

    if ((*(++token)).size() != 1) return false;
    m_details.orderStatus = boost::lexical_cast<char>(*token);

    if ((*(++token)).size() != 1) return false;
    //m_details.aggressor = boost::lexical_cast<uint8_t>(*token);
    m_details.aggressor = boost::numeric_cast<uint8_t>(boost::lexical_cast<int>(*token) & 0xFF);

    if ((*(++token)).size() != 8) return false;
    m_details.member = boost::lexical_cast<uint32_t>(*token);

    return true;
}

std::string CpaRecord::pack()
{
    unsigned char packet[sizeof(CpaRecordDetails)];
    unsigned char *pp = packet;

    packValue(&pp, m_details.sessionDate, sizeof(m_details.sessionDate));
    packValue(&pp, m_details.instrument, sizeof(m_details.instrument));

    packValue(&pp, m_details.orderSide, 1);
    packValue(&pp, m_details.orderNumber, 8);
    packValue(&pp, m_details.orderId, 8);
    packValue(&pp, m_details.executionType, 2);

    packValue(&pp, m_details.priorityTime, sizeof(m_details.priorityTime));

    packValue(&pp, m_details.priorityIndicator, 8);
    packValue(&pp, m_details.orderPriceInt, 8);
    packValue(&pp, m_details.orderPriceDec, 8);
    packValue(&pp, m_details.totalQuantity, 8);
    packValue(&pp, m_details.tradedQuantity, 8);

    packValue(&pp, m_details.orderDate, sizeof(m_details.orderDate));
    packValue(&pp, m_details.orderDatetime, sizeof(m_details.orderDatetime));

    packValue(&pp, m_details.orderStatus, 1);
    packValue(&pp, m_details.aggressor, 1);
    packValue(&pp, m_details.member, 4);

    std::string str(packet, packet + sizeof(CpaRecordDetails));
    std::cout << str.size() << std::endl;
    str = "#" + str + "@";

    return str;
}

bool CpaRecord::unpack(const std::string& str)
{
    if (str.size() != sizeof(CpaRecordDetails))
    {
        return true;
    }

    const char* packet = str.c_str();
    unsigned char *pp = (unsigned char*) packet;

    unpackValue(&pp, m_details.sessionDate, 10 + 1);
    unpackValue(&pp, m_details.instrument, 50 + 1);

    unpackValue(&pp, m_details.orderSide, 1);
    unpackValue(&pp, m_details.orderNumber, 8);
    unpackValue(&pp, m_details.orderId, 8);
    unpackValue(&pp, m_details.executionType, 2);

    unpackValue(&pp, m_details.priorityTime, 15 + 1);

    unpackValue(&pp, m_details.priorityIndicator, 8);
    unpackValue(&pp, m_details.orderPriceInt, 8);
    unpackValue(&pp, m_details.orderPriceDec, 8);
    unpackValue(&pp, m_details.totalQuantity, 8);
    unpackValue(&pp, m_details.tradedQuantity, 8);

    unpackValue(&pp, m_details.orderDate, 10 + 1);
    unpackValue(&pp, m_details.orderDatetime, 19 + 1);

    unpackValue(&pp, m_details.orderStatus, 1);
    unpackValue(&pp, m_details.aggressor, 1);
    unpackValue(&pp, m_details.member, 4);

    return true;
}

void CpaRecord::print()
{
    m_details.print();
}
