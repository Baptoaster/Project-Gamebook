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
#include <cctype>

using namespace std;
using namespace chrono;
using namespace this_thread;


class File;

class Interface
{
private:
	bool createLog;
	string pathLog;
	string chapter;
	string scene;
	size_t start;
	int numberChoices;
	string tabGoChapter[3] = { "0", "0", "0" };
	string tabGoScene[5] = { "0", "0", "0", "0", "0" };
	string tabTrust[5] = { "0", "0", "0", "0", "0" };
	string defaultChoiceScene;
	string defaultChoice;
	bool timers;
	int time;
	bool beepBackground;
	bool nextChapter;
	int trust;

public:
	Interface(string chapter, string scene, int start, int numberChoices, string defaultChoice, bool timers, int time, bool beepBackground, bool nextChapter, bool createLog, string pathLog, int trust);
	bool getCreateLog();
	string getPathLog();
	string getChapter();
	string getScene();
	int getNumberChoices();
	const string* getTabGoChapter();
	const string* getTabGoScene();
	const string* getTabTrust();
	string getDefaultChoiceScene();
	string getDefaultChoice();
	bool getTimer();
	int getTime();
	bool getBeepBackground();
	bool getNextChapter();
	void setCreateLog(bool createLog);
	void setPathLog(string pathLog);
	void setTime();
	void setChapter(string chapter);
	void setScene(string scene);
	void setBeepBackground(bool beepBackground);
	void setNextChapter(bool nexChapter);
	void setTrust(int trust);
	void consoleInitialisation();
	bool error(Interface& interfaces, File& file, string path, string pathExe);
	COORD getPosCursor();
	void posCursor(int posX, int posY);
	void resizeConsole(int width, int height);
	void setConsoleFontSize(int fontSize);
	void setConsoleWindowPosition(int x, int y);
	void displayInterface();
	bool displayText(string content);
	void stopTimer();
	void trustBar(string val);
	bool timer();
	void clear();
};

class File
{
public:
	static string dateTime();
	static void createFileErrors(string pathExe);
	static string read(Interface& interfaces, string path);
	static void FileLog(string pathExe, string input, Interface& interfaces);
	static string createFileLog(string pathExe, string input, string chapter, string scene);
	static void addFileLog(string pathLog, string input, string chapter, string scene);
	static void readFileError(string pathExe, string name);
};

string UserInput(bool& finish, Interface& interfaces);
void BeepBackground(future<void>& futures, Interface& interfaces);