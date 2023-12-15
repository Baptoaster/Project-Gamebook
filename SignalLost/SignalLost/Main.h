#pragma once

#include "GlobalHeader.h"

class File;

class Interface
{
private:
	bool createLog;
	string pathLog;
	string chapter;
	string chapterTitle;
	string scene;
	size_t start;
	int numberChoices;
	string tabGoChapter[3] = { "", "", "" };
	string tabGoScene[5] = { "", "", "", "", "" };
	string tabTrust[5] = { "", "", "", "", "" };
	string tabTrustNumber[5] = { "", "", "", "", "" };
	string tabTrustRequirement[5] = { "", "", "", "", "" };
	string tabTrustRequirementScene[5] = { "", "", "", "", "" };
	string defaultChoiceScene;
	string defaultChoice;
	bool defaultTrust;
	bool timers;
	bool noBeepSound;
	int time;
	bool beepBackground;
	bool nextChapter;
	bool newChapter;
	int trust;
	bool showMenu;
	bool soundActivated;
	int textFontSize;
	string titleConsole;

public:
	Interface(string chapter, string chapterTitle, string scene, int start, int numberChoices, string defaultChoice, bool defaultTrust, bool timers, int time, bool beepBackground, bool noBeepSound, bool nextChapter, bool newChapter, bool createLog, string pathLog, int trust, bool showMenu, bool soundActivated, int textFontSize);
	bool getCreateLog();
	string getPathLog();
	string getChapter();
	string getChapterTitle();
	string getScene();
	int getNumberChoices();
	const string* getTabGoChapter();
	const string* getTabGoScene();
	const string* getTabTrust();
	const string* getTabTrustNumber();
	const string* getTabTrustRequirement();
	const string* getTabTrustRequirementScene();
	string getDefaultChoiceScene();
	string getDefaultChoice();
	bool getDefaultTrust();
	bool getTimer();
	int getTime();
	bool getBeepBackground();
	bool getNextChapter();
	bool getNewChapter();
	int getTrust();
	bool getShowMenu();
	bool getSoundActivated();
	string getTitleConsole();
	void setCreateLog(bool createLog);
	void setPathLog(string pathLog);
	void setDefaultTrust(bool defaultTrust);
	void setTime();
	void setChapter(string chapter);
	void setChapterTitle(string chapterTitle);
	void setScene(string scene);
	void setBeepBackground(bool beepBackground);
	void setNextChapter(bool nextChapter);
	void setNewChapter(bool newChapter);
	void setTrust(int trust);
	void setShowMenu(bool showMenu);
	void setTitleConsole(string titleConsole);
	void consoleInitialisation();
	bool error(Interface& interfaces, File& file, string path, string pathExe);
	void Menu();
	void posCursor(int posX, int posY);
	void resizeConsole(int width, int height);
	void setConsoleFontSize(int fontSize);
	void setConsoleWindowPosition(int x, int y);
	void displayInterface();
	bool displayText(string content);
	void stopTimer();
	void trustBar(string val);
	bool timer();
	void timerShow();
	void clear();
	void pourcentage();
	void transition();
	void numberZero(int digit, int y);
	void numberOne(int digit, int y);
	void numberTwo(int digit, int y);
	void numberThree(int digit, int y);
	void numberFour(int digit, int y);
	void numberFive(int digit, int y);
	void numberSix(int digit, int y);
	void numberSeven(int digit, int y);
	void numberEight(int digit, int y);
	void numberNine(int digit, int y);
};

class File
{
public:
	static string dateTime();
	static void createFileErrors(Interface& interfaces, string pathExe);
	static string read(Interface& interfaces, string path);
	static void FileLog(string pathExe, string input, Interface& interfaces);
	static string createFileLog(Interface& interfaces, string pathExe, string input, string chapter, string scene);
	static void addFileLog(string pathLog, string input, string chapter, string scene);
	static void readFileError(Interface& interfaces, string pathExe, string name);
};

string UserInput(bool& finish, Interface& interfaces);
void BeepBackground(future<void>& futures, Interface& interfaces);