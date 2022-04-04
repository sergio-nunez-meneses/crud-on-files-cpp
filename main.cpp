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

int main()
{
	string cwd = getCurrentProjectPath();
	string fileDirPath = cwd + "/created-files";
	string filePath, fileContent;
	fstream file;

	if (!fs::is_directory(fileDirPath))
		fs::create_directory(fileDirPath);

	cout << "Howdy, what would you like to do? Type a number and press enter:" << endl;
	cout << "\t\t[1] Read a file" << endl;
	cout << "\t\t[2] Create a text file" << endl;

	int action;
	cin >> action;

	if (action == 1)
	{
		cout << "\nWhich file would you like to read? Type a number and press enter:" << endl;

		vector<string> files;

		int fileIndex = 0;
		for (const auto &entry: fs::directory_iterator(fileDirPath))
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
			string fileName = fs::path(filePath).filename().string();

			cout << "\nReading file: " << fileName << "\n" << endl;
			while (getline(file, fileContent))
				cout << fileContent << endl;

			file.close();
			cout << "\n*-- End reading file --*" << endl;

			cout << "\nWould you like to edit this file?" << endl;
			cout << "\t\t[1] Yes" << endl;
			cout << "\t\t[2] No" << endl;

			cin >> action;

			if (action == 1)
			{
				file.open(filePath, ios::out | ios::app);

				if (file.is_open())
				{
					cout << "\nEditing file: " << fileName << endl;
					cout << "(Press enter to save and continue, type exit and press enter to stop)\n" << endl;

					while (getline(cin, fileContent))
					{
						if (fileContent != "exit")
							file << fileContent << endl;
						else
							break;
					}
					file.close();
					cout << "\n*-- End editing file --*" << endl;
				}
				else
					cout << "Unable to open file" << endl;
			}
			else
				file.close();
		}
		else
			cout << "Unable to open file" << endl;
	}
	else
	{
		cout << "Enter file name:" << endl;

		string fileName;
		cin >> fileName;

		if (fileName.find('.') == string::npos)
			fileName += ".txt";
		else
		{
			size_t needle = fileName.find_last_of('.'); // unsigned integer type of the result of the sizeof operator

			if (fileName.substr(needle + 1) != "txt")
				fileName = fileName.substr(0, needle) + ".txt";
		}

		filePath = fileDirPath + "/" + fileName;
		file.open(filePath, ios::out);

		if (file.is_open())
		{
			cout << "\nEditing file: " << fileName << endl;
			cout << "(Press enter to save and continue, type exit and press enter to stop)\n" << endl;

			while (getline(cin, fileContent))
			{
				if (fileContent != "exit")
					file << fileContent << endl;
				else
					break;
			}
			file.close();
			cout << "\n*-- End editing file --*" << endl;
		}
		else
			cout << "Unable to open file" << endl;
	}

	return 0;
}

