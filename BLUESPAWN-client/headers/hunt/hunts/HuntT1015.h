#pragma once
#include "../Hunt.h"

#include "reaction/Reaction.h"
#include "reaction/Log.h"

namespace Hunts {

	/**
	 * HuntT1015 looks for Windows Accessibility Features to be messed with in some way
	 */
	class HuntT1015 : public Hunt {
	private:
		std::vector<std::wstring> vAccessibilityBinaries = { L"sethc.exe", L"utilman.exe", L"osk.exe", L"Magnify.exe",
			L"Narrator.exe", L"DisplaySwitch.exe", L"AtBroker.exe" };
		std::wstring wsIFEO = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\";
		std::wstring wsIFEOWow64 = L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\";

		void HuntT1015::EvaluateRegistry(std::vector<std::shared_ptr<DETECTION>>& detections);
		void HuntT1015::EvaluateFiles(std::vector<std::shared_ptr<DETECTION>>& detections);
	public:
		HuntT1015();

		virtual std::vector<std::shared_ptr<DETECTION>> RunHunt(const Scope& scope) override;
		virtual std::vector<std::shared_ptr<Event>> GetMonitoringEvents() override;
	};
}