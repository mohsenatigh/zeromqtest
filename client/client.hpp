#pragma once
#include "../common/message.pb.h"
#include <cstdint>
#include <vector>

namespace PositionInfo {

/**
 * @brief Serialize interface. it is possible to have different serializer with
 * different  output type
 */
class ISerializer {
public:
  /**
   * @brief
   *
   * @param obj position object
   * @return std::vector<uint8_t>
   */
  virtual std::vector<uint8_t>
  Serialize(const PositionInfo::GeneratedPosition &obj) = 0;
};

/**
 * @brief
 *
 */
class ITransmiter {
public:
  /**
   * @brief
   *
   * @param address server address
   * @return std::pair<bool,std::string> return <RESULT,ERROR MSG in case of
   * error>
   */
  virtual std::pair<bool, std::string> Connect(const std::string& address) = 0;

  /**
   * @brief
   *
   * @param msg
   * @return true In case of successful data transmission
   * @return false
   */
  virtual bool Transmit(const std::vector<uint8_t> &msg) = 0;
};

/**
 * @brief
 *
 */
class IPositionGenerator {
public:
  /**
   * @brief 
   * 
   * @param time 
   * @param maxZ 
   * @param maxY 
   * @param noise 
   * @param speed 
   * @return PositionInfo::GeneratedPosition 
   */
  virtual PositionInfo::Data3d Generate(uint64_t time,float maxX=100.0f,float maxY=100.0f,float noise=0.3f,float speed=1.0f) = 0;
};

} // namespace PositionInfo
