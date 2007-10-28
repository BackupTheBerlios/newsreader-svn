#pragma once

class IMethodRequest
{
public:
	virtual bool call() = 0;
	virtual ~IMethodRequest(void)=0{};
};
