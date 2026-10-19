#ifndef EXPR_HPP
#define EXPR_HPP

#include "Token.hpp"
#include <memory>

class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor
{
  public:
    virtual ~ExprVisitor();

    virtual Object Visit(const Binary &expr) = 0;
    virtual Object Visit(const Grouping &expr) = 0;
    virtual Object Visit(const Literal &expr) = 0;
    virtual Object Visit(const Unary &expr) = 0;
};

class Expr
{
  public:
    virtual ~Expr();

    virtual Object Accept(ExprVisitor &visitor) = 0;
};

class Binary : public Expr
{
  public:
    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
    ~Binary();

    const std::unique_ptr<Expr> m_left;
    const Token m_op;
    const std::unique_ptr<Expr> m_right;

    Object Accept(ExprVisitor &visitor) override;
};

class Grouping : public Expr
{
  public:
    Grouping(std::unique_ptr<Expr> expression);
    ~Grouping();

    const std::unique_ptr<Expr> m_expression;

    Object Accept(ExprVisitor &visitor) override;
};

class Literal : public Expr
{
  public:
    Literal(Object value);
    ~Literal();

    const Object m_value;

    Object Accept(ExprVisitor &visitor) override;
};

class Unary : public Expr
{
  public:
    Unary(Token op, std::unique_ptr<Expr> right);
    ~Unary();

    const Token m_op;
    const std::unique_ptr<Expr> m_right;

    Object Accept(ExprVisitor &visitor) override;
};

#endif // EXPR_HPP
