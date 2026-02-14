#include "Payers.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>  // for runtime_error
#include <locale>

// вспомогательная функция проверки формата при чтении из файла
void checkInputFormat(istringstream& iss) {
	if (iss.fail()) throw runtime_error("CSV: Ошибка чтения");
} // checkInputFormat


// конструктор - инициализация коллекции набором из 15 плательщиков 
Payers::Payers() {
	for (int i = 0; i < 15; ++i) {
		list_.push_back(Payer::createFactory(nextId_++));
	} // for i
} // Payers::Payers


// добавить нового плательщика в список
void Payers::addPayer() {
	list_.push_back(Payer::createFactory(nextId_++));
} // Payers::addPayer


// удалить плательщика из списка по идентификатору
void Payers::deleteById(int id) {
	list_.remove_if([id](const Payer& p) { return p.getId() == id; });
} // Payers::deleteById


// отбор плательщиков по тарифу
list<Payer> Payers::selectByTariff(double tariff) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[tariff](const Payer& p) {
			return eq(p.getTariff(), tariff);
		}
	);
	
	return result;
} // Payers::selectByTariff


// отбор плательщиков по скидке
list<Payer> Payers::selectByDiscount(int discount) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[discount](const Payer& p) {
			return p.getDiscount() == discount;
		}
	);
	
	return result;
} // Payers::selectByDiscount


// отбор плательщиков по диапазону суммы платежа с сортировкой по номеру телефона
list<Payer> Payers::selectBySumRange(double low, double high) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[low, high](const Payer& p) {
			double sum = p.calculateSum();
			return sum >= low && sum <= high;
		}
	);
	
	// сортировка по номеру телефона
	result.sort([](const Payer& a, const Payer& b) { 
		return a.getPhone() < b.getPhone(); 
	});
	
} // Payers::selectBySumRange


// отбор плательщиков по номеру телефона
list<Payer> Payers::selectByPhone(const string& phone) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[&phone](const Payer& p) {
			return p.getPhone() == phone;
		}
	);
	
	return result;
} // Payers::selectByPhone


// отбор плательщиков по фамилии и инициалам
list<Payer> Payers::selectByName(const string& name) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[&name](const Payer& p) {
			return p.getName() == name;
		}
	);
	
	return result;
} // Payers::selectByName


// отбор плательщиков по дате платежа
list<Payer> Payers::selectByDate(const Date& date) const {
	list<Payer> result;
	
	copy_if(list_.begin(), list_.end(), back_inserter(result), 
		[&date](const Payer& p) {
			return p.getDate() == date;
		}
	);
	
	return result;
} // Payers::selectByDate


// вычисление полной стоимости платежей всего списка плательщиков
double Payers::totalPayments() const {
	double sum = 0.0;
	
	for (const auto& p : list_) {
		sum += p.calculateSum();
	} // for p
	
	return sum;
} // Payers::totalPayments


// сортировка списка плательщиков по номеру телефона
void Payers::sortByPhone() {
	list_.sort([](const Payer& a, const Payer& b) { 
		return a.getPhone() < b.getPhone(); 
	});
} // Payers::sortByPhone


// сортировка списка плательщиков по убыванию продолжительности разговоров
void Payers::sortByTimeDescending() {
	list_.sort([](const Payer& a, const Payer& b) { 
		return a.getTimeMin() > b.getTimeMin(); 
	});
} // Payers::sortByTimeDescending


// сортировка списка плательщиков по идентификатору плательщика
void Payers::sortById() {
	list_.sort([](const Payer& a, const Payer& b) { 
		return a.getId() < b.getId(); 
	});
} // Payers::sortById


// сортировка списка плательщиков по фамилии и инициалам
void Payers::sortByName() {
	list_.sort([](const Payer& a, const Payer& b) { 
		return a.getName() < b.getName(); 
	});
} // Payers::sortByName


// сортировка списка плательщиков по убыванию суммы к оплате
void Payers::sortBySumDescending() {
	list_.sort([](const Payer& a, const Payer& b) { 
		return a.calculateSum() > b.calculateSum(); 
	});
} // Payers::sortBySumDescending


// изменение плательщика по идентификатору (все поля кроме идентификатора)
void Payers::changePayer(int id) {
	for (auto& p : list_) {
		if (p.getId() == id) {
			p = Payer::createFactory(id);
			return;
		} // if
	} // for p
	
	throw runtime_error("Payer: Не найден плательщик с указанным идентификатором.");
} // Payers::changePayer


// запись коллекции плательщиков в CSV файл
void Payers::saveToCSV(const string& fname) const {
	ofstream out(fname);
	out.imbue(locale(".1251"));
	
	if (!out.is_open()) {
		throw runtime_error(("CSV: Ошибка открытия файла для записи : " + fname).c_str());
	} // if

	// Запись заголовка CSV файла с описанием колонок
	out << "ID,Имя,Телефон,Тариф,Скидка,Время,День,Месяц,Год\n";
	
	// Запись данных плательщиков
	for (const auto& p : list_) {
		out << p.getId() << "," << p.getName() << "," << p.getPhone() << "," 
			<< p.getTariff() << "," << p.getDiscount()
			<< "," << p.getTimeMin() << "," << p.getDate().getDay() << "," 
			<< p.getDate().getMonth() << "," << p.getDate().getYear() << "\n";
	} // for p
} // Payers::saveToCSV


// чтение коллекции плательщиков из CSV файла
void Payers::loadFromCSV(const string& fname) {
	if (fname.empty()) {
		throw runtime_error("CSV: Пустое имя файла.");
	} // if

	ifstream in(fname);
	in.imbue(locale(".1251"));
	
	if (!in.is_open()) {
		throw runtime_error(("CSV: Ошибка открытия файла для чтения " + fname).c_str());
	} // if

	// Чтение заголовка файла
	string line;
	if (!getline(in, line)) {
		throw runtime_error("CSV: Ошибка чтения заголовка файла.");
	} // if

	// Проверка что первое поле - это ID
	{
		istringstream iss(line);
		string token;
		if (!getline(iss, token, ',')) {
			throw runtime_error("CSV: Ошибка чтения первого поля.");
		} // if
		if (token != "ID") {
			throw runtime_error("CSV: Некорректный формат заголовка (первое поле должно быть ID).");
		} // if
	}

	// Очистка текущей коллекции и чтение данных из файла
	list_.clear();
	while (getline(in, line)) {
		if (line.empty()) {
			continue;
		} // if
		
		istringstream iss(line);
		Payer p;
		int id, discount, timeMin, d, m, y;
		double tariff;
		string name, phone;

		// Чтение и проверка формата каждого поля
		iss >> id;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля ID).");
		} // if
		
		getline(iss, name, ',');
		getline(iss, phone, ',');
		
		iss >> tariff;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля тариф).");
		} // if
		
		iss >> discount;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля скидка).");
		} // if
		
		iss >> timeMin;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля время).");
		} // if
		
		iss >> d;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля день).");
		} // if
		
		iss >> m;
		checkInputFormat(iss);
		if (iss.get() != ',') {
			throw runtime_error("CSV: Ошибка чтения (после поля месяц).");
		} // if
		
		iss >> y;
		checkInputFormat(iss);

		// Установка значений и добавление в коллекцию
		p.setId(id);
		p.setName(name);
		p.setPhone(phone);
		p.setTariff(tariff);
		p.setDiscount(discount);
		p.setTimeMin(timeMin);
		p.setDate(d, m, y);

		list_.push_back(p);
		nextId_ = max(nextId_, p.getId() + 1);
	} // while

	// Проверка что коллекция не пустая после загрузки
	if (list_.empty()) {
		throw runtime_error("CSV: Коллекция должна быть непустая.");
	} // if
} // Payers::loadFromCSV
}