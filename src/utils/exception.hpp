#ifndef PROTOSHOP_UTILS_EXCEPTION
#define PROTOSHOP_UTILS_EXCEPTION

class Exception : public std::exception {
protected:
  std::string msg_;
public:
  // https://stackoverflow.com/questions/8152720/correct-way-to-inherit-from-stdexception
  explicit Exception(const char* message): msg_(message) {}
  explicit Exception(const std::string& message) : msg_(message) {}
  virtual ~Exception() throw() {}
  std::string get_message() const {
    return msg_;
  }
};

#endif
