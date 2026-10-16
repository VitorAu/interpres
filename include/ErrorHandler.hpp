#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>

class ErrorHandler {
  public:
    ErrorHandler();
    ~ErrorHandler();

    inline static bool m_hadError;

    static void Error(int line, std::string message);
    static void ReportError(int line, std::string where, std::string message);
};

#endif // ERROR_HANDLER_HPP
