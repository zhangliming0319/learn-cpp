#include <functional>  // fucntion/bind
#include <iostream>

class ClassCalled {
 public:
  void FunCalled1() { std::cout << "ClassCalled.FunCalled1() called.." << std::endl; }

  void FunCalled2() { std::cout << "ClassCalled.FunCalled2() called.." << std::endl; }
  bool FunCalled5(int s) {
    std::cout << "ClassCalled.FunCalled2() called.. " << s << std::endl;
    return s > 0;
  }

  static void FunCalled3() { std::cout << "ClassCalled.FunCalled3() called.." << std::endl; }
};

class ClassCaller {
  using CallbackFun     = std::function<void()>;
  using CallbackFunBool = std::function<bool(int s)>;

 public:
  void FunCaller(CallbackFun callback) {
    std::cout << "ClassCaller.FunCaller() called.." << std::endl;
    callback();
  }
  void FunCaller() { callback_(); }
  bool FunCaller(int s) { callbackbool_(s); }
  bool FunCallerBool(CallbackFunBool callback, int s) {
    std::cout << "ClassCaller.CallbackFunBool() called.." << std::endl;
    return callback(s);
  }
  void RegisteCallback(CallbackFun callback) { callback_ = callback; }
  void RegisteCallback(CallbackFunBool callback) { callbackbool_ = callback; }

 private:
  CallbackFun     callback_;
  CallbackFunBool callbackbool_;
};

void GlobalFun() {
  std::cout << "GlobalFun() called.." << std::endl;
}

int main(int argc, char** argv) {
  printf("\n-------------\n");
  ClassCalled called;
  called.FunCalled1();
  int         var = atoi(argv[1]);
  ClassCaller caller;
  caller.RegisteCallback(GlobalFun);
  caller.FunCaller();
  caller.RegisteCallback(ClassCalled::FunCalled3);
  caller.FunCaller();
  caller.RegisteCallback(std::bind(&ClassCalled::FunCalled2, &called));
  caller.FunCaller();
  caller.RegisteCallback(std::bind(&ClassCalled::FunCalled5, &called, std::placeholders::_1));
  auto temp = caller.FunCaller(var);

  std::cout << "return : " << temp << std::endl;
  printf("\n-------------\n");
}
