#include "Main.h"

string File::dateTime()
{
	// Get Date and Time
	auto now = system_clock::now();

	// Convert Time Point to a Time_t Object
	time_t now_time_t = system_clock::to_time_t(now);

	// Convert Time_t Object to a Local Time Struct
	tm* local_time = localtime(&now_time_t);

	// Format Date and Time
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", local_time);

	return buffer;
}

string File::read(string path)
{
	// Initialisation
	string contentLine;
	string content;

	fstream infile;

	// Open the file
	infile.open(path, fstream::in);

	// Read line by line
	while (getline(infile, contentLine))
	{
		content += contentLine;
	}

	// Close the file
	infile.close();

	return content;
}

string File::createFileLog(string path, string val, int chapter, string scene)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = path;

	// Find Name File
	int find = paths.find("Chapter-1");

	// Remove Name
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

	// Open the file
	outfile.open(paths, fstream::app);

	// Put Text
	outfile << "Chapter " << chapter << " : " << "Scene " << scene << " : " << "Choice " << val << "\n";

	// Close the file
	outfile.close();

	return paths;
}

void File::addFileLog(string pathLog, string val, int chapter, string scene)
{
	// Initialisation
	ofstream outfile;

	// Open the file
	outfile.open(pathLog, fstream::app);

	// Put Text
	outfile << "Chapter " << chapter << " : " << "Scene " << scene << " : " << "Choice " << val << "\n";

	// Close the file
	outfile.close();
}

void File::readFileError(string path, string name)
{
	// Get Path
	string paths = path;

	// Find Name File
	int find = paths.find("Chapter-1");

	// Remove Name
	paths = paths.substr(0, find);

	//  ---------- TO DO ----------

	// Error No File
	if (name == "NoFile")
	{
		// Add Name File
		paths += "Folder-Errors\\NoFile.txt";
	}
	
	cout << paths << endl;
}

Interface::Interface(int chapter, string scene, int start, int numberChoices)
{
	// Constructor
	this->chapter = chapter;
	this->scene = scene;
	this->start = start;
	this->numberChoices = numberChoices;
}

int Interface::getChapter()
{
	return this->chapter;
}

string Interface::getScene()
{
	return this->scene;
}

int Interface::getNumberChoices()
{
	return this->numberChoices;
}

const int* Interface::getTabGoScene()
{
	return this->tabGoScene;
}

int Interface::getValue()
{
	return this->value;
}

string Interface::getDefaultChoice()
{
	return this->defaultChoice;
}

bool Interface::getTimer()
{
	return this->timers;
}

int Interface::getTime()
{
	return this->time;
}

void Interface::setScene(string scene)
{
	this->scene = scene;
}

void Interface::functionDisplay(string content)
{
	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initialisation
	int speedLetters = 30000000; // Nanoseconds
	int pause = 600; // Miliseconds
	int index = 0;
	int indexTab[5];
	int indexScene = 0;
	int numberChoice = 0;
	bool skip = false;
	string defaultChoices = "";
	numberChoices = 0;
	value = 0;
	defaultChoice = "";
	timers = false;

	// Find Scene
	start = content.find("[Scene " + scene);
	index = content.find("]", start);

	// Read Each Caracters
	for (int i = start; i < index; i++)
	{
		// Back to Line
		if (content[i] == '_')
		{
			cout << endl;
		}
		// Good Choice
		else if (content[i] == '%')
		{
			/// Set Text Color Green
			SetConsoleTextAttribute(hConsole, 2);
		}
		// Bad Choice
		else if (content[i] == '&')
		{
			// Set Text Color Red
			SetConsoleTextAttribute(hConsole, 4);
		}
		// End of Text Color
		else if (content[i] == '=')
		{
			// Set Text Color White
			SetConsoleTextAttribute(hConsole, 7);
		}
		// Remove Caracter
		else if (skip || content[i] == '[' || content[i] == ']' || content[i] == '>' || content[i] == ')' || content[i] == '$')
		{
			skip = false;
		}
		// Pause Between Text
		else if (content[i] == '+')
		{
			// Wait
			Sleep(pause);
		}
		// Scene of the Choice
		else if(content[i] == '(')
		{
			// Get Scene
			string sceneNumber = content.substr(i + 1, 1);
			string sceneNumber2 = content.substr(i + 2, 1);

			// 2 digits
			if (sceneNumber2 != ")")
			{
				sceneNumber += sceneNumber2;
			}

			// Add to Table of Choice
			indexTab[indexScene] = stoi(sceneNumber);

			// Add Index of The Table
			indexScene += 1;
			skip = true;
		}
		// Number of Choice
		else if (content[i] == '<')
		{
			// Add Choice
			numberChoice += 1;
		}
		// Scene Default Choice Timer
		else if (content[i] == '^')
		{
			// Get Scene
			defaultChoices = content.substr(i + 2, 1);
			string sceneNumber2 = content.substr(i + 3, 1);

			// 2 digits
			if (sceneNumber2 != ")")
			{
				defaultChoices += sceneNumber2;
			}

			// Set Default Choice
			defaultChoice = content.substr(i + 4, 1);

			// Offset
			if (defaultChoice == ")")
			{
				defaultChoice = content.substr(i + 5, 1);
			}
		}
		// Show Caracter
		else
		{
			cout << content[i];
		}

		// Wait Speed Letters
		sleep_for(nanoseconds(speedLetters));
	}

	// End of Read
	numberChoices = numberChoice;

	// Set the Choices in Table
	for (int i = 0; i < indexScene; i++)
	{
		tabGoScene[i] = indexTab[i];
	}
	
	// Set the Default Choice
	if (defaultChoices != "")
	{
		value = stoi(defaultChoices);
		timers = true;
	}
}

void Interface::stopTimer()
{
	// Stop and Restart Timer Values
	autos = true;
	timers = false;

	time = 11;
}

bool Interface::timer()
{
	// Initialisation
	string times;

	// Decrementation
	time -= 1;

	// Show Timer Correctly
	if (time < 10)
	{
		times = "0" + to_string(time);
	}
	else
	{
		times = to_string(time);
	}

	cout << "Timer : " << times << endl;

	// End Timer
	return time <= 0;
}

COORD Interface::getPosCursor()
{
	// Get Cursor Pos
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD currentPosition = csbi.dwCursorPosition;

	return currentPosition;
}

void Interface::posCursor(int posX, int posY)
{
	// Set Cursor Pos
	COORD pos = { posX, posY };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

string getUserInput(bool& vals)
{
	// Initialisation
	string input;

	// Timer Runing
	while (!vals)
	{
		// Key Pressed
		if (_kbhit())
		{
			// Get Input
			char ch = _getch();
			input = ch;

			break;
		}
	}

	return input;
}