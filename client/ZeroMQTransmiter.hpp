#pragma once
#include "client.hpp"
#include <mutex>
#include <zmq.hpp>
namespace PositionInfo {
/**
 * @brief ZEROMQ
 *
 */
class ZeroMQTransmiter final : public PositionInfo::ITransmiter {
private:
  zmq::context_t context_;
  zmq::socket_t socket_ = {context_, ZMQ_PAIR};
  std::mutex lock_;
  bool connected_ = false;

public:
  /**
   * @brief
   *
   * @param addr
   * @return std::pair<bool, std::string>
   */
  std::pair<bool, std::string> Connect(const std::string &addr) override {

    /**
     * @brief we can use ZMQ monitor to monitor the connection status
     *
     */
    socket_.connect(addr);

    connected_ = true;
    return {true, ""};
  }

  /**
   * @brief
   *
   * @param msg
   * @return true
   * @return false
   */
  bool Transmit(const std::vector<uint8_t> &msg) override {
    std::lock_guard<std::mutex> gurd(lock_);
    if (!connected_) {
      return false;
    }
    
    zmq::message_t zmsg{msg.size()};
    memcpy(zmsg.data(), msg.data(), msg.size());
    if (socket_.send(zmsg, zmq::send_flags::none)) {
      return true;
    }
    return false;
  };
};

} // namespace PositionInfo