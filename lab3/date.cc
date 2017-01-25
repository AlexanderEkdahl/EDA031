#include <ctime>  // time and localtime
#include <iomanip>
#include "date.h"

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
  time_t timer = time(0);           // time in seconds since 1970-01-01
  tm* locTime = localtime(&timer);  // broken-down time
  year = 1900 + locTime->tm_year;
  month = 1 + locTime->tm_mon;
  day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) {
  if (m < 1 || m > 12 || d > daysPerMonth[m - 1] || d < 1) {
    throw std::invalid_argument("Invalid");
  }

  year = y;
  month = m;
  day = d;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
  os << std::setw(4) << std::setfill('0') << d.year << '-';
  os << std::setw(2) << std::setfill('0') << d.month << '-';
  os << std::setw(2) << std::setfill('0') << d.day;
  return os;
}

std::istream& operator>>(std::istream& is, Date& d) {
  int year;
  is >> year;

  if (is.get() != '-') {
    is.setstate(std::ios::failbit);
    return is;
  }

  int month;
  is >> month;

  if (is.get() != '-') {
    is.setstate(std::ios::failbit);
    return is;
  }

  int day;
  is >> day;

  try {
    d = Date(year, month, day);
  } catch (const std::invalid_argument& e) {
    is.setstate(std::ios_base::failbit);
  }

  return is;
}

int Date::getYear() const { return year; }

int Date::getMonth() const { return month; }

int Date::getDay() const { return day; }

void Date::next() {
  if (day + 1 > daysPerMonth[month - 1]) {
    day = 1;
    year = (month < 12 ? year : year + 1);
    month = (month < 12 ? month + 1 : 1);
  } else {
    day += 1;
  }
}
