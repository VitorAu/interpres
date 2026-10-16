#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "Token.hpp"
#include "TokenType.hpp"
#include <map>
#include <vector>

class Scanner
{
  private:
    const std::string m_source;

    std::vector<Token> m_tokens;
    inline static const std::map<std::string, TokenType> m_keywords = {
      // clang-format off
      {"and", TokenType::AND},
      {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},
      {"false", TokenType::FALSE},
      {"for", TokenType::FOR},
      {"fun", TokenType::FUN},
      {"if", TokenType::IF},
      {"nil", TokenType::NIL},
      {"or", TokenType::OR},
      {"print", TokenType::PRINT},
      {"return", TokenType::RETURN},
      {"super", TokenType::SUPER},
      {"this", TokenType::THIS},
      {"true", TokenType::TRUE},
      {"var", TokenType::VAR},
      {"while", TokenType::WHILE}
      // clang-format on
    };

    int m_start = 0;
    int m_current = 0;
    int m_line = 1;

    bool IsAtEnd();
    bool Match(char expected);
    bool IsDigit(char c);
    bool IsAlpha(char c);
    bool IsAlphaNumeric(char c);

    char Advance();
    char Peek();
    char PeekNext();
    
    void String();
    void Number();
    void Identifier();
    void AddToken(TokenType type);
    void AddToken(TokenType type, Object literal);
    void ScanToken();

  public:
    Scanner(std::string source);
    ~Scanner();

    std::vector<Token> ScanTokens();
};

#endif // SCANNER_HPP
