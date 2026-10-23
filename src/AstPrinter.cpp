#include "AstPrinter.hpp"
#include "Expr.hpp"

AstPrinter::AstPrinter() = default;
AstPrinter::~AstPrinter() = default;

std::string AstPrinter::Print(const Object obj)
{
    std::string str;
    if (auto aux = std::get_if<std::string>(&obj)) str = *aux;
    else if (auto aux = std::get_if<long double>(&obj)) str = std::to_string(*aux);
    else if (auto aux = std::get_if<bool>(&obj)) *aux ? str = "true" : str = "false";
    else str = "nil";

    return str;
}

std::string AstPrinter::Print(Expr &expr)
{
    std::string str = this->Print(expr.Accept(*this));
    return str;
}

Object AstPrinter::VisitBinaryExpr(const Binary &expr)
{
    Object obj = Parenthesize(expr.m_op.GetLexeme(), expr.m_left, expr.m_right);
    return obj;
}

Object AstPrinter::VisitGroupingExpr(const Grouping &expr)
{
    Object obj = Parenthesize("group", expr.m_expression);
    return obj;
}

Object AstPrinter::VisitLiteralExpr(const Literal &expr)
{
    Object obj = expr.m_value;
    return obj;
}

Object AstPrinter::VisitUnaryExpr(const Unary &expr)
{
    Object obj = Parenthesize(expr.m_op.GetLexeme(), expr.m_right);
    return obj;
}
