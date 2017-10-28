#include "stdafx.h"
#include "CriticalSection.h"

ScopedCriticalSection::ScopedCriticalSection(CriticalSection &cs)
{
	this->cs_ = &cs;
	cs_->lock();
}

ScopedCriticalSection::~ScopedCriticalSection()
{
	cs_->unlock();
}

CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&(this->cs_));
}

CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&(this->cs_));
}

void CriticalSection::lock()
{
	EnterCriticalSection(&(this->cs_));
}

void CriticalSection::unlock()
{
	LeaveCriticalSection(&(this->cs_));
}
