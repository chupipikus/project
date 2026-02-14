#pragma once

// ��� ������������� ������, ������������ �������, �������� sprintf()
#define _CRT_SECURE_NO_WARNINGS

#ifdef _MSC_VER
#include <corecrt_math_defines.h>
#include <Windows.h>
#include <conio.h>
#endif

#include <iostream>
#include <iomanip>
#include <sstream>   // ��� ������� ostringstream
#include <fstream>   // ��� �������� ������� �����/������

#include <vector>
#include <algorithm>
#include <numeric>

#include <locale> // ���� �� �������� � �����������
#include <map>    // for freq dict
#include <list>

using namespace std;

// ���������� ������������� ��������� - ������� �������� (UTF-8)
constexpr auto CODE_PAGE = 1251;