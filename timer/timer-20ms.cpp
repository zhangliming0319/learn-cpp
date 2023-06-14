#include <chrono>
namespace timer {
class ElapsedTime {
 private:
  std::chrono::system_clock::time_point _t1, _t2;

 public:
  inline void   MarkStart() { _t1 = std::chrono::system_clock::now(); }
  inline void   MarkEnd() { _t2 = std::chrono::system_clock::now(); }
  inline double GetElapsedTime() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(_t2 - _t1).count();
  }
};

double CurrentTime() {
  return (static_cast<double>(std::chrono::system_clock::now().time_since_epoch().count())
          * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den);
}
}  // namespace timer
#ifndef _WIN32
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr int  PORT      = 8080;         // 目标端口
constexpr auto TARGET_IP = "127.0.0.1";  // 目标 IP 地址
constexpr auto PERIOD_NS = 20'000'000;   // 发送周期 (20ms in nanoseconds)

// 设置定时器
int setup_timer() {
  int timer_fd = timerfd_create(CLOCK_REALTIME, 0);
  if (timer_fd < 0) {
    throw std::runtime_error("Error: Failed to create timer.");
  }

  timespec period{};
  period.tv_sec  = 0;
  period.tv_nsec = PERIOD_NS;

  itimerspec timer_spec{};
  timer_spec.it_interval = period;
  timer_spec.it_value    = period;  // 第一次触发的时间（可以根据需要设置）

  if (timerfd_settime(timer_fd, 0, &timer_spec, nullptr) < 0) {
    close(timer_fd);
    throw std::runtime_error("Error: Failed to set timer.");
  }

  return timer_fd;
}

int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    throw std::runtime_error("Error: Failed to create socket.");
  }

  sockaddr_in target_address{};
  std::memset(&target_address, 0, sizeof(target_address));
  target_address.sin_family = AF_INET;
  target_address.sin_port   = htons(PORT);
  if (inet_pton(AF_INET, TARGET_IP, &target_address.sin_addr) <= 0) {
    close(sockfd);
    throw std::runtime_error("Error: Invalid address or address not supported.");
  }

  int timer_fd = setup_timer();

  uint64_t    expired_times;
  std::string message   = "Hello from LINUX C++ UDP client!";
  double      last_time = timer::CurrentTime();
  double      max_delta_t, avg_delta_t = 0.0;
  double      min_delta_t = 100.0;
  while (read(timer_fd, &expired_times, sizeof(uint64_t)) > 0) {
    double now     = timer::CurrentTime();
    auto   delta_t = now - last_time;
    min_delta_t    = delta_t < min_delta_t ? delta_t : min_delta_t;
    max_delta_t    = delta_t > max_delta_t ? delta_t : max_delta_t;

    std::cout << std::fixed << std::setprecision(8) << " now: " << now << " delta-time: " << delta_t << "("
              << min_delta_t << "," << max_delta_t << ")" << std::endl;
    last_time = now;

    // sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&target_address, sizeof(target_address));
  }

  close(timer_fd);
  close(sockfd);
  return 0;
}

#else
#define _WIN32_WINNT 0x600
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <fcntl.h>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")
using std::chrono_literals::operator""ms;

constexpr int  PORT      = 8080;         // 目标端口
constexpr auto TARGET_IP = "127.0.0.1";  // 目标 IP 地址
constexpr auto PERIOD_MS = 20ms;         // 发送周期

int main() {
  WSADATA wsaData;
  int     result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0) {
    throw std::runtime_error("Error: Failed to initialize Winsock.");
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    WSACleanup();
    throw std::runtime_error("Error: Failed to create socket.");
  }

  sockaddr_in target_address{};
  std::memset(&target_address, 0, sizeof(target_address));
  target_address.sin_family = AF_INET;
  target_address.sin_port   = htons(PORT);
  if (inet_pton(AF_INET, TARGET_IP, &target_address.sin_addr) <= 0) {
    closesocket(sockfd);
    WSACleanup();
    throw std::runtime_error("Error: Invalid address or address not supported.");
  }

  auto        next_wake_time = std::chrono::steady_clock::now() + PERIOD_MS;
  std::string message        = "Hello from WINDOWS C++ UDP client!";
  double      last_time      = timer::CurrentTime();
      //std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
      /// 1000.0;
  double      max_delta_t = 0.0, avg_delta_t = 0.0;
  double      min_delta_t = 100.0;
  Sleep(20);
  while (true) {
    //sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&target_address, sizeof(target_address));
    auto now_unix = std::chrono::system_clock::now();

    auto duration_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now_unix.time_since_epoch());

    // 计算当前的 Unix 时间戳（精确到毫秒）
    double current_unix_time_ms = duration_since_epoch.count()/1000.0;
    double now                  = timer::CurrentTime();
    auto   delta_t              = now - last_time;
    min_delta_t                 = delta_t < min_delta_t ? delta_t : min_delta_t;
    max_delta_t                 = delta_t > max_delta_t ? delta_t : max_delta_t;

    std::cout << std::fixed << std::setprecision(8) << " now: " << now << " delta-time: " << delta_t << "("
              << min_delta_t << "," << max_delta_t << ")" << std::endl;
    last_time = now;
    // 打印当前的 Unix 时间戳
    //std::cout << "Current Unix timestamp (ms): " << current_unix_time_ms/1000.0 << " seconds" << std::endl;

    std::this_thread::sleep_until(next_wake_time);
    next_wake_time += PERIOD_MS;
  }

  closesocket(sockfd);
  WSACleanup();

  return 0;
}
#endif