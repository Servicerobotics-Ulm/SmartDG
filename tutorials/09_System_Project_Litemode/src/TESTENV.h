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
		cout << "Possibilities are Endless in Life!!" << endl;
	SmartDependencyObjects.push_back("alpha");	Wiki["alpha"] = "Demo object alpha";
	SmartDependencyObjects.push_back("beta");	Wiki["beta"]  = "Demo object beta";
	SmartDependencyObjects.push_back("gamma");
	SmartDependencyObjects.push_back("hooah");

	isMultiSmartDependencyObjects["alpha"] 	    = true;	Wiki["alpha"] = "[Multi] " + Wiki["alpha"];
	isMultiSmartDependencyObjects["hooah"] 	    = true;	Wiki["hooah"] = "[Multi] " + Wiki["hooah"];

	SmartComponents.push_back("DGTest");	Wiki["DGTest"] = "Demo Component";
		InputPorts["DGTest"].push_back("DGTestIn");
			InputObjectInstances["DGTest.DGTestIn"].push_back("alpha");
			InputObjectInstances["DGTest.DGTestIn"].push_back("beta");
		OutputPorts["DGTest"].push_back("DGTestOut");
			OutputObjectInstances["DGTest.DGTestOut"].push_back("gamma");
			OutputObjectInstances["DGTest.DGTestOut"].push_back("hooah");
	TransferFunctions.emplace("DGTest", &SmartDG::TransferFunctions::TFT);

	SmartComponents.push_back("DGTestA");	Wiki["DGTestA"] = "Demo Component A";
		OutputPorts["DGTestA"].push_back("DGTestOut");
			OutputObjectInstances["DGTestA.DGTestOut"].push_back("alpha");
			OutputObjectInstances["DGTestA.DGTestOut"].push_back("beta");
	TransferFunctions.emplace("DGTestA", &SmartDG::TransferFunctions::TFT);

	SmartComponents.push_back("DGTestB");	Wiki["DGTestB"] = "Demo Component B";
		InputPorts["DGTestB"].push_back("DGTestIn");
			InputObjectInstances["DGTestB.DGTestIn"].push_back("alpha");
			InputObjectInstances["DGTestB.DGTestIn"].push_back("beta");
		OutputPorts["DGTestB"].push_back("DGTestOut");
			OutputObjectInstances["DGTestB.DGTestOut"].push_back("alpha");
			OutputObjectInstances["DGTestB.DGTestOut"].push_back("beta");
	TransferFunctions.emplace("DGTestB", &SmartDG::TransferFunctions::TFT);

	SmartComponents.push_back("DGTestC");	Wiki["DGTestC"] = "Demo Component C";
		InputPorts["DGTestC"].push_back("DGTestIn");
			InputObjectInstances["DGTestC.DGTestIn"].push_back("alpha");
			InputObjectInstances["DGTestC.DGTestIn"].push_back("beta");
	TransferFunctions.emplace("DGTestC", &SmartDG::TransferFunctions::TFT);

	SmartComponents.push_back("DGTestD");	Wiki["DGTestD"] = "Demo Component D";
		InputPorts["DGTestD"].push_back("DGTestIn");
			InputObjectInstances["DGTestD.DGTestIn"].push_back("alpha");
			InputObjectInstances["DGTestD.DGTestIn"].push_back("beta");
		OutputPorts["DGTestD"].push_back("DGTestOut");
			OutputObjectInstances["DGTestD.DGTestOut"].push_back("alpha");
			OutputObjectInstances["DGTestD.DGTestOut"].push_back("beta");
	TransferFunctions.emplace("DGTestD", &SmartDG::TransferFunctions::TFT);
	// Smart Connectors
	SmartConnectors.push_back("CS05");
	SmartConnectors.push_back("AF42");
	SmartConnectors.push_back("Unnamed");
	}

	void Makedgdatajson(string Location)	{
		string DGliteDir1 = Location+"/"+string(SmartDG_LiteFoldername);
		string DGliteDir2 = "~/."+string(SmartDG_LiteFoldername);
		std::system(string("mkdir -p "+DGliteDir1).c_str());
		std::system(string("mkdir -p "+DGliteDir2).c_str());

		ofstream LaunchServer;	LaunchServer.open (DGliteDir1+"/LaunchServer.sh",ios::trunc);
		LaunchServer << SmartDG_Lite_Server_Launch_COMMAND << endl;	LaunchServer.close();
		std::system(string("cp "+string(DGliteDir1+"/LaunchServer.sh ")+DGliteDir2).c_str());

		string DGliteJSONFile = string(DGliteDir1+"/"+SmartDG_BaseLite+".json");
		while(true){
			if(SmartDG_SyncLiteVerbose)	cout << "Makedgdatajson " << SmartDG_GlobalData::togglelive << endl;
			ofstream jsonfile;
			jsonfile.open (DGliteJSONFile);
			if ( ! jsonfile ) if(SmartDG_SyncLiteVerbose) cout << DGliteJSONFile << "  " << "Error ! Open\n" << strerror(errno) << endl;
			jsonfile << "var dgdata = [" << endl;
			jsonfile << "{\"id\":\""<<"#BLINKY"<<"\",\"val\":\""<<to_string(SmartDG_GlobalData::togglelive)<<"\"}," << endl;
			SmartDG_GlobalData::togglelive++;
			if(SmartDG_GlobalData::togglelive == 11) SmartDG_GlobalData::togglelive = 0;
			for(map <string,string> ::const_iterator it =
					SmartDG_GlobalData::GlobalPackageLite.begin();
					it != SmartDG_GlobalData::GlobalPackageLite.end(); ++it)	{
				jsonfile << "{\"id\":\""<<it->first<<"\",\"val\":\""<<it->second<<"\"}," << endl;
			}
			jsonfile << "]" << endl;
			jsonfile.close();
			if ( ! jsonfile ) if(SmartDG_SyncLiteVerbose) cout << DGliteJSONFile << "  " << "Error ! Close\n" << strerror(errno) << endl;
			std::system(string("cp "+DGliteJSONFile+" "+DGliteDir2).c_str());
			std::this_thread::sleep_for(std::chrono::milliseconds(SmartDG_SLEEP_BETWEEN_SYNLITE));
		}
	}
}

#endif /* TESTENV */
