#include "OrderCache.h"
#include <memory>
#include <list>

const std::string OrderCache::BUY_SIDE = "Buy";

OrderCache::OrderCache()
  : m_sequence(1)
{
}

void OrderCache::addOrder(Order order)
{
  std::unique_lock<std::shared_mutex> lock(m_mutex);
  auto result = m_orderIdToSequence.try_emplace(order.orderId(), m_sequence);
  if (result.second)
  {
    auto * emplaced = &(m_orders.try_emplace(m_sequence, order).first->second);
    m_ordersBySecurity.try_emplace(order.securityId()).first->second.emplace(m_sequence);
    m_ordersByUser.try_emplace(order.user()).first->second.emplace(m_sequence);
    m_ordersBySecuritySortByQty
      .try_emplace(order.securityId()).first->second
        .try_emplace(order.qty()).first->second
          .emplace(m_sequence);
    m_sequence++;
  }
}

void OrderCache::cancelOrder(const std::string& orderId)
{
  std::unique_lock<std::shared_mutex> lock(m_mutex);
  auto it = m_orders.find(sequence(orderId));
  if (it != m_orders.end())
  {
    auto & order = it->second;
    eraseOrderBySecurity(order);
    eraseOrderBySecuritySortByQty(order);
    eraseOrderByUser(order);
    m_orders.erase(it);
  }
}

void OrderCache::cancelOrdersForUser(const std::string& user)
{
  std::unique_lock<std::shared_mutex> lock(m_mutex);
  auto it = m_ordersByUser.find(user);
  if (it != m_ordersByUser.end())
  {
    for (auto & sequence : it->second)
    {
      auto & order = m_orders.at(sequence);
      eraseOrderBySecurity(order);
      eraseOrderBySecuritySortByQty(order);
      m_orders.erase(sequence);
    }

    m_ordersByUser.erase(it);
  }
}

void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
  std::unique_lock<std::shared_mutex> lock(m_mutex);
  auto itBySecSortByQty = m_ordersBySecuritySortByQty.find(securityId);
  if (itBySecSortByQty != m_ordersBySecuritySortByQty.end())
  {
    auto & sortByQty = itBySecSortByQty->second;
    auto low = sortByQty.lower_bound(minQty);
    for (auto itSortByQty = low; itSortByQty != sortByQty.end(); )
    {
      for (auto & sequence : itSortByQty->second)
      {
        auto & order = m_orders.at(sequence);
        eraseOrderBySecurity(order);
        eraseOrderByUser(order);
        m_orders.erase(sequence);
      }
      sortByQty.erase(itSortByQty++);
    }
  }
}

unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
  std::shared_lock<std::shared_mutex> lock(m_mutex);
  auto itBySecurity = m_ordersBySecurity.find(securityId);
  if (itBySecurity == m_ordersBySecurity.end())
  {
    return 0;
  }

  std::list<BookEntry> bid;
  std::list<BookEntry> ask;
  unsigned int matchingSize = 0;

  auto match = [](const Order & order,
      std::list<BookEntry> & side,
      std::list<BookEntry> & counterparty)
  {
    auto remainingQty = order.qty();
    for (auto book_entry = counterparty.begin(); book_entry != counterparty.end(); )
    {
      if (book_entry->company == order.company())
      {
        ++book_entry;
      }
      else
      {
        if (remainingQty > book_entry->qty)
        {
          remainingQty -= book_entry->qty;
          counterparty.erase(book_entry++);
        }
        else
        {
          book_entry->qty -= remainingQty;
          remainingQty = 0;
          break;
        }
      }
    }

    if (remainingQty)
    {
      side.emplace_back(BookEntry{order.company(), remainingQty});
    }
    return order.qty() - remainingQty;
  };

  auto orderSequences = itBySecurity->second;
  for (auto & orderSequence : orderSequences)
  {
    auto order = m_orders.at(orderSequence);
    matchingSize += order.side() == BUY_SIDE
      ? match(order, bid, ask)
      : match(order, ask, bid);
  }

  return matchingSize;
}

std::vector<Order> OrderCache::getAllOrders() const
{
  std::shared_lock<std::shared_mutex> lock(m_mutex);
  std::vector<Order> orders;
  orders.reserve(m_orders.size());
  for (auto & item : m_orders)
  {
    orders.emplace_back(item.second);
  }

  return std::move(orders);
}

std::size_t OrderCache::sequence(const std::string & orderId)
{
  auto it = m_orderIdToSequence.find(orderId);
  if (it != m_orderIdToSequence.end())
  {
    return it->second;
  }
  return 0;
}

void OrderCache::eraseOrderBySecurity(const Order & order)
{
  auto itBySecurity = m_ordersBySecurity.find(order.securityId());
  if (itBySecurity != m_ordersBySecurity.end())
  {
    itBySecurity->second.erase(sequence(order.orderId()));
  }
}

void OrderCache::eraseOrderBySecuritySortByQty(const Order & order)
{
  auto itBySecSortByQty = m_ordersBySecuritySortByQty.find(order.securityId());
  if (itBySecSortByQty != m_ordersBySecuritySortByQty.end())
  {
    auto itSortByQty = itBySecSortByQty->second.find(order.qty());
    if (itSortByQty != itBySecSortByQty->second.end())
    {
      itSortByQty->second.erase(sequence(order.orderId()));
    }
  }
}

void OrderCache::eraseOrderByUser(const Order & order)
{
  auto itByUser = m_ordersByUser.find(order.user());
  if (itByUser != m_ordersByUser.end())
  {
    itByUser->second.erase(sequence(order.orderId()));
  }
}

