#pragma once
#include "pch.h"


class TextProcessor
{
	// Вспомогательная функция разбить строку по пробелам, возвращает вибор слов для поиска правила
	static vector<string> splitBySpace(const string &line);

	// Чтение строк в вектор
	static vector<string> readLines(const string &fileName);

	// Запись строк в файл
	static void writeLines(const string &fileName, const vector<string> &text);

	// Соединить слова по разделюему с пробелом
	static string join(const string &delimeter, const vector<string> tokens);

public:

	// Формирование частотный словарь
	static map<string, double> makeWordsFrequencyDict(const string &fileName);

	// Формирование частотный словарь букв
	static map<char, double> makeLettersFrequencyDict(const string& fileName);

	// Обработка текста, в тексте поменять местами каждые две соседние строки,
	// сохранить измененный текст в файл result
	static void swapLines(const string &fileName, const string &result);

	// Обработка текста, в тексте все слова переводить в регистр Capitalize,
	// сохранить измененный текст в файл result
	static void capitalizeText(const string& fileName, const string& result);

	// Упорядочить текст по длине строк, сохранить измененный текст в файл result
	static void orderByLen(const string &fileName, const string &result);

	// Упорядочить слова в строках по алфавиту, сохранить измененный текст в файл result
	static void orderLines(const string& fileName, const string &result);
};
