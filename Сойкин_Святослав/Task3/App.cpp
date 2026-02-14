#include "pch.h"
#include "App.h"
#include "TicketFactory.h"
#include "Utils.h"
#include <locale>

App::App():App(TicketFactory::create(1000, getRand(12, 18)), "tickets.bin") {

} // App::App


App::App(const list<Ticket> tickets, const string& fileName) {
	tickets_ = tickets;
	fileName_ = fileName;
} // App::App

//     
void App::show(const string& title) {
	show(title, tickets_);
} // App::show


//      
void App::show(const string& title, list<Ticket>& data) {
	cout << title << "\n" << Ticket::header();

	for (auto ticket: data) {
		cout << "    " << ticket.toTableRow() << "\n";
	} // for ticket

	cout << Ticket::footer();
} // App::show


//      
void App::show(const string& title, vector<Ticket>& data) {
	cout << title << "\n" << Ticket::header();

	for (auto ticket : data) {
		cout << "    " << ticket.toTableRow() << "\n";
	} // for ticket

	cout << Ticket::footer();
} // App::show


//      
void App::save() {
	fstream fs(fileName_, ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App:    " + fileName_ + "  ").c_str());
	} // if

	for (auto datum : tickets_) {
		datum.save(fs);
	} // for datum

	fs.close();
} // App::save


//      (    )
void App::load() {
	fstream fs(fileName_, ios::in | ios::binary);

		if (!fs.is_open()) {
			throw exception((string("App: cannot open ") + fileName_).c_str());
		} // if

		tickets_.clear();
		while (fs.peek() != EOF) {
		Ticket ticket;
		ticket.load(fs);
			if (fs.fail()) break;
			tickets_.emplace_back(ticket);
	} // for fs

	fs.close();
} // App::load


//        
void App::firstLastSwap() {
	fstream fs(fileName_, ios::in | ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App:    " + fileName_ + "  /").c_str());
	} // if

	//   
	Ticket first;
	first.load(fs);

	//       
	fs.seekg(-Ticket::recordLen(), ios::end);
	Ticket last;
	last.load(fs);

	//       ()
	fs.seekp(0, ios::beg);
	last.save(fs);

	//      
	fs.seekp(-Ticket::recordLen(), ios::end);
	first.save(fs);

	fs.close();
} // App::firstLastSwap


//              
void App::earliestLatestSwap() {
	fstream fs(fileName_, ios::in | ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App:    " + fileName_ + "  /").c_str());
	} // if

	//   ,      
	//      "" 
	Ticket earliest;
	earliest.load(fs);
	Ticket latest = earliest;

	int posEarliest = 0, posLatest = 0;

	//     ,   
	//    EOF (End Of File), .. 
	//        
	// 
	for (int i = 1; !fs.eof(); i++, fs.peek()) {
		Ticket ticket;
		ticket.load(fs);
		if (fs.fail()) break;

		if (ticket.departureDate() < earliest.departureDate()) {
			earliest = ticket;
			posEarliest = i;
		}

		if (ticket.departureDate() > latest.departureDate()) {
			latest = ticket;
			posLatest = i;
		}
		++i;
	}

	//       
	fs.clear();

	//       
	fs.seekp(posEarliest*Ticket::recordLen(), ios::beg);
	latest.save(fs);

	fs.seekp(posLatest * Ticket::recordLen(), ios::beg);
	earliest.save(fs);

	fs.close();
} // App::earliestLatestSwap


//      
void App::doGenerate() {
	showNavBarMessage(hintColor, "        ");

	tickets_ = list<Ticket>(getRand(12, 18));
	int id = getRand(1, 9) * 1000;
	generate(tickets_.begin(), tickets_.end(), [&id]() {
		return TicketFactory::create(id++);
	});

	show("        ");
} // App::doGenerate


//     
void App::doShowAll() {
	showNavBarMessage(hintColor, "      ");

	show("       :");
} // App::doShowAll


//  ,   
void App::doAddByFactory() {
	showNavBarMessage(hintColor, "");

	// 
	int idMax = max_element(tickets_.begin(), tickets_.end(), 
		[](const Ticket& t1, const Ticket& t2) { return t1.id() < t2.id(); })->id();
	auto ticket = TicketFactory::create(idMax + 1);
	tickets_.emplace_back(ticket);

	//   
	show("         . "s + to_string(ticket.id()));
} // App::doAddByFactory


//    
void App::doDeleteById() {
	showNavBarMessage(hintColor, "     ");

	show("       :");

	//     
	int id;
	cout<< "\n       : "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	getXY(&position);
	cin >> pos(position.X - 30, position.Y) >> cursor >> id >> nocursor >> color(mainColor);
	checkInputFormat(cin);

	if (id <= 0) {
		throw exception("App.   ");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	//      
	auto it = find_if(tickets_.begin(), tickets_.end(),
		[id](const Ticket& ticket) {
			return ticket.id() == id;
		}
	);
	if (it == tickets_.end()) {
		cout<< color(errColor) << "        . " 
			<< id << "    " << color(mainColor);
		return;
	} // if

	tickets_.erase(it);
	show("         . "s + to_string(id) + ":"s);
} // App::doDeleteById


//      
void App::doFindByFlight() {
	showNavBarMessage(hintColor, "        ");

	show("       :");

	//      
	string flight;
	cout << "\n        : "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getXY(&position);
	cout << pos(position.X - 30, position.Y) << cursor;
	getline(cin, flight);
	cout << nocursor << color(mainColor);

	if (flight.empty()) {
		throw exception("App.       ");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	//      
	vector<Ticket> result;
	copy_if(tickets_.begin(), tickets_.end(), back_inserter(result), [flight](const Ticket& ticket) {
		return ticket.flight() == flight;
	});
	show("       /    '"s + flight + "':"s, result);
} // App::doFindByFlight


//       
void App::doFindbyPax() {
	showNavBarMessage(hintColor, "        ");

	show("       :");

	//        
	string pax;
	cout << "\n          : "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	getXY(&position);
	cout << pos(position.X - 30, position.Y) << cursor;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, pax);
	cout << nocursor << color(mainColor);

	if (pax.empty()) {
		throw exception("App.      ");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	//   
	vector<Ticket> result;
	copy_if(tickets_.begin(), tickets_.end(), back_inserter(result), [pax](const Ticket &ticket) {
		return ticket.pax() == pax;
	});
	show("       /  "s + pax + ":"s, result);
} // App::doFindbyPax


//    
void App::doOrderById() {
	showNavBarMessage(hintColor, "");

	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.id() < t2.id();
	});
	show("       :");
} // App::doOrderById


//      
void App::doOrderByDepartureDate() {
	showNavBarMessage(hintColor, "       ");
	
	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.departureDate() < t2.departureDate();
	});
	show("         :");
} // App::doOrderByDepartureDate


//     
void App::doOrderByDestination() {
	showNavBarMessage(hintColor, "      ");

	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.destination() < t2.destination();
	});
	show("        :");
} // App::doOrderByDestination


//        
void App::doSaveToBinary() {
	showNavBarMessage(hintColor, "         ");
	
	save();
	show("         '" + fileName_ + "':");
} // App::doSaveToBinary


//        
void App::doLoadFrombinary() {
	showNavBarMessage(hintColor, "");

	load();
	show("         '" + fileName_ + "':");
} // App::doLoadFrombinary


//        
void App::doFirstLastSwap() {
	showNavBarMessage(hintColor, "       ");

	//        
	load();
	show("            :");
	firstLastSwap();
	
	//        
	load();
	show("\n\n            :");
} // App::doFirstLastSwap


//         
void App::doEarliestLatestSwap() {
	showNavBarMessage(hintColor, "          ");

	//      
	load();
	show("              :");
	
	//   
	earliestLatestSwap();

	//        
	load();
	show("\n\n              :");
} // App::doEarliestLatestSwap
#pragma endregion
