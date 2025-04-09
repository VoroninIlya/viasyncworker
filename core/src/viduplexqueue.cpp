#include "viduplexqueue.hpp"

namespace viasyncworker {

  template<typename T, typename F>
  uint32_t ViDuplexQueue<T, F>::m_nextSubscriberId = 0;

  template<typename T, typename F>
  ViDuplexQueue<T, F>::ViDuplexQueue(){}

  template<typename T, typename F>
  uint32_t ViDuplexQueue<T, F>::addSubscriber(std::shared_ptr<IViSubscriber<T, F>> subscriber) {
    m_subscribers[m_nextSubscriberId] = std::move(subscriber);
    return m_nextSubscriberId++;
  }

  template<typename T, typename F>
  void ViDuplexQueue<T, F>::removeSubscriber(uint32_t id) {
    m_subscribers.erase(id);
  }

  template<typename T, typename F>
  void ViDuplexQueue<T, F>::pushIncoming(const T& elem) {
    std::lock_guard lock(m_incomingMutex);
    m_incoming.push_front(elem);

    for (auto& [id, ptr] : m_subscribers) {
      ptr->call(elem);
    }
  }

  template<typename T, typename F>
  T ViDuplexQueue<T, F>::popIncoming() {
    if(!hasIncoming())
      return T();

    std::lock_guard lock(m_incomingMutex);
    auto elem = m_incoming.back();
    m_incoming.pop_back();

    return elem;
  }

  template<typename T, typename F>
  void ViDuplexQueue<T, F>::pushOutgoing(const T& s) {
    std::lock_guard lock(m_outgoingMutex);
    m_outgoing.push_front(s);
  }

  template<typename T, typename F>
  T ViDuplexQueue<T, F>::popOutgoing() {
    if(!hasOutgoing())
      return T();

    std::lock_guard lock(m_outgoingMutex);
    auto elem = m_outgoing.back();
    m_outgoing.pop_back();

    return elem;
  }

  template<typename T, typename F>
  bool ViDuplexQueue<T, F>::hasIncoming() {
    std::lock_guard lock(m_incomingMutex);
    return !m_incoming.empty();
  }

  template<typename T, typename F>
  bool ViDuplexQueue<T, F>::hasOutgoing() {
    std::lock_guard lock(m_outgoingMutex);
    return !m_outgoing.empty();
  }

}