#include <iostream>

#include <functional> // fucntion/bind

class ClassCalled {
public:
  void FunCalled1() {
    std::cout << "ClassCalled.FunCalled1() called.." << std::endl;
  }

  void FunCalled2() {
    std::cout << "ClassCalled.FunCalled2() called.." << std::endl;
  }
  bool FunCalled5(int s) {
    std::cout << "ClassCalled.FunCalled2() called.. " << s << std::endl;
    return s > 0;
  }

  static void FunCalled3() {
    std::cout << "ClassCalled.FunCalled3() called.." << std::endl;
  }
};

class ClassCaller {
  using CallbackFun = std::function<void()>;
  using CallbackFunBool = std::function<bool(int s)>;

public:
  void FunCaller(CallbackFun callback) {
    std::cout << "ClassCaller.FunCaller() called.." << std::endl;
    callback();
  }
  bool FunCallerBool(CallbackFunBool callback, int s) {
    std::cout << "ClassCaller.CallbackFunBool() called.." << std::endl;
    return callback(s);
  }
};

void GlobalFun() { std::cout << "GlobalFun() called.." << std::endl; }

int main(int argc, char **argv) {
  printf("\n-------------\n");
  ClassCalled called;
  called.FunCalled1();
  int var = int(atoi(argv[1]));
  ClassCaller caller;
  caller.FunCaller(GlobalFun);
  caller.FunCaller(ClassCalled::FunCalled3);
  caller.FunCaller(std::bind(&ClassCalled::FunCalled2, &called));
  auto temp = caller.FunCallerBool(
      std::bind(&ClassCalled::FunCalled5, &called, std::placeholders::_1), var);
  std::cout << "return : " << temp << std::endl;
  printf("\n-------------\n");
}
