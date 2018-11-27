// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"
#include <iostream>
using namespace std;
namespace aid {

	// number of days in month mon and year year
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13; //value of month is within 1 and 12, if yes month = mon otherwise month = 13
		month--; //subtract 1 from month because we will use this as index for days[]
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

  void Date::errCode(int errorCode) {
    errorCode = errorCode;
  }

  //implimentation for constructors
  Date::Date() {
    year = 0;
    month = 0;
    day = 0;
    comparatorValue = 0;
    errorState = NO_ERROR;
  }

  Date::Date(int year, int month, int day) {
    int upDay = mdays(month, year);
    if (year>=min_year && year <= max_year) {
      if (month >=1 && month <= 12) {
        if (day >=1 && day <= upDay) {
          if ((year * 372 + month * 31 + day)>=min_date) {
            this->year = year;
            this->month = month;
            this->day = day;
            this->comparatorValue = year * 372 + month * 31 + day;
            this->errorState = NO_ERROR;
          }
          else {
            *this = Date();
            this->errorState = PAST_ERROR;
          }
        }
        else {
          *this = Date();
          this->errorState = DAY_ERROR;
        }
      }
      else {
        *this = Date();
        this->errorState = MON_ERROR;
      }
    }
    else {
      *this = Date();
      this->errorState = YEAR_ERROR;
    }
  }

  //implimentation for relational operators
  bool Date::operator==(const Date& rhs) const {
    bool equal = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this->comparatorValue == rhs.comparatorValue) {
      equal = true;
    }
    return equal;
  }

  bool Date::operator!=(const Date& rhs) const {
    bool notEqual = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this ->comparatorValue != rhs.comparatorValue) {
      notEqual = true;
    }
    return notEqual;
  }
  
  bool Date::operator<(const Date& rhs) const {
    bool lessThan = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this ->comparatorValue < rhs.comparatorValue) {
      lessThan = true;
    }
    return lessThan;
  }
  
  bool Date::operator>(const Date& rhs) const {
    bool greaterThan = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this->comparatorValue > rhs.comparatorValue) {
      greaterThan = true;
    }
    return greaterThan;
  }
  
  bool Date::operator<=(const Date& rhs) const {
    bool lessEqual = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this->comparatorValue <= rhs.comparatorValue) {
      lessEqual = true;
    }
    return lessEqual;
  }

  bool Date::operator>=(const Date& rhs) const {
    bool greaterEqual = false;
    if (!this->isEmpty() && !rhs.isEmpty() && this->comparatorValue >= rhs.comparatorValue) {
      greaterEqual = true;
    }
    return greaterEqual;
  }

  //implimentation for queries and modifies
  int Date::errCode() const {
    return errorState;
  }

  bool Date::bad() const {
    bool noError = errorState != NO_ERROR;
    return noError;
  }

  std::istream& Date::read(std::istream& input) {
    char symbol;
    int year;
    int month;
    int day;
    input >> year >> symbol >> month >> symbol >> day;
    if (input.fail()) {
      errorState = CIN_FAILED;
    }
    else {
      Date inputDate(year, month, day);
      if (!inputDate.isEmpty()) {
          *this = inputDate;
      }
    }
    return input;
  }

  std::ostream& Date::write(std::ostream& ostr) const {
    ostr << year << '/';
    ostr.fill('0');
    ostr.width(2);
    ostr << month << "/";
    ostr.fill('0');
    ostr.width(2);
    ostr << day;
    return ostr;
  }

  //implimentation of addition function
  bool Date::isEmpty() const {
    bool empty = year == 0 && month == 0 && day == 0 && comparatorValue == 0 && errorState == NO_ERROR;
    return empty;
  }

  //implimentation for helper functions
  std::istream& operator>>(std::istream& istr, Date& date) {
    date.read(istr);
    return istr;
  }

  std::ostream& operator<<(std::ostream& ostr, const Date& date) {
    date.write(ostr);
    return ostr;
  }

}
