
#include "elapsed_time.h"
#include <dirent.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>

DEFINE_bool(verbose, false, "whether to print log"); // 调试开关
DEFINE_double(rate, 2.0, "");                        // 代替宏定义

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
std::string GetCurrentPath() {
  char curr_path[1024];
#ifdef _WIN32
  ::GetModuleFileName(NULL, curr_path, MAX_PATH);
  (_tcsrchr(curr_path, '\\'))[1] = 0;
#else
  getcwd(curr_path, 1024);
  sprintf(curr_path, "%s/", curr_path);
#endif
  std::string str_curr_path = curr_path;
  return str_curr_path;
}
/*     FLAGS_log_dir = "./"; // 设置log输出文件夹，默认输出到本地/tmp文件夹下
  FLAGS_logtostderr = 1; // 设置log输出到stderr，不保存到本地
  FLAGS_alsologtostderr = 1; // 设置log输出到stderr和本地
  FLAGS_stderrthreshold = 1; //
  WARNING以及更高级别的log将会记录到stderr中；(INFO: 0, WARNING: 1, ERROR: 2
   FATAL: 3)
  FLAGS_minloglevel = 0; //   默认是0，INFO以及更高级别的Log将会被记录；(INFO:
   0, WARNING: 1, ERROR: 2 FATAL: 3)
  FLAGS_colorlogtostderr = 1; // 设置记录到标准输出的颜色消息（如果终端支持）
  FLAGS_log_prefix = true; //   设置日志前缀是否应该添加到每行输出
   FLAGS_logbufsecs = 0;//   设置可以缓冲日志的最大秒数，0指实时输出
   FLAGS_max_log_size =10;//   设置最大日志文件大小（以MB为单位）
  FLAGS_stop_logging_if_full_disk = true; //
   设置是否在磁盘已满时避免日志记录到磁盘 */
int main(int argc, char *argv[]) {
  static const bool age_dummy =
      gflags::RegisterFlagValidator(&FLAGS_age, &ValidateAge);
  google::SetVersionString("v1.09"); //设定，使用google::VersionString
  gflags::SetUsageMessage("\nusage: ./test --log_dir <log_path>");
  google::ParseCommandLineFlags(&argc, &argv, true); // 初始化gflags

  FLAGS_logbuflevel = -1;
  FLAGS_max_log_size = 100;
  // FLAGS_logtostderr = 1; // lone
  FLAGS_colorlogtostderr = 1;
  google::InstallFailureSignalHandler();
  std::string log_path;

  log_path = GetCurrentPath() + "log";

  if (!FLAGS_log_dir.empty()) {
    FLAGS_log_dir = log_path;
  }
  if (NULL == opendir(FLAGS_log_dir.c_str()))
    mkdir(FLAGS_log_dir.c_str(), 0775);
  google::InitGoogleLogging(argv[0]); // 初始化glog
  google::SetLogFilenameExtension("log");
  google::SetStderrLogging(google::GLOG_INFO);

  if (FLAGS_log_dir.empty()) {
    gflags::ShowUsageWithFlagsRestrict(argv[0], "main");
    LOG(ERROR) << "FLAGS_log_dir is empty !";
  }
  CHECK(!FLAGS_log_dir.empty()) << "log_dir is empty";

  for (int index = 0; index <= 10; ++index) {
    LOG(INFO) << "index: " << index;
    LOG_IF(INFO, index > 5) << "  --> index > 5"; // 当index > 5时输出log
    LOG_EVERY_N(WARNING, 5) << "  --> index % 5 == 0"; // 每隔5次输出一次log
    LOG_IF_EVERY_N(ERROR, index < 5, 2)
        << "  --> index < 5, i % 2 == 0"; // 当index < 5时每隔2次输出一次log；
    LOG_FIRST_N(INFO, 8) << "  --> index < 8"; // 输出前8次log
  }
  ElapsedTime et;
  et.MarkStart();
  VLOG(0) << "VLOG 0: ";
  VLOG(1) << "VLOG 1: ";
  VLOG(2) << "VLOG 2: ";
  VLOG(3) << "VLOG 3: ";
  et.MarkEnd();
  VLOG(1) << "vlog const time:" << et.GetElapsedTime();
  VLOG(1) << std::setprecision(15) << "chrono time now:" << et.GetCurrentTime();

  DLOG(INFO) << "Debug Mode Message!"; // debug模式输出log，release模式不输出
  google::ShutdownGoogleLogging();

  return 0;
}