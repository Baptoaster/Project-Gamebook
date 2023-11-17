#include "main.h"

int main(int argc, char* argv[])
{
	// Initialisation
	int start = 0;
	int scene = 1;

	// Path of the file
	File file;
	string path = argv[1];

	// Content of the file
	string content = file.GetFile(path);

	while (1)
	{
		// Initialisation
		bool succed = false;

		// Show the interface
		start = functionDisplay(content, start, scene);

		// Input chose
		string Temp;

		while (succed == false && Temp != "Exit")
		{
			// Input
			Temp = "";
			cin >> Temp;

			// Verify integer
			try
			{
				(void)stoi(Temp);
				scene = stoi(Temp);
				succed = true;
			}
			catch (const logic_error& e)
			{
				succed = false;
			}
		}

		if (succed == true)
		{
			system("cls");
		}
	}

	return 0;
}
