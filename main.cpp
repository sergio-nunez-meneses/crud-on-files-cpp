#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = __fs::filesystem;

int main()
{
	string projectPath = fs::current_path().parent_path().string();
	cout << projectPath << endl;
}

