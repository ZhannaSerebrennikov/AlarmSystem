#pragma once
#include <iostream>

class AlarmSystemState {
public:
	AlarmSystemState() = default;
	virtual ~AlarmSystemState() = default;

	virtual void DisplaySystemState() = 0;
	virtual void Handle() = 0;
};