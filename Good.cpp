#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Good.h"
#include "Error.h"
#include "iGood.h"
using namespace std;

namespace aid {
  //definitions of supporting private member functions
  void Good::createDynamicCString(char* dst, const char* src) {
    if (goodName != nullptr) {
        deallocateDynamicCString();
    }
    if (src != nullptr) {
      if (strlen(src) <= max_name_length) {
        goodName = new char[strlen(src) + 1];
        strncpy(goodName, src, strlen(src));
        goodName[strlen(src)] = '\0';
      }
      else {
        goodName = new char[max_name_length + 1];
        strncpy(goodName, src, max_name_length);
        goodName[max_name_length] = '\0';
      }
    }
  }

  void Good::copyStaticCString(char* dest, const char* src, int max) {
    if (strlen(src) <= static_cast<unsigned int>(max)) {
      strncpy(dest, src, strlen(src));
      dest[strlen(src)] = '\0';
    }
    else {
      strncpy(dest, src, max);
      dest[max] = '\0';
    }
  }

  void Good::deallocateDynamicCString() {
    //delete[] goodName;
    goodName = nullptr;
  }
  //definition of protected member functions
  void Good::name(const char* name) {
    if (name != nullptr) {
      createDynamicCString(goodName, name);
    }
    else {
      deallocateDynamicCString();
      goodName = nullptr;
    }
  }

  const char* Good::name() const {
    return goodName;
  }

  const char* Good::sku() const {
    return stockKeepingUnit;
  }

  const char* Good::unit() const {
    return goodUnit;
  }

  bool Good::taxed() const {
    return taxable;
  }

  double Good::itemPrice() const {
    return unitPrice_BT;
  }

  double Good::itemCost() const {
    double cost = taxable ? (unitPrice_BT * (1 + TAX_RATE)) : unitPrice_BT;
    return cost;
  }

  void Good::message(const char* msg) {
    errorState.message(msg);
  }

  bool Good::isClear() const {
    return errorState.isClear();
  }



  //definition of public member functions
  Good::Good(char goodType) {
    typeOfGood = goodType;
    stockKeepingUnit[0] = '\0';
    goodUnit[0] = '\0';
    goodName = nullptr;
    goodOnHand = 0;
    goodNeeded = 0;
    unitPrice_BT = 0.00;
    taxable = true;
  }

  Good::Good(const char* skUnit, const char* name, const char* unit, int onHand, bool tax, double priceBT, int quantNeeded) {
    if (typeOfGood != 'N' || typeOfGood != 'P') {
      *this = Good();
    }
    copyStaticCString(stockKeepingUnit, skUnit, max_sku_length);
    copyStaticCString(goodUnit, unit, max_unit_length);
    createDynamicCString(goodName, name);
    goodOnHand = onHand;
    goodNeeded = quantNeeded;
    unitPrice_BT = priceBT;
    taxable = tax;
    //typeOfGood = 'N';
  }

  Good::Good(const Good& src) {
    *this = src;
  }

  Good::~Good() {
    deallocateDynamicCString();
  }

  void Good::operator=(const Good& src) {
    this->typeOfGood = src.typeOfGood;
    copyStaticCString(this->stockKeepingUnit, src.stockKeepingUnit, max_sku_length);
    copyStaticCString(this->goodUnit, src.goodUnit, max_unit_length);
    createDynamicCString(this->goodName, src.goodName);
    this->goodOnHand = src.goodOnHand;
    this->goodNeeded = src.goodNeeded;
    this->unitPrice_BT = src.unitPrice_BT;
    this->taxable = src.taxable;
    this->errorState.message(src.errorState.message());
  }

  std::fstream& Good::store(std::fstream& file, bool newLine) const {
    file << typeOfGood << ",";
    file << stockKeepingUnit << ",";
    file << goodName << ",";
    file << goodUnit << ",";
    file << taxable << ",";
    file << unitPrice_BT << ",";
    file << goodOnHand << ",";
    file << goodNeeded;
    //file << errorState << endl;
    
    if (newLine) {
      file << endl;
    }
    return file;
  }
  
  std::fstream& Good::load(std::fstream& file) {
    //char type_;
    char sku_[max_sku_length + 1];
    char* name_ = new char[max_name_length + 1];
    char unit_[max_unit_length + 1];
    bool taxable_;
    double price_;
    int qHand_;
    int qNeeded_;
    Error errorState_;
    char sym;

    //file >> type_;
    //file >> sym;
    file.getline(sku_, max_sku_length, ',');
    file.getline(name_, max_name_length, ',');
    file.getline(unit_, max_unit_length, ',');
    file >> taxable_;
    file >> sym;
    file >> price_;
    file >> sym;
    file >> qHand_;
    file >> sym;
    file >> qNeeded_;
    file >> sym;

    //const char* skUnit, const char* name, const char* unit, int onHand, bool tax, double priceBT, int quantNeeded
    *this = Good(sku_, name_, unit_, qHand_, taxable_, price_, qNeeded_);

    return file;
  }

  std::ostream& Good::write(std::ostream& os, bool linear) const {
    if (!errorState.isClear()) {
      os << errorState;
    }
    else if (!isEmpty()) {
      if (linear) {
        os << setfill(' ');
        os << setw(max_sku_length) << left << stockKeepingUnit << "|";
        os << setw(20) << left << goodName << "|";
        os << setw(7) << right << fixed << setprecision(2) << itemCost() << "|";
        os << setw(4) << right << goodOnHand << "|";
        os << setw(10) << left << goodUnit << "|";
        os << setw(4) << right << goodNeeded << "|";
      }
      else {
        os << " Sku: " << stockKeepingUnit << endl;
        os << " Name (no spaces): " << goodName << endl;
        os << " Price: " << unitPrice_BT << endl;
        os << " Price after tax: ";
        if (taxable) {
          os << itemCost() << endl;
        }
        else {
          os << "N/A" << endl;
        }
        os << " Quantity on hand: " << goodOnHand << " " << goodUnit << endl;
        os << " Quantity needed: " << goodNeeded << endl;
      }
    }

    return os;
  }

  std::istream& Good::read(std::istream& is) {
    char sku_[max_sku_length + 1];
    char unit_[max_unit_length + 1];
    char* name_ = new char[max_name_length + 1];
    char tax_;
    bool taxable_;
    int qHand_=0;
    int qNeeded_=0;
    double price_=0;
    Error errorState_;

    cout << " Sku: ";
    is >> sku_;
    cout << " Name (no spaces): ";
    is >> name_;
    cout << " Unit: ";
    is >> unit_;
    cout << " Taxed? (y/n): ";
    is >> tax_;
    if (!(tax_ == 'y' || tax_ == 'Y' || tax_ == 'n' || tax_ == 'N')) {
      is.setstate(std::ios::failbit);
      errorState_.message("Only (Y)es or (N)o are acceptable");
      taxable_ = false;
    }
    else if (tax_ == 'N' || tax_ == 'n') {
      taxable_ = false;
    }
    else {
      taxable_ = true;
    }
    if (!is.fail()) {
      cout << " Price: ";
      is >> price_;
      if (is.fail()) {
        errorState_.message("Invalid Price Entry");
      }
    }
    if (!is.fail()) {
      cout << " Quantity on hand: ";
      is >> qHand_;
      if (is.fail()) {
        errorState_.message("Invalid Quantity Entry");
      }
    }
    if (!is.fail()) {
      cout << " Quantity needed: ";
      is >> qNeeded_;
      if (!is) {
        errorState_.message("Invalid Quantity Needed Entry");
      }
    }

    //if (!(is.fail())) {
    *this = Good(sku_, name_, unit_, qHand_, taxable_, price_, qNeeded_);
    this->errorState.message(errorState_.message());
    //}
    return is;
  }

  bool Good::operator==(const char* str) const {
    bool equal;
    strcmp(stockKeepingUnit, str) ? equal = false : equal = true;
    return equal;
  }

  double Good::total_cost() const {
    return goodOnHand * itemCost();
  }

  void Good::quantity(int goh) {
    if (goh) {
      goodOnHand = goh;
    }
  }

  bool Good::isEmpty() const {
    return goodName == nullptr || goodName[0] == '\0';
  }

  int Good::qtyNeeded() const {
    return goodNeeded;
  }

  int Good::quantity() const {
    return goodOnHand;
  }

  bool Good::operator>(const char* str) const {
    bool greaterThan = strcmp(stockKeepingUnit, str) ? true : false;
    return greaterThan;
  }

  bool Good::operator>(const iGood& good) const {
    bool greaterThan;
    strcmp(this->name(), good.name()) ? greaterThan = true : greaterThan = false;
    return greaterThan;
  }

  int Good::operator+=(int upGOH) {
    if (upGOH) {
      goodOnHand += upGOH;
    }
    return goodOnHand;
  }

  //definition of helper functions
  std::ostream& operator<<(std::ostream& os, const iGood& rhs) {
    rhs.write(os, true);
    return os;
  }

  std::istream& operator>>(std::istream& is, iGood& rhs) {
    rhs.read(is);
    return is;
  }

  double operator+=(double& additionalCost, const iGood& src) {
    return src.total_cost() + additionalCost;
  }


}