#include "parse_arguments.hpp"
#include "page_generator.hpp"
#include <iostream>
#include <span>
#include <map>
#include <optional>
#include <unistd.h>
#include <filesystem>


using namespace std;

int main(int argc, const char * argv[]) {
	try {
		const span args(argv + 1, size_t(argc) - 1); // Skip the app path.
		map<string, string> settings;
		
		aw3::parse_arguments(args, settings);
		string working_dir{aw3::argument("0", settings)};
		if (0 != chdir(working_dir.c_str())) {
			throw runtime_error("Can't find directory \"" + working_dir + "\".");
		}
		
		string sp(2048, '\0');
		getcwd(sp.data(), sp.size());
		sp.resize(strlen(sp.c_str()));
		filesystem::path sitePath(sp);

		aw3::page_generator pageGenerator(sitePath);
		filesystem::create_directory(sitePath / "_site");
		
		filesystem::directory_iterator start(sitePath);
		filesystem::directory_iterator end;
		vector<string> paths;
		
		for (auto curr = start; curr != end; ++curr) {
			pageGenerator.generate_page(curr->path());
		}
		
		return 0;
	} catch(const exception& err) {
		cerr << "error: " << err.what() << endl;
		return 1;
	}
}
