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
	int find = paths.find("SignalLost.exe");

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

void File::createFileErrors(string path)
{
	// Initialisation
	ofstream outfile;

	// Get Path
	string paths = path;

	// Find Name File
	int find = paths.find("SignalLost.exe");

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
	string BadFile = "BadFile.txt";
	string FileEmpty = "FileEmpty.txt";
	string NoFile = "NoFile.txt";

	// All Files Errors
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			// Add Name File
			paths += BadFile;

			// Open the file
			outfile.open(paths, fstream::out);

			// Put Text
			outfile << "Bad File";

			// Close the file
			outfile.close();

			// Find Name File
			int find = paths.find("BadFile.txt");

			// Remove Name
			paths = paths.substr(0, find);
		}
		else if (i == 1)
		{
			// Add Name File
			paths += FileEmpty;

			// Open the file
			outfile.open(paths, fstream::out);

			// Put Text
			outfile << "File Empty";

			// Close the file
			outfile.close();

			// Find Name File
			int find = paths.find("FileEmpty.txt");

			// Remove Name
			paths = paths.substr(0, find);
		}
		else if (i == 2)
		{
			// Add Name File
			paths += NoFile;

			// Open the file
			outfile.open(paths, fstream::out);

			// Put Text
			outfile << "No File";

			// Close the file
			outfile.close();

			// Find Name File
			int find = paths.find("NoFile.txt");

			// Remove Name
			paths = paths.substr(0, find);
		}
	}
}

void File::readFileError(string path, string name)
{
	// Initialisation
	fstream infile;
	string content;
	string contentLine;

	// Get Path
	string paths = path;

	// Find Name File
	int find = paths.find("SignalLost.exe");

	// Remove Name
	paths = paths.substr(0, find);

	// Add Name Folder
	paths += "Folder-Errors\\";

	// Add Name File
	paths += name + ".txt";

	// Open the file
	infile.open(paths, fstream::in);

	// Read line by line
	while (getline(infile, contentLine))
	{
		content += contentLine;
	}

	// Close the file
	infile.close();
	
	cout << content << endl;
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

void Interface::setTime()
{
	this->time -= 1;
}

void Interface::setScene(string scene)
{
	this->scene = scene;
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

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
}

void Interface::setConsoleWindowPosition(int x, int y)
{
	// Get Console
	HWND consoleWindow = GetConsoleWindow();

	// Set Position
	SetWindowPos(consoleWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Interface::show()
{
	// Get Console
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Menu Barre Down
	for (int i = 0; i < 120; i++)
	{
		posCursor(0 + i, 6);
		cout << char(223);
	}

	// Menu Barre Left
	for (int i = 0; i < 6; i++)
	{
		posCursor(15, 0 + i);
		cout << char(219);
	}

	// Set Text Color Blue
	SetConsoleTextAttribute(consoleHandle, 1);

	// Connection Barre
	for (int i = 0; i < 1; i++)
	{
		posCursor(2, 4 - i);
		cout << char(219);
	}

	for (int i = 0; i < 2; i++)
	{
		posCursor(5, 4 - i);
		cout << char(219);
	}

	for (int i = 0; i < 3; i++)
	{
		posCursor(8, 4 - i);
		cout << char(219);
	}

	for (int i = 0; i < 4; i++)
	{
		posCursor(11, 4 - i);
		cout << char(219);
	}

	// Set Text Color Red
	SetConsoleTextAttribute(consoleHandle, 7);

	// Trust Bar Up
	for (int i = 0; i < 36; i++)
	{
		posCursor(19 + i, 1);
		if (i == 0)
		{
			cout << char(219);
		}
		else if (i == 35)
		{
			cout << char(219);
		}
		else
		{
			cout << char(223) << endl;
		}
	}

	// Trust Bar Left
	for (int i = 0; i < 2; i++)
	{
		posCursor(19, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Right
	for (int i = 0; i < 2; i++)
	{
		posCursor(54, 2 + i);
		cout << char(219) << endl;
	}

	// Trust Bar Down
	for (int i = 0; i < 36; i++)
	{
		posCursor(19 + i, 4);
		if (i == 0)
		{
			cout << char(219);
		}
		else if (i == 35)
		{
			cout << char(219);
		}
		else
		{
			cout << char(220) << endl;
		}
	}

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
}

void Interface::functionDisplay(string content)
{
	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initialisation
	int speedLetters = 25000000; // Nanoseconds
	int pause = 600; // Miliseconds
	int index = 0;
	int indexTab[5];
	int indexScene = 0;
	int numberChoice = 0;
	int skip = 0;
	int space = 0;
	string defaultChoices = "";
	numberChoices = 0;
	value = 0;
	defaultChoice = "";
	timers = false;
	int supp = 9;
	int temp = stoi(scene);

	// Find Scene
	if (temp > 9)
	{
		supp += 1;
	}

	start = content.find("[Scene " + scene) + supp;
	index = content.find("]", start);

	// Read Each Caracters
	for (int i = start; i <= index; i++)
	{
		// Remove Caracter
		if (skip > 0 || content[i] == '[' || content[i] == ']')
		{
			skip -= 1;
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
		// End of Text Color
		else if (content[i] == '=')
		{
			// Set Text Color White
			SetConsoleTextAttribute(hConsole, 7);
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
			skip = 2;

			// 2 digits
			if (sceneNumber2 != ")")
			{
				sceneNumber += sceneNumber2;
				skip += 1;
			}

			// Add to Table of Choice
			indexTab[indexScene] = stoi(sceneNumber);

			// Add Index of The Table
			indexScene += 1;
		}
		// Number of Choice
		else if (content[i] == '<')
		{
			// Stop Speed
			speedLetters = 0;

			// Choice Position
			posCursor(15, 26 + space);
			space += 2;

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
		// Timer Time
		else if (content[i] == '/')
		{
			// Get Timer
			string sceneTimer = content.substr(i + 1, 1);
			string sceneTimer2 = content.substr(i + 2, 1);
			skip = 2;

			// 2 digits
			if (sceneTimer2 != "\\")
			{
				sceneTimer += sceneTimer2;
				skip += 1;
			}

			time = stoi(sceneTimer);
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
			beepBackground = true;
		}
		// Chapter Next
		else if (content[i] == '$')
		{

		}
		// Trust +
		else if (content[i] == '@')
		{

		}
		// Trust -
		else if (content[i] == '|')
		{

		}
		// TEMP
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
	timers = false;
}

bool Interface::timer()
{
	// Initialisation
	string times;

	// Get Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Show Timer Correctly
	if (time < 10)
	{
		times = "0" + to_string(time);
	}
	else
	{
		times = to_string(time);
	}

	// Verify Time
	if (time <= 5)
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
	cout << "Timer : " << times << endl;

	// Beep Timer
	Beep(500, 300);

	// Set Text Color White
	SetConsoleTextAttribute(hConsole, 7);

	// Timer Finish
	if (time <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Interface::clear()
{
	// Beep Desactivate
	beepBackground = false;

	// Timer
	posCursor(96, 2);
	cout << "          " << endl;

	// Scene Text
	for (int i = 0; i < 17; i++)
	{
		posCursor(0, 7 + i);
		cout << "                                                                                                                        " << endl;
	}

	// Choice Text
	for (int i = 0; i < 11; i++)
	{
		posCursor(13, 25 + i);
		cout << "                                                                                           " << endl;
	}
}

string getUserInput(bool& vals, Interface& interfaces)
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
			}	
		}
	}

	return input;
}

void test(future<void>& futures, bool& test)
{
	// Beep Activate
	if (test)
	{
		// Beep
		Beep(800, 300);

		// Beep
		Beep(800, 300);

		// Beep
		Beep(800, 300);

		// Wait 2 Seconds
		while (futures.wait_for(chrono::seconds(0)) == future_status::timeout && test == true)
		{
			if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
			{
				if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
				{
					if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
					{
						if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
						{
							if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
							{
								if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
								{
									if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
									{
										if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
										{
											if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
											{
												if (futures.wait_for(chrono::milliseconds(200)) == future_status::timeout && test == true)
												{
													if (test == true)
													{
														// Beep
														Beep(800, 300);
													}

													if (test == true)
													{
														// Beep
														Beep(800, 300);
													}

													if (test == true)
													{
														// Beep
														Beep(800, 300);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}