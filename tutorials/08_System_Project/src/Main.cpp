#include <SmartDG.h>
#include "TESTENV.h"

namespace SmartDG	{
namespace ComponentDevelopmentMode_TEST{
int Run(string mode, string displaymode){
	cout << "Smart Dependency Graph "<< "DGTest" << endl;
	SmartDG::SmartDGGenerator DGG("DGTest", mode);
	DGG.Display();
	DGG.Show(displaymode);
	return(Fl::run());
}
} /* namespace ComponentDevelopmentMode_TEST */
namespace SystemProject_TEST{
int Run(string mode, string displaymode){
	string SystemProjectName = "SystemAlpha";
	cout << "Smart Dependency Graph : SmartDGSystemProject : "<< SystemProjectName << endl;
	vector<SmartDG::DependencyDescriptor> DD;
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestA1","DGTestOut","alpha","DGTestC1","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("AF42","DGTestA1","DGTestOut","beta" ,"DGTestC1","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestA1","DGTestOut","alpha","DGTestB","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("AF42","DGTestB","DGTestOut","beta" ,"DGTestC1","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestA2","DGTestOut","alpha","DGTestC2","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("AF42","DGTestA2","DGTestOut","beta" ,"DGTestC2","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestA2","DGTestOut","beta","DGTestB","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("AF42","DGTestB","DGTestOut","alpha" ,"DGTestC2","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestA1","DGTestOut","alpha","DGTestD","DGTestIn"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","DGTestD","DGTestOut","alpha","DGTestC1","DGTestIn"));
	map<string, SmartDG::GUIPoint> GUI;
	GUI["DGTestA1"] = SmartDG::GUIPoint("DGTestA1",10*(SmartDG_TAB/10),10*(SmartDG_TAB/10));
	GUI["DGTestA2"] = SmartDG::GUIPoint("DGTestA2",10*(SmartDG_TAB/10),100*(SmartDG_TAB/10));
	GUI["DGTestB"] = SmartDG::GUIPoint("DGTestB",100*(SmartDG_TAB/10),50*(SmartDG_TAB/10));
	GUI["DGTestC1"] = SmartDG::GUIPoint("DGTestC1",200*(SmartDG_TAB/10),10*(SmartDG_TAB/10));
	GUI["DGTestC2"] = SmartDG::GUIPoint("DGTestC2",200*(SmartDG_TAB/10),100*(SmartDG_TAB/10));
	GUI["DGTestD"] = SmartDG::GUIPoint("DGTestD",100*(SmartDG_TAB/10),120*(SmartDG_TAB/10));
	map<string, string> CIM; // Component Instance Map
	CIM["DGTestA1"] = "DGTestA";
	CIM["DGTestA2"] = "DGTestA";
	CIM["DGTestB"]  = "DGTestB";
	CIM["DGTestC1"] = "DGTestC";
	CIM["DGTestC2"] = "DGTestC";
	CIM["DGTestD"]  = "DGTestD";
	SmartDG::SmartDGGenerator DGG(SystemProjectName,DD,GUI,CIM,mode);
	DGG.Display();
	DGG.Show(displaymode);
	std::thread LiteSyncThread(SmartDG_GlobalFunction::Makedgdatajson, SmartDG_LiteFolderLocation);
	return(Fl::run());
}
} /* namespace SystemProject_TEST */
} /* namespace SmartDG */

int main()	{
	bool run_test_componentproject = false;
	bool run_test_objectmode_systemproject    	 = false;
	bool run_test_componentmode_systemproject    	 = false;
	bool run_test_dualmode_systemproject    	 = true;

	string displaymode = SmartDG_FLTK_DISPLAYMODE;
	//string displaymode = SmartDG_LITE_DISPLAYMODE;
	//string displaymode = SmartDG_DUAL_DISPLAYMODE;

	if(run_test_componentproject)	{
		// ComponentDevelopment Project
		string mode(SmartDG_COMPONENT_DEVELOPER_MODE);
		return(SmartDG::ComponentDevelopmentMode_TEST::Run(mode, displaymode));
	}
	if(run_test_objectmode_systemproject || run_test_componentmode_systemproject || run_test_dualmode_systemproject)	{
		// System Project
		string mode = "";
		if(run_test_objectmode_systemproject) 	 mode = SmartDG_OBJECT_MODE;
		if(run_test_componentmode_systemproject) mode = SmartDG_COMPONENT_MODE;
		if(run_test_dualmode_systemproject) 	 mode = SmartDG_DUAL_MODE;

		return(SmartDG::SystemProject_TEST::Run(mode, displaymode));
	}
	return 1;
}

