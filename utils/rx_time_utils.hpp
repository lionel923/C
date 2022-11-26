#include <iostream>
#include <string>
#include <unistd.h>


namespace rx {
  namespace timeutils {
    int current_s(char *buf, int max, const char *format);
    int current_s();
    int today_s();

    void nolocks_localtime(struct tm *tmp, time_t t); // copy from redis src, sovle localtime thread-safe problem
    int is_leap_year(time_t year);
  }
}

