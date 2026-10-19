#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "Expr.hpp"
#include <memory>

class AstPrinter : public ExprVisitor
{
  public:
    AstPrinter();
    ~AstPrinter();

    std::string Print(std::unique_ptr<Expr> expr);
};

#endif // AST_PRINTER_HPP
