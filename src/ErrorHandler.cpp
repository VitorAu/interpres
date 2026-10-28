#include "ErrorHandler.hpp"

#include "TokenType.hpp"
#include <iostream>

ErrorHandler::ErrorHandler() = default;
ErrorHandler::~ErrorHandler() = default;

void ErrorHandler::Error(int line, std::string message)
{
    ErrorHandler::ReportError(line, "", message);
}

void ErrorHandler::Error(Token token, std::string message)
{
    if (token.GetTokenType() == TokenType::INTERPRES_EOF) ErrorHandler::ReportError(token.GetLine(), " at end", message);
    else ErrorHandler::ReportError(token.GetLine(), " at '" + token.GetLexeme() + "'", message);
}

void ErrorHandler::ReportError(int line, std::string where, std::string message)
{
    std::cerr << "[" << line << "] Error " << where << ": " << message << std::endl;
    ErrorHandler::m_hadError = true;
}
