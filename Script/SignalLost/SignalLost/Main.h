#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>


using namespace std::chrono;
using namespace std::this_thread;
using namespace std;

class File
{
public:
	static string GetFile(string path);
	static string Read(string path);
};

int functionDisplay(string content, int start, int scene);
