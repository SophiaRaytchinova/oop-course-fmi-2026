#include "ResumeSelectionSystem.h"
#include "CustomResumeExceptions.h"
#include <format>

void ResumeSelectionSystem::copyFrom(const ResumeSelectionSystem& other) {
    std::vector<std::unique_ptr<Requirement>> requirementsCopy;
    requirementsCopy.reserve(other.requirements.size());
    for (const auto& requirement : other.requirements) {
        requirementsCopy.push_back(requirement->clone());
    }
    requirements = std::move(requirementsCopy);
    acceptedResumes = other.acceptedResumes;
}

ResumeSelectionSystem::ResumeSelectionSystem(const ResumeSelectionSystem& other) {
    copyFrom(other);
}

ResumeSelectionSystem& ResumeSelectionSystem::operator=(const ResumeSelectionSystem& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

const ResumePool& ResumeSelectionSystem::getResumes() const {
    return acceptedResumes;
}

void ResumeSelectionSystem::addRequirement(const Requirement& requirement) {
    requirements.push_back(requirement.clone());
}

void ResumeSelectionSystem::addRequirement(const std::unique_ptr<Requirement>& requirement) {
    requirements.push_back(requirement->clone());
}

std::optional<Resume> ResumeSelectionSystem::findResumeByEmail(const std::string& email) const {
    return acceptedResumes.findByEmail(email);
}

ApplicationResult ResumeSelectionSystem::addResume(const Resume& resume) {
    if (findResumeByEmail(resume.getEmail())) {
        /*
        alternatively if we don't want exceptions for code logic:
            std::vector<std::string> result;
            result.push_back(std::format("Resume for email {} already exists.", resume.getEmail()));
            return ApplicationResult::rejected(result);
        */
        throw ResumeAlreadyExistsException(std::format("Resume for email {} already exists.", resume.getEmail()));
    }

    std::vector<std::string> rejectionReasons;
    for (const auto& requirement : requirements) {
        std::optional<std::string> rejectionReason = requirement->check(resume);
        if (rejectionReason.has_value()) {
            rejectionReasons.push_back(rejectionReason.value());
        }
    }

    if (rejectionReasons.empty()) {
        acceptedResumes.add(resume);
        return ApplicationResult::accepted();
    }
    return ApplicationResult::rejected(rejectionReasons);
}

/*
std::vector<std::string> ResumeSelectionSystem::addResume(const Resume& resume) {
    if (findResumeByEmail(resume.getEmail())) {
        throw ResumeAlreadyExistsException(std::format("Resume for email {} already exists.", resume.getEmail()));
    }

    std::vector<std::string> rejectionReasons;
    for (const auto& requirement : requirements) {
        std::optional<std::string> rejectionReason = requirement->check(resume);
        if (rejectionReason.has_value()) {
            rejectionReasons.push_back(rejectionReason.value());
        }
    }

    if (rejectionReasons.empty()) {
        acceptedResumes.add(resume);
    }

    return rejectionReasons;
}
*/

void ResumeSelectionSystem::removeResumeByEmail(const std::string& email) {
    bool removed = acceptedResumes.remove([&email](const Resume& resume) {
        return resume.getEmail() == email;
    });

    if (!removed) {
        throw ResumeNotFoundException(std::format("Resume for email {} not found. Could not delete.", email));
    }
}

std::ostream& operator<<(std::ostream& os, const ResumeSelectionSystem& resumeSystem) {
    const ResumePool& resumes = resumeSystem.getResumes();

    if (resumes.isEmpty()) {
        return os << "No accepted resumes.\n";
    }

    return os << resumes;
}
