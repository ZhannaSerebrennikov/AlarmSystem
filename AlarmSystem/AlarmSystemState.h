#pragma once
#include <iostream>

class AlarmSystemState {
public:
	AlarmSystemState() = default;
	virtual ~AlarmSystemState() = default;

	virtual void Handle() = 0;
};