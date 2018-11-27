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
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

namespace aid {
  const int min_year = 2018;
  const int max_year = 2038;
  const int min_date = 751098;

  class Date {
    int year;
    int month;
    int day;
    int comparatorValue;
    int errorState;
    //This class uses a comparator value for comparing the date stored 
    //in the current object with the date stored in another Date object. 
    //Your constructors set this comparator value and your public 
    //relational operators use it to compare dates. (If the value of 
    //date one is larger than the value of date two, then date one is 
    //more recent than date two; that is, date one is after date two).
    #define NO_ERROR 0
    #define CIN_FAILED 1
    #define DAY_ERROR 2
    #define MON_ERROR 3
    #define YEAR_ERROR 4
    #define PAST_ERROR 5

    int mdays(int, int)const;
    void errCode(int errorCode);

  public:
    //prototypes for constructors
    Date();
    Date(int year, int month, int day);
    
    //prototypes for relational operators
    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const;
    bool operator<=(const Date& rhs) const;
    bool operator>=(const Date& rhs) const;
    
    //prototypes for queries and modifies
    int errCode() const;
    bool bad() const;
    std::istream& read(std::istream& istr);
    std::ostream& write(std::ostream& ostr) const;

    //additional member function
    bool isEmpty() const;

  };
  
  //prototypes for helper functions
  std::istream& operator>>(std::istream& istr, Date& date);
  std::ostream& operator<<(std::ostream& ostr, const Date& date);




}
#endif