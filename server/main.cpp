#include "../common/message.pb.h"
#include <iostream>
#include <string>
#include <zmq.hpp>

/**
 * @brief simple ZeroMQ server for testing
 *
 */
void StartServer() {

  zmq::context_t context{1};
  zmq::socket_t socket{context, zmq::socket_type::pair};
  socket.bind("tcp://127.0.0.1:1111");
  while (true) {
    // request
    zmq::message_t request;
    PositionInfo::GeneratedPosition position;

    // receive a request from client
    if (socket.recv(request, zmq::recv_flags::none)) {
      if (request.size()) {
        position.ParseFromArray(request.data(), request.size());
        std::cout << position.DebugString() << std::endl;
      }
    }
  }
}

int main(int argc, char *argv[]) { StartServer(); }