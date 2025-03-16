#include "parse_arguments.hpp"
#include <optional>

namespace aw3 {
	
	using namespace std;
	
	static void make_key_unique(string &key, const map<string, string> &settings) {
		string oldKey = key;
		size_t count = 0;
		if (key.empty()) {
			key = oldKey + to_string(count);
		}
		while (settings.find(key) != settings.end()) {
			key = oldKey + to_string(++count);
		}
	}
	
	static void end_current_argument(optional<string> &currKey, optional<string> &currValue, map<string, string> &outSettings) {
		if (currKey.has_value() || currValue.has_value()) {
			string key = currKey.has_value() ? *currKey : string();
			make_key_unique(key, outSettings);
			
			string value = currValue.has_value() ? *currValue : string();
			outSettings[key] = value;
		}
		
		currKey = nullopt;
		currValue = nullopt;
	}
	
	void parse_arguments(const span<const char*> &args, map<string, string> &outSettings) {
		optional<string> currKey;
		optional<string> currValue;
		bool forwardArgs = false;
		
		for (const char * currCArg : args) {
			string currArg(currCArg);
			
			if (currArg == "--") {
				forwardArgs = true;
				currKey = nullopt;
			} else if (!forwardArgs && currArg.starts_with("--")) {
				end_current_argument(currKey, currValue, outSettings);
				currKey = currArg;
			} else {
				currValue = currArg;
				end_current_argument(currKey, currValue, outSettings);
			}
		}
		end_current_argument(currKey, currValue, outSettings);
	}
	
	string argument(const string &key, const map<string, string> &settings) {
		auto foundSetting = settings.find(key);
		if (foundSetting == settings.end()) {
			if (key.starts_with("--")) {
				throw runtime_error(string("Argument ") + key + "is missing.");
			} else {
				throw runtime_error("File/folder to operate on is missing.");
			}
		}
		return foundSetting->second;
	}
	
	vector<string> arguments(const string &baseKey, const map<string, string> &settings) {
		size_t count = 0;
		vector<string> result;
		string key{baseKey};
		map<string, string>::const_iterator foundSetting;
		while ((foundSetting = settings.find(key)) != settings.end()) {
			result.insert(result.end(), foundSetting->second);
			key = baseKey + to_string(++count);
		}
		return result;
	}

} // namespace aw3
