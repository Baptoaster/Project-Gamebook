#include "Main.h"

int main(int argc, char* argv[])
{
	// Name Console
	const wchar_t* Title = L"SignalLost";
	SetConsoleTitle(Title);

	// Instance Running
	LPCWSTR mutexName = L"SignalLost";
	HANDLE mutexHandle = CreateMutex(NULL, TRUE, mutexName);

	// Verify Already Exist
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// Exit
		CloseHandle(mutexHandle);

		return 1;
	}

	// Class Initialisation
	File file;
	Interface interfaces("1", "1", 0, 0, "0", false, 0, false, false, false, "", 50);

	// Console Initialisation
	interfaces.consoleInitialisation();

	// No File
	if (argv[1] == nullptr)
	{
		// Clean Console
		system("cls");

		// Read File Error No File
		file.readFileError(argv[0], "NoFile");
		char temp = _getch();
	}
	else
	{
		// Paths Initialisation
		string pathExe = argv[0];
		string path = argv[1];

		// Create Files Errors
		file.createFileErrors(pathExe);

		// All Chapters
		while (1)
		{
			// Initialisation
			bool error = false;
			string content = "";

			// Reset Trust
			interfaces.setTrust(50);

			// Verify Error
			error = interfaces.error(interfaces, file, path, pathExe);

			// No Error
			if (!error)
			{
				// Read Chapter
				string content = file.read(interfaces, path);

				// Set Local Default
				locale::global(locale("C"));

				// Show Interface
				interfaces.displayInterface();
				interfaces.setNextChapter(false);

				// Set Local UTF-8
				locale::global(locale("en_US.utf8"));

				// Chapter Read
				while (!interfaces.getNextChapter())
				{
					// Initialisation
					bool succed = false;
					string input = "";
					bool time = false;

					// Chapter 1 Scene 1
					if (interfaces.getChapter() == "1" && interfaces.getScene() == "1")
					{
						// Activate Beep
						interfaces.setBeepBackground(true);
					}

					// Create Async Bip
					future<void> futures = async(launch::async, BeepBackground, ref(futures), ref(interfaces));

					// Show Interface
					error = interfaces.displayText(content);

					// Error
					if (error)
					{
						// Clean Console
						system("cls");

						// Read File Error No Scene Exist
						file.readFileError(pathExe, "NoSceneExist");
						char temp = _getch();

						break;
					}
					else
					{
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
								bool finish = false;

								// Create Async Timer
								future<string> future = async(launch::async, UserInput, ref(finish), ref(interfaces));

								// Timer Run
								while (!finish)
								{
									// Start Timer
									finish = interfaces.timer();

									// End Timer
									if (finish)
									{
										// Set Variables
										succed = true;
										time = true;

										// Get Input Function
										input = future.get();

										// Set Input Default Value
										input = interfaces.getDefaultChoiceScene();

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
									}
								}
								// Fail
								catch (const logic_error& e)
								{
									(void)e;
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
								// File Log
								file.FileLog(pathExe, interfaces.getDefaultChoice(), interfaces);

								// Stop Timer
								if (interfaces.getTimer() == true)
								{
									interfaces.stopTimer();
								}

								// Change Scene
								interfaces.setScene(input);

								// Trust
								string val = interfaces.getTabTrust()[stoi(interfaces.getDefaultChoice()) - 1];
								interfaces.trustBar(val);
							}
							// Scene With Chapter
							else if (interfaces.getNextChapter())
							{
								// File Log
								file.FileLog(pathExe, input, interfaces);

								// Stop Timer
								if (interfaces.getTimer())
								{
									interfaces.stopTimer();
								}

								// Change Scene
								interfaces.setScene("1");

								// Change Chapter
								interfaces.setChapter(interfaces.getTabGoChapter()[stoi(input) - 1]);

								// Change Path
								path = pathExe;

								// Find Name File
								size_t find = path.find("SignalLost.exe");

								// Remove Name
								path = path.substr(0, find);
								path += "Chapter-" + interfaces.getChapter() + ".txt";
							}
							// Scene Without Timer
							else
							{
								// File Log
								file.FileLog(pathExe, input, interfaces);

								// Stop Timer
								if (interfaces.getTimer())
								{
									interfaces.stopTimer();
								}

								// Change Scene
								interfaces.setScene(interfaces.getTabGoScene()[stoi(input) - 1]);

								// Trust
								string val = interfaces.getTabTrust()[stoi(input) - 1];
								interfaces.trustBar(val);
							}

							// Clear Interface
							interfaces.clear();
						}
					}
				}

				if (error)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	return 0;
}