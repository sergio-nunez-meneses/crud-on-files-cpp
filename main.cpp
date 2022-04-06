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
	for (const auto &entry: fs::directory_iterator(path)) files.push_back(entry.path().string());

	return files;
}

void displayStoredFiles(const vector<string> &files, const string &userAction = "", const string &goToAction = "")
{
	string action = (userAction == "r" || goToAction == "r") ? "read" : "update";

	cout << "\nWhich file would you like to " << action << "? Type a number and press enter:" << endl;
	for (int i = 0; i < files.size(); ++i) cout << "\t\t[" << i + 1 << "] " << files[i] << endl;
}

void checkFileNameExtension(string &fileName)
{
	if (fileName.find('.') == string::npos) fileName = fileName + ".txt";
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

	cout << "Howdy, what would you like to do? Type a character and press enter:" << endl;
	cout << "\t\t[c] Create a file" << endl;
	if (!files.empty())
	{
		cout << "\t\t[r] Read a file" << endl;
		cout << "\t\t[u] Update a file" << endl;
	}
	cout << "\t\t[e] Quit" << endl;

	string userAction, goToAction;
	while (getline(cin, userAction))
	{
		if (userAction == "c" || goToAction == "c")
		{
			cout << "\nType the file name:" << endl;

			string fileName;
			cin >> fileName;

			checkFileNameExtension(fileName);

			filePath = fileDirPath + "/" + fileName;
			goToAction = "u";
		}
		else if (userAction == "r" || goToAction == "r")
		{
			files = getStoredFiles(fileDirPath);
			displayStoredFiles(files, userAction, goToAction);

			int fileIndex;
			cin >> fileIndex;

			filePath = files[fileIndex - 1];
			file.open(filePath, ios::in);

			if (file.is_open())
			{
				string fileName = fs::path(filePath).filename().string();

				cout << "\n----- Reading file " << fileName << " -----" << endl;
				readFile(file, fileContent);
				cout << "----- End reading file -----" << endl;

				cout << "\nWhat would you like to do now?" << endl;
				cout << "\t\t[u] Update file" << endl;
				cout << "\t\t[e] Quit" << endl;

				cin >> goToAction;
			}
			else cout << "Unable to open file" << endl;
		}
		else if (userAction == "u" || goToAction == "u")
		{
			file.open(filePath, ios::out | ios::app);

			if (file.is_open())
			{
				string fileName = fs::path(filePath).filename().string();

				cout << "\nTo add content, type whatever you want, and press enter to save and continue." << endl;
				cout << "To stop, type exit and press enter." << endl;

				cout << "\n----- Editing file " << fileName << " -----" << endl;
				editFile(file, fileContent);
				cout << "----- End editing file -----" << endl;

				cout << "\nWhat would you like to do now?" << endl;
				cout << "\t\t[c] Create a file" << endl;
				cout << "\t\t[r] Read a file" << endl;
				cout << "\t\t[u] Update file" << endl;
				cout << "\t\t[e] Quit" << endl;

				cin >> goToAction;
			}
			else
			{
				files = getStoredFiles(fileDirPath);
				displayStoredFiles(files, userAction, goToAction);

				int fileIndex;
				cin >> fileIndex;

				filePath = files[fileIndex - 1];
				goToAction = "u";
			}
		}
		else if (userAction == "d") cout << "-- deleting file --\n" << endl;
		else if (userAction == "m") cout << "-- menu --\n" << endl;
		else if (userAction == "e" || goToAction == "e") break;
		else cout << "-- pressed " << userAction << " --\n" << endl;
	}
	cout << "Catch ya later buddy!" << endl;

	return 0;
}

