#include <cparecord.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
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

    if (std::distance(tokens.begin(), tokens.end()) != 17)
    {
        return false;
    }

    auto token = tokens.begin();

    if ((*token).size() != 10) return false;
    m_details.sessionDate = *token;

    if ((*(++token)).size() != 50) return false;
    m_details.instrument = *token;

    if ((*(++token)).size() != 1) return false;
    m_details.orderSide = boost::lexical_cast<uint8_t>(*token);

    if ((*(++token)).size() != 15) return false;
    m_details.orderNumber = boost::lexical_cast<uint32_t>(*token);

    if ((*(++token)).size() != 15) return false;
    m_details.orderId = boost::lexical_cast<uint32_t>(*token);

    if ((*(++token)).size() != 3) return false;
    m_details.executionType = boost::lexical_cast<uint8_t>(*token);

    if ((*(++token)).size() != 15) return false;
    m_details.priorityTime = *token;

    if ((*(++token)).size() != 10) return false;
    m_details.priorityIndicator = boost::lexical_cast<uint32_t>(*token);

    if ((*(++token)).size() != 20) return false;
    std::size_t dotPos = (*token).find('.');
    if (dotPos == std::string::npos) return false;
    m_details.orderPriceInt = boost::lexical_cast<uint64_t>((*token).substr(0, dotPos));
    m_details.orderPriceDec = boost::lexical_cast<uint64_t>((*token).substr(dotPos+1));

    if ((*(++token)).size() != 18) return false;
    m_details.totalQuantity = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 18) return false;
    m_details.tradedQuantity = boost::lexical_cast<uint64_t>(*token);

    if ((*(++token)).size() != 10) return false;
    m_details.orderDate = *token;

    if ((*(++token)).size() != 19) return false;
    m_details.orderDatetime = *token;

    if ((*(++token)).size() != 1) return false;
    m_details.orderStatus = boost::lexical_cast<char>(*token);

    if ((*(++token)).size() != 1) return false;
    m_details.aggressor = boost::lexical_cast<uint8_t>(*token);

    if ((*(++token)).size() != 8) return false;
    m_details.member = boost::lexical_cast<uint32_t>(*token);

    return true;
}

std::string CpaRecord::str()
{
    std::ostringstream stream;
    boost::archive::text_oarchive archive(stream);
    archive << m_details;
    return stream.str();
}
