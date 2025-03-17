#include "page_generator.hpp"
#include <iostream>
#include <fstream>
#include "../tinymarkdown/tinymarkdown/tinymarkdown.hpp"

namespace aw3 {
	
	using namespace std;
	
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
			cout << "Generating " << path.string() << endl;
			ofstream ofile(destPath.string());
			string html{parser.parse(fileText)};
			ofile.write(html.data(), html.size());
		} else if (!path.filename().string().starts_with("_") && !path.filename().string().starts_with(".")) {
			filesystem::path destPath{filesystem::path{mSitePath / filesystem::path{"_site"} / path.lexically_relative(mSitePath)}};
			filesystem::copy(path, destPath);
			cout << "Copying " << path.string() << " to " << destPath.string() << endl;
		}
	}
	
}
