#include "page_generator.hpp"
#include <iostream>
#include <fstream>
#include "../tinymarkdown/tinymarkdown/tinymarkdown.hpp"

namespace aw3 {
	
	using namespace std;
	
	void page_generator::create_directory_hierarchy(const filesystem::path &path) {
		filesystem::directory_iterator end;
		for (auto curr = filesystem::directory_iterator(path); curr != end; ++curr) {
			string currName{curr->path().filename().string()};
			if (!currName.starts_with("_")
				&& !currName.starts_with(".")
				&& filesystem::is_directory(curr->path())) {
				filesystem::path destPath{filesystem::path{mSitePath / filesystem::path{"_site"} / curr->path().lexically_relative(mSitePath)}};
				filesystem::create_directory(destPath);
				
				create_directory_hierarchy(curr->path());
			}
		}
	}
	
	void page_generator::generate_pages(const filesystem::path &path) {
		filesystem::directory_iterator end;
		
		for (auto curr = filesystem::directory_iterator(path); curr != end; ++curr) {
			string currName{curr->path().filename().string()};
			if (currName.starts_with("_")
				|| currName.starts_with(".")) { continue; }
			if (filesystem::is_directory(curr->path())) {
				generate_pages(curr->path());
			} else {
				generate_page(curr->path());
			}
		}
	}
	
	void page_generator::generate_page(const filesystem::path &path) {
		string ext = path.extension();
		if (ext == ".md") {
			filesystem::path destPath{filesystem::path{mSitePath / filesystem::path{"_site"} / path.lexically_relative(mSitePath)}};
			destPath.replace_extension(".html");
			fstream file(path.string());
			file.seekg(0, ios_base::seekdir::end);
			auto fileSize = file.tellg();
			string fileText(size_t(fileSize), '\0');
			file.seekg(0, ios_base::seekdir::beg);
			file.read(fileText.data(), fileSize);
			tinymarkdown::parser parser;
			cout << "Generating " << destPath.lexically_relative(mSitePath).string() << endl;
			ofstream ofile(destPath.string());
			string html{parser.parse(fileText)};
			ofile.write(html.data(), html.size());
		} else if (!path.filename().string().starts_with("_")
				   && !path.filename().string().starts_with(".")) {
			filesystem::path destPath{filesystem::path{mSitePath / filesystem::path{"_site"} / path.lexically_relative(mSitePath)}};
			filesystem::copy(path, destPath);
			cout << "Copying " << path.lexically_relative(mSitePath).string() << " to " << destPath.lexically_relative(mSitePath).string() << endl;
		}
	}
	
}
