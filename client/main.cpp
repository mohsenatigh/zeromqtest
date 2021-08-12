#include "Generator.hpp"
#include "LinerPositionGenerator.hpp"
#include "ProtoSerializer.hpp"
#include "ZeroMQTransmiter.hpp"

/**
 * @brief Create a Generators object
 *
 * @param count number of clients
 */
void CreateGenerators(int count) {

  std::vector<std::shared_ptr<PositionInfo::Generator>> clients;

  auto transmiter = std::make_shared<PositionInfo::ZeroMQTransmiter>();
  auto protoSerializer = std::make_shared<PositionInfo::ProtoSerializer>();
  auto posGenerator = std::make_shared<PositionInfo::LinerPositionGenerator>();

  /**
   * create clients
   */
  for (int i = 0; i < count; i++) {
    auto obj = std::make_shared<PositionInfo::Generator>(
        posGenerator, protoSerializer, transmiter, i);

    obj->Init();

    clients.emplace_back(obj);
  }

  /**
   * create monitor loop
   *
   */
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    uint64_t totalPoints = 0;
    for (const auto &i : clients) {
      totalPoints += i->GetStat();
    }
    std::cout << "generate " << totalPoints << " event " << std::endl;
  }
}

int main(int argc, char *argv[]) {
  CreateGenerators(10);
  return 0;
}