#include "internal.hpp"
#include "external_type.hpp"

Internal::Internal() :
    data{std::string("External type"), 1}
{    
}

Internal::~Internal() = default;

void Internal::hello() {
    data->hello();
}