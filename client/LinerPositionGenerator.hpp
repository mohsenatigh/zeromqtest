#pragma once
#include "client.hpp"
#include <cmath>

namespace PositionInfo {

/**
 * @brief Simple linear position generator
 *
 */
class LinerPositionGenerator final : public PositionInfo::IPositionGenerator {

public:
  /**
   * @brief
   *
   * @param time
   * @param maxX
   * @param maxY
   * @param noise
   * @param speed
   * @return PositionInfo::Data3d
   */
  PositionInfo::Data3d Generate(uint64_t time, float maxX = 100.0f,
                                float maxY = 100.0f, float noise = 0.30f,
                                float speed = 1.0f) override {

    PositionInfo::Data3d out;

    // expected position
    float cPos = (time * speed);

    //generate a random value between noise and -noise
    auto generateNoise = [&]() -> float {
      float nVal = fmod(rand(), (noise * 2)) - noise;
      return nVal;
    };

    // calculate next position
    auto getNextPos = [&](float max) -> float {
      float rt = (max * 2);
      float distance = fmod(cPos, rt);
      if (distance > max) {
        distance = max-(distance-max);
      }
      
      // apply noise
      distance = std::max(0.0f,generateNoise()+distance);
      return distance;
    };

    out.set_x(getNextPos(maxX));
    out.set_y(getNextPos(maxY));
    out.set_z(0);

    return out;
  }
};
} // namespace PositionInfo