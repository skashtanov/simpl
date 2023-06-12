#pragma once
#include "simpl/simpl.hpp"

struct ExternalType;

struct Internal
{
    simpl<ExternalType, 40, 8> data;

    Internal();
    ~Internal();

    void hello();
};