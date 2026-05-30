#pragma once
#include <vector>
#include <string>

class AdmissionResult {
public:
    static AdmissionResult accepted();
    static AdmissionResult rejected(const std::vector<std::string>& reasons);

    operator bool() const;

    const std::vector<std::string>& getRejectionReasons() const;

private:
    bool admissionStatus;
    std::vector<std::string> rejectionReasons;

    AdmissionResult(bool admissionStatus, const std::vector<std::string>& rejectionReasons);
};