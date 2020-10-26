#include <SmartDG.h>
#include "FriendlyEnvironment.h"

namespace SmartDG	{
namespace SystemProject_TEST{
int Run(string mode, string displaymode){
	string SystemProjectName = "System42";
	cout << "Smart Dependency Graph : SmartDGSystemProject : "<< SystemProjectName << endl;
	vector<SmartDG::DependencyDescriptor> DD;
	DD.push_back(SmartDG::DependencyDescriptor("ConX","DComp1","Out","DObj1","DComp2","In1"));
	DD.push_back(SmartDG::DependencyDescriptor("Unnamed","DComp1","Out","DObj2" ,"DComp2","In2"));
	map<string, SmartDG::GUIPoint> GUI;
	GUI["DComp1"] = SmartDG::GUIPoint("DComp1",10*(SmartDG_TAB/10),10*(SmartDG_TAB/10));
	GUI["DComp2"] = SmartDG::GUIPoint("DComp2",200*(SmartDG_TAB/10),10*(SmartDG_TAB/10));
	map<string, string> CIM; // Component Instance Map
	CIM["DComp1"] = "DComp1";
	CIM["DComp2"] = "DComp2";
	SmartDG::SmartDGGenerator DGG(SystemProjectName,DD,GUI,CIM,mode);
	DGG.Display();
	DGG.Show(displaymode);
	std::thread LiteSyncThread(SmartDG_GlobalFunction::Makedgdatajson, SmartDG_LiteFolderLocation);
	return(Fl::run());
}
} /* namespace SystemProject_TEST */
} /* namespace SmartDG */

int main()	{
	SmartDG::Environment E;
	E.Display();
	cout << "Press any key to continue..." << endl;
	getchar();
	return(SmartDG::SystemProject_TEST::Run(SmartDG_DUAL_MODE, SmartDG_FLTK_DISPLAYMODE));
}

