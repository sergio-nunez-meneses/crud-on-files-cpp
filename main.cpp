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
	{
		cout << "Our file " << fileName << ".txt has been created! Now, let's add some content to it." << endl;
		cout << "Type whatever you want, and press enter to save and continue." << endl;
		cout << "When you're finish, type exit and press enter." << endl;

		string content;

		while (getline(cin, content))
		{
			if (content != "exit")
				fileStream << content << endl;
			else
				break;
		}
	}
	else
		cout << "Handle errors" << endl;

	return 0;
}

