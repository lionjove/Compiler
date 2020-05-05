#pragma once
#include "IStage.h"
#include "CompilerParts/Observers/INewParserTreeObserver.h"

class __declspec(dllexport) SemanticAnalyzer : public IStage, public INewParserTreeObserver
{
public:
	void DoStage() override;

	[[nodiscard]] std::wstring GetStageName() override { return L"CodeGenerator"; }

	void Notify(std::shared_ptr<AbstractTreeNode> root) override;

	void RegisterListener(INewParserTreeObserver* observer) { m_observers.push_back(observer); }
	void UnRegisterListener(INewParserTreeObserver* observer) { m_observers.erase(std::find(m_observers.begin(), m_observers.end(), observer)); }
	
private:

	struct ScopeData
	{
		size_t level = 0;
		size_t counter = 0;

		std::wstring ToString() const;
	};

	void ProcessNode(std::shared_ptr<AbstractTreeNode> node, const ScopeData& currScopeData);
	
	std::vector<INewParserTreeObserver*> m_observers;
};