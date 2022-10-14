#include <gflags/gflags.h>
#include <iostream>

DEFINE_string(name, "zhang san", "your name");
DEFINE_int32(age, 18, "your age");
DEFINE_int32(port, 8080, "udp port");

static bool ValidateAge(const char *flagname, int value) {
  if (value > 0 && value < 200) {
    return true;
  }
  printf("Invalid value for --%s: %d\n", flagname, (int)value);
  return false;
}

int main(int argc, char **argv) {
  static const bool age_dummy =
      gflags::RegisterFlagValidator(&FLAGS_age, &ValidateAge);
  google::SetVersionString("v1.09"); //设定，使用google::VersionString
  gflags::SetUsageMessage("./gflags");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  google::CommandLineFlagInfo info;
  if (GetCommandLineFlagInfo("port", &info) && info.is_default) {
    FLAGS_port = 27015;
  }
  std::cout << "your port is : " << FLAGS_port << std::endl;
  std::cout << "your name is : " << FLAGS_name << ", your age is: " << FLAGS_age
            << std::endl;

  return 0;
}
