#ifndef TESTENV
#define TESTENV

#include <SmartDG.h>
#include "TRANSFUN.h"

namespace SmartDG_GlobalData
{
	map<string, map<string, SmartDG::DependencyDataPackage> > GlobalPackage;
	map<string, string > GlobalPackageLite;
    	map<string, SmartDG::DependencyDataPackage> GlobalDebug;
   	bool View2ViewFlag = SmartDG_View2ViewFlag_DEFAULT_VALUE;
    	int togglelive = 0;
}

namespace SmartDG_GlobalFunction{

	string i2s(unsigned int i)	{
		string s = ""+std::to_string(i);
		if (i < 10) s = "0" + s;
		return s;
	}

	void EnvironmentGenerator(vector <string> &SmartDependencyObjects,
			map <string, bool> &isMultiSmartDependencyObjects,
			vector <string> &SmartComponents,
			SmartDG__map &TransferFunctions,
			map <string,vector<string>> &InputPorts,
			map <string,vector<string>> &OutputPorts,
			map <string,vector<string>> &InputObjectInstances,
			map <string,vector<string>> &OutputObjectInstances,
			vector <string> &SmartConnectors,
			map <string,string> &Wiki)	{
	cout << "Smart Connectors !!" << endl;
	SmartDependencyObjects.push_back("do");

	SmartComponents.push_back("From");
	for(unsigned int i=0; i<16; i++)	{
		OutputPorts["From"].push_back("Out"+i2s(i));
		OutputObjectInstances["From.Out"+i2s(i)].push_back("do");
	}
	TransferFunctions.emplace("From", &SmartDG::TransferFunctions::TFT);

	SmartComponents.push_back("To");
	for(unsigned int i=0; i<16; i++)	{
		InputPorts["To"].push_back("In"+i2s(i));
		InputObjectInstances["To.In"+i2s(i)].push_back("do");
	}
	TransferFunctions.emplace("To", &SmartDG::TransferFunctions::TFT);

	// Smart Connectors
	//============================================================
	// Connector Profiles
	//============================================================
	//	Service class		Dynamic Host Configuration Protocol(DSCP)
	//	
	//    Network control         CS6
	//    Telephony               EF
	//    Signaling               CS5
	//    Multimedia conferencing AF41, AF42, AF43
	//    Real-time interactive   CS4
	//    Multimedia streaming    AF31, AF32, AF33
	//    Broadcast video         CS3
	//    Low-latency data        AF21, AF22, AF23
	//    OAM                     CS2
	//    High-throughput data    AF11, AF12, AF13
	//    Standard                DF
	//    Low-priority data       CS1
	//	
	//------------------------------------------------------------
	//	QoS Levels
	//					
	//    BestEffore              No guarantees or performance measures.
	//                          Only checks if the file transfer was 
	//                          successful or not.
	//    SoftQoS                 alias: Differentiated service.
	//                          Different priority classes, No absolute guarantees
	//    HardQos                 alias: Guaranteed service.
	//------------------------------------------------------------
	SmartConnectors.push_back("CS06");
	SmartConnectors.push_back("CS05");
	SmartConnectors.push_back("CS04");
	SmartConnectors.push_back("CS03");
	SmartConnectors.push_back("CS02");
	SmartConnectors.push_back("CS01");	
				
	SmartConnectors.push_back("AF41");
	SmartConnectors.push_back("AF42");
	SmartConnectors.push_back("AF43");
	SmartConnectors.push_back("AF31");
	SmartConnectors.push_back("AF32");
	SmartConnectors.push_back("AF33");
	SmartConnectors.push_back("AF21");
	SmartConnectors.push_back("AF22");
	SmartConnectors.push_back("AF23");
	SmartConnectors.push_back("AF11");
	SmartConnectors.push_back("AF12");
	SmartConnectors.push_back("AF13");	
	
	SmartConnectors.push_back("EF");
	SmartConnectors.push_back("DF");
	
	// When none of the above is specified in the model  
	SmartConnectors.push_back("Unnamed");
	}

	void Makedgdatajson(string Location)	{
	// Nothing to do
	}
}

#endif /* TESTENV */
