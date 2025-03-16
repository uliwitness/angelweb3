#include <iostream>
#include <span>
#include <map>
#include <optional>
#include "parse_arguments.hpp"
#include <unistd.h>

using namespace std;

int main(int argc, const char * argv[]) {
	try {
		const span args(argv + 1, size_t(argc) - 1); // Skip the app path.
		map<string, string> settings;
		
		aw3::parse_arguments(args, settings);
		if (0 != chdir(aw3::argument("0", settings).c_str())) {
			throw runtime_error("Can't find specified directory.");
		}
		
		FILE * f = fopen("testfile.txt", "w");
		fclose(f);
		
		string cwd(1024, '\0');
		const char* cCwd = getcwd(cwd.data(), cwd.size());
		cwd.resize(strlen(cCwd));
		
		cout << cwd << endl;
		
		return 0;
	} catch(const exception& err) {
		cerr << "error: " << err.what() << endl;
		return 1;
	}
}
