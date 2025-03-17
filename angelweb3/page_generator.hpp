#pragma once

#include <string>
#include <filesystem>

namespace aw3 {
	
	using namespace std;
	
	class page_generator {
	public:
		page_generator(const filesystem::path &sitePath) : mSitePath(sitePath) {}
		
		void create_directory_hierarchy(const filesystem::path &path);
		void generate_pages(const filesystem::path &path);
		void generate_page(const filesystem::path &path);
		
	protected:
		filesystem::path mSitePath;
	};
	
} // namespace aw3
