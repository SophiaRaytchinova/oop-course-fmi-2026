#pragma once
#include <vector>
#include <string>

class ApplicationResult {
public:
    static ApplicationResult accepted();
    static ApplicationResult rejected(const std::vector<std::string>& reasons);

    operator bool() const;

    const std::vector<std::string>& getRejectionReasons() const;

private:
    bool acceptedStatus;
    std::vector<std::string> rejectionReasons;

    ApplicationResult(bool acceptedStatus, const std::vector<std::string>& rejectionReasons);
};
