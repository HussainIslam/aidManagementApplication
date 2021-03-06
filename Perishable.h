#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H
#include <fstream>
#include "Good.h"
#include "Date.h"
using namespace std;

namespace aid {
  class Perishable : public Good {
    Date expiryDate;

  public:
    Perishable();
    ~Perishable();
    std::fstream& store(std::fstream& file, bool newLine = true) const;
    std::fstream& load(std::fstream& file);
    std::ostream& write(std::ostream& os, bool linear) const;
    std::istream& read(std::istream& is);
    const Date& expiry() const;
    //supporting member function
    void typeSetter(char);
  };
}

#endif // !AID_PERISHABLE_H
