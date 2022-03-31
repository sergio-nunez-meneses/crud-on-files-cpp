#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = __fs::filesystem;

string getCurrentProjectPath()
{
	return fs::current_path().parent_path().string();
}

string setFilePath(const string &path, const string &file)
{
	return path + "/" + file + ".txt";
}

int main()
{
	cout << "We're about to create a very simple text file, enter its name:" << endl;

	string filePath, fileName;
	getline(cin, fileName);

	string cwd = getCurrentProjectPath();
	string fileDirPath = cwd + "/created-files";

	if (!fs::is_directory(fileDirPath))
		fs::create_directory(fileDirPath);

	filePath = setFilePath(fileDirPath, fileName);
	ofstream fileStream(filePath, ios::app);

	if (fileStream)
		cout << "Update file" << endl;
	else
		cout << "Handle errors" << endl;

	return 0;
}

