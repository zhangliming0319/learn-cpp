#pragma once
#include <chrono>

class Timer {
   private:
    std::chrono::high_resolution_clock::time_point t1_, t2_;
    void MarkEnd() { t2_ = std::chrono::high_resolution_clock::now(); }

   public:
    explicit Timer() {
        MarkStart();
    }
    void MarkStart() { t1_ = std::chrono::high_resolution_clock::now(); }
    
    double GetElapsedTime() {
      MarkEnd();
      return std::chrono::duration_cast<std::chrono::duration<double>>(t2_ - t1_).count();
    }
    static double CurrentTime() {
      return (static_cast<double>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) *
            std::chrono::system_clock::period::num / std::chrono::system_clock::period::den);
    }
};

