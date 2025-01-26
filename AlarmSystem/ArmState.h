#pragma once
#include "AlarmSystemState.h"

class ArmState : public AlarmSystemState {
public:
	void Handle() override;
};