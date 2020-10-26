#ifndef FRIENDLYENVIRONMENT
#define FRIENDLYENVIRONMENT

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
		cout << "Friendly Environment !!" << endl;
		// Dependency Objects
		SmartDependencyObjects.push_back("DObj1");	Wiki["DObj1"] = "Wiki entry is optional";
		SmartDependencyObjects.push_back("DObj2");
		isMultiSmartDependencyObjects["DObj2"] 	    = true;	// Multiple instances of DObj2 are possible at a port
		
		// Dependency Component
		SmartComponents.push_back("DComp1");	
		Wiki["DComp1"] = "Dependency Component 1";
		// Input Port(s)
		InputPorts["DComp1"].push_back("In");
			// Dependency Objects handled at this input port	
			InputObjectInstances["DComp1.In"].push_back("DObj1");
			InputObjectInstances["DComp1.In"].push_back("DObj2");
		// Output Port(s)
		OutputPorts["DComp1"].push_back("Out");
			// Dependency Objects handled at this output port	
			OutputObjectInstances["DComp1.Out"].push_back("DObj1");
			OutputObjectInstances["DComp1.Out"].push_back("DObj2");
		// Attaching Transfer function to Dependency Component
		TransferFunctions.emplace("DComp1", &SmartDG::TransferFunctions::TFT);

		// Dependency Component
		SmartComponents.push_back("DComp2");	
		Wiki["DComp2"] = "Dependency Component 2";
		// Input Port(s)
		InputPorts["DComp2"].push_back("In1");
			// Dependency Objects handled at this input port	
			InputObjectInstances["DComp2.In1"].push_back("DObj1");
		InputPorts["DComp2"].push_back("In2");
			// Dependency Objects handled at this input port	
			InputObjectInstances["DComp2.In2"].push_back("DObj2");
		// Attaching Transfer function to Dependency Component
		TransferFunctions.emplace("DComp2", &SmartDG::TransferFunctions::TFT);

		// Smart Connectors
		SmartConnectors.push_back("ConX");
		SmartConnectors.push_back("ConY");
		SmartConnectors.push_back("Unnamed");
	}

	void Makedgdatajson(string Location)	{
	// Nothing to do
	}
}

#endif /* FRIENDLYENVIRONMENT */
