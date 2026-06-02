#include "CustomResumeExceptions.h"

ResumeAlreadyExistsException::ResumeAlreadyExistsException(const std::string& message)
    : std::runtime_error(message) {}

ResumeNotFoundException::ResumeNotFoundException(const std::string& message) : std::runtime_error(message) {}
