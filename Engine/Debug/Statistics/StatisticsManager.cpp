#include "StatisticsManager.h"

StatisticsManager::StatisticsManager () :
	_statistics ()
{

}

StatisticsManager::~StatisticsManager ()
{
	for (auto it : _statistics) {
		if (it.second == nullptr) {
			continue;
		}

		delete it.second;
	}
}

StatisticsObject* StatisticsManager::GetStatisticsObject (const std::string& name) const
{
	auto it = _statistics.find (name);

	if (it == _statistics.end ()) {
		return nullptr;
	}

	return it->second;
}

void StatisticsManager::SetStatisticsObject (const std::string& name, StatisticsObject* object)
{
	auto it = _statistics.find (name);

	if (it != _statistics.end ()) {
		delete it->second;
	}

	_statistics [name] = object;
}