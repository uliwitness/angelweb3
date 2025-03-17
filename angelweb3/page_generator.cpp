#include "page_generator.hpp"
#include <iostream>

namespace aw3 {
	
	using namespace std;
	
	void page_generator::generate_page(const filesystem::path &path) {
		cout << path.string() << endl;
	}
	
}
