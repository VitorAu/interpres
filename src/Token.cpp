#include "Token.hpp"
#include "TokenType.hpp"
#include <string>

Token::Token(TokenType tokenType, std::string lexeme, Object literal, int line)
    : m_tokenType(tokenType), m_lexeme(lexeme), m_literal(literal), m_line(line)
{
}
Token::~Token() = default;

const std::string Token::Stringify() const
{
    std::string literalText;
    // clang-format off
    switch (this->m_tokenType)
    {
      case TokenType::IDENTIFIER: literalText = this->m_lexeme; 
      break;
      case TokenType::STRING: literalText = std::get<std::string>(this->m_literal);
      break;
      case TokenType::NUMBER: literalText = std::to_string(std::get<long double>(this->m_literal));
      break;
      case TokenType::TRUE: literalText = "true";
      break;
      case TokenType::FALSE: literalText = "false";
      default: literalText = "nil";
      break;
    }
    // clang-format on

    std::string aux = TokenTypeToString(this->m_tokenType) + " " + this->m_lexeme + " " + literalText;
    return aux;
}
