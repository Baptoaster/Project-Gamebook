#include "Main.h"

string File::dateTime()
{
	// Get Date and Time
	auto now = system_clock::now();

	// Convert Time Point to Time_t Object
	time_t now_time_t = system_clock::to_time_t(now);

	// Convert Time_t Object to Local Time Struct
	tm* local_time = localtime(&now_time_t);

	// Format Date and Time
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", local_time);

	return buffer;
}

void File::createFileErrors(Interface& interfaces, string pathExe)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find(interfaces.getTitleConsole());

	// Name Console
	paths = paths.substr(0, find);

	// Add Name File
	paths += "Folder-Errors\\";

	// Get Attributes
	DWORD attributes = GetFileAttributesA(paths.c_str());

	// Verify Folder Exist
	if (!(attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		// Create Folder
		CreateDirectoryA(paths.c_str(), NULL);
	}

	// Initialisation Files
	string pathError = paths;

	string nameFile[5] = { "BadFile.txt", "FileEmpty.txt", "NoSceneExist.txt", "NoFile.txt", "NoChapterExist.txt" };
	string textFile[5] = { "Bad File", "File Empty", "Scene Doesn't Exist", "No File Exist", "Chapter Doesn't Exist" };

	// All Files Errors
	for (int i = 0; i < size(nameFile); i++)
	{
		// Initialisation
		paths = pathError;

		// Add Name File
		paths += nameFile[i];

		// Open the file
		outfile.open(paths, fstream::out);

		// Put Text
		outfile << textFile[i];

		// Close the file
		outfile.close();
	}
}

string File::read(Interface& interfaces, string path)
{
	// Initialisation
	fstream infile;
	string contentLine = "";
	string content = "";
	string chapter = "";
	string chapterTitle = "";
	string scene = "";
	string trust = "";
	bool skipChapter = false;
	bool skipChapterTitle = false;
	bool skipScene = false;
	bool skipTrust = false;
	int line = 0;

	// Open File
	infile.open(path, fstream::in);

	// Read Line by Line
	while (getline(infile, contentLine))
	{
		// Add to Content
		content += contentLine;

		// First Line Chapter
		if (line == 0)
		{
			// Read Each Caracters
			for (int i = 0; i < contentLine.length(); i++)
			{
				// Scene Number
				if (skipScene)
				{
					// End
					if (contentLine[i] == '>')
					{
						skipScene = false;
					}
					else
					{
						scene += contentLine[i];
					}
				}
				// Trust Number
				else if (skipTrust)
				{
					// End
					if (contentLine[i] == '\\')
					{
						skipTrust = false;
						skipScene = true;
						i += 1;

						// Set Trust
						if (!interfaces.getDefaultTrust())
						{
							interfaces.setDefaultTrust(true);
							interfaces.setTrust(stoi(trust));
						}
					}
					// Add Digit
					else
					{
						trust += contentLine[i];
					}
				}
				// Chapter Title
				else if (skipChapterTitle)
				{
					// End
					if (contentLine[i] == ')')
					{
						skipChapterTitle = false;
						skipTrust = true;
						i += 1;
					}
					// Set Title
					else
					{
						chapterTitle += contentLine[i];
					}
				}
				// Chapter Number
				else if (skipChapter)
				{
					// End
					if (contentLine[i] == '(')
					{
						skipChapter = false;
						skipChapterTitle = true;
					}
					// Add Digit
					else
					{
						chapter += contentLine[i];
					}
				}
				// Start Chapter Number
				else if (contentLine[i] == '-')
				{
					skipChapter = true;
				}
			}

			// Set Chapter & Scene
			interfaces.setChapter(chapter);
			interfaces.setChapterTitle(chapterTitle);
			interfaces.setScene(scene);;
		}

		// Line Incrementation
		line += 1;
	}

	// Close File
	infile.close();

	return content;
}

void File::FileLog(string pathExe, string input, Interface& interfaces)
{
	// Verify Exist
	if (!interfaces.getCreateLog())
	{
		// Create File Log
		string paths = createFileLog(interfaces, pathExe, input, interfaces.getChapter(), interfaces.getScene());

		// Define File Log
		interfaces.setCreateLog(true);
		interfaces.setPathLog(paths);
	}
	else
	{
		// Add File Log
		addFileLog(interfaces.getPathLog(), input, interfaces.getChapter(), interfaces.getScene());
	}
}

string File::createFileLog(Interface& interfaces, string pathExe, string input, string chapter, string scene)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find(interfaces.getTitleConsole());

	// Name Console
	paths = paths.substr(0, find);

	// Add Name Folder
	paths += "Folder-Logs\\";

	// Get Attributes
	DWORD attributes = GetFileAttributesA(paths.c_str());

	// Verify Folder Exist
	if (!(attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		// Create Folder
		CreateDirectoryA(paths.c_str(), NULL);
	}

	// Add Name File
	paths += "Log_" + dateTime() + ".txt";

	// Open file
	outfile.open(paths, fstream::app);

	// Put Text
	outfile << "Chapter " << chapter << " : " << "Scene " << scene << " : " << "Choice " << input << "\n";

	// Close File
	outfile.close();

	return paths;
}

void File::addFileLog(string pathLog, string input, string chapter, string scene)
{
	// Initialisation
	ofstream outfile;

	// Open the file
	outfile.open(pathLog, fstream::app);

	// Put Text
	outfile << "Chapter " << chapter << " : " << "Scene " << scene << " : " << "Choice " << input << "\n";

	// Close the file
	outfile.close();
}

void File::readFileError(Interface& interfaces, string pathExe, string name)
{
	// Initialisation
	fstream infile;
	string content;
	string contentLine;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find(interfaces.getTitleConsole());

	// Name Console
	paths = paths.substr(0, find);

	// Add Name Folder
	paths += "Folder-Errors\\";

	// Add Name File
	paths += name + ".txt";

	// Open File
	infile.open(paths, fstream::in);

	// Read Line by Line
	while (getline(infile, contentLine))
	{
		// Add to Content
		content += contentLine;
	}

	// Close File
	infile.close();

	// Show Error File
	cout << content << endl;
}