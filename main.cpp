#include "AstPrinter.hpp"
#include "Expr.hpp"
// #include "Interpres.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    // Interpres interpres;
    //
    // if (argc > 2)
    // {
    //     std::cout << "Usage: interpres [script]" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    // else if (argc == 2) interpres.RunFile(argv[1]);
    // else interpres.RunPrompt();

    std::unique_ptr<Expr> expression = std::make_unique<Binary>(
        std::make_unique<Unary>(Token(TokenType::MINUS, "-", nullptr, 1), std::make_unique<Literal>(123.0L)),
        Token(TokenType::STAR, "*", nullptr, 1), std::make_unique<Grouping>(std::make_unique<Literal>(45.67L)));

    AstPrinter printer;
    std::cout << printer.Print(*expression) << '\n';

    return 0;

    return EXIT_SUCCESS;
}
