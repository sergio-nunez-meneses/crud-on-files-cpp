#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = __fs::filesystem;

int main()
{
	cout << "We're about to create a very simple text file, enter its name:" << endl;

	string filename, projectPath, fullPath;
	getline(cin, filename);

	projectPath = fs::current_path().parent_path().string();
	fullPath = projectPath + "/" + filename + ".txt";
	cout << fullPath << endl;
}

