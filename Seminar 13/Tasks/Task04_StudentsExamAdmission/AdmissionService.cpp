#include "AdmissionService.h"

#include "AdmissionResult.h"

AdmissionResult AdmissionService::check(const Student& student) const {
    std::vector<std::string> messages;
    for (const auto& requirement : items) {
        std::optional<std::string> checkResult = requirement->check(student);
        if (checkResult) {
            messages.push_back(checkResult.value());
        }
    }
    if (messages.empty()) {
        return AdmissionResult::accepted();
    }
    return AdmissionResult::rejected(messages);
}
