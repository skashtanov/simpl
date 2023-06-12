#pragma once
#include <string>

struct ExternalType
{
    std::string data;
    int id;

    ExternalType(std::string d, int i);
    ~ExternalType();
    void hello();
};