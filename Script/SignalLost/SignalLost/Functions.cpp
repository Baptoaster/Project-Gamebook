#include "main.h"

string File::Read(string path)
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
		content += contentLine.c_str();
	}

	// Close the file
	infile.close();

	return content;
}

void File::CreateFileLog(string path)
{
	string paths = path;

	int find = paths.find("Chapitre");

	paths = paths.substr(0, find);

	paths += "Log.text";
	
	cout << paths;
}

Interface::Interface(int chapter, int scene, int start, int numberChoices)
{
	this->chapter = chapter;
	this->scene = scene;
	this->start = start;
	this->numberChoices = numberChoices;
}

int Interface::getNumberChoices()
{
	return this->numberChoices;
}

const int* Interface::getTabGoScene()
{
	return this->tabGoScene;
}

void Interface::setScene(string scene)
{
	this->scene = "[Scene " + scene;
}

void Interface::functionDisplay(string content)
{
	// Console color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Speed of the scrolling
	int speedLetters = 40000000;

	// Set in table of caracter the content
	char* caracter = const_cast<char*>(content.c_str());

	// Initialisation
	int index = 0;
	int indexTab[5];
	int indexScene = 0;
	int numberChoice = 1;
	bool skip = false;
	string defaultChoice = "";

	if (start > 1)
	{
		// After
		start = content.find(scene, start);
		index = content.find("]", start);
	}
	else
	{
		index = content.find("]");
	}

	for (int i = start; i < index; i++)
	{
		if (caracter[i] == '_')
		{
			caracter[i] = NULL;
			cout << endl;
		}
		else if (caracter[i] == '%')
		{
			caracter[i] = NULL;
			// Set color of console to green
			SetConsoleTextAttribute(hConsole, 2);
		}
		else if (caracter[i] == '&')
		{
			caracter[i] = NULL;
			// Set color of console to red
			SetConsoleTextAttribute(hConsole, 4);
		}
		else if (caracter[i] == '=')
		{
			caracter[i] = NULL;
			// Set color of console to white
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (caracter[i] == '[' || caracter[i] == ']' || caracter[i] == '>' || caracter[i] == ')' || skip == true)
		{
			caracter[i] = NULL;
			skip = false;
		}
		else if (caracter[i] == '+')
		{
			Sleep(600);
		}
		else if(caracter[i] == '(')
		{
			string sceneNumber = content.substr(i + 1, 1);
			
			string sceneNumber2 = content.substr(i + 2, 1);

			if (sceneNumber2 != ")")
			{
				sceneNumber += sceneNumber2;
			}

			indexTab[indexScene] = stoi(sceneNumber);

			indexScene += 1;
			skip = true;
		}
		else if (caracter[i] == '<')
		{
			caracter[i] = NULL;
			numberChoice += 1;
		}
		else if (caracter[i] == '^')
		{
			defaultChoice = content.substr(i + 2, 1);

			string sceneNumber2 = content.substr(i + 3, 1);

			if (sceneNumber2 != ")")
			{
				defaultChoice += sceneNumber2;
			}

			caracter[i] = NULL;
		}
		else if (caracter[i] == '$')
		{
			caracter[i] = NULL;
		}
		else
		{
			cout << caracter[i];
		}

		// Wait
		sleep_for(nanoseconds(speedLetters));
	}

	start = index;
	numberChoices = numberChoice;

	for (int i = 0; i < indexScene; i++)
	{
		tabGoScene[i] = indexTab[i];
	}
	
	if (defaultChoice != "")
	{
		int val = stoi(defaultChoice);
		//Timer(val);
	}

}

void Interface::InterfaceShow()
{
	cout << chapter << " " << scene << " " << start << " " << numberChoices << endl;

	for (int i = 0; i < sizeof(tabGoScene) / sizeof(tabGoScene[0]); i++)
	{
		cout << tabGoScene[i] << endl;
	}
}

void Interface::Timer(int val)
{
	int timer = 10;

	thread timerThread([&]()
	{
		while (timer > 0)
		{
			cout << timer << endl;

			//Sleep(1000);
			this_thread::sleep_for(chrono::seconds(1));
			timer--;

		}
		if (timer <= 0)
		{
			autos = true;

			setScene(to_string(val));

			system("cls");
		}
	});

	// Input chose
	bool succed = false;
	string input;
	int valS;

	while (succed == false && input != "Exit")
	{

		if (autos == true)
		{
			autos = false;
			break;
		}

		// Input
		input = "";
		cin >> input;

		// Verify integer
		try
		{
			(void)stoi(input);

			if (stoi(input) > 0 && stoi(input) <= getNumberChoices())
			{
				// Succed
				succed = true;
				valS = stoi(input);
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
		valS = getTabGoScene()[valS - 1];

		// Ajout Log
		//file.CreateFileLog(path);

		// Change Scene
		setScene(to_string(valS));
		system("cls");
	}

	timerThread.join();
}