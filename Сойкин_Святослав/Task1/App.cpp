#include "pch.h"
#include "Utils.h"
#include "App.h"
#include <locale>

App::App() :App(VectorProcess(), "vector.bin") {} // App::App

App::App(const VectorProcess& vectorProcess, const string& fileName) {
	vectorProcess_ = vectorProcess;
	fileName_ = fileName;
} // App::App


// Выполняет обработку вектора: ввод интервала, сохранение, вычисление статистик и вывод/фильтрацию/сортировку результатов.
void App::doProcess() {
	showNavBarMessage(hintColor, "    Применение алгоритмов для обработки вектора float");

	show("    Вектор для обработки: ");

	// Читает интервал выбора [a,b] от пользователя
	float a, b;
	cout << "\n\n"
		<< "      [a, b]: " << color(infoColor) << setw(30) << " ";
	COORD coord;
	getXY(&coord);
	cin >> pos(coord.X - 29, coord.Y) >> a >> b >> color(mainColor);
	checkInputFormat(cin);

	// Сохраняет текущий вектор в бинарный файл
	vectorProcess_.saveToBinary(fileName_);

	int negatives = vectorProcess_.numberNegatives();
	int notInRanges = vectorProcess_.numberNotInRange(a, b);
	
	// Вычисляет сумму элементов до первого минимального значения
	float sumBeforeMin = vectorProcess_.sumBeforeFirstMin();

	// Вычисляет сумму элементов между первым минимумом и первым максимумом
	float sumBetweenMinMax = vectorProcess_.sumBetweenFirstMinFirstMax();

	cls();
	showNavBarMessage(hintColor, "    Применение алгоритмов для обработки вектора float");

	cout<< pos(4, 4) << "Вектор сохранен в бинарном файле " << fileName_ << "\n\n";
	show("    Вектор для обработки: ", a, b);

	cout<< "\n\n"
		<< "    Отрицательных элементов в векторе                    : " << setw(8) << negatives << "\n"
		<< "    Элементов, не попадающих в интервал [" << a << ", " << b << "]: " << setw(8) << notInRanges << "\n"
		<< "    Сумма элементов до первого минимального              : " << setw(8) << sumBeforeMin << "\n"
		<< "    Сумма элементов между минимальным и максимальным     : " << setw(8) << sumBetweenMinMax 
		<< "\n\n";

	// Выборка в другой вектор отрицательных элементов
	auto selected = vectorProcess_.fihdNegatives();
	cout << "\n    Выборка отрицательных элементов\n";
	show("    Выборка элементов: ", selected);

	// Выбрка в другой вектор элементов, не попадающих в интервал [a, b]
	selected = vectorProcess_.fihdNotInRange(a, b);
	cout<< "\n    Выборка элементов, не попадающих в интервал [" << a << ", " << b << "]\n";
	show("    Выборка элементов: ", selected);

	// Сортировка по убыванию
	vectorProcess_.orderByDesc();
	cout<< "\n    Сортировка элементов по убыванию \n";
	show("    Вектор для обработки: ", a, b);

	// Сортировка по абсолютному значению
	vectorProcess_.orderByAbs();
	cout<< "\n    Сортировка элементов по модулю  \n";
	show("    Вектор для обработки: ", a, b);

	// Перева сортировка: элементы вне [a,b] в конец, сохраняя относительный порядок
	vectorProcess_.orderByNotInRangeLast(a, b);
	cout<< "\n    Перестановка элементов: элементы вне [" 
		<< a << ", " << b << "] в конец вектора  \n";
	show("    Вектор для обработки: ", a, b);

	vectorProcess_.loadFromBinary(fileName_);
	cout<< "\n\n    Восстановление вектора из файла " << fileName_ << "\n\n";
	show("    Вектор для обработки: ", a, b);
} // App::doProcess


// Отображает вектор с подсветкой минимума, максимума и элементов в интервале
void App::show(const string& title, float a, float b, int m, int precision) {
	auto data = vectorProcess_.data();
	float min = *min_element(data.begin(), data.end());
	float max = *max_element(data.begin(), data.end());

	cout << fixed << setprecision(precision) << title;
	int counter = 0;
	
	for(auto item:data) {
		short itemColor;
		
		if (eq(item, min)) {
			itemColor = sumColor;
		} else if (eq(item, max)) {
			itemColor = acctColor;
		} else if (a <= item && item <= b) {
			itemColor = hintColor;
		} else {
			itemColor = mainColor;
		} // if


		cout << color(itemColor) << setw(8) << item << "  " << color(mainColor) << "  ";
		if (++counter % m == 0) {
			cout << "\n" << setw(title.length()) << " ";
		} // if
	}

	// Завершение строки вывода, если последний ряд не полный
	if (counter % m != 0) {
		cout << "\n";
	} // if
} // App::show


void App::show(const string& title, const vector<float>& data, int m, int precision) {
	cout << fixed << setprecision(precision) << title;
	int counter = 0;

	for (auto item : data) {
		cout << setw(8) << item << "    ";
		if (++counter % m == 0) {
			cout << "\n" << setw(title.length()) << " ";
		} // if
	}

	// Завершение строки вывода, если последний ряд не полный
	if (counter % m != 0) {
		cout << "\n";
	} // if
} // App::show