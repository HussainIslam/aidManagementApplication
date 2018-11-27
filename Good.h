#ifndef AID_GOOD_H
#define AID_GOOD_H
#include "Error.h"
#include "iGood.h"

namespace aid {
  const int max_sku_length = 7;
  const int max_unit_length = 10;
  const int max_name_length = 75;
  const float TAX_RATE = 0.13;

  class Good : public iGood{
    char typeOfGood;
    char stockKeepingUnit[max_sku_length + 1];
    char goodUnit[max_unit_length + 1];
    char* goodName;
    int goodOnHand;
    int goodNeeded;
    double unitPrice_BT;
    bool taxable;
    Error errorState;

    //private supporting member functions
    void createDynamicCString(char* dst, const char* src);
    void copyStaticCString(char* dest, const char* src, int max);
    void deallocateDynamicCString();

  protected:
    void name(const char*);
    const char* name() const;
    const char* sku() const;
    const char* unit() const;
    bool taxed() const;
    double itemPrice() const;
    double itemCost() const;
    void message(const char*);
    bool isClear() const;

  public:
    Good(char goodType = 'N');
    Good(const char* skUnit, const char* name, const char* unit, int onHand = 0, bool tax = true, double priceBT = 0.00, int quantNeeded = 0);
    Good(const Good&);
    ~Good();
    void operator=(const Good&);
    std::fstream& store(std::fstream& file, bool newLine = true) const;
    std::fstream& load(std::fstream& file);
    std::ostream& write(std::ostream& os, bool linear) const;
    std::istream& read(std::istream& is);
    bool operator==(const char*) const;
    double total_cost() const;
    void quantity(int);
    bool isEmpty() const;
    int qtyNeeded() const;
    int quantity() const;

    bool operator>(const char*) const;
    bool operator>(const iGood&) const;
    int operator+=(int);

  };

  std::ostream& operator<<(std::ostream&, const iGood&);
  std::istream& operator>>(std::istream&, iGood&);
  double operator+=(double&, const iGood&);

}
#endif // !AID_GOOD_H
