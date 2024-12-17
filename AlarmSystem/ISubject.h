#pragma once
#include "IObserver.h"

class ISubject {
public:
	virtual void AddObserver(std::shared_ptr<IObserver>observer) = 0;
	virtual void RemoveObserver(std::shared_ptr<IObserver> observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual ~ISubject() = default;
};