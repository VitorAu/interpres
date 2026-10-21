#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "Expr.hpp"
#include <string>

class AstPrinter : public ExprVisitor<Object>
{
  private:
    template <typename... Exprs>
    std::string Parenthesize(const std::string &name, const Exprs &...exprs)
    {
        std::string str = "(" + name;
        ((str += " " + Print(*exprs)), ...);
        str += ")";
        return str;
    }

  public:
    AstPrinter() = default;
    ~AstPrinter() = default;

    std::string Print(const Object obj)
    {
        std::string str;
        if (auto aux = std::get_if<std::string>(&obj)) str = *aux;
        else if (auto aux = std::get_if<long double>(&obj)) str = std::to_string(*aux);
        else if (auto aux = std::get_if<bool>(&obj)) *aux ? str = "true" : str = "false";
        else str = "nil";

        return str;
    }

    std::string Print(Expr &expr)
    {
        std::string str = this->Print(expr.Accept(*this));
        return str;
    }

    Object VisitBinaryExpr(const Binary &expr) override
    {
        Object obj = Parenthesize(expr.m_op.GetLexeme(), expr.m_left, expr.m_right);
        return obj;
    }

    Object VisitGroupingExpr(const Grouping &expr) override
    {
        Object obj = Parenthesize("group", expr.m_expression);
        return obj;
    }

    Object VisitLiteralExpr(const Literal &expr) override
    {
        Object obj = expr.m_value;
        return obj;
    }

    Object VisitUnaryExpr(const Unary &expr) override
    {
        Object obj = Parenthesize(expr.m_op.GetLexeme(), expr.m_right);
        return obj;
    }
};

#endif // AST_PRINTER_HPP
