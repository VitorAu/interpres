#include "Scanner.hpp"
#include "ErrorHandler.hpp"
#include "TokenType.hpp"
#include <string>

Scanner::Scanner(std::string source) : m_source(source)
{
}
Scanner::~Scanner() = default;

bool Scanner::IsAtEnd()
{
    bool aux = this->m_current >= this->m_source.length();
    return aux;
}

bool Scanner::Match(char expected)
{
    if (this->IsAtEnd()) return false;
    if (this->m_source.at(this->m_current) != expected) return false;

    this->m_current++;
    return true;
}

bool Scanner::IsDigit(char c)
{
    bool aux = c >= '0' && c <= '9';
    return aux;
}

bool Scanner::IsAlpha(char c)
{
    bool aux = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    return aux;
}

bool Scanner::IsAlphaNumeric(char c)
{
    bool aux = this->IsAlpha(c) || this->IsDigit(c);
    return aux;
}

char Scanner::Advance()
{
    char aux = this->m_source.at(this->m_current++);
    return aux;
}

char Scanner::Peek()
{
    if (this->IsAtEnd()) return '\0';
    return this->m_source.at(this->m_current);
}

char Scanner::PeekNext()
{
    if (this->m_current + 1 >= this->m_source.length()) return '\0';
    return this->m_source.at(this->m_current + 1);
}

void Scanner::String()
{
    while (this->Peek() != '"' && this->IsAtEnd())
    {
        if (this->Peek() == '\n') this->m_line++;
        this->Advance();
    }

    if (this->IsAtEnd())
    {
        ErrorHandler::Error(this->m_line, "Unterminated string.");
        return;
    }

    this->Advance();
    std::string aux = this->m_source.substr(this->m_start + 1, this->m_current - this->m_current - 2);
    this->AddToken(TokenType::STRING, aux);
}

void Scanner::Number()
{
    while (this->IsDigit(this->Peek())) this->Advance();
    if (this->Peek() == '.' && this->IsDigit(this->PeekNext()))
    {
        this->Advance();
        while (this->IsDigit(this->Peek())) Advance();
    }

    this->AddToken(TokenType::NUMBER,
                   std::stold(this->m_source.substr(this->m_start, this->m_current - this->m_start)));
}

void Scanner::Identifier()
{
    while (this->IsAlphaNumeric(this->Peek())) this->Advance();
    std::string text = this->m_source.substr(this->m_start, this->m_current - this->m_start);

    TokenType type;
    auto it = this->m_keywords.find(text);
    if(it != this->m_keywords.end()) type = it->second;
    else type = TokenType::IDENTIFIER;

    this->AddToken(type);
}

void Scanner::AddToken(TokenType type)
{
    this->AddToken(type, nullptr);
}

void Scanner::AddToken(TokenType type, Object literal)
{
    std::string text = this->m_source.substr(this->m_start, this->m_current - this->m_start);
    this->m_tokens.emplace_back(type, text, literal, this->m_line);
}

void Scanner::ScanToken()
{
    char c = this->Advance();
    // clang-format off
    switch (c)
    {
      case '(': AddToken(TokenType::LEFT_PAREN); break;
      case ')': AddToken(TokenType::RIGHT_PAREN); break;
      case '{': AddToken(TokenType::LEFT_BRACE); break;
      case '}': AddToken(TokenType::RIGHT_BRACE); break;
      case ',': AddToken(TokenType::COMMA); break;
      case '.': AddToken(TokenType::DOT); break;
      case '-': AddToken(TokenType::MINUS); break;
      case '+': AddToken(TokenType::PLUS); break;
      case ';': AddToken(TokenType::SEMICOLON); break;
      case '*': AddToken(TokenType::STAR); break;
      case '!': AddToken(this->Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);break;
      case '=': AddToken(this->Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);break;
      case '<': AddToken(this->Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);break;
      case '>': AddToken(this->Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;

      case '/':
      if(this->Match('=')) while(this->Peek() != '\n' && !this->IsAtEnd()) this->Advance();
      else AddToken(TokenType::SLASH);
      break;

      case ' ': break;
      case '\r': break;
      case '\t': break;
      case '\n': this->m_line++; break;

      case '"': this->String(); break;

      default: 
      if (this->IsDigit(c)) Number();
      else if (this->IsAlpha(c)) this->Identifier();
      else ErrorHandler::Error(this->m_line, "Unexpected character.");
      break;
    }
    // clang-format on
}

std::vector<Token> Scanner::ScanTokens()
{
    while (!this->IsAtEnd())
    {
        this->m_start = this->m_current;
        this->ScanToken();
    }

    this->m_tokens.emplace_back(TokenType::INTERPRES_EOF, "", nullptr, this->m_line);
    return this->m_tokens;
}
