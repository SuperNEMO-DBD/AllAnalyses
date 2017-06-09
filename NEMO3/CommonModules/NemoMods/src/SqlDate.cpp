#include "NemoMods/SqlDate.h"
#include <cstdio>
SqlDate::SqlDate() : year(0), month(0), day(0), hour(0), minute(0), second(0) {
  }

SqlDate::SqlDate(char *sqldate) {
    sscanf(sqldate, "%d-%d-%d %d:%d:%d",
           &year, &month, &day, &hour, &minute, &second);
}

void SqlDate::print(std::ostream& out) const {
  char string[50];
  sprintf(string, "%d-%d-%d %d:%d:%d", year, month, day, hour, minute, second);
  out << string;
}

std::ostream& operator << (std::ostream& os, const SqlDate& obj) {
  obj.print(os);
  return os;
}

bool SqlDate::operator==(const SqlDate &rhs) const{
  return (year   == rhs.year)  && (month  == rhs.month) &&
         (day    == rhs.day)   && (hour   == rhs.hour)  &&
         (minute == rhs.minute)&& (second == rhs.second);
}

bool SqlDate::operator!=(const SqlDate &rhs) const{
  return !operator==(rhs);
}
