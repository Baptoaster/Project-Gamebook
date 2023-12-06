#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include <locale>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>

using namespace std;
using namespace chrono;
using namespace this_thread;

class File
{
public:
	static string dateTime();
	static string read(string path);
	static string createFileLog(string path, string val, int chapter, string scene);
	static void addFileLog(string pathLog, string val, int chapter, string scene);
	static void createFileErrors(string path);
	static void readFileError(string path, string name);
};

class Interface
{
private:
	int chapter;
	string scene;
	int start;
	int numberChoices;
	int tabGoScene[5] = { 0, 0, 0, 0, 0 };
	int value;
	string defaultChoice;
	bool timers;
	int time;

public:
	bool beepBackground;
	Interface(int chapter, string scene, int start, int numberChoices);
	COORD getPosCursor();
	void posCursor(int posX, int posY);
	void resizeConsole(int width, int height);
	void setConsoleFontSize(int fontSize);
	void setConsoleWindowPosition(int x, int y);
	int getChapter();
	string getScene();
	int getNumberChoices();
	const int* getTabGoScene();
	int getValue();
	string getDefaultChoice();
	bool getTimer();
	int getTime();
	void setTime();
	void setScene(string scene);
	void show();
	void functionDisplay(string content);
	void stopTimer();
	bool timer();
	void clear();
};

string getUserInput(bool& vals, Interface& interfaces);
void test(future<void>& futures, bool& test);