#pragma once

// Для избежания проблем, связанные с функциями, включая sprintf()
#define _CRT_SECURE_NO_WARNINGS

#ifdef _MSC_VER
#include <corecrt_math_defines.h>
#include <Windows.h>
#include <conio.h>
#endif

#include <iostream>
#include <iomanip>
#include <sstream>   // для работы с ostringstream
#include <fstream>   // для операций файловой ввода/вывода

#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <locale>

using namespace std;
