#pragma once
#include <stdexcept>
#include <string>

class ResumeAlreadyExistsException : public std::runtime_error {
public:
    explicit ResumeAlreadyExistsException(const std::string& message);
};

class ResumeNotFoundException : public std::runtime_error {
public:
    explicit ResumeNotFoundException(const std::string& message);
};
