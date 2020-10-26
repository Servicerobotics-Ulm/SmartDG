#include <SmartDG.h>
#include "TESTENV.h"

namespace SmartDG	{
namespace SystemProject_TEST{
int Run(string mode, string displaymode){
	string SystemProjectName = "Smart_Connectors";
	cout << "Smart Dependency Graph : SmartDGSystemProject : "<< SystemProjectName << endl;
	vector<SmartDG::DependencyDescriptor> DD;
	DD.push_back(SmartDG::DependencyDescriptor("CS06","From","Out00","do","To","In00"));
	DD.push_back(SmartDG::DependencyDescriptor("CS05","From","Out01","do","To","In01"));
	DD.push_back(SmartDG::DependencyDescriptor("CS04","From","Out02","do","To","In02"));
	DD.push_back(SmartDG::DependencyDescriptor("CS03","From","Out03","do","To","In03"));
	DD.push_back(SmartDG::DependencyDescriptor("CS02","From","Out04","do","To","In04"));
	DD.push_back(SmartDG::DependencyDescriptor("CS01","From","Out05","do","To","In05"));

	DD.push_back(SmartDG::DependencyDescriptor("AF41","From","Out06","do","To","In06"));
	DD.push_back(SmartDG::DependencyDescriptor("AF42","From","Out07","do","To","In07"));
	DD.push_back(SmartDG::DependencyDescriptor("AF43","From","Out08","do","To","In08"));
	DD.push_back(SmartDG::DependencyDescriptor("AF31","From","Out09","do","To","In09"));
	DD.push_back(SmartDG::DependencyDescriptor("AF32","From","Out10","do","To","In10"));
	DD.push_back(SmartDG::DependencyDescriptor("AF33","From","Out11","do","To","In11"));
	DD.push_back(SmartDG::DependencyDescriptor("AF21","From","Out12","do","To","In12"));
	DD.push_back(SmartDG::DependencyDescriptor("EF","From","Out13","do","To","In13"));
	DD.push_back(SmartDG::DependencyDescriptor("DF","From","Out14","do","To","In14"));
	DD.push_back(SmartDG::DependencyDescriptor("Unnamed","From","Out15","do","To","In15"));

	map<string, SmartDG::GUIPoint> GUI;
	GUI["From"] = SmartDG::GUIPoint("DGTestA1",10*(SmartDG_TAB/10),20*(SmartDG_TAB/10));
	GUI["To"]   = SmartDG::GUIPoint("DGTestA2",200*(SmartDG_TAB/10),20*(SmartDG_TAB/10));
	map<string, string> CIM; // Component Instance Map
	CIM["From"] = "From";
	CIM["To"]   = "To";
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
	return(SmartDG::SystemProject_TEST::Run(SmartDG_OBJECT_MODE, SmartDG_FLTK_DISPLAYMODE));
	return 1;
}

