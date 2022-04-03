#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

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
	string filePath, fileContent;
	fstream file;

	if (!fs::is_directory(fileDirPath))
		fs::create_directory(fileDirPath);

	cout << "Howdy, what would you like to do? Type a number and press enter:" << endl;
	cout << "\t\t[1] Read a file." << endl;
	cout << "\t\t[2] Create a text file." << endl;

	int action;
	cin >> action;

	// TODO: Add user interaction
	string createFilePath = fileDirPath + "/createFile.txt";

	if (action == 1)
	{
		vector<string> files;

		cout << "Which file would you like to read? Type a number and press enter:" << endl;

		int fileIndex = 0;
		for (const auto &entry : fs::directory_iterator(fileDirPath))
		{
			files.push_back(entry.path().string());
			++fileIndex;

			cout << "\t\t[" << fileIndex << "] " << entry.path().string() << endl;
		}

		cin >> fileIndex;

		filePath = files[fileIndex - 1];
		file.open(filePath, ios::in);

		if (file.is_open())
		{
			cout << "Opened file " << fs::path(filePath).filename().string() << endl;

			while (getline(file, fileContent))
				cout << fileContent << endl;
			file.close();
		}
		else
			cout << "Unable to open file" << endl;
	}
	else if (action == 2)
		file.open(createFilePath, ios::out);

	return 0;
}

