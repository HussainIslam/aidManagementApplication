#include "Perishable.h"

namespace aid {

  Perishable::Perishable() : Good('P') {
    
  }

  Perishable::~Perishable() {};

  std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
    Good::store(file, false);
    file << ",";
    file << expiryDate;
    if (newLine) {
      file << "\n";
    }
    return file;
  }

  std::fstream& Perishable::load(std::fstream& file) {
    Good::load(file);
    expiryDate.read(file);
    file.ignore();
    return file;
  }

  std::ostream& Perishable::write(std::ostream& os, bool linear) const {
    Good::write(os, linear);
  
    if (isClear() && !isEmpty()) {
      linear ? os << expiryDate : (os << "\n Expiry date: " << expiryDate);
    }
    return os;
  }

  std::istream& Perishable::read(std::istream& is) {
    this->Good::read(is);
    this->typeSetter('P');
    Date temp;
    if (!is.fail()) {
      cout << " Expiry date (YYYY/MM/DD): ";
      is >> temp;
    }
    if (temp.bad()) {
      is.setstate(std::ios::failbit);
      if (temp.errCode() == CIN_FAILED) this->message("Invalid Date Entry");
      else if (temp.errCode() == DAY_ERROR) this->message("Invalid Day in Date Entry");
      else if (temp.errCode() == MON_ERROR) this->message("Invalid Month in Date Entry");
      else if (temp.errCode() == YEAR_ERROR) this->message("Invalid Year in Date Entry");
      else this->message("Invalid Expiry in Date Entry");
    }
    else {
      this->expiryDate = temp;
      //is.clear();
    }

    return is;
  }

  const Date& Perishable::expiry() const {
    return expiryDate;
  }

  void Perishable::typeSetter(char type) {
    Good::typeSetter(type);
  }
}