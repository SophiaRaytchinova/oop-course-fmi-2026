#pragma once
#include <stdexcept>

class StudentAlreadyExistsException : public std::runtime_error {
public:
    explicit StudentAlreadyExistsException(const std::string& message);
    using std::runtime_error::what;
};

class StudentNotFoundException : public std::runtime_error {
public:
    explicit StudentNotFoundException(const std::string& message);
    using std::runtime_error::what;
};
