#include "Expr.hpp"
#include "Token.hpp"
#include <memory>
#include <utility>

ExprVisitor::~ExprVisitor() = default;

Expr::~Expr() = default;

Binary::Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
    : m_left(std::move(left)), m_op(op), m_right(std::move(right))
{
}
Binary::~Binary() = default;

Object Binary::Accept(ExprVisitor &visitor)
{
    return visitor.Visit(*this);
}

Grouping::Grouping(std::unique_ptr<Expr> expression) : m_expression(std::move(expression))
{
}
Grouping::~Grouping() = default;

Object Grouping::Accept(ExprVisitor &visitor)
{
    return visitor.Visit(*this);
}

Literal::Literal(Object value) : m_value(value)
{
}
Literal::~Literal() = default;

Object Literal::Accept(ExprVisitor &visitor)
{
    return visitor.Visit(*this);
}

Unary::Unary(Token op, std::unique_ptr<Expr> right) : m_op(op), m_right(std::move(right))
{
}
Unary::~Unary() = default;

Object Unary::Accept(ExprVisitor &visitor)
{
    return visitor.Visit(*this);
}
