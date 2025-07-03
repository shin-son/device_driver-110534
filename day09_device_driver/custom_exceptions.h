#pragma once
#include <stdexcept>

class ReadFailException : public std::runtime_error {
public:
    ReadFailException() : std::runtime_error("Read failed: inconsistent data") {}
};

class WriteFailException : public std::runtime_error {
public:
    WriteFailException() : std::runtime_error("Write failed: address is already written") {}
};