#include "Main.h"

int main(int argc, char* argv[])
{
	// Path of the Files
	File file;
	File& other = file;
	string pathExe = argv[0];
	string path = argv[1];
	bool error = false;

	// Initialisation
	Interface interfaces(1, "1", 0, 0);
	bool createLog = false;
	string pathLog = "";
	string content = "";

	// Create Files Errors
	file.createFileErrors(pathExe);

	// Console Parameters
	interfaces.setConsoleWindowPosition(300, 20);
	interfaces.resizeConsole(120, 40);
	interfaces.setConsoleFontSize(24);

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

	// Find Name File
	int find = path.find(".txt");

	// Verify File Name
	if (find <= 0)
	{
		// Error
		error = true;

		// Read File Error Bad File
		file.readFileError(pathExe, "BadFile");
		cout << "" << endl;
		char temp = _getch();
	}

	// No Error
	if (error == false)
	{
		// Content File
		content = file.read(path);

		// Verify Not Null
		if (content == "")
		{
			// Error
			error = true;

			// Read File Error File Empty
			file.readFileError(pathExe, "FileEmpty");
			cout << "" << endl;
			char temp = _getch();
		}
	}
	
	// No Error
	if(error == false)
	{
		// Show Interface
		interfaces.show();

		// Chapter Read
		while (1)
		{
			// Initialisation
			bool succed = false;
			string input = "";
			int val = 0;
			bool time = false;

			// Chapter Scene 1
			if (interfaces.getChapter() == 1 && interfaces.getScene() == "1")
			{
				interfaces.beepBackground = true;
			}

			// Create Async Bip
			future<void> futures = async(launch::async, test, ref(futures), ref(interfaces.beepBackground));

			// Show Interface
			locale::global(locale("en_US.utf8"));
			interfaces.posCursor(0, 7);
			interfaces.functionDisplay(content);

			// Key Pressed Before
			while (_kbhit())
			{
				char temp = _getch();
			}

			// Input System
			while (!succed)
			{
				// Timer
				if (interfaces.getTimer())
				{
					// Initialisation
					bool vals = false;

					// Create Async Timer
					future<string> future = async(launch::async, getUserInput, ref(vals), ref(interfaces));

					// Timer Run
					while (!vals)
					{
						// Cursor Pos
						COORD pos = interfaces.getPosCursor();
						interfaces.posCursor(96, 2);
						vals = interfaces.timer();

						// End Timer
						if (vals)
						{
							// Set variable
							succed = true;
							time = true;

							// Get Input Function
							input = future.get();

							// Set Input Default Value
							input = to_string(interfaces.getValue());

							break;
						}
						// Input Before End Timer
						else if (future.wait_for(chrono::seconds(1)) == future_status::ready)
						{
							// Get Input Function
							input = future.get();

							// Set Text Color White
							SetConsoleTextAttribute(consoleHandle, 7);

							break;
						}

						// Decrement Time
						interfaces.setTime();
					}
				}
				else
				{
					// Initialisation
					input = "";

					// Get Input
					char ch = _getch();
					input = ch;
				}

				// No Timer
				if (!time)
				{
					// Try Integer
					try
					{
						// Verify Integer
						(void)stoi(input);

						// Verify Choice Possible
						if (stoi(input) > 0 && stoi(input) <= interfaces.getNumberChoices())
						{
							// Succed
							succed = true;
							val = stoi(input);
						}
					}
					// Fail
					catch (const logic_error& e)
					{
						succed = false;
					}
				}
			}

			// Succed
			if (succed)
			{
				// Scene With Timer
				if (time)
				{
					// Verify Exist
					if (!createLog)
					{
						// Create File Log
						string paths = file.createFileLog(pathExe, interfaces.getDefaultChoice(), interfaces.getChapter(), interfaces.getScene());

						createLog = true;
						pathLog = paths;
					}
					else
					{
						// Add to File Log
						file.addFileLog(pathLog, interfaces.getDefaultChoice(), interfaces.getChapter(), interfaces.getScene());
					}

					// Stop Timer
					if (interfaces.getTimer() == true)
					{
						interfaces.stopTimer();
					}

					// Change Scene
					interfaces.setScene(input);
				}
				// Scene Without Timer
				else
				{
					// Verify Exist
					if (!createLog)
					{
						// Create File Log
						string paths = file.createFileLog(pathExe, input, interfaces.getChapter(), interfaces.getScene());

						createLog = true;
						pathLog = paths;
					}
					else
					{
						// Add to File Log
						file.addFileLog(pathLog, input, interfaces.getChapter(), interfaces.getScene());
					}

					// Get Scene Choice
					val = interfaces.getTabGoScene()[val - 1];

					// Stop Timer
					if (interfaces.getTimer())
					{
						interfaces.stopTimer();
					}

					// Change Scene
					interfaces.setScene(to_string(val));
				}

				// Clear Interface
				interfaces.clear();
			}
		}
	}

	return 0;
}
