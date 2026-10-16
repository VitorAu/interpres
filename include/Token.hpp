#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "TokenType.hpp"

#include <cstddef>
#include <string>
#include <variant>

typedef std::variant<std::string, long double, bool, std::nullptr_t> Object;

class Token
{
  private:
    const TokenType m_tokenType;
    const std::string m_lexeme;
    const Object m_literal;
    const int m_line;

  public:
    Token(TokenType tokenType, std::string lexeme, Object literal, int line);
    ~Token();

    const std::string Stringify() const;
};

#endif // TOKEN_HPP
