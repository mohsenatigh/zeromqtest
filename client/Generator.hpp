#pragma once
#include "client.hpp"
#include <chrono>
#include <memory>
#include <thread>

namespace PositionInfo {

class Generator {
private:
  using PosGenerator = std::shared_ptr<PositionInfo::IPositionGenerator>;
  using Serializer = std::shared_ptr<PositionInfo::ISerializer>;
  using Transmiter = std::shared_ptr<PositionInfo::ITransmiter>;

  PosGenerator pGenerator_;
  Serializer serializer_;
  Transmiter transmitter_;
  uint64_t id_ = 0;

  bool isActive_ = false;
  std::thread thread_;

  uint64_t posSend_ = 0;

  /**
   * @brief generator routine
   *
   */
  void GenerateThread() {
    uint64_t time = 0;
    while (isActive_) {
      PositionInfo::GeneratedPosition pos;
      std::this_thread::sleep_for(std::chrono::seconds(1));

      // fill position object
      auto allocatedPos = pGenerator_->Generate(time);
      pos.set_sensorid(id_);
      pos.set_timestamp_usec(time);
      pos.set_allocated_position(&allocatedPos);

      // serialize
      auto buffer = serializer_->Serialize(pos);
      if (buffer.size()) {
        transmitter_->Transmit(buffer);
      }

      // get ownership of the object
      pos.release_position();

      posSend_++;

      
      time++;
    }
  }

public:
  /**
   * @brief Construct a new Generator object
   *
   * @param gen
   * @param ser
   * @param trans
   */
  Generator(PosGenerator gen, Serializer ser, Transmiter trans, uint64_t id)
      : pGenerator_(gen), serializer_(ser), transmitter_(trans), id_(id) {}

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool Init(const std::string &host = "tcp://127.0.0.1:1111") {
    if (auto [res, err] = transmitter_->Connect(host); res == false) {
      std::cerr << "can not init transmiter with error " << err << std::endl;
      return false;
    }
    isActive_ = true;
    thread_ = std::thread(&Generator::GenerateThread, this);
    return true;
  }

  /**
   * @brief Destroy the Generator object
   *
   */
  ~Generator() {
    isActive_ = false;
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  uint64_t GetStat() const { return posSend_; }
};

} // namespace PositionInfo