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

string File::GetFile(string path)
{
	// Read the file
	string content = File::Read(path);

	return content;
}

int functionDisplay(string content, int start, int scene)
{
	// Console color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Speed of the scrolling
	int speedLetters = 50000000;

	// Set in table of caracter the content
	char* caracter = const_cast<char*>(content.c_str());

	int index;

	//cout << start - 8 + content.find("Scene " + scene);

	if (start > 0)
	{
		index = start - 8 + content.find("+");
	}
	else
	{
		index = start + content.find("+");
	}

	for (int i = start; i < index; i++)
	{
		if (caracter[i] == '}' || caracter[i] == ']' || caracter[i] == '>' || caracter[i] == '&')
		{
			cout << endl;
			cout << endl;
		}
		else if (caracter[i] == '[' || caracter[i] == '{' || caracter[i] == '<' || caracter[i] == '~' || caracter[i] == '_')
		{
			cout << endl;
		}
		else if (caracter[i] == '*')
		{
			// Set color of console to green
			SetConsoleTextAttribute(hConsole, 2);
		}
		else if (caracter[i] == '=')
		{
			// Set color of console to white
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (caracter[i] == '+')
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
	return start;
}

/* TEMP
	int index = content.find("{");
	int index2 = content.find("}");

	cout << content.substr(index+1,index2-index-1) << endl;

	int index3 = content.find("[");
	int index4 = content.find("]");

	cout << content.substr(index3 + 1, index4 - index3 - 1) << endl;

	int index5 = content.find("<");
	int index6 = content.find(">");

	cout << content.substr(index5 + 1, index6 - index5 - 1) << endl;

	int index7 = content.find("~");
	int index8 = content.find("&");

	cout << content.substr(index7 + 1, index8 - index7 - 1) << endl;

	int index9 = content.find("~");
	int index10 = content.find("&");

	cout << content.substr(index9 + 1, index10 - index9 - 1) << endl;
	*/