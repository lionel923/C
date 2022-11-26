#include "rx_time_utils.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <unistd.h>

using namespace std;

namespace rx {
  namespace timeutils {
    int current_s(char *buf, int max, const char *format) {	
        time_t t = time(0);
	struct tm tm;
	nolocks_localtime(&tm, t);
	strftime(buf, max, format,&tm);
	return 0;
    }

    int current_s() {
	char buf[128];
	current_s(buf, 128, "%H%M%S");
	return atoi(buf);
    }

    int today_s() {
	time_t t = time(0);
	struct tm tm;
	nolocks_localtime(&tm, t);
	char buf[128];
	strftime(buf,sizeof(buf), "%Y%m%d",&tm);
	return atoi(buf);
    }

  void nolocks_localtime(struct tm *tmp, time_t t) {
    if (!tmp) {
        return;
    }
    const time_t secs_min = 60;
    const time_t secs_hour = 3600;
    const time_t secs_day = 3600*24;

    t -= -28800;                         
    //t += 3600*dst;                      
    time_t days = t / secs_day;           
    time_t seconds = t % secs_day;        

    tmp->tm_isdst = 0;
    tmp->tm_hour = seconds / secs_hour;
    tmp->tm_min = (seconds % secs_hour) / secs_min;
    tmp->tm_sec = (seconds % secs_hour) % secs_min;
    tmp->tm_wday = (days+4)%7;
    tmp->tm_year = 1970;
    while(1) {
        time_t days_this_year = 365 + is_leap_year(tmp->tm_year);
        if (days_this_year > days) break;
        days -= days_this_year;
        tmp->tm_year++;
    }
    tmp->tm_yday = days; 

    int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    mdays[1] += is_leap_year(tmp->tm_year);

    tmp->tm_mon = 0;
    while(days >= mdays[tmp->tm_mon]) {
        days -= mdays[tmp->tm_mon];
        tmp->tm_mon++;
    }

        tmp->tm_mday = days+1;  
        tmp->tm_year -= 1900; 
    }

    int is_leap_year(time_t year) {
        if (year % 4) return 0;       
        else if (year % 100) return 1;  
        else if (year % 400) return 0;  
        else return 1;                  
    }

  }
}


