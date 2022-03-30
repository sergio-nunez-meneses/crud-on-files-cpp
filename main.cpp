#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = __fs::filesystem;

int main()
{
	cout << "We're about to create a very simple text file, enter its name:" << endl;

	const string projectPath = fs::current_path().parent_path().string();
	string fullPath, filename;

	getline(cin, filename);

	fullPath = projectPath + "/" + filename + ".txt";
	ofstream fileStream(fullPath);
}

