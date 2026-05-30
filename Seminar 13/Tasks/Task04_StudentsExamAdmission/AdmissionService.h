#pragma once
#include "PolymorphicContainer.hpp"
#include "AdmissionRequirement.h"
#include "AdmissionResult.h"

class AdmissionService : public PolymorphicContainer<AdmissionRequirement> {
public:
    AdmissionResult check(const Student& student) const;
};
