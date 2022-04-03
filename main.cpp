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
	string cwd = getCurrentProjectPath();
	string fileDirPath = cwd + "/created-files";
	fstream file;

	if (!fs::is_directory(fileDirPath))
		fs::create_directory(fileDirPath);

	cout << "Howdy, what would you like to do? Type a number and press enter:" << endl;
	cout << "\t\t[1] Read a file." << endl;
	cout << "\t\t[2] Create a text file." << endl;

	int action;
	cin >> action;

	// TODO: Add user interaction
	string readFilePath = fileDirPath + "/readFile.txt";
	string createFilePath = fileDirPath + "/createFile.txt";

	if (action == 1)
		file.open(readFilePath, ios::in);
	else if (action == 2)
		file.open(createFilePath, ios::out);

	return 0;
}

