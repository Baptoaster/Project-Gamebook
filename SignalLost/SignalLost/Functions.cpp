#include "Main.h"

Interface::Interface(string chapter, string scene, int start, int numberChoices, string defaultChoice, bool timers, int time, bool beepBackground, bool nextChapter, bool createLog, string pathLog, int trust)
{
	this->chapter = chapter;
	this->scene = scene;
	this->start = start;
	this->numberChoices = numberChoices;
	this->defaultChoice = defaultChoice;
	this->timers = timers;
	this->time = time;
	this->beepBackground = beepBackground;
	this->nextChapter = nextChapter;
	this->createLog = createLog;
	this->pathLog = pathLog;
	this->trust = trust;
}

bool Interface::getCreateLog()
{
	return this->createLog;
}

string Interface::getPathLog()
{
	return this->pathLog;
}

string Interface::getChapter()
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

const string* Interface::getTabGoChapter()
{
	return this->tabGoChapter;
}

const string* Interface::getTabGoScene()
{
	return this->tabGoScene;
}

const string* Interface::getTabTrust()
{
	return this->tabTrust;
}

string Interface::getDefaultChoiceScene()
{
	return this->defaultChoiceScene;
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

bool Interface::getBeepBackground()
{
	return this->beepBackground;
}

bool Interface::getNextChapter()
{
	return this->nextChapter;
}

void Interface::setCreateLog(bool createLog)
{
	this->createLog = createLog;
}

void Interface::setPathLog(string pathLog)
{
	this->pathLog = pathLog;
}

void Interface::setTime()
{
	this->time -= 1;
}

void Interface::setChapter(string chapter)
{
	this->chapter = chapter;
}

void Interface::setScene(string scene)
{
	this->scene = scene;
}

void Interface::setBeepBackground(bool beepBackground)
{
	this->beepBackground = beepBackground;
}

void Interface::setNextChapter(bool nextChapter)
{
	this->nextChapter = nextChapter;
}

void Interface::setTrust(int trust)
{
	this->trust = trust;
}

void Interface::consoleInitialisation()
{
	// Console Parameters
	setConsoleWindowPosition(200, 20);
	resizeConsole(120, 40);
	setConsoleFontSize(24);

	// Hide Cursor
	HWND consoleWindow = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	// Disable Resize
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	// Disable Mouse Paused
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
}

bool Interface::error(Interface& interfaces, File& file, string path, string pathExe)
{
	// Initialisation
	fstream infile;
	bool error = false;
	string errorName = "";

	// No Error
	if (!error)
	{
		// Open File
		infile.open(path, fstream::in);

		// Verify Exist
		if (infile.is_open())
		{
			// Close File
			infile.close();
		}
		else
		{
			// Error
			error = true;
			errorName = "NoChapterExist";
		}
	}

	// No Error
	if (!error)
	{
		// Find Name File
		size_t find = path.find(".txt");

		// Verify File Name
		if (find == string::npos)
		{
			// Error
			error = true;
			errorName = "BadFile";
		}
	}

	// No Error
	if (!error)
	{
		// Content File
		string content = file.read(interfaces, path);

		// Verify Not Null
		if (content == "")
		{
			// Error
			error = true;
			errorName = "FileEmpty";
		}
	}

	// Error
	if (error)
	{
		// Clean Console
		system("cls");

		// Read File Error File Empty
		file.readFileError(pathExe, errorName);
		char temp = _getch();
	}

	return error;
}

COORD Interface::getPosCursor()
{
	// Get Cursor Position
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD currentPosition = csbi.dwCursorPosition;

	return currentPosition;
}

void Interface::posCursor(int posX, int posY)
{
	// Set Cursor Position
	COORD pos = { SHORT(posX), SHORT(posY) };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void Interface::resizeConsole(int width, int height)
{
	// Get Console
	HWND consoleWindow = GetConsoleWindow();

	// Get Buffer Size
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	// Set Console Size
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);

	// Set Console Buffer Size
	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
}

void Interface::setConsoleFontSize(int fontSize)
{
	// Get Console
	HWND consoleWindow = GetConsoleWindow();

	// Get Current Font
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);

	// Set Font
	fontInfo.dwFontSize.X = 0;
	fontInfo.dwFontSize.Y = fontSize;
	wcscpy_s(fontInfo.FaceName, L"Clarendon");

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
}

void Interface::setConsoleWindowPosition(int x, int y)
{
	// Get Console
	HWND consoleWindow = GetConsoleWindow();

	// Set Position
	SetWindowPos(consoleWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Interface::displayInterface()
{
	// Get Console
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Menu Barre Down
	for (int i = 0; i < 120; i++)
	{
		posCursor(0 + i, 7);
		cout << char(223);
	}

	// Menu Barre Left
	for (int i = 0; i < 7; i++)
	{
		posCursor(15, 0 + i);
		cout << char(219);
	}

	// Set Text Color Blue
	SetConsoleTextAttribute(consoleHandle, 1);

	// Connection Barre
	for (int i = 0; i < 1; i++)
	{
		posCursor(2, 5 - i);
		cout << char(219);
	}

	for (int i = 0; i < 2; i++)
	{
		posCursor(5, 5 - i);
		cout << char(219);
	}

	for (int i = 0; i < 3; i++)
	{
		posCursor(8, 5 - i);
		cout << char(219);
	}

	for (int i = 0; i < 4; i++)
	{
		posCursor(11, 5 - i);
		cout << char(219);
	}

	// Set Text Color White
	SetConsoleTextAttribute(consoleHandle, 7);

	// Trust Bar Up
	for (int i = 0; i < 38; i++)
	{
		posCursor(19 + i, 1);
		cout << char(220) << endl;
	}

	// Trust Bar Left
	for (int i = 0; i < 3; i++)
	{
		posCursor(19, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Right
	for (int i = 0; i < 3; i++)
	{
		posCursor(56, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Down
	for (int i = 0; i < 38; i++)
	{
		posCursor(19 + i, 5);
		cout << char(223) << endl;
	}

	// Set Text Color Green
	SetConsoleTextAttribute(consoleHandle, 2);

	// Clear Trust
	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 2);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 3);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 4);
		cout << " " << endl;
	}

	// Trust
	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 2);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 3);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 4);
		cout << char(219) << endl;
	}

	// Set Text Color White
	SetConsoleTextAttribute(consoleHandle, 7);

	// Trust Number Pourcentage First
	posCursor(59, 1);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(59, 2);
	cout << char(219) << endl;
	posCursor(59, 3);
	cout << char(219) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(63, 4);
	cout << char(219) << endl;
	posCursor(59, 5);
	cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;

	// Trust Number Pourcentage Second
	posCursor(67, 1);
	cout << char(220) << char(220) << char(220) << endl;
	posCursor(66, 2);
	cout << char(219) << endl;
	posCursor(70, 2);
	cout << char(219) << endl;
	posCursor(66, 3);
	cout << char(219) << endl;
	posCursor(70, 3);
	cout << char(219) << endl;
	posCursor(66, 4);
	cout << char(219) << endl;
	posCursor(70, 4);
	cout << char(219) << endl;
	posCursor(67, 5);
	cout << char(223) << char(223) << char(223) << endl;

	// Trust Pourcentage
	posCursor(73, 1);
	cout << char(220) << "  " << char(220) << endl;
	posCursor(75, 2);
	cout << char(220) << char(223) << endl;
	posCursor(74, 3);
	cout << char(220) << char(223) << endl;
	posCursor(73, 4);
	cout << char(220) << char(223) << endl;
	posCursor(73, 5);
	cout << char(223) << "  " << char(223) << endl;

	/*
	// Trust Number Pourcentage Third
	posCursor(74, 1);
	cout << char(220) << char(220) << char(220) << endl;
	posCursor(73, 2);
	cout << char(219) << endl;
	posCursor(77, 2);
	cout << char(219) << endl;
	posCursor(73, 3);
	cout << char(219) << endl;
	posCursor(77, 3);
	cout << char(219) << endl;
	posCursor(73, 4);
	cout << char(219) << endl;
	posCursor(77, 4);
	cout << char(219) << endl;
	posCursor(74, 5);
	cout << char(223) << char(223) << char(223) << endl;
	*/

	/*
	// Trust Pourcentage 
	posCursor(80, 1);
	cout << char(220) << "  " << char(220) << endl;
	posCursor(82, 2);
	cout << char(220) << char(223) << endl;
	posCursor(81, 3);
	cout << char(220) << char(223) << endl;
	posCursor(80, 4);
	cout << char(220) << char(223) << endl;
	posCursor(80, 5);
	cout << char(223) << "  " << char(223) << endl;
	*/

	// Choice Barre Up
	posCursor(11, 24);
	for (int i = 0; i < 96; i++)
	{
		if (i == 0)
		{
			cout << char(219);
		}
		else if (i == 95)
		{
			cout << char(219);
		}
		else
		{
			cout << char(223);
		}
	}

	// Choice Barre Left
	for (int i = 0; i < 11; i++)
	{
		posCursor(11, 25 + i);
		cout << char(219) << endl;
	}

	// Choice Barre Right
	for (int i = 0; i < 11; i++)
	{
		posCursor(106, 25 + i);
		cout << char(219) << endl;
	}

	// Choice Barre Down
	posCursor(11, 36);
	for (int i = 0; i < 96; i++)
	{
		if (i == 0)
		{
			cout << char(219);
		}
		else if (i == 95)
		{
			cout << char(219);
		}
		else
		{
			cout << char(220);
		}
	}

	// Reset Position Cursor
	posCursor(0, 0);
}

void Interface::displayText(string content)
{
	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initialisation
	int speedLetters = 25000000; // Nanoseconds
	int pause = 600; // Miliseconds
	size_t index = 0;
	int indexScene = 0;
	int indexChapter = 0;
	int indexTrust = 0;
	int numberChoice = 0;
	string numberScene = "";
	string numberDefaultChoiceScene = "";
	string numberChapter = "";
	string numberTime = "";
	int skipCaracter = 0;
	int spaceChoice = 0;
	this->numberChoices = 0;
	this->defaultChoiceScene = "";
	this->defaultChoice = "";
	this->timers = false;
	bool skipScene = false;
	bool skipDefaultChoice = false;
	bool skipChapter = false;
	bool skipTime = false;
	size_t hide = 8;
	int initial = 0;

	for (int i = 0; i < size(this->tabGoScene); i++)
	{
		this->tabGoScene[i] = "";
	}

	for(int i = 0; i < size(this->tabGoChapter); i++)
	{
		this->tabGoChapter[i] = "";
	}
	
	for (int i = 0; i < size(this->tabTrust); i++)
	{
		this->tabTrust[i] = "";
	}

	// Hide Scene Number
	hide += this->scene.length();

	// Find Start / End
	this->start = content.find("[Scene " + this->scene) + hide;
	index = content.find("]", this->start);

	// Read Each Caracters
	for (size_t i = this->start; i <= index; i++)
	{
		// Remove Caracter
		if (skipCaracter > 0 || content[i] == '[' || content[i] == ']')
		{
			skipCaracter -= 1;
		}
		// Skip Scene Number
		else if (skipScene)
		{
			// End
			if (content[i] == ')')
			{
				skipScene = false;

				this->tabGoScene[indexScene] = numberScene;

				// Add Index of The Table
				indexScene += 1;
				numberScene = "";
			}
			// Add Digit
			else
			{
				// Add to Table of Choice
				numberScene += content[i];
			}
		}
		// Skip Default Choice
		else if (skipDefaultChoice)
		{
			// End
			if (content[i] == ')')
			{
				skipDefaultChoice = false;

				// Set Default Choice
				this->defaultChoiceScene = numberDefaultChoiceScene;
				this->defaultChoice = content.substr(i + 1, 1);
				i = initial;
			}
			// Add Digit
			else
			{
				// Add to Default Choice
				numberDefaultChoiceScene += content[i];
			}
		}
		// Skip Chapter Number
		else if (skipChapter)
		{
			// End
			if (content[i] == ' ')
			{
				skipChapter = false;

				// Set Chapter
				this->tabGoChapter[indexChapter] = numberChapter;

				// Add Index of The Table
				indexChapter += 1;
				numberChapter = "";
			}
			// Add Digit
			else
			{
				// Add to Chapter
				numberChapter += content[i];
			}
		}
		// Skip Time Number
		else if (skipTime)
		{
			// End
			if (content[i] == '\\')
			{
				skipTime = false;

				// Set Time
				this->time = stoi(numberTime);
			}
			// Add Digit
			else
			{
				// Add to Time
				numberTime += content[i];
			}
		}
		// Back to Line
		else if (content[i] == '_')
		{
			cout << endl << "  ";
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
		// End Text Color
		else if (content[i] == '=')
		{
			// Set Text Color White
			SetConsoleTextAttribute(hConsole, 7);
		}
		// Bip
		else if (content[i] == '#')
		{
			// Beep Text
			Beep(800, 300);
		}
		// Bip Background
		else if (content[i] == '~')
		{
			// Beep Activate
			this->beepBackground = true;
		}
		// Pause Between Text
		else if (content[i] == '+')
		{
			// Wait
			Sleep(pause);
		}
		// Number of Choice
		else if (content[i] == '<')
		{
			// Stop Speed
			speedLetters = 0;

			// Choice Position
			posCursor(15, 26 + spaceChoice);
			spaceChoice += 2;

			// Add Choice
			numberChoice += 1;
		}
		// Scene of the Choice
		else if(content[i] == '(')
		{
			skipScene = true;
		}
		// Scene Default Choice Timer
		else if (content[i] == '^')
		{
			skipDefaultChoice = true;
			skipCaracter = 1;
			initial = i;
		}
		// Trust +
		else if (content[i] == '@')
		{
			this->tabTrust[indexTrust] = "1";
			indexTrust += 1;
		}
		// Trust -
		else if (content[i] == '|')
		{
			this->tabTrust[indexTrust] = "-1";
			indexTrust += 1;
		}
		// Timer Time
		else if (content[i] == '/')
		{
			skipTime = true;
		}
		// Chapter Next
		else if (content[i] == '$')
		{
			this->nextChapter = true;
			skipChapter = true;
		}
		// TO DO -----------------------------------------------------------------------------------------------
		else if (content[i] == ';' || content[i] == '>')
		{
			// ; choix bloquer 3
			// > choix bloquer 4
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
	this->numberChoices = numberChoice;
	
	// Set the Default Choice
	if (this->defaultChoiceScene != "")
	{
		this->timers = true;
	}
}

void Interface::stopTimer()
{
	// Stop and Restart Timer Values
	this->timers = false;
}

void Interface::trustBar(string val)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Verify Val
	if (val == "1" && this->trust < 100)
	{
		// Incrementation
		this->trust += 25;
	}
	else if (val == "-1" && this->trust > 0)
	{
		// Decrementation
		this->trust -= 25;
	}

	// Set Local Default
	locale::global(locale("C"));

	// Set Text Color Green
	SetConsoleTextAttribute(consoleHandle, 2);

	// Clear Trust
	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 2);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 3);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(20 + i, 4);
		cout << " " << endl;
	}

	// Trust
	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 2);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 3);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(20 + i, 4);
		cout << char(219) << endl;
	}

	// Set Text Color White
	SetConsoleTextAttribute(consoleHandle, 7);

	// Set Local UTF-8
	locale::global(locale("en_US.utf8"));
}

bool Interface::timer()
{
	// Initialisation
	string times;
	bool result = false;

	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Show Timer Correctly
	if (this->time < 10)
	{
		times = "0" + to_string(this->time);
	}
	else
	{
		times = to_string(this->time);
	}

	// Verify Time
	if (this->time <= 5)
	{
		// Set Text Color Red
		SetConsoleTextAttribute(hConsole, 4);
	}
	else
	{
		// Set Text Color White
		SetConsoleTextAttribute(hConsole, 7);
	}

	// Show Timer
	posCursor(96, 3);
	cout << "Timer : " << times << endl;

	// Beep Timer
	if (this->chapter != "1" || this->scene != "1")
	{
		Beep(500, 300);
	}

	// Set Text Color White
	SetConsoleTextAttribute(hConsole, 7);

	// Timer Finish
	if (this->time <= 0)
	{
		result = true;
	}

	return result;
}

void Interface::clear()
{
	// Beep Desactivate
	this->beepBackground = false;

	// Timer
	posCursor(96, 3);
	cout << "          " << endl;

	// Scene Text
	for (int i = 0; i < 16; i++)
	{
		posCursor(0, 8 + i);
		cout << "                                                                                                                        " << endl;
	}

	// Choice Text
	for (int i = 0; i < 11; i++)
	{
		posCursor(13, 25 + i);
		cout << "                                                                                           " << endl;
	}

	// Reset Position Cursor
	posCursor(0, 0);
}

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

void File::createFileErrors(string pathExe)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find("SignalLost.exe");

	// Remove Name
	paths = paths.substr(0, find);

	// Add Name Folder
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

	string nameFile[4] = { "BadFile.txt", "FileEmpty.txt", "NoFile.txt", "NoChapterExist.txt" };
	string textFile[4] = { "Bad File", "File Empty", "No File Exist", "Chapter Doesn't Exist" };

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
	bool skip = false;
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
				// Chapter Number
				if(skip)
				{
					// End
					if (contentLine[i] == ' ')
					{
						skip = false;
					}
					// Add Digit
					else
					{
						chapter += contentLine[i];
					}
				}
				// Other
				else if (contentLine[i] == '-')
				{
					skip = true;
				}
			}

			// Set Chapter
			interfaces.setChapter(chapter);
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
		string paths = createFileLog(pathExe, input, interfaces.getChapter(), interfaces.getScene());

		// Define File Log
		interfaces.setCreateLog(true);
		interfaces.setPathLog(pathExe);
	}
	else
	{
		// Add File Log
		addFileLog(interfaces.getPathLog(), input, interfaces.getChapter(), interfaces.getScene());
	}
}

string File::createFileLog(string pathExe, string input, string chapter, string scene)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find("SignalLost.exe");

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

void File::readFileError(string pathExe, string name)
{
	// Initialisation
	fstream infile;
	string content;
	string contentLine;

	// Get Path
	string paths = pathExe;

	// Find Name File
	size_t find = paths.find("SignalLost.exe");

	// Remove Name
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

string UserInput(bool& finish, Interface& interfaces)
{
	// Initialisation
	string input;

	// Timer Runing
	while (!finish)
	{
		// Key Pressed
		if (_kbhit())
		{
			// Get Input
			char ch = _getch();
			input = ch;

			// Try Integer
			try
			{
				// Verify Integer
				(void)stoi(input);

				// Verify Choice Possible
				if (stoi(input) > 0 && stoi(input) <= interfaces.getNumberChoices())
				{
					// Succed
					break;
				}
			}
			// Fail
			catch (const logic_error& e)
			{
				(void)e;
			}	
		}
	}

	return input;
}

void BeepBackground(future<void>& futures, Interface& interfaces)
{
	// Initialisation
	int val = 0;

	// Beep Activate
	if (interfaces.getBeepBackground())
	{
		// Beep
		Beep(800, 300);

		// Beep
		Beep(800, 300);

		// Beep
		Beep(800, 300);

		// Wait 200 Milliseconds
		while (interfaces.getBeepBackground() && futures.wait_for(chrono::milliseconds(200)) == future_status::timeout)
		{
			// Wait 2 Seconds
			if (interfaces.getBeepBackground() && val >= 10)
			{
				val = 0;

				if (interfaces.getBeepBackground())
				{
					Beep(800, 300);
				}
				
				if (interfaces.getBeepBackground())
				{
					Beep(800, 300);
				}

				if (interfaces.getBeepBackground())
				{
					Beep(800, 300);
				}
			}

			val += 1;
		}
	}
}