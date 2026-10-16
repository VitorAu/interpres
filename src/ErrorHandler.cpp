#include "ErrorHandler.hpp"

#include <iostream>

ErrorHandler::ErrorHandler() = default;
ErrorHandler::~ErrorHandler() = default;

void ErrorHandler::Error(int line, std::string message)
{
    ErrorHandler::ReportError(line, "", message);
}

void ErrorHandler::ReportError(int line, std::string where, std::string message)
{
    std::cerr << "[" << line << "] Error " << where << ": " << message << std::endl;
    ErrorHandler::m_hadError = true;
}
