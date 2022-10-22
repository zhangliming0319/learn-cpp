#include <chrono>
class ElapsedTime {
private:
  std::chrono::high_resolution_clock::time_point _t1, _t2;

public:
  inline void MarkStart() { _t1 = std::chrono::high_resolution_clock::now(); }
  inline void MarkEnd() { _t2 = std::chrono::high_resolution_clock::now(); }
  inline double GetElapsedTime() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(_t2 - _t1)
        .count();
  }
  double GetCurrentTime() {
    return (static_cast<double>(std::chrono::high_resolution_clock::now()
                                    .time_since_epoch()
                                    .count()) *
            std::chrono::system_clock::period::num /
            std::chrono::system_clock::period::den);
  }
};
