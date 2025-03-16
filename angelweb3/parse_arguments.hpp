#pragma once

#include <stdio.h>
#include <span>
#include <map>

namespace aw3 {
	
	using namespace std;
	
	void parse_arguments(const span<const char*> &args, map<string, string> &outSettings);
	string argument(const string &key, const map<string, string> &settings);
	vector<string> arguments(const string &key, const map<string, string> &settings);
	
} // namespace aw3
