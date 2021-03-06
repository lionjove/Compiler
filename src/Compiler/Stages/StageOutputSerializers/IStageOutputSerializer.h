#pragma once
#include <string>

class __declspec(dllexport) IStageOutputSerializer
{
public:
	virtual ~IStageOutputSerializer() {}

	virtual void OpenDocToSave(const std::wstring_view path) = 0;

	virtual void Finalize() = 0;
};