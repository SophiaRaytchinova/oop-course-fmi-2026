#include "AdmissionResult.h"

AdmissionResult AdmissionResult::accepted() {
    return AdmissionResult(true, {});
}

AdmissionResult AdmissionResult::rejected(const std::vector<std::string>& rejectionReasons) {
    return AdmissionResult(false, rejectionReasons);
}

AdmissionResult::AdmissionResult(bool admissionStatus, const std::vector<std::string>& rejectionReasons)
    : admissionStatus(admissionStatus), rejectionReasons(rejectionReasons) {}

AdmissionResult::operator bool() const {
    return admissionStatus;
}

const std::vector<std::string>& AdmissionResult::getRejectionReasons() const {
    return rejectionReasons;
}
