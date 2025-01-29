#pragma once
#include "AlarmSystemState.h"

class DisarmState : public AlarmSystemState {
public:
	void Handle() override;
	void DisplaySystemState() override;
};