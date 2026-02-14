#pragma once
#include "pch.h"
#include "Ticket.h"

class App
{
	//      
	list<Ticket> tickets_;

	//        
	//    
	string fileName_;

	//      
	void save();

	//      
	void load();

	//      
	void firstLastSwap();

	//       
	void earliestLatestSwap();

	//     
	void show(const string &title);

	//     
	void show(const string& title, list<Ticket> &data);
	void show(const string& title, vector<Ticket> &data);

public:
	App();
	App(const list<Ticket> tickets, const string &fileName);

    //      
    void doGenerate();

   //     
   void doShowAll();

   //  ,   
   void doAddByFactory();

   //    
   void doDeleteById();

   //      
   void doFindByFlight();

   //       
   void doFindbyPax();

   //    
   void doOrderById();

   //      
   void doOrderByDepartureDate();

   //     
   void doOrderByDestination();

   //        
   void doSaveToBinary();

   //        
   void doLoadFrombinary();

   //        
   void doFirstLastSwap();

   //         
   void doEarliestLatestSwap();
};

