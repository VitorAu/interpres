#include "Interpres.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    Interpres interpres;

    if (argc > 2)
    {
        std::cout << "Usage: interpres [script]" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (argc == 2) interpres.RunFile(argv[1]);
    else interpres.RunPrompt();

    return EXIT_SUCCESS;
}
