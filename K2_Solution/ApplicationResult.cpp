#include "ApplicationResult.h"

ApplicationResult ApplicationResult::accepted() {
    return ApplicationResult(true, {});
}

ApplicationResult ApplicationResult::rejected(const std::vector<std::string>& rejectionReasons) {
    return ApplicationResult(false, rejectionReasons);
}

ApplicationResult::ApplicationResult(bool acceptedStatus, const std::vector<std::string>& rejectionReasons)
    : acceptedStatus(acceptedStatus), rejectionReasons(rejectionReasons) {}

ApplicationResult::operator bool() const {
    return acceptedStatus;
}

const std::vector<std::string>& ApplicationResult::getRejectionReasons() const {
    return rejectionReasons;
}
