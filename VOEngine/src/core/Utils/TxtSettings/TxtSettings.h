#include "../Settings.h"


namespace VOEngine {
	class TxtSettings : SettingsManager {
		TxtSettings(const std::string& filename) : SettingsManager(filename) {

		}
		~TxtSettings() override {

		}
		// Унаследовано через SettingsManager
		std::string GetValue(const std::string& filename, const std::string& key) override;
		void AddPair(const std::string& filename, const std::pair<std::string&, std::string&> pair) override;
		std::vector<std::string> GetKeyByValue(const std::string& filename, const std::string& value) override;
	};
}