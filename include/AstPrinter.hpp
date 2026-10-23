#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "Expr.hpp"
#include <string>

class AstPrinter : public ExprVisitor<Object>
{
  private:
    template <typename... T>
    std::string Parenthesize(const std::string &name, const T &...exprs)
    {
        std::string str = "(" + name;
        ((str += " " + Print(*exprs)), ...);
        str += ")";
        return str;
    }

  public:
    AstPrinter();
    ~AstPrinter();

    std::string Print(const Object obj);
    std::string Print(Expr &expr);

    Object VisitBinaryExpr(const Binary &expr) override;
    Object VisitGroupingExpr(const Grouping &expr) override;
    Object VisitLiteralExpr(const Literal &expr) override;
    Object VisitUnaryExpr(const Unary &expr) override;
};

#endif // AST_PRINTER_HPP
