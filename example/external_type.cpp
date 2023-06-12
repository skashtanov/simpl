#include "external_type.hpp"
#include <iostream>
#include <utility>

ExternalType::ExternalType(std::string d, int i) :
    data{std::move(d)},
    id{i}
{
}

ExternalType::~ExternalType() = default;

void ExternalType::hello() {
    std::cout << "Hello from " << data << " with id " << id << '\n';
}