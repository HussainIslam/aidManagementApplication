#include <cstring>
#include "Error.h"

namespace aid {
  //member functions
  Error::Error(const char* errorMessage) {
    if (errorMessage == nullptr || errorMessage[0] == '\0') {
      errMessage = nullptr;
    }
    else {
      init(errorMessage);
    }
  }
  
  Error::~Error() {
    deleteAndSafe();
  }
  
  

  void Error::clear() {
    deleteAndSafe();
  }

  bool Error::isClear() const {
    bool clear = errMessage == nullptr || errMessage[0] == '\0';
    return clear;
  }

  void Error::message(const char* str) {
    deleteAndSafe();
    if (str == nullptr || str[0] == '\0') {
      errMessage = nullptr;
    }
    else {
      init(str);
    }
  }

  const char* Error::message() const {
    const char* msg = errMessage;
    return msg;
  }

  //definition of supporting member function (public)
  std::ostream& Error::write(std::ostream& os) const {
    os << errMessage;
    return os;
  }

  //definition of supporting member function (private)
  void Error::deleteAndSafe() {
    if (!isClear()) {
      delete[] errMessage;
      errMessage = nullptr;
    }
  }

  void Error::init(const char* source) {
    int size = strlen(source);
    errMessage = new char[size+1];
    strncpy(errMessage, source, size);
    errMessage[size] = '\0';
  }

  //helper function
  std::ostream& operator<<(std::ostream& os, const Error& error) {
    if (!error.isClear()) {
      error.write(os);
    }
    return os;
  }
}