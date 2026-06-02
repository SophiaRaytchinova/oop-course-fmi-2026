#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <memory>
#include <optional>
#include "ApplicationResult.h"
#include "Requirement.h"
#include "Resume.h"
#include "ResumePool.h"

class ResumeSelectionSystem {
public:
    ResumeSelectionSystem() = default;

    ResumeSelectionSystem(const ResumeSelectionSystem& other);
    ResumeSelectionSystem& operator=(const ResumeSelectionSystem& other);

    ResumeSelectionSystem(ResumeSelectionSystem&& other) noexcept = default;
    ResumeSelectionSystem& operator=(ResumeSelectionSystem&& other) noexcept = default;

    void addRequirement(const Requirement& requirement);
    void addRequirement(const std::unique_ptr<Requirement>& requirement);

    // std::vector<std::string> addResume(const Resume&);
    ApplicationResult addResume(const Resume& resume);
    std::optional<Resume> findResumeByEmail(const std::string& email) const;

    void removeResumeByEmail(const std::string& email);


    const ResumePool& getResumes() const;

private:
    ResumePool acceptedResumes;
    std::vector<std::unique_ptr<Requirement>> requirements;

    void copyFrom(const ResumeSelectionSystem& other);
};

std::ostream& operator<<(std::ostream& os, const ResumeSelectionSystem& resumeSystem);
