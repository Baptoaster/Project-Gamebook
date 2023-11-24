#include "main.h"

int main(int argc, char* argv[])
{
	// Initialisation
	locale::global(locale("en_US.utf8"));
	Interface interfaces(1, 1, 1, 1);

	// Path of the file
	File file;
	string path = argv[1];

	// Content of the file
	string content = file.Read(path);

	while (1)
	{
		// Initialisation
		bool succed = false;

		// Show the interface
		interfaces.functionDisplay(content);

		// Input chose
		string input;
		int val;

		while (succed == false && input != "Exit")
		{

			if (interfaces.autos == true)
			{
				interfaces.autos = false;
				break;
			}

			// Input
			input = "";
			cin >> input;

			// Verify integer
			try
			{
				(void)stoi(input);

				if (stoi(input) > 0 && stoi(input) <= interfaces.getNumberChoices())
				{
					// Succed
					succed = true;
					val = stoi(input);
				}
				else
				{
					cout << "Not a option !";
				}
			}
			catch (const logic_error& e)
			{
				succed = false;
			}
		}

		if (succed == true)
		{
			// Get Scene
			val = interfaces.getTabGoScene()[val- 1];

			// Ajout Log
			//file.CreateFileLog(path);

			// Change Scene
			interfaces.setScene(to_string(val));
			system("cls");
		}
	}

	return 0;
}
