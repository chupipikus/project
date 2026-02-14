#include "App.h"
#include "Utils.h"
#include <locale>

App::App() :App("test.txt") {}
App::App(const string& fileName) {
	fileName_ = fileName;
} // App::App

// Построить и показать частотный словарь слов из файла
void App::doFreqDictWords() {
	showNavBarMessage(hintColor, "    Формирование частотного словаря слов текста");

	// Отобразить исходный текст для анализа
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Построить частотный словарь слов
	map<string, double> freqDict = TextProcessor::makeWordsFrequencyDict(fileName_);

	// Показать результаты
	show("\n\n    Частотный словарь слов текста, файл " + fileName_ + ":", freqDict);
} // App::doFreqDictWords


// Построить и показать частотный словарь букв из файла
void App::doFreqDictLetters() {
	showNavBarMessage(hintColor, "    Формирование частотного словаря букв текста");

	// Отобразить исходный текст для анализа
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Построить частотный словарь букв
	map<char, double> freqDict = TextProcessor::makeLettersFrequencyDict(fileName_);

	// Показать результаты
	show("\n\n    Частотный словарь букв текста, файл " + fileName_ + ":", freqDict);
} // App::doFreqDictLetters


// Поменять местами строки в файле и показать результат
void App::doSwapLines() {
	showNavBarMessage(hintColor, "    Поменять местами в тексте каждые две соседние строки");

	// Показать исходный файл
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Создать файл с переставленными строками
	string result = "swap.txt";
	TextProcessor::swapLines(fileName_, result);

	// Показать результат
	viewText("Файл " + result + ", в тексте каждые две соседние строки поменяли местами:", result);
} // App::doSwapLines


// Привести первые буквы слов к верхнему регистру и показать результат
void App::doWordsCapitalize() {
	showNavBarMessage(hintColor, "    Все слова текста перевести в регистр Capitalize, запись в файл");

	// Показать исходный файл
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Записать результат в новый файл
	string result = "capitalize.txt";
	TextProcessor::capitalizeText(fileName_, result);

	// Показать результат
	viewText("Файл " + result + ", в тексте каждые две соседние строки поменяли местами:", result);
} // App::doWordsCapitalize


// Упорядочить слова по длине и показать результат (orderByLen.txt)
void App::doOrderByLen() {
	showNavBarMessage(hintColor, "    Упорядочить строки текста по длине");

	// Показать исходный файл
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Создать файл с упорядоченными по длине словами
	string result = "orderByLen.txt";
	TextProcessor::orderByLen(fileName_, result);

	// Показать результат
	viewText("Файл " + result + ", строки упорядочены по длине:", result);
} // App::doOrderByLen


// Упорядочить слова в каждой строке и показать результат (orderlines.txt)
void App::doOrderWordsInLines() {
	showNavBarMessage(hintColor, "    Упорядочить слова в каждой строке текста");

	// Показать исходный файл
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Сохранить результат в файл
	string result = "orderlines.txt";
	TextProcessor::orderLines(fileName_, result);

	// Показать результат
	viewText("Файл " + result + ", слова в каждой строке упорядочены:", result);
} // App::doOrderWordsInLines


// -------------------------------------------------------

void App::viewText(const string & title, const string &fileName) {
	cout<< "    " << title << "\n"
		<< "    +" << setfill('-') << setw(92) << "-" << "+" 
		<< setfill(' ') << "\n";

	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("App: cannot open " + fileName + " for reading").c_str());
	} // if

	// Читать файл в кодировке CP1251 и выводить строки
	fs.imbue(locale(".1251"));

	int row = 1;
	string line;
	while (getline(fs, line)) {
		cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
			<< " | " << left << setw(90) << line << right << " |\n";
	}

	fs.close();
	cout<< "     +" << setfill('-') << setw(92) << "-" << "+"
		<< setfill(' ') << "\n";
} // App::viewText


void App::viewText(const string& title) {
	viewText(title, fileName_);
} // App::viewText


void App::show(const string& title, const map<string, double>& freqDict) {
	cout << "    " << title << "\n" << setprecision(3);
	
	int counter = 1;
	double r = 0;
	for (auto &item: freqDict) {
		cout<< "    " << left << setw(20) << item.first << right
			<< setw(5) << item.second << " || ";

		if (counter++ % 3 == 0) {
			cout << "\n";
		} // if

		r += item.second;
	} // for item 

	cout << "\n    Сумма : " << r << "\n\n";
} // App::show 


void App::show(const string& title, const map<char, double>& freqDict) {
	cout << "    " << title << "\n" << setprecision(3);

	int counter = 1;
	double r = 0;
	for (auto& item : freqDict) {
		// Вывести одиночный символ (если несколько символов, выводить как есть)
		cout << "    " << string(1, item.first) << "  "
			<< setw(5) << item.second << " || ";

		if (counter++ % 5 == 0) cout << "\n";
		r += item.second;
	}

	cout << "\n    Сумма : " << r << "\n\n";
} // App::show 
