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
	Interface interfaces("1", "", "1", 0, 0, "0", false, 0, false, false, false, false, true, false, "", 50, true, true, 24);

	// Console Initialisation
	interfaces.consoleInitialisation();

	// Paths Initialisation
	string pathExe = argv[0];

	// Get Name Console
	string titleConsole = pathExe;

	// Find Name
	size_t find = titleConsole.find("SignalLost.exe");

	// Take Name
	titleConsole = titleConsole.substr(find);

	// Set Name
	interfaces.setTitleConsole(titleConsole);

	// Create Files Errors
	file.createFileErrors(interfaces, pathExe);

	// No File
	if (argv[1] == nullptr)
	{
		// Clean Console
		system("cls");

		// Read File Error No File
		file.readFileError(interfaces, argv[0], "NoFile");
		char temp = _getch();
	}
	else
	{	
		// Paths Initialisation
		string path = argv[1];

		// All Chapters
		while (1)
		{
			// Initialisation
			bool error = false;
			string content = "";

			// Verify Error
			error = interfaces.error(interfaces, file, path, pathExe);

			// No Error
			if (!error)
			{
				// Read Chapter
				string content = file.read(interfaces, path);

				// Menu
				if (interfaces.getShowMenu())
				{
					interfaces.setShowMenu(false);
					interfaces.Menu();
				}

				// New Chapter Transition
				if (interfaces.getNewChapter())
				{
					interfaces.setNewChapter(false);

					// Clear Console
					system("cls");

					// Transition
					interfaces.transition();

					// Clear Console
					system("cls");
				}

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
						file.readFileError(interfaces, pathExe, "NoSceneExist");
						char temp = _getch();
						if (temp == 133) 
						{
							continue;
						}

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

								// Quit Choice
								if (interfaces.getTabGoChapter()[stoi(input) - 1] == "99")
								{
									// Quit
									exit(0);
								}
								// Return Menu
								else if (interfaces.getTabGoChapter()[stoi(input) - 1] == "00")
								{
									// Clear
									system("cls");

									// Menu
									interfaces.setShowMenu(true);
									interfaces.setNewChapter(true);
									interfaces.setScene("1");
								}
								else
								{
									// Change Scene
									interfaces.setScene("1");

									// Change Chapter
									interfaces.setChapter(interfaces.getTabGoChapter()[stoi(input) - 1]);

									// Change Path
									path = pathExe;

									// Find Name File
									size_t find = path.find(interfaces.getTitleConsole());

									// Remove Name
									path = path.substr(0, find);
									path += "Chapter-" + interfaces.getChapter() + ".txt";

									// Trust
									if (interfaces.getTabTrustNumber()[stoi(input) - 1] != "")
									{
										// Reset Trust
										interfaces.setTrust(stoi(interfaces.getTabTrustNumber()[stoi(input) - 1]));
									}

									interfaces.setNewChapter(true);
								}
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

								// Trust Requirement 75
								if (interfaces.getTabTrustRequirement()[stoi(input) - 1] == ">" && interfaces.getTrust() < 75)
								{
									// Change Scene
									interfaces.setScene(interfaces.getTabTrustRequirementScene()[stoi(input) - 1]);
								}
								// Trust Requirement 50
								else if (interfaces.getTabTrustRequirement()[stoi(input) - 1] == ";" && interfaces.getTrust() < 50)
								{
									// Change Scene
									interfaces.setScene(interfaces.getTabTrustRequirementScene()[stoi(input) - 1]);
								}
								else
								{
									// Change Scene
									interfaces.setScene(interfaces.getTabGoScene()[stoi(input) - 1]);
								}

								// Trust
								string val = interfaces.getTabTrust()[stoi(input) - 1];
								interfaces.trustBar(val);
							}

							// BeepBackground Activate
							if (interfaces.getBeepBackground())
							{
								// Beep Desactivate
								interfaces.setBeepBackground(false);
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