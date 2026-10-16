#ifndef INTERPRES_HPP
#define INTERPRES_HPP

#include <string>

class Interpres
{
  public:
    Interpres();
    ~Interpres();
    
    const std::string ReadFile(std::string m_filePath);
    void RunFile(std::string m_filePath);
    void RunPrompt();
    void Run(const std::string &source);
};

#endif // INTERPRES_HPP
