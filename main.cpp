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

vector<string> getStoredFiles(const string &path)
{
	vector<string> files;

	for (const auto &entry: fs::directory_iterator(path)) {
		string filePath = entry.path().string();
		files.push_back(filePath);
	}
	return files;
}

void displayStoredFiles(const vector<string> &files)
{
	int fileIndex = 0;
	for (const auto & file : files) {
		++fileIndex;

		cout << "\t\t[" << fileIndex << "] " << file << endl;
	}
}

void checkFileNameExtension(string &fileName)
{
	if (fileName.find('.') == string::npos) fileName += ".txt";
	else
	{
		size_t needle = fileName.find_last_of('.'); // unsigned integer type of the result of the sizeof operator

		if (fileName.substr(needle + 1) != "txt") fileName = fileName.substr(0, needle) + ".txt";
	}
}

void readFile(fstream &file, string &fileContent)
{
	while (getline(file, fileContent)) cout << fileContent << endl;
	file.close();
}

void editFile(fstream &file, string &fileContent)
{
	while (getline(cin, fileContent))
	{
		if (fileContent != "exit") file << fileContent << endl;
		else break;
	}
	file.close();
}

int main()
{
	string cwd = getCurrentProjectPath();
	string fileDirPath = cwd + "/created-files";

	if (!fs::is_directory(fileDirPath)) fs::create_directory(fileDirPath);

	vector<string> files = getStoredFiles(fileDirPath);
	string filePath, fileContent;
	fstream file;

	cout << "Howdy, what would you like to do? Type number and press enter:" << endl;
	if (!files.empty()) cout << "\t\t[r] Read a file" << endl;
	cout << "\t\t[c] Create a text file" << endl;

	string action;
	cin >> action;

	if (action == "r")
	{
		cout << "\nWhich file would you like to read? Type a number and press enter:" << endl;
		displayStoredFiles(files);

		int fileIndex;
		cin >> fileIndex;

		filePath = files[fileIndex - 1];
		file.open(filePath, ios::in);

		if (file.is_open())
		{
			string fileName = fs::path(filePath).filename().string();

			cout << "\n----- Reading file " << fileName << " -----" << endl;
			readFile(file, fileContent);
			cout << "\n----- End reading file -----" << endl;

			cout << "\nWould you like to edit this file?" << endl;
			cout << "\t\t[y] Yes" << endl;
			cout << "\t\t[n] No" << endl;

			cin >> action;

			if (action == "y")
			{
				file.open(filePath, ios::out | ios::app);

				if (file.is_open()) {
					cout << "\nPress enter to save and continue, type exit and press enter to stop)" << endl;
					cout << "\n----- Editing file " << fileName << " -----" << endl;
					editFile(file, fileContent);
					cout << "\n----- End editing file -----" << endl;
				}
				else cout << "Unable to open file" << endl;
			}
			else file.close();
		}
		else cout << "Unable to open file" << endl;
	}
	else if (action == "c")
	{
		cout << "Enter file name:" << endl;

		string fileName;
		cin >> fileName;

		checkFileNameExtension(fileName);

		filePath = fileDirPath + "/" + fileName;
		file.open(filePath, ios::out);

		if (file.is_open()) {
			cout << "\nPress enter to save and continue, type exit and press enter to stop)" << endl;
			cout << "\n----- Editing file " << fileName << " -----" << endl;
			editFile(file, fileContent);
			cout << "\n----- End editing file -----" << endl;
		}
		else cout << "Unable to open file" << endl;
	}

	return 0;
}

