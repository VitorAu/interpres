#include "Interpres.hpp"
#include "ErrorHandler.hpp"
#include "Scanner.hpp"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
#include <string>

Interpres::Interpres() = default;
Interpres::~Interpres() = default;

const std::string Interpres::ReadFile(std::string filePath)
{
    std::ifstream file;
    file.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Failed to open" << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string fileStr(fileSize, '\0');
    file.read(&fileStr[0], fileSize);
    file.close();

    return fileStr;
}

void Interpres::RunFile(std::string filePath)
{   
    std::string fileContent = this->ReadFile(filePath);
    this->Run(fileContent);

    if(ErrorHandler::m_hadError) exit(EXIT_FAILURE);
}

void Interpres::RunPrompt()
{
    while (true)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;
        this->Run(line);

        ErrorHandler::m_hadError = false;
    }
}

void Interpres::Run(const std::string &source)
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();

    for (Token &token : tokens)
    {
        std::cout << token.Stringify() << std::endl;
    }
}
