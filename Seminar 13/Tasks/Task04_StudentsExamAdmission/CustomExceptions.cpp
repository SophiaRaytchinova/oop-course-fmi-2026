#include "CustomExceptions.h"

StudentAlreadyExistsException::StudentAlreadyExistsException(const std::string& message) : std::runtime_error(message) {
}

StudentNotFoundException::StudentNotFoundException(const std::string& message) : std::runtime_error(message) {
}
