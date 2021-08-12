#pragma once
#include "client.hpp"

namespace PositionInfo {

/**
 * @brief Protobuf serializer
 *
 */
class ProtoSerializer final : public PositionInfo::ISerializer {
public:
  /**
   * @brief
   *
   * @param obj
   * @return std::vector<uint8_t>
   */
  std::vector<uint8_t>
  Serialize(const PositionInfo::GeneratedPosition &obj) override {
    auto objSize = obj.ByteSizeLong();
    std::vector<uint8_t> out(objSize);

    // serialize
    if (!obj.SerializeToArray(out.data(), objSize)) {
      return {};
    }
    return out;
  }
};
} // namespace PositionInfo
