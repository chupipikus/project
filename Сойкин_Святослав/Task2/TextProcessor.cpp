#include "TextProcessor.h"
#include <locale>
#include <cctype>

// Сформировать частотный словарь слов текста
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName) {
	map<string, double> freqDict;
	
	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение и обработка файла
	int wordsCounter = 0;
	string line;
	while (getline(fs, line)) {
		// не обрабатываем пустую строку
		if (line.empty()) { 
			continue; 
		} // if

		// Построчная обработка: выделение слов, нормализация,
		// подсчет общего количества слов, заполнение словаря
		vector<string> words = splitBySpace(line);
		for (auto &w : words) {
			// нормализация слова к нижнему регистру
			for (auto &ch : w) ch = (char)tolower((unsigned char)ch);
			freqDict[w] += 1.0;
		} // for word

		wordsCounter += (int)words.size();
	} // while

	fs.close();

	// нормирование словаря: поделить в каждой паре количество слов
	// на общее количество слов в тексте
	if (wordsCounter > 0) {
		for (auto &item : freqDict) {
			item.second /= wordsCounter;
		} // for item
	} // if
	
	return freqDict;
} // TextProcessor::makeWordsFrequencyDict


// Сформировать частотный словарь букв текста
map<char, double> TextProcessor::makeLettersFrequencyDict(const string& fileName) {
	map<char, double> freqDict;

	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение всего файла в буфер
	int lettersCounter = 0;
	string line;
	while (getline(fs, line)) {
		// не обрабатываем пустую строку
		if (line.empty()) {
			continue;
		} // if

		// Построчная обработка: подсчет общего количества букв,
		// заполнение словаря (отключение пробелов и знаков пунктуации)
		for (auto ch : line) {
			if (isalpha((unsigned char)ch)) {
				char lc = (char)tolower((unsigned char)ch);
				freqDict[lc] += 1.0;
				lettersCounter++;
			} // if
		} // for ch
	} // while

	fs.close();

	// нормирование словаря: поделить в каждой паре количество букв
	// на общее количество букв в тексте
	if (lettersCounter > 0) {
		for (auto &item : freqDict) {
			item.second /= lettersCounter;
		} // for item
	} // if

	return freqDict;
} // TextProcessor::makeLettersFrequencyDict


// Поменять местами в тексте каждые две соседние строки
void TextProcessor::swapLines(const string& fileName, const string& result) {
	auto text = readLines(fileName);
	
	// Обработка файла, в тексте поменять местами каждые две соседние строки,
	// сохранить измененный текст в файл result
	for (size_t i = 0; i + 1 < text.size(); i += 2) {
		swap(text[i], text[i + 1]);
	} // for i
	
	writeLines(result, text);
} // TextProcessor::swapLines


// Перевести все слова в тексте в формат: первая буква верхнего регистра,
// остальные буквы в нижнем регистре (Это Пример Такого Формата)
void TextProcessor::capitalizeText(const string& fileName, const string& result) {
	auto text = readLines(fileName);
	
	// Обработка файла, в тексте все слова перевести в регистр Capitalize,
	// сохранить измененный текст в файл result
	for (auto &line : text) {
		if (line.empty()) continue;
		
		auto words = splitBySpace(line);
		for (auto &w : words) {
			if (!w.empty()) {
				w[0] = (char)toupper((unsigned char)w[0]);
			} // if
		} // for w
		
		line = join(" ", words);
	} // for line
	
	writeLines(result, text);
} // TextProcessor::capitalizeText


// Упорядочить строки текста по длине
void TextProcessor::orderByLen(const string& fileName, const string& result) {
	auto text = readLines(fileName);
	
	// Сортировка по длине строки
	sort(text.begin(), text.end(), [](const string &a, const string &b) { 
		return a.size() < b.size(); 
	});
	
	writeLines(result, text);
} // TextProcessor::orderByLen


// В каждой строке текста упорядочить слова по алфавиту
void TextProcessor::orderLines(const string& fileName, const string& result) {
	auto text = readLines(fileName);
	
	// Обработка файла, в каждой строке упорядочить слова по алфавиту
	// оставить между словами по одному пробелу
	for (auto &line : text) {
		if (line.empty()) continue;
		
		auto words = splitBySpace(line);
		sort(words.begin(), words.end());
		line = join(" ", words);
	} // for line
	
	writeLines(result, text);
} // TextProcessor::orderLines


// Вспомогательная функция: разбить строку по пробелам
vector<string> TextProcessor::splitBySpace(const string& line) {
	vector<string> tokens;
	string token;
	stringstream ss(line);
	while (ss >> token) {
		tokens.emplace_back(token);
	} // while
	return tokens;
} // TextProcessor::splitBySpace


// Вспомогательная функция: прочитать все строки из файла
vector<string> TextProcessor::readLines(const string& fileName) {
	fstream fs(fileName, ios::in);
	
	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	fs.imbue(locale(".1251"));
	
	vector<string> lines; 
	string line;
	while (getline(fs, line)) {
		lines.emplace_back(line);
	} // while
	
	fs.close();
	return lines;
} // TextProcessor::readLines


// Вспомогательная функция: записать все строки в файл
void TextProcessor::writeLines(const string& fileName, const vector<string>& text) {
	fstream fs(fileName, ios::out);
	
	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для записи").c_str());
	} // if

	fs.imbue(locale(".1251"));
	
	for (auto &l : text) {
		fs << l << '\n';
	} // for l
	
	fs.close();
} // TextProcessor::writeLines


// Вспомогательная функция: объединить вектор строк в одну строку с разделителем
string TextProcessor::join(const string& delimeter, const vector<string> tokens) {
	string out;
	for (size_t i = 0; i < tokens.size(); ++i) {
		out += tokens[i];
		if (i + 1 < tokens.size()) {
			out += delimeter;
		} // if
	} // for i
	return out;
} // TextProcessor::join
