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
	vector<string>  files;
	for (const auto &entry: fs::directory_iterator(path)) files.push_back(entry.path().string());

	return files;
}

void displayStoredFiles(const vector<string> &files, const string &userAction = "", const string &goToAction = "")
{
	string action;
	if (userAction == "r" || goToAction == "r") action = "read";
	else if (userAction == "u" || goToAction == "u") action = "update";
	else action = "delete";

	cout << "\nWhich file would you like to " << action << "? Type a number and press enter:" << endl;
	for (int i = 0; i < files.size(); ++i) cout << "\t\t[" << i + 1 << "] " << files[i] << endl;
}

void displayActionMenu(const vector<string> &files, const string &action = "")
{
	string title = (action.empty()) ? "Howdy, what would you like to do?" : "\nWhat would you like to do now?";

	cout << title << " Type a character and press enter:" << endl;
	cout << "\t\t[c] Create a file" << endl;
	if (!files.empty())
	{
		cout << "\t\t[r] Read a file" << endl;
		cout << "\t\t[u] Update a file" << endl;
		cout << "\t\t[d] Delete a file" << endl;
	}
	cout << "\t\t[q] Quit" << endl;
}

string setFileName(const string &fileName)
{
	const bool isFilePath = fs::exists(fileName);

	if (isFilePath) return fs::path(fileName).filename().string();
	else
	{
		if (fileName.find('.') == string::npos) return fileName + ".txt";
		else
		{
			size_t needle = fileName.find_last_of('.'); // unsigned integer type of the result of the sizeof operator

			if (fileName.substr(needle + 1) != "txt") return fileName.substr(0, needle) + ".txt";
		}
	}
}

void readFile(fstream &file, const string &filePath, string &fileContent)
{
	string fileName = setFileName(filePath);

	cout << "\n----- Reading file " << fileName << " -----" << endl;
	while (getline(file, fileContent)) cout << fileContent << endl;
	cout << "----- End reading file -----" << endl;

	file.close();
}

void editFile(fstream &file, const string &filePath, string &fileContent)
{
	string fileName = setFileName(filePath);

	cout << "\nTo add content, type whatever you want, and press enter to save and continue." << endl;
	cout << "To stop, type exit and press enter." << endl;

	cout << "\n----- Editing file " << fileName << " -----" << endl;
	while (getline(cin, fileContent))
	{
		if (fileContent != "exit") file << fileContent << endl;
		else break;
	}
	cout << "----- End editing file -----" << endl;

	file.close();
	file.flush();
}

void deleteFile(const string &filePath)
{
	string fileName = fs::path(filePath).filename().string();

	cout << "\n----- Deleting file " << fileName << " -----" << endl;
	const bool fileDeleted = fs::remove(filePath);

	if (fileDeleted) cout << "----- End deleting file -----" << endl;
	else cout << "Unable to delete file" << endl;
}

int main()
{
	string cwd         = getCurrentProjectPath();
	string fileDirPath = cwd + "/created-files";

	if (!fs::is_directory(fileDirPath)) fs::create_directory(fileDirPath);

	vector<string> files      = getStoredFiles(fileDirPath);
	bool           fromAction = false;
	string         filePath, fileContent, userAction, goToAction;
	fstream        file;

	displayActionMenu(files);

	while (getline(cin, userAction))
	{
		if (userAction == "c" || goToAction == "c")
		{
			cout << "\nType the file name:" << endl;

			string fileNameWithoutPath, fileName;
			cin >> fileName;

			fileNameWithoutPath = setFileName(fileName);
			filePath            = fileDirPath + "/" + fileNameWithoutPath;

			goToAction = "u";
			fromAction = true;
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
				readFile(file, filePath, fileContent);
				displayActionMenu(getStoredFiles(fileDirPath), "r");

				cin >> goToAction;

				fromAction = false;
			}
			else cout << "Unable to open file" << endl;
		}
		else if (userAction == "u" || goToAction == "u" || userAction == "d" || goToAction == "d")
		{
			if (!fromAction)
			{
				files = getStoredFiles(fileDirPath);
				displayStoredFiles(files, userAction, goToAction);

				int fileIndex;
				cin >> fileIndex;

				filePath = files[fileIndex - 1];
			}

			file.open(filePath, ios::out | ios::app);

			if (file.is_open())
			{
				if (userAction == "u" || goToAction == "u") editFile(file, filePath, fileContent);
				else if (userAction == "d" || goToAction == "d") deleteFile(filePath);

				displayActionMenu(getStoredFiles(fileDirPath), "u");

				cin >> goToAction;
				fromAction = false;
			}
			else cout << "Unable to update file" << endl;
		}
		else if (userAction == "q" || goToAction == "q") break;
		else cout << "-- pressed " << userAction << " --\n" << endl;
	}
	cout << "Catch ya later buddy!" << endl;

	return 0;
}
