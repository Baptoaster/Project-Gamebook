#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <locale>

using namespace std::chrono;
using namespace std::this_thread;
using namespace std;

class File
{
public:
	static void CreateFileLog(string path);
	static string Read(string path);
};

class Interface
{
private:
	int chapter;
	string scene;
	int start;
	int numberChoices;
	int tabGoScene[5] = { 0, 0, 0, 0, 0 };

public:
	bool autos;
	Interface(int chapter, int scene, int start, int numberChoices);
	int getNumberChoices();
	const int* getTabGoScene();
	void setScene(string scene);
	void functionDisplay(string content);
	void InterfaceShow();
	void Timer(int val);
};
