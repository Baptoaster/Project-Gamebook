#include "Main.h"

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

	// Wait 50 Milliseconds
	Sleep(50);

	// Beep Activate
	if (interfaces.getBeepBackground() && interfaces.getSoundActivated())
	{
		// Beep
		Beep(700, 300);

		// Beep
		Beep(700, 300);

		// Beep
		Beep(700, 300);

		// Wait 200 Milliseconds
		while (interfaces.getBeepBackground() && futures.wait_for(chrono::milliseconds(200)) == future_status::timeout)
		{
			// Wait 2 Seconds
			if (interfaces.getBeepBackground() && val >= 10)
			{
				val = 0;

				if (interfaces.getBeepBackground())
				{
					Beep(700, 300);
				}

				if (interfaces.getBeepBackground())
				{
					Beep(700, 300);
				}

				if (interfaces.getBeepBackground())
				{
					Beep(700, 300);
				}
			}

			val += 1;
		}
	}
}