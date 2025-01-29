#pragma once
#include "AlarmSystemState.h"

class StayArmedState : public AlarmSystemState {
public:
	void Handle() override;
	void DisplaySystemState() override;
};