#ifndef SICT_ERROR_H
#define SICT_ERROR_H

#include <iostream>

namespace aid {
  class Error {
    char* errMessage;
    void deleteAndSafe();
    void init(const char* source);
  public:
    explicit Error(const char* errorMessage = nullptr);
    Error(const Error& em) = delete;
    Error& operator=(const Error& em) = delete;
    virtual ~Error();
    void clear();
    bool isClear() const;
    void message(const char* str);
    const char* message()const;
    std::ostream& write(std::ostream& os) const;
  };
  std::ostream& operator<<(std::ostream& os, const Error& error);
}


#endif // !SICT_ERROR_H
