#pragma once
#include <stdexcept>

class ReadFailException : public std::runtime_error {
public:
    ReadFailException() : std::runtime_error("Read failed: inconsistent data") {}
};
