#pragma once
#include "pch.h"

// Обработка текстовых файлов: частотный анализ и трансформация текста
class TextProcessor {

public:
	// Вспомогательный метод: разбить строку по пробелам
	static vector<string> splitBySpace(const string& line);
	
	// Формирование частотного словаря слов (слово -> частота)
	static map<string, double> makeWordsFrequencyDict(const string& fileName);
	
	// Формирование частотного словаря букв (буква -> частота)
	static map<char, double> makeLettersFrequencyDict(const string& fileName);

	// Обработка: поменять местами каждые две соседние строки
	static void swapLines(const string& fileName, const string& result);

	// Обработка: привести первые буквы слов к верхнему регистру
	static void capitalizeText(const string& fileName, const string& result);

	// Обработка: упорядочить строки по длине
	static void orderByLen(const string& fileName, const string& result);

	// Обработка: упорядочить слова в каждой строке
	static void orderLines(const string& fileName, const string& result);

private:
	// Вспомогательные функции
	static vector<string> readLines(const string& fileName);
	static void writeLines(const string& fileName, const vector<string>& lines);
};