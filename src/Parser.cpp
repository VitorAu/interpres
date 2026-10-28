#include "Parser.hpp"

#include "ErrorHandler.hpp"
#include "TokenType.hpp"
#include <memory>

Parser::Parser(std::vector<Token> tokens) : m_tokens(tokens)
{
}
Parser::~Parser() = default;

bool Parser::Check(TokenType type)
{
    if (this->IsAtEnd()) return false;
    return this->Peek().GetTokenType() == type;
}

bool Parser::IsAtEnd()
{
    bool aux = this->Peek().GetTokenType() == TokenType::INTERPRES_EOF;
    return aux;
}

Token Parser::Advance()
{
    if (!this->IsAtEnd()) this->m_current++;
    return this->Previous();
}

Token Parser::Peek()
{
    return this->m_tokens.at(this->m_current);
}

Token Parser::Previous()
{
    return this->m_tokens.at(this->m_current - 1);
}

Token Parser::Consume(TokenType type, std::string message)
{
    if (this->Check(type)) return this->Advance();
    throw this->Error(this->Peek(), message);
}

Parser::ParseError Parser::Error(Token token, std::string message)
{
    ErrorHandler::Error(token, message);
    return ParseError(message);
}

void Parser::Synchronize()
{
    this->Advance();
    while (!this->IsAtEnd())
    {
        if (this->Previous().GetTokenType() == TokenType::SEMICOLON) return;

        // clang-format off
        switch (this->Peek().GetTokenType()) 
        {
          case TokenType::CLASS:
          case TokenType::FUN:
          case TokenType::VAR:
          case TokenType::FOR:
          case TokenType::IF:
          case TokenType::WHILE:
          case TokenType::PRINT:
          case TokenType::RETURN:
            return;
        }
        // clang-format on

        this->Advance();
    }
}

std::unique_ptr<Expr> Parser::Expression()
{
    return this->Equality();
}

std::unique_ptr<Expr> Parser::Equality()
{
    auto expr = this->Comparison();
    while (this->Match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL))
    {
        auto op = this->Previous();
        auto right = this->Comparison();

        expr = std::make_unique<::Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Comparison()
{
    auto expr = this->Term();
    while (this->Match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL))
    {
        auto op = this->Previous();
        auto right = this->Term();

        expr = std::make_unique<::Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Term()
{
    auto expr = this->Factor();
    while (this->Match(TokenType::MINUS, TokenType::PLUS))
    {
        auto op = this->Previous();
        auto right = this->Factor();

        expr = std::make_unique<::Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Factor()
{
    auto expr = this->Unary();
    while (this->Match(TokenType::SLASH, TokenType::STAR))
    {
        auto op = this->Previous();
        auto right = this->Unary();

        expr = std::make_unique<::Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Unary()
{
    if (this->Match(TokenType::BANG, TokenType::MINUS))
    {
        auto op = this->Previous();
        auto right = this->Unary();

        return std::make_unique<::Unary>(op, std::move(right));
    }

    return this->Primary();
}

std::unique_ptr<Expr> Parser::Primary()
{
    if (this->Match(TokenType::FALSE)) return std::make_unique<::Literal>(false);
    if (this->Match(TokenType::TRUE)) return std::make_unique<::Literal>(true);
    if (this->Match(TokenType::INTERPRES_EOF)) return std::make_unique<::Literal>(nullptr);
    if (this->Match(TokenType::NUMBER, TokenType::STRING))
        return std::make_unique<::Literal>(this->Previous().GetLiteral());

    if (this->Match(TokenType::LEFT_PAREN))
    {
        auto expr = this->Expression();
        this->Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<::Grouping>(std::move(expr));
    }

    throw this->Error(this->Peek(), "Expect expression.");
}

std::unique_ptr<Expr> Parser::Parse()
{
    try
    {
        return this->Expression();
    }
    catch (ParseError error)
    {
        return nullptr;
    }
}
