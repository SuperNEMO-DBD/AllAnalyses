//
//  SqlDate.h
//
//  Created by Stefano Torre on 19/01/12.
//

#ifndef NEMOMODS_SQLDATE_H_
#define NEMOMODS_SQLDATE_H_
#include <iostream>
struct SqlDate {
  int year, month, day, hour, minute, second;
  SqlDate();
  SqlDate(char *sqldate);
  void print(std::ostream& out) const;
  bool operator==(const SqlDate &rhs) const;
  bool operator!=(const SqlDate &rhs) const;
};

std::ostream& operator << (std::ostream& os, const SqlDate& obj);

#endif
