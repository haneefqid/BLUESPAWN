#include "hunt/hunts/HuntT1136.h"
#include "util/eventlogs/EventLogs.h"
#include "util/log/Log.h"
#include "util/log/HuntLogMessage.h"

namespace Hunts {

	HuntT1136::HuntT1136() : Hunt(L"T1136 - Account Created") {
		dwCategoriesAffected = (DWORD) Category::Configurations;
		dwSourcesInvolved = (DWORD) DataSource::EventLogs;
		dwTacticsUsed = (DWORD) Tactic::Persistence;
	}

	std::vector<std::shared_ptr<DETECTION>> HuntT1136::RunHunt(const Scope& scope) {
		HUNT_INIT();

		// Create existance queries so interesting data is output
		std::vector<EventLogs::XpathQuery> queries;
		auto param1 = EventLogs::ParamList();
		auto param2 = EventLogs::ParamList();
		param1.push_back(std::make_pair(L"Name", L"'TargetUserName'"));
		param2.push_back(std::make_pair(L"Name", L"'SubjectUserName'"));
		queries.push_back(EventLogs::XpathQuery(L"Event/EventData/Data", param1));
		queries.push_back(EventLogs::XpathQuery(L"Event/EventData/Data", param2));

		auto results = EventLogs::QueryEvents(L"Security", 4720, queries);
		for (auto result : results)
			EVENT_DETECTION(result);

		HUNT_END();
	}

	std::vector<std::shared_ptr<Event>> HuntT1136::GetMonitoringEvents() {
		std::vector<std::shared_ptr<Event>> events;
		events.push_back(std::make_shared<EventLogEvent>(L"Security", 4720));
		return events;
	}
}