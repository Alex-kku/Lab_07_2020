// Copyright 2021 Kushpelev Alexei leha.kushpelev@mail.ru

#ifndef INCLUDE_SUGGEST_HPP_
#define INCLUDE_SUGGEST_HPP_

#include <algorithm>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <shared_mutex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using nlohmann::json;

class Server {
 public:
  Server();
  int startServer(int argc, char* argv[]);

 private:
  uint16_t port;
  std::shared_ptr<std::string> doc_root;
};

#endif  // INCLUDE_SUGGEST_HPP_
