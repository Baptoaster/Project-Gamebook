#include "Main.h"

int main(int argc, char* argv[])
{
	// Path of the file
	File file;
	File& other = file;
	string path = argv[1];

	// Initialisation
	locale::global(locale("en_US.utf8"));
	Interface interfaces(1, "1", 0, 0);
	bool createLog = false;
	string pathLog = "";

	// Hide Cursor
	HWND consoleWindow = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	// Content of the file
	string content = file.read(path);

	// Chapter Read
	while (1)
	{
		// Initialisation
		bool succed = false;
		string input = "";
		int val = 0;
		bool time = false;

		// Show Interface
		interfaces.functionDisplay(content);

		// Key Pressed Before
		while (_kbhit())
		{
			char temp = _getch();
		}

		// Show User Interraction
		cout << "[Press your Choice]" << endl;

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
					interfaces.posCursor(90, 0);
					vals = interfaces.timer();
					interfaces.posCursor(pos.X, pos.Y);

					// End Timer
					if (vals)
					{
						// Set variable
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
					string paths = file.createFileLog(path, interfaces.getDefaultChoice(), interfaces.getChapter(), interfaces.getScene());

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
				system("cls");
			}
			// Scene Without Timer
			else
			{
				// Verify Exist
				if (!createLog)
				{
					// Create File Log
					string paths = file.createFileLog(path, input, interfaces.getChapter(), interfaces.getScene());

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
				system("cls");
			}
		}
	}

	return 0;
}
