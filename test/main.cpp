#include "rx_time_utils.hpp"
#include "rx_file_utils.hpp"
#include <chrono>

using namespace rx::timeutils;
using namespace std::chrono;

inline void test_nolock_once(){
    char buf[100];
    time_t t = time(0);
    struct tm tm;
    nolocks_localtime(&tm, t);
//    strftime(buf,sizeof(buf), "%Y%m%d %H:%M:%S",&tm);
//    std::cout << buf << std::endl;
}

inline void test_localtime_once() {
    char buf[100];
    time_t t = time(0);
    struct tm *tm = localtime(&t);
//    strftime(buf,sizeof(buf), "%Y%m%d %H:%M:%S",tm);
//    std::cout << buf << std::endl;
}

void test(int times) {
  auto s1 = std::chrono::steady_clock::now();
  for(auto i = 0; i < times; i++) {
    test_nolock_once();
  }
  auto e1 = std::chrono::steady_clock::now();
  auto t1 = std::chrono::duration_cast<microseconds>(e1-s1);
  std::cout << "nolocks_time:" << t1.count() << " us" << std::endl;

  auto s2 = std::chrono::steady_clock::now();
  for (auto j = 0; j < times; j++){
    test_localtime_once();
  }
  auto e2 = std::chrono::steady_clock::now();
  auto t2 = std::chrono::duration_cast<microseconds>(e2-s2);
  std::cout << "localtime:" << t2.count() << " us" << std::endl;
}

namespace test_file_uils {
  void test01 () {
    cout << rx::fileutils::is_file("makefile") << endl;
    cout << rx::fileutils::is_file("makefile.inc") << endl;
    cout << rx::fileutils::is_file("../test/") << endl;

    cout << rx::fileutils::is_dir("../test/") << endl;
    cout << rx::fileutils::is_dir("../test1/") << endl;
    cout << rx::fileutils::is_dir("makefile") << endl;

    vector<string> files;
    rx::fileutils::extract_filename("./", files, true);
    for (auto i = 0; i < files.size(); i++) {
      cout << i << "=" << files[i] << endl;
    }
  
    cout <<  rx::fileutils::mkdir_n("level_1") << endl;
    cout <<  rx::fileutils::mkdir_n("1level/2level") << endl;
    cout <<  rx::fileutils::mkdir_n("level_1/2level") << endl;
    cout <<  rx::fileutils::mkdir_n("o/newd2/yes/ok/no/", true) << endl;
    vector<string> lines;
    cout <<  rx::fileutils::get_lines("makefile", lines) << endl;
    for (auto i : lines) {
      cout << i << endl;
    }
  }

}
int main(int argc, char * argv[]) {
  if (argc < 2) { std::cerr << "usage:" << argv[0] << " times{like 5}" << std::endl; return -1;}

  test(atoi(argv[1]));

  char buf[128]; 
  current_s(buf, 128, "%Y%m%d %H:%M:%S");
  std::cout << "yyyymmdd hhmmss:" << buf << std::endl;
  current_s(buf, 128, "%H%M");
  std::cout << "mmss:" << buf << std::endl;
  std::cout << "hhmmss" << current_s() << std::endl;
  std::cout << "yyyymmdd:" << today_s() << std::endl;

  test_file_uils::test01();
  return 0;
}

