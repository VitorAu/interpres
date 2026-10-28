#ifndef PARSER_HPP
#define PARSER_HPP

#include "Expr.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

class Parser
{
    typedef std::runtime_error ParseError;

  private:
    const std::vector<Token> m_tokens;
    int m_current = 0;

    template <typename... T>
    bool Match(const T &...types)
    {
        assert((... && std::is_same<T, TokenType>::value));
        if ((... || this->Check(types)))
        {
            this->Advance();
            return true;
        }

        return false;
    }
    bool Check(TokenType type);
    bool IsAtEnd();

    Token Advance();
    Token Peek();
    Token Previous();
    Token Consume(TokenType type, std::string message);

    ParseError Error(Token token, std::string message);

    void Synchronize();

    std::unique_ptr<Expr> Expression();
    std::unique_ptr<Expr> Equality();
    std::unique_ptr<Expr> Comparison();
    std::unique_ptr<Expr> Term();
    std::unique_ptr<Expr> Factor();
    std::unique_ptr<Expr> Unary();
    std::unique_ptr<Expr> Primary();

  public:
    Parser(std::vector<Token> tokens);
    ~Parser();

    std::unique_ptr<Expr> Parse();
};

#endif // PARSER_HPP
