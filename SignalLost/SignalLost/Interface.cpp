#include "Main.h"

Interface::Interface(string chapter, string chapterTitle, string scene, int start, int numberChoices, string defaultChoice, bool defaultTrust, bool timers, int time, bool beepBackground, bool noBeepSound, bool nextChapter, bool newChapter, bool createLog, string pathLog, int trust, bool showMenu, bool soundActivated, int textFontSize)
{
	this->chapter = chapter;
	this->chapterTitle = chapterTitle;
	this->scene = scene;
	this->start = start;
	this->numberChoices = numberChoices;
	this->defaultChoice = defaultChoice;
	this->timers = timers;
	this->time = time;
	this->beepBackground = beepBackground;
	this->noBeepSound = noBeepSound;
	this->nextChapter = nextChapter;
	this->newChapter = newChapter;
	this->createLog = createLog;
	this->pathLog = pathLog;
	this->trust = trust;
	this->defaultTrust = defaultTrust;
	this->showMenu = showMenu;
	this->soundActivated = soundActivated;
	this->textFontSize = textFontSize;
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

string Interface::getChapterTitle()
{
	return this->chapterTitle;
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

const string* Interface::getTabTrustNumber()
{
	return this->tabTrustNumber;
}

const string* Interface::getTabTrustRequirement()
{
	return this->tabTrustRequirement;
}

const string* Interface::getTabTrustRequirementScene()
{
	return this->tabTrustRequirementScene;
}

string Interface::getDefaultChoiceScene()
{
	return this->defaultChoiceScene;
}

string Interface::getDefaultChoice()
{
	return this->defaultChoice;
}

bool Interface::getDefaultTrust()
{
	return this->defaultTrust;
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

bool Interface::getNewChapter()
{
	return this->newChapter;
}

int Interface::getTrust()
{
	return this->trust;
}

bool Interface::getShowMenu()
{
	return this->showMenu;
}

bool Interface::getSoundActivated()
{
	return this->soundActivated;
}

string Interface::getTitleConsole()
{
	return this->titleConsole;
}

void Interface::setCreateLog(bool createLog)
{
	this->createLog = createLog;
}

void Interface::setPathLog(string pathLog)
{
	this->pathLog = pathLog;
}

void Interface::setDefaultTrust(bool defaultTrust)
{
	this->defaultTrust = defaultTrust;
}

void Interface::setTime()
{
	this->time -= 1;
}

void Interface::setChapter(string chapter)
{
	this->chapter = chapter;
}

void Interface::setChapterTitle(string chapterTitle)
{
	this->chapterTitle = chapterTitle;
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

void Interface::setNewChapter(bool newChapter)
{
	this->newChapter = newChapter;
}

void Interface::setTrust(int trust)
{
	this->trust = trust;
}

void Interface::setShowMenu(bool showMenu)
{
	this->showMenu = showMenu;
}

void Interface::setTitleConsole(string titleConsole)
{
	this->titleConsole = titleConsole;
}

void Interface::consoleInitialisation()
{
	// Desactivated F11
	DWORD previousMode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &previousMode);
	auto newMode = previousMode & ~ENABLE_PROCESSED_INPUT;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), newMode);

	// Get Screen
	HWND hDesktop = GetDesktopWindow();

	// Get Screen Dimension
	RECT desktopRect;
	GetWindowRect(hDesktop, &desktopRect);

	// Width Screen
	int screenWidth = (desktopRect.right - desktopRect.left) / 2 - 780;

	// Console Parameters
	setConsoleWindowPosition(screenWidth, 20);
	resizeConsole(120, 40);

	// Adapt police
	int screenWidth2 = (desktopRect.right - desktopRect.left);
	if (screenWidth2 >= 1920)
	{
		this->textFontSize = 24;
		setConsoleFontSize(24);
	}
	else if (screenWidth2 >= 1680)
	{
		this->textFontSize = 20;
		setConsoleFontSize(20);
	}
	else if (screenWidth2 >= 1280)
	{
		this->textFontSize = 16;
		setConsoleFontSize(16);
	}

	// Hide Cursor
	HWND consoleWindow = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	// Disable Resize
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &=  ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
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
	if (!error || path.find("NoChapterExist.txt"))
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
	if (!error || path.find("BadFile.txt"))
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
	if (!error || path.find("FileEmpty.txt"))
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
		file.readFileError(interfaces, pathExe, errorName);
		char temp = _getch();
	}

	return error;
}

void Interface::Menu()
{
	// Input Choice
	char temp = '0';

	// Choice
	while (1)
	{
		// Set Local Default
		locale::global(locale("C"));

		// Title
		int posX = 12;
		int posY = 4;

		// Letter -
		posCursor(posX, posY);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << " " << " " << " " << endl;

		posX += 7;

		// Letter -
		posCursor(posX, posY);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << " " << " " << " " << endl;

		posX += 7;

		// Letter S
		posCursor(posX, posY);
		cout << " " << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(223) << char(220) << char(220) << char(220) << " " << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << char(223) << char(223) << char(223) << " " << endl;

		posX += 5;

		// Letter I
		posCursor(posX, posY);
		cout << " " << " " << char(220) << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << char(219) << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << " " << " " << char(219) << " " << " " << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << char(219) << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << char(223) << " " << " " << endl;

		posX += 5;

		// Letter G
		posCursor(posX, posY);
		cout << " " << char(220) << char(220) << char(220) << " " << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << char(223) << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << char(220) << char(220) << " " << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << " " << char(223) << char(223) << char(223) << " " << endl;

		posX += 7;

		// Letter N
		posCursor(posX, posY);
		cout << char(220) << " " << " " << " " << char(220) << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << char(219) << " " << " " << char(219) << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << char(219) << " " << char(219) << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << " " << " " << char(219) << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << " " << " " << " " << char(223) << endl;

		posX += 7;

		// Letter A
		posCursor(posX, posY);
		cout << " " << " " << char(220) << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << char(219) << " " << char(219) << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << char(223) << char(223) << char(223) << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << " " << " " << " " << char(223) << endl;

		posX += 7;

		// Letter L
		posCursor(posX, posY);
		cout << char(220) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;

		posX += 5;

		// Letter Space
		posCursor(posX, posY);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << " " << " " << " " << endl;

		posX += 5;

		// Letter L
		posCursor(posX, posY);
		cout << char(220) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;

		posX += 7;

		// Letter O
		posCursor(posX, posY);
		cout << " " << char(220) << char(220) << char(220) << " " << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 2);
		cout << char(219) << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 3);
		cout << char(219) << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << " " << char(223) << char(223) << char(223) << " " << endl;

		posX += 7;

		// Letter S
		posCursor(posX, posY);
		cout << " " << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 1);
		cout << char(219) << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(223) << char(220) << char(220) << char(220) << " " << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << char(219) << endl;
		posCursor(posX, posY + 4);
		cout << char(223) << char(223) << char(223) << char(223) << " " << endl;

		posX += 7;

		// Letter T
		posCursor(posX, posY);
		cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << char(219) << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << " " << " " << char(219) << " " << " " << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << char(219) << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << char(223) << " " << " " << endl;

		posX += 7;

		// Letter -
		posCursor(posX, posY);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << " " << " " << " " << endl;

		posX += 7;

		// Letter -
		posCursor(posX, posY);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 2);
		cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
		posCursor(posX, posY + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(posX, posY + 4);
		cout << " " << " " << " " << " " << " " << endl;

		// Box Choice
		posCursor(50, 17);
		for (int i = 0; i < 19; i++)
		{
			if (i == 0 || i == 18)
			{
				cout << char(219);
			}
			else
			{
				cout << char(223);
			}
		}

		for (int i = 0; i < 9; i++)
		{
			posCursor(50, 18 + i);
			cout << char(219);
		}

		for (int i = 0; i < 9; i++)
		{
			posCursor(68, 18 + i);
			cout << char(219);
		}

		posCursor(50, 27);
		for (int i = 0; i < 19; i++)
		{
			if (i == 0 || i == 18)
			{
				cout << char(219);
			}
			else
			{
				cout << char(220);
			}
		}

		// Set Local UTF-8
		locale::global(locale("en_US.utf8"));

		// Menu Choice
		posCursor(54, 19);
		cout << "1 - Start" << endl;
		posCursor(54, 21);
		cout << "2 - Credits" << endl;
		posCursor(54, 23);
		cout << "3 - Options" << endl;
		posCursor(54, 25);
		cout << "4 - Quit" << endl;


		temp = _getch();

		// Start
		if (temp == '1')
		{
			break;
		}
		// Credit
		if (temp == '2')
		{
			// Clear
			system("cls");

			Sleep(600);

			// Set Local Default
			locale::global(locale("C"));

			// Title
			posX = 37;
			posY = 10;

			// Letter C
			posCursor(posX, posY);
			cout << " " << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << " " << char(223) << char(223) << char(223) << " " << endl;

			Sleep(200);
			posX += 7;

			// Letter R
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << char(223) << char(219) << char(223) << " " << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << char(219) << " " << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << " " << " " << " " << char(223) << endl;

			Sleep(200);
			posX += 7;

			// Letter E
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;

			Sleep(200);
			posX += 7;

			// Letter D
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << char(223) << char(223) << char(223) << "" << endl;

			Sleep(200);
			posX += 5;

			// Letter I
			posCursor(posX, posY);
			cout << " " << " " << char(220) << " " << " " << endl;
			posCursor(posX, posY + 1);
			cout << " " << " " << char(219) << " " << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << " " << " " << char(223) << " " << " " << endl;

			Sleep(200);
			posX += 5;

			// Letter T
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << " " << " " << char(223) << " " << " " << endl;

			Sleep(200);
			posX += 7;

			// Letter S
			posCursor(posX, posY);
			cout << " " << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << char(223) << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << char(223) << char(223) << char(223) << " " << endl;

			// Set Local UTF-8
			locale::global(locale("en_US.utf8"));

			Sleep(800);

			// Names
			posCursor(42, 18);
			cout << "Game Designer : Baptiste PERRIN";
			posCursor(42, 19);
			cout << "Game Designer : Loic VAREILLES" << endl;
			posCursor(42, 21);
			cout << "Game Programming : Killian FURNO" << endl;
			posCursor(42, 22);
			cout << "Game Programming : Florian MARTINS" << endl;
			posCursor(42, 23);
			cout << "Game Programming : Hortense MARIE" << endl;
			posCursor(42, 24);
			cout << "Game Programming : Adrien LECHAT" << endl;

			Sleep(8000);

			// Clear
			system("cls");

			// Key Pressed Before
			if (_kbhit())
			{
				while (_kbhit())
				{
					char temps = _getch();
				}
			}
		}
		// Options
		else if (temp == '3')
		{
			// Clear
			system("cls");

			// Set Local Default
			locale::global(locale("C"));

			// Title
			posX = 37;
			posY = 10;

			// Letter O
			posCursor(posX, posY);
			cout << " " << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << " " << char(223) << char(223) << char(223) << " " << endl;

			posX += 7;

			// Letter P
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << char(220) << char(220) << char(220) << char(223) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << " " << " " << " " << " " << endl;

			posX += 7;

			// Letter T
			posCursor(posX, posY);
			cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << " " << " " << char(223) << " " << " " << endl;

			posX += 5;

			// Letter I
			posCursor(posX, posY);
			cout << " " << " " << char(220) << " " << " " << endl;
			posCursor(posX, posY + 1);
			cout << " " << " " << char(219) << " " << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << char(219) << " " << " " << endl;
			posCursor(posX, posY + 4);
			cout << " " << " " << char(223) << " " << " " << endl;

			posX += 5;

			// Letter O
			posCursor(posX, posY);
			cout << " " << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << " " << char(223) << char(223) << char(223) << " " << endl;

			posX += 7;

			// Letter N
			posCursor(posX, posY);
			cout << char(220) << " " << " " << " " << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << char(219) << " " << " " << char(219) << endl;
			posCursor(posX, posY + 2);
			cout << char(219) << " " << char(219) << " " << char(219) << endl;
			posCursor(posX, posY + 3);
			cout << char(219) << " " << " " << char(219) << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << " " << " " << " " << char(223) << endl;

			posX += 7;

			// Letter S
			posCursor(posX, posY);
			cout << " " << char(220) << char(220) << char(220) << char(220) << endl;
			posCursor(posX, posY + 1);
			cout << char(219) << " " << " " << " " << " " << endl;
			posCursor(posX, posY + 2);
			cout << char(223) << char(220) << char(220) << char(220) << " " << endl;
			posCursor(posX, posY + 3);
			cout << " " << " " << " " << " " << char(219) << endl;
			posCursor(posX, posY + 4);
			cout << char(223) << char(223) << char(223) << char(223) << " " << endl;

			// Box Choice
			posCursor(45, 17);
			for (int i = 0; i < 26; i++)
			{
				if (i == 0 || i == 25)
				{
					cout << char(219);
				}
				else
				{
					cout << char(223);
				}
			}

			for (int i = 0; i < 8; i++)
			{
				posCursor(45, 18 + i);
				cout << char(219);
			}

			for (int i = 0; i < 8; i++)
			{
				posCursor(70, 18 + i);
				cout << char(219);
			}

			posCursor(45, 25);
			for (int i = 0; i < 26; i++)
			{
				if (i == 0 || i == 25)
				{
					cout << char(219);
				}
				else
				{
					cout << char(220);
				}
			}

			// Set Local UTF-8
			locale::global(locale("en_US.utf8"));

			// Option Choice
			posCursor(49, 19);
			cout << "1 - Sound" << endl;
			posCursor(49, 21);
			cout << "2 - Font Size" << endl;
			posCursor(54, 23);
			cout << "3 - Back" << endl;

			// Get Console
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			while (1)
			{
				// Set Text Color Green
				SetConsoleTextAttribute(consoleHandle, 2);

				posCursor(63, 19);
				if (this->soundActivated)
				{
					cout << "ON " << endl;
				}
				else
				{
					cout << "OFF" << endl;
				}

				posCursor(63, 21);
				cout << this->textFontSize << "px" << endl;

				// Set Text Color White
				SetConsoleTextAttribute(consoleHandle, 7);

				char temps2 = _getch();

				if (temps2 == '1')
				{
					if (this->soundActivated)
					{
						this->soundActivated = false;
					}
					else
					{
						this->soundActivated = true;
					}
					
				}
				else if(temps2 == '2')
				{
					if (this->textFontSize == 16)
					{
						this->textFontSize = 20;
						setConsoleFontSize(20);
					}
					else if (this->textFontSize == 20)
					{
						this->textFontSize = 24;
						setConsoleFontSize(24);
					}
					else if (this->textFontSize == 24)
					{
						this->textFontSize = 16;
						setConsoleFontSize(16);
					}
				}
				else if(temps2 == '3')
				{
					break;
				}
			}

			// Clear
			system("cls");
		}
		// Quit
		else if (temp == '4')
		{
			exit(0);
		}
	}
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

	// Letter T
	int digit5 = 18;
	posCursor(digit5, 1);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(digit5, 2);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit5, 3);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit5, 4);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit5, 5);
	cout << " " << " " << char(223) << " " << " " << endl;

	// Letter R
	int digit6 = 25;
	posCursor(digit6, 1);
	cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit6, 2);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit6, 3);
	cout << char(219) << char(223) << char(219) << char(223) << " " << endl;
	posCursor(digit6, 4);
	cout << char(219) << " " << " " << char(219) << " " << endl;
	posCursor(digit6, 5);
	cout << char(223) << " " << " " << " " << char(223) << endl;

	// Letter U
	int digit7 = 32;
	posCursor(digit7, 1);
	cout << char(220) << " " << " " << " " << char(220) << endl;
	posCursor(digit7, 2);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit7, 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit7, 4);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit7, 5);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;

	// Letter S
	int digit8 = 39;
	posCursor(digit8, 1);
	cout << " " << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(digit8, 2);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(digit8, 3);
	cout << char(223) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit8, 4);
	cout << " " << " " << " " << " " << char(219) << endl;
	posCursor(digit8, 5);
	cout << char(223) << char(223) << char(223) << char(223) << " " << endl;

	// Letter T
	int digit9 = 46;
	posCursor(digit9, 1);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(digit9, 2);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit9, 3);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit9, 4);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit9, 5);
	cout << " " << " " << char(223) << " " << " " << endl;

	// Trust Bar Up
	for (int i = 0; i < 38; i++)
	{
		posCursor(53 + i, 1);
		cout << char(220) << endl;
	}

	// Trust Bar Left
	for (int i = 0; i < 3; i++)
	{
		posCursor(53, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Right
	for (int i = 0; i < 3; i++)
	{
		posCursor(90, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Down
	for (int i = 0; i < 38; i++)
	{
		posCursor(53 + i, 5);
		cout << char(223) << endl;
	}

	// Set Text Color Green
	SetConsoleTextAttribute(consoleHandle, 2);

	// Clear Trust
	for (int i = 0; i < 36; i++)
	{
		posCursor(54 + i, 2);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(54 + i, 3);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(54 + i, 4);
		cout << " " << endl;
	}

	// Trust
	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 2);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 3);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 4);
		cout << char(219) << endl;
	}

	// Set Text Color White
	SetConsoleTextAttribute(consoleHandle, 7);

	pourcentage();

	// Choice Barre Up
	posCursor(3, 25);
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
		posCursor(3, 26 + i);
		cout << char(219) << endl;
	}

	// Choice Barre Right
	for (int i = 0; i < 11; i++)
	{
		posCursor(98, 26 + i);
		cout << char(219) << endl;
	}

	// Choice Barre Down
	posCursor(3, 37);
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

bool Interface::displayText(string content)
{
	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	posCursor(0, 8);

	// Initialisation
	int speedLetters = 20000000; // Nanoseconds
	int pause = 600; // Miliseconds
	size_t index = 0;
	int indexScene = 0;
	int indexChapter = 0;
	int indexTrustNumber = 0;
	int indexTrustRequirement = 0;
	int numberChoice = 0;
	string numberScene = "";
	string numberDefaultChoiceScene = "";
	string numberChapter = "";
	string numberTime = "";
	string numberTrust = "";
	string numberTrustRequirement = "";
	int skipCaracter = 0;
	int spaceChoice = 0;
	this->numberChoices = 0;
	this->defaultChoiceScene = "";
	this->defaultChoice = "";
	this->timers = false;
	bool skipScene = false;
	bool skipDefaultChoice = false;
	bool skipChapter = false;
	bool skipTrust = false;
	bool skipTrustRequirement = false;
	bool skipTime = false;
	bool connexionBar = false;
	size_t hide = 8;
	size_t initial = 0;

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

	for (int i = 0; i < size(this->tabTrustNumber); i++)
	{
		this->tabTrustNumber[i] = "";
	}

	for (int i = 0; i < size(this->tabTrustRequirement); i++)
	{
		this->tabTrustRequirement[i] = "";
	}

	for (int i = 0; i < size(this->tabTrustRequirementScene); i++)
	{
		this->tabTrustRequirementScene[i] = "";
	}

	// Hide Scene Number
	hide += this->scene.length();

	// Find Scene
	size_t find = content.find("[Scene " + this->scene);
	if(find == string::npos)
	{
		return true;
	}

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
		// Skip Trust Reset
		else if (skipTrust)
		{
			if (content[i] == '\\')
			{
				skipTrust = false;

				// Set Trust Reset
				this->tabTrustNumber[indexTrustNumber] = numberTrust;

				// Add Index of The Table
				indexTrustNumber += 1;
				numberTrust = "";
			}
			else
			{
				// Add to Trust Number
				numberTrust += content[i];
			}
		}
		// Skip Trust Number Scene
		else if (skipTrustRequirement)
		{
			if (content[i] == '_')
			{
				skipTrustRequirement = false;

				// Set Trust Requirement Number Scene
				this->tabTrustRequirementScene[indexTrustRequirement] = numberTrustRequirement;

				// Add Index of The Table
				indexTrustRequirement += 1;
				numberTrustRequirement = "";
			}
			else
			{
				// Add to Trust Requirement Number Secene
				numberTrustRequirement += content[i];
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
			else if (content[i] == '/')
			{
				skipChapter = false;
				skipTrust = true;

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
			if (this->soundActivated)
			{
				// Beep Text
				Beep(800, 300);
			}
		}
		// Connexion Bar 0
		else if (content[i] == ')')
		{
			// Set Local Default
			locale::global(locale("C"));

			// Set Text Color Blue
			SetConsoleTextAttribute(hConsole, 1);

			// Connection Barre
			for (int i = 0; i < 1; i++)
			{
				posCursor(2, 5 - i);
				cout << " ";
			}

			for (int i = 0; i < 2; i++)
			{
				posCursor(5, 5 - i);
				cout << " ";
			}

			for (int i = 0; i < 3; i++)
			{
				posCursor(8, 5 - i);
				cout << " ";
			}

			for (int i = 0; i < 4; i++)
			{
				posCursor(11, 5 - i);
				cout << " ";
			}

			// Set Text Color White
			SetConsoleTextAttribute(hConsole, 7);

			// Set Local UTF-8
			locale::global(locale("en_US.utf8"));

			posCursor(0, 8);
		}
		// Connexion Bar 2 & 4
		else if (content[i] == '\\')
		{
			// Set Local Default
			locale::global(locale("C"));

			// Set Text Color Blue
			SetConsoleTextAttribute(hConsole, 1);
			
			// Connexion Bar 4
			if (connexionBar)
			{
				connexionBar = false;

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
			}
			// Connexion Bar 2
			else
			{
				connexionBar = true;

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
					cout << " ";
				}

				for (int i = 0; i < 4; i++)
				{
					posCursor(11, 5 - i);
					cout << " ";
				}
			}

			// Set Text Color White
			SetConsoleTextAttribute(hConsole, 7);

			// Set Local UTF-8
			locale::global(locale("en_US.utf8"));

			// Reset Cursor
			posCursor(0, 8);
		}
		// Bip Background
		else if (content[i] == '~')
		{
			// Beep Activate
			this->beepBackground = true;
			this->noBeepSound = true;
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
			posCursor(8, 27 + spaceChoice);
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
			this->tabTrust[numberChoice - 1] = "1";
		}
		// Trust -
		else if (content[i] == '|')
		{
			this->tabTrust[numberChoice - 1] = "-1";
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
		// Trust Requirement
		else if (content[i] == '>' || content[i] == ';')
		{
			this->tabTrustRequirement[indexTrustRequirement] = content[i];
			skipTrustRequirement = true;
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

	return false;
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
		posCursor(54 + i, 2);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(54 + i, 3);
		cout << " " << endl;
	}

	for (int i = 0; i < 36; i++)
	{
		posCursor(54 + i, 4);
		cout << " " << endl;
	}

	// Trust
	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 2);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 3);
		cout << char(219) << endl;
	}

	for (int i = 0; i < (this->trust / 100.0) * 36; i++)
	{
		posCursor(54 + i, 4);
		cout << char(219) << endl;
	}

	// Set Text Color White
	SetConsoleTextAttribute(consoleHandle, 7);

	pourcentage();

	// Set Local UTF-8
	locale::global(locale("en_US.utf8"));
}

bool Interface::timer()
{
	// Initialisation
	bool result = false;

	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Show Timer
	timerShow();

	// Beep Timer
	if (!this->noBeepSound && this->soundActivated)
	{
		Beep(500, 300);
	}

	// Set Text Color White
	SetConsoleTextAttribute(hConsole, 7);

	// Timer Finish
	if (this->time <= 0)
	{
		result = true;
		this->noBeepSound = false;
	}

	return result;
}

void Interface::timerShow()
{
	// Initialisation
	string times;

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

	// Set Local Default
	locale::global(locale("C"));

	// Initialisation
	int val = 104;
	int valH = 29;

	// Number Timer
	for (int i = 0; i < size(times); i++)
	{
		// Timer Number Value
		char number = times[i];

		if (number == '0')
		{
			numberZero(val, valH);
		}
		else if (number == '1')
		{
			numberOne(val, valH);
		}
		else if (number == '2')
		{
			numberTwo(val, valH);
		}
		else if (number == '3')
		{
			numberThree(val, valH);
		}
		else if (number == '4')
		{
			numberFour(val, valH);
		}
		else if (number == '5')
		{
			numberFive(val, valH);
		}
		else if (number == '6')
		{
			numberSix(val, valH);
		}
		else if (number == '7')
		{
			numberSeven(val, valH);
		}
		else if (number == '8')
		{
			numberEight(val, valH);
		}
		else if (number == '9')
		{
			numberNine(val, valH);
		}

		val += 7;
	}

	// Set Local UTF-8
	locale::global(locale("en_US.utf8"));
}

void Interface::clear()
{
	// Set Beep Sound
	this->noBeepSound = false;

	// Scene Text
	for (int i = 0; i < 16; i++)
	{
		posCursor(0, 8 + i);
		cout << "                                                                                                                        " << endl;
	}

	// Choice Text
	for (int i = 0; i < 11; i++)
	{
		posCursor(4, 26 + i);
		cout << "                                                                                              " << endl;
	}

	// Initialisation
	int val = 104;
	int valH = 29;

	// Number Timer
	for (int i = 0; i < 2; i++)
	{
		// Timer
		posCursor(val, valH);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(val, valH + 1);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(val, valH + 2);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(val, valH + 3);
		cout << " " << " " << " " << " " << " " << endl;
		posCursor(val, valH + 4);
		cout << " " << " " << " " << " " << " " << endl;

		val += 7;
	}

	// Reset Position Cursor
	posCursor(0, 0);
}

void Interface::pourcentage()
{
	int digit1 = 93;
	int digit2 = 100;
	int digit3 = 107;
	int digit4 = 114;

	if (this->trust == 0)
	{
		// Trust Number 0
		numberZero(digit1, 1);

		// Trust Number 0
		numberZero(digit2, 1);

		// Trust Number 0
		numberZero(digit3, 1);
	}
	else if (this->trust == 25)
	{
		// Trust Number 0
		numberZero(digit1, 1);

		// Trust Number 2
		numberTwo(digit2, 1);

		// Trust Number 5
		numberFive(digit3, 1);
	}
	else if (this->trust == 50)
	{
		// Trust Number 0
		numberZero(digit1, 1);

		// Trust Number 5
		numberFive(digit2, 1);

		// Trust Number 0
		numberZero(digit3, 1);
	}
	else if (this->trust == 75)
	{
		// Trust Number 0
		numberZero(digit1, 1);

		// Trust Number 7
		numberSeven(digit2, 1);

		// Trust Number 5
		numberFive(digit3, 1);
	}
	else if (this->trust == 100)
	{
		// Trust Number 1
		numberOne(digit1, 1);

		// Trust Number 0
		numberZero(digit2, 1);

		// Trust Number 0
		numberZero(digit3, 1);
	}

	// Trust Pourcentage
	posCursor(digit4, 1);
	cout << char(220) << " " << " " << char(220) << endl;
	posCursor(digit4, 2);
	cout << " " << " " << char(220) << char(223) << endl;
	posCursor(digit4, 3);
	cout << " " << char(220) << char(223) << " " << endl;
	posCursor(digit4, 4);
	cout << char(220) << char(223) << " " << " " << endl;
	posCursor(digit4, 5);
	cout << char(223) << " " << " " << char(223) << endl;
}

void Interface::transition()
{
	// Set Local Default
	locale::global(locale("C"));

	int posX = 24;
	int posY = 14;

	// Letter C
	posCursor(posX, posY);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(posX, posY + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 4);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;

	Sleep(200);
	posX += 7;

	// Letter H
	posCursor(posX , posY);
	cout << char(220) << " " << " " << " " << char(220) << endl;
	posCursor(posX, posY + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << char(220) << char(220) << char(220) << char(219) << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 4);
	cout << char(223) << " " << " " << " " << char(223) << endl;

	Sleep(200);
	posX += 7;

	// Letter A
	posCursor(posX, posY);
	cout << " " << " " << char(220) << " " << " " << endl;
	posCursor(posX, posY + 1);
	cout << " " << char(219) << " " << char(219) << " " << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << char(223) << char(223) << char(223) << char(219) << endl;
	posCursor(posX, posY + 4);
	cout << char(223) << " " << " " << " " << char(223) << endl;

	Sleep(200);
	posX += 7;

	// Letter P
	posCursor(posX, posY);
	cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(posX, posY + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << char(220) << char(220) << char(220) << char(223) << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 4);
	cout << char(223) << " " << " " << " " << " " << endl;

	Sleep(200);
	posX += 7;

	// Letter T
	posCursor(posX, posY);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(posX, posY + 1);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(posX, posY + 2);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(posX, posY + 3);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(posX, posY + 4);
	cout << " " << " " << char(223) << " " << " " << endl;

	Sleep(200);
	posX += 7;

	// Letter E
	posCursor(posX, posY);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(posX, posY + 1);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 4);
	cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;

	Sleep(200);
	posX += 7;

	// Letter R
	posCursor(posX, posY);
	cout << char(220) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(posX, posY + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(posX, posY + 2);
	cout << char(219) << char(223) << char(219) << char(223) << " " << endl;
	posCursor(posX, posY + 3);
	cout << char(219) << " " << " " << char(219) << " " << endl;
	posCursor(posX, posY + 4);
	cout << char(223) << " " << " " << " " << char(223) << endl;

	Sleep(200);
	posX += 7;

	// Letter -
	posCursor(posX, posY);
	cout << " " << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 1);
	cout << " " << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 2);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(posX, posY + 3);
	cout << " " << " " << " " << " " << " " << endl;
	posCursor(posX, posY + 4);
	cout << " " << " " << " " << " " << " " << endl;
	
	Sleep(200);
	posX += 7;

	// Chapter
	for (int i = 0; i < size(getChapter()); i++)
	{
		// Timer Number Value
		char number = getChapter()[i];

		if (number == '0')
		{
			numberZero(posX, posY);
		}
		else if (number == '1')
		{
			numberOne(posX, posY);
		}
		else if (number == '2')
		{
			numberTwo(posX, posY);
		}
		else if (number == '3')
		{
			numberThree(posX, posY);
		}
		else if (number == '4')
		{
			numberFour(posX, posY);
		}
		else if (number == '5')
		{
			numberFive(posX, posY);
		}
		else if (number == '6')
		{
			numberSix(posX, posY);
		}
		else if (number == '7')
		{
			numberSeven(posX, posY);
		}
		else if (number == '8')
		{
			numberEight(posX, posY);
		}
		else if (number == '9')
		{
			numberNine(posX, posY);
		}

		posX += 7;
		Sleep(200);
	}

	// Set Local UTF-8
	locale::global(locale("en_US.utf8"));

	// Title Show
	Sleep(800);
	posX -= 35;
	posX -= SHORT(size(this->chapterTitle)) / 2;
	posY += 6;

	posCursor(posX, posY);
	cout << this->chapterTitle << endl;

	Sleep(2000);
}

void Interface::numberZero(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;
}

void Interface::numberOne(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << " " << char(220) << " " << " " << endl;
	posCursor(digit, y + 1);
	cout << char(220) << char(223) << char(219) << " " << " " << endl;
	posCursor(digit, y + 2);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit, y + 3);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit, y + 4);
	cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;
}

void Interface::numberTwo(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << " " << " " << " " << char(219) << " " << endl;
	posCursor(digit, y + 3);
	cout << " " << char(220) << char(223) << " " << " " << endl;
	posCursor(digit, y + 4);
	cout << char(223) << char(223) << char(223) << char(223) << char(223) << endl;
}

void Interface::numberThree(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << " " << " " << " " << char(219) << " " << endl;
	posCursor(digit, y + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;
}

void Interface::numberFour(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << " " << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << " " << char(220) << char(223) << char(219) << " " << endl;
	posCursor(digit, y + 2);
	cout << char(220) << char(223) << " " << char(219) << " " << endl;
	posCursor(digit, y + 3);
	cout << char(219) << char(220) << char(220) << char(219) << char(220) << endl;
	posCursor(digit, y + 4);
	cout << " " << " " << " " << char(223) << " " << endl;
}

void Interface::numberFive(int digit, int y)
{
	posCursor(digit, y);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << " " << endl;
	posCursor(digit, y + 2);
	cout << char(219) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 3);
	cout << " " << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << char(223) << char(223) << char(223) << char(223) << " " << endl;
}

void Interface::numberSix(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << " " << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << " " << char(219) << " " << " " << " " << endl;
	posCursor(digit, y + 2);
	cout << char(219) << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;
}

void Interface::numberSeven(int digit, int y)
{
	posCursor(digit, y);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	posCursor(digit, y + 1);
	cout << " " << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << " " << " " << " " << char(219) << " " << endl;
	posCursor(digit, y + 3);
	cout << " " << " " << char(219) << " " << " " << endl;
	posCursor(digit, y + 4);
	cout << " " << " " << char(223) << " " << " " << endl;
}

void Interface::numberEight(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << char(219) << char(220) << char(220) << char(220) << char(219) << endl;
	posCursor(digit, y + 3);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << " " << char(223) << char(223) << char(223) << " " << endl;
}

void Interface::numberNine(int digit, int y)
{
	posCursor(digit, y);
	cout << " " << char(220) << char(220) << char(220) << " " << endl;
	posCursor(digit, y + 1);
	cout << char(219) << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 2);
	cout << char(219) << char(220) << char(220) << char(220) << char(219) << endl;
	posCursor(digit, y + 3);
	cout << " " << " " << " " << " " << char(219) << endl;
	posCursor(digit, y + 4);
	cout << char(223) << char(223) << char(223) << char(223) << " " << endl;
}
