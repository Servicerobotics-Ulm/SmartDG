////////////////////////////////////////////////////////////////////////////////
///	\file	SmartDGGenerator.cpp
/// \brief	Source file for SmartDGGenerator class
/// \author Vineet Nagrath
/// \date	July 2, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#include "SmartDG.h"

namespace SmartDG {

void SmartDGGenerator::SystemDevelopmentMode(string &SystemProjectName,
		vector<DependencyDescriptor> &DD, map<string, GUIPoint> &GUI,
		map<string, string> CIM) {
	// Environment Consistency Check
	setexit = 1;
	for (unsigned int i = 0; i < DD.size(); i++) {
		// Smart Connector
		if (!VFind<string>(XE.SmartConnectors, DD[i].DependencyName)) {
			ErrorExit<string>(DD[i].DependencyName, "SmartConnector");
			continue;
		}
		// Smart Components
		if (!VFind<string>(XE.SmartComponents,
				CIM[DD[i].FromDependencyNodeName])) {
			ErrorExit<string>(DD[i].FromDependencyNodeName, "SmartComponent");
			continue;
		}
		if (!VFind<string>(XE.SmartComponents,
				CIM[DD[i].ToDependencyNodeName])) {
			ErrorExit<string>(DD[i].ToDependencyNodeName, "SmartComponent");
			continue;
		}
		// Ports
		if (!VFind<string>(XE.OutputPorts[CIM[DD[i].FromDependencyNodeName]],
				DD[i].FromDependencyPortName)) {
			ErrorExit<string>(DD[i].FromDependencyPortName,
					DD[i].FromDependencyNodeName
							+ " Does Not Contain OutputPort");
			continue;
		}
		if (!VFind<string>(XE.InputPorts[CIM[DD[i].ToDependencyNodeName]],
				DD[i].ToDependencyPortName)) {
			ErrorExit<string>(DD[i].ToDependencyPortName,
					DD[i].ToDependencyNodeName + " Does Not Contain InputPort");
			continue;
		}
		// Smart Dependency Object
		if (!VFind<string>(XE.SmartDependencyObjects,
				DD[i].DependencyObjectName)) {
			ErrorExit<string>(DD[i].DependencyObjectName,
					"SmartDependencyObjects");
			continue;
		}
		// Smart Dependency Object Instance
		string tmp1 = CIM[DD[i].FromDependencyNodeName] + "."
				+ DD[i].FromDependencyPortName;
		if (!VFind<string>(XE.OutputObjectInstances[tmp1],
				DD[i].DependencyObjectName)) {
			ErrorExit<string>(DD[i].DependencyObjectName,
					tmp1 + " Does Not Contain Instance For Dependency Object");
			continue;
		}
		string tmp2 = CIM[DD[i].ToDependencyNodeName] + "."
				+ DD[i].ToDependencyPortName;
		if (!VFind<string>(XE.InputObjectInstances[tmp2],
				DD[i].DependencyObjectName)) {
			ErrorExit<string>(DD[i].DependencyObjectName,
					tmp2 + " Does Not Contain Instance For Dependency Object");
			continue;
		}
	}
	if (setexit == 0)
		exit(0);
	for (unsigned int i = 0; i < DD.size(); i++) {
		SystemViews[DD[i].DependencyObjectName] = DD[i].DependencyObjectName;
		SystemNodes[DD[i].FromDependencyNodeName] =
				DD[i].FromDependencyNodeName;
		SystemNodesCIMDisplayStrings[DD[i].FromDependencyNodeName] =
				DD[i].FromDependencyNodeName + "["
						+ CIM[DD[i].FromDependencyNodeName] + "]";
		SystemNodes[DD[i].ToDependencyNodeName] = DD[i].ToDependencyNodeName;
		SystemNodesCIMDisplayStrings[DD[i].ToDependencyNodeName] =
				DD[i].ToDependencyNodeName + "["
						+ CIM[DD[i].ToDependencyNodeName] + "]";
		SystemConnectors[DD[i].DependencyName] = DD[i].DependencyName;
	}
	for (map<string, string>::const_iterator it = SystemViews.begin();
			it != SystemViews.end(); ++it) {
		DependencyObjects[it->second] = new DependencyObject(it->second);
		if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_DUAL_MODE))
			DependencyMonitors[it->second] = new DependencyMonitor(
					SystemProjectName + " Monitor", SystemProjectName,
					it->second, SmartDG_OBJECT_MODE);
	}
	for (map<string, string>::const_iterator it = SystemNodes.begin();
			it != SystemNodes.end(); ++it) {
		if ((Mode == SmartDG_COMPONENT_MODE) || (Mode == SmartDG_DUAL_MODE))
			ComponentMonitors[it->second] = new DependencyMonitor(
					SystemProjectName + " Monitor", SystemProjectName,
					it->second, SmartDG_COMPONENT_MODE);
	}
	DependencyGraph DGtmp;
	for (map<string, string>::const_iterator it = SystemNodes.begin();
			it != SystemNodes.end(); ++it) {
		DependencyNode tmpnode(it->second);
		tmpnode.x = GUI[it->second].x;
		tmpnode.y = GUI[it->second].y;
		string nodecim = CIM[it->second];
		tmpnode.isInstanceOf = nodecim;
		for (unsigned int i = 0; i < XE.InputPorts[nodecim].size(); i++) {
			string portkeyname = nodecim + "." + XE.InputPorts[nodecim][i];
			DependencyPort tmpport(XE.InputPorts[nodecim][i]);
			for (unsigned int j = 0;
					j < XE.InputObjectInstances[portkeyname].size(); j++)
				tmpport.DO.push_back(
						*DependencyObjects[XE.InputObjectInstances[portkeyname][j]]);
			tmpnode.DP_In.push_back(tmpport);
		}
		for (unsigned int i = 0; i < XE.OutputPorts[nodecim].size(); i++) {
			string portkeyname = nodecim + "." + XE.OutputPorts[nodecim][i];
			DependencyPort tmpport(XE.OutputPorts[nodecim][i]);
			for (unsigned int j = 0;
					j < XE.OutputObjectInstances[portkeyname].size(); j++)
				tmpport.DO.push_back(
						*DependencyObjects[XE.OutputObjectInstances[portkeyname][j]]);
			tmpnode.DP_Out.push_back(tmpport);
		}
		tmpnode.Generate_DP();
		DGtmp.DN.push_back(tmpnode);
	}
	DGtmp.Generate_URLs();
	for (unsigned int i = 0; i < DD.size(); i++) {
		string n1 = DD[i].FromDependencyNodeName;
		string p1 = DD[i].FromDependencyPortName;
		string o = DD[i].DependencyObjectName;
		string n2 = DD[i].ToDependencyNodeName;
		string p2 = DD[i].ToDependencyPortName;
		URL fromurl = DGtmp.ulm[n1]["Out"][p1][o];
		URL tourl = DGtmp.ulm[n2]["In"][p2][o];
		Dependency tmpdep(DD[i].DependencyName, fromurl, tourl);
		DGtmp.AddDependency(tmpdep);
	}
	for (map<string, string>::const_iterator it = SystemViews.begin();
			it != SystemViews.end(); ++it) {
		for (unsigned int i = 0; i < DGtmp.DN.size(); i++) {
			DGtmp.DN[i].TFT = XE.TransferFunctions[CIM[DGtmp.DN[i].Name]];
		}
	}
	if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_DUAL_MODE))
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it)
			DependencyMonitors[it->second]->DG = DGtmp;
	if ((Mode == SmartDG_COMPONENT_MODE) || (Mode == SmartDG_DUAL_MODE))
		for (map<string, string>::const_iterator it = SystemNodes.begin();
				it != SystemNodes.end(); ++it)
			ComponentMonitors[it->second]->DG = DGtmp;
}

void SmartDGGenerator::ComponentDevelopmentMode() {
	// Environment Consistency Check
	setexit = 1;
	// Component Under Development
	if (!VFind<string>(XE.SmartComponents, ComponentName))
		ErrorExit<string>(ComponentName, "SmartComponent Under Development");
	if (!VFind<string>(XE.SmartComponents, XE.god(0)))
		ErrorExit<string>(XE.god(0), "SmartComponent Under Development");
	if (!VFind<string>(XE.SmartComponents, XE.god(1)))
		ErrorExit<string>(XE.god(1), "SmartComponent Under Development");
	if (setexit == 0)
		exit(0);

	for (unsigned int i = 0; i < XE.InputPorts[ComponentName].size(); i++) {
		string cn = ComponentName;
		string ipn = XE.InputPorts[cn][i];
		for (unsigned int j = 0;
				j < XE.InputObjectInstances[cn + "." + ipn].size(); j++) {
			string ipni = XE.InputObjectInstances[cn + "." + ipn][j];
			if (XE.isMultiSmartDependencyObjects[ipni]) {
				DD.push_back(
						DependencyDescriptor(XE.godstr, XE.god(2), XE.god(2),
								ipni, cn, ipn));
				DD.push_back(
						DependencyDescriptor(XE.godstr, XE.god(3), XE.god(3),
								ipni, cn, ipn));
				DD.push_back(
						DependencyDescriptor(XE.godstr, XE.god(4), XE.god(4),
								ipni, cn, ipn));
			} else
				DD.push_back(
						DependencyDescriptor(XE.godstr, XE.god(0), XE.god(0),
								ipni, cn, ipn));
		}
	}
	for (unsigned int i = 0; i < XE.OutputPorts[ComponentName].size(); i++) {
		string cn = ComponentName;
		string opn = XE.OutputPorts[cn][i];
		for (unsigned int j = 0;
				j < XE.OutputObjectInstances[cn + "." + opn].size(); j++) {
			string opni = XE.OutputObjectInstances[cn + "." + opn][j];
			if (XE.isMultiSmartDependencyObjects[opni]) {
				DD.push_back(
						DependencyDescriptor(XE.godstr, cn, opn, opni,
								XE.god(5), XE.god(5)));
				DD.push_back(
						DependencyDescriptor(XE.godstr, cn, opn, opni,
								XE.god(6), XE.god(6)));
				DD.push_back(
						DependencyDescriptor(XE.godstr, cn, opn, opni,
								XE.god(7), XE.god(7)));
			} else
				DD.push_back(
						DependencyDescriptor(XE.godstr, cn, opn, opni,
								XE.god(1), XE.god(1)));
		}
	}
	for (unsigned int i = 0; i < DD.size(); i++) {
		SystemViews[DD[i].DependencyObjectName] = DD[i].DependencyObjectName;
		SystemNodes[DD[i].FromDependencyNodeName] =
				DD[i].FromDependencyNodeName;
		SystemNodes[DD[i].ToDependencyNodeName] = DD[i].ToDependencyNodeName;
		SystemConnectors[DD[i].DependencyName] = DD[i].DependencyName;
	}
	for (map<string, string>::const_iterator it = SystemViews.begin();
			it != SystemViews.end(); ++it) {
		DependencyObjects[it->second] = new DependencyObject(it->second);
	}
	ComponentDeveloper = new DependencyMonitor("Component Development",
			"Component Development", ComponentName,
			SmartDG_COMPONENT_DEVELOPER_MODE);
	DependencyGraph DGtmp;
	for (map<string, string>::const_iterator it = SystemNodes.begin();
			it != SystemNodes.end(); ++it) {
		DependencyNode tmpnode(it->second);
		tmpnode.isInstanceOf = it->second;
		for (unsigned int i = 0; i < XE.InputPorts[it->second].size(); i++) {
			string portkeyname = it->second + "."
					+ XE.InputPorts[it->second][i];
			DependencyPort tmpport(XE.InputPorts[it->second][i]);
			for (unsigned int j = 0;
					j < XE.InputObjectInstances[portkeyname].size(); j++)
				if (DependencyObjects[XE.InputObjectInstances[portkeyname][j]])
					tmpport.DO.push_back(
							*DependencyObjects[XE.InputObjectInstances[portkeyname][j]]);
			tmpnode.DP_In.push_back(tmpport);
		}
		for (unsigned int i = 0; i < XE.OutputPorts[it->second].size(); i++) {
			string portkeyname = it->second + "."
					+ XE.OutputPorts[it->second][i];
			DependencyPort tmpport(XE.OutputPorts[it->second][i]);
			for (unsigned int j = 0;
					j < XE.OutputObjectInstances[portkeyname].size(); j++)
				if (DependencyObjects[XE.OutputObjectInstances[portkeyname][j]])
					tmpport.DO.push_back(
							*DependencyObjects[XE.OutputObjectInstances[portkeyname][j]]);
			tmpnode.DP_Out.push_back(tmpport);
		}
		tmpnode.Generate_DP();
		DGtmp.DN.push_back(tmpnode);
	}
	DGtmp.Generate_URLs();
	for (unsigned int i = 0; i < DD.size(); i++) {
		string n1 = DD[i].FromDependencyNodeName;
		string p1 = DD[i].FromDependencyPortName;
		string o = DD[i].DependencyObjectName;
		string n2 = DD[i].ToDependencyNodeName;
		string p2 = DD[i].ToDependencyPortName;
		URL fromurl = DGtmp.ulm[n1]["Out"][p1][o];
		URL tourl = DGtmp.ulm[n2]["In"][p2][o];
		Dependency tmpdep(DD[i].DependencyName, fromurl, tourl);
		DGtmp.AddDependency(tmpdep);
	}
	for (map<string, string>::const_iterator it = SystemViews.begin();
			it != SystemViews.end(); ++it) {
		for (unsigned int i = 0; i < DGtmp.DN.size(); i++) {
			DGtmp.DN[i].TFT = XE.TransferFunctions[DGtmp.DN[i].Name];
		}
	}
	ComponentDeveloper->DG = DGtmp;
}

template<typename T>
bool SmartDGGenerator::VFind(const vector<T> & V, const T & E) {
	auto it = find(V.begin(), V.end(), E);
	if (it == V.end())
		return false;
	return true;
}

template<typename T>
void SmartDGGenerator::ErrorExit(const T Item, string Message) {
	cout << "ERROR[NOT FOUND IN ENVIRONMENT]: " << Message << " <"
			<< string(Item) << ">" << endl;
	setexit = 0;
}

SmartDGGenerator::SmartDGGenerator(string SystemProjectName,
		vector<DependencyDescriptor> DD, map<string, GUIPoint> GUI,
		map<string, string> CIM, string mode) {
	Mode = mode;
	if (Mode == SmartDG_OBJECT_MODE) {
		SystemDevelopmentMode(SystemProjectName, DD, GUI, CIM);
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it)
			DependencyMonitors[it->second]->Init();
	}
	if (Mode == SmartDG_COMPONENT_MODE) {
		SystemDevelopmentMode(SystemProjectName, DD, GUI, CIM);
		for (map<string, string>::const_iterator it = SystemNodes.begin();
				it != SystemNodes.end(); ++it)
			ComponentMonitors[it->second]->InitComponent();
	}
	if (Mode == SmartDG_DUAL_MODE) {
		SystemDevelopmentMode(SystemProjectName, DD, GUI, CIM);
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it)
			DependencyMonitors[it->second]->Init();
		for (map<string, string>::const_iterator it = SystemNodes.begin();
				it != SystemNodes.end(); ++it)
			ComponentMonitors[it->second]->InitComponent();
	}
}

SmartDGGenerator::SmartDGGenerator(string componentName, string mode) {
	Mode = mode;
	if (Mode == SmartDG_COMPONENT_DEVELOPER_MODE) {
		ComponentName = componentName;
		ComponentDevelopmentMode();
		ComponentDeveloper->InitComponent();
	}
}

void SmartDGGenerator::Show(string displaymode) {
	if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_DUAL_MODE))
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it)
			DependencyMonitors[it->second]->Show(displaymode);
	if ((Mode == SmartDG_COMPONENT_MODE) || (Mode == SmartDG_DUAL_MODE))
		for (map<string, string>::const_iterator it = SystemNodes.begin();
				it != SystemNodes.end(); ++it)
			ComponentMonitors[it->second]->Show(displaymode);
	if (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)
		ComponentDeveloper->Show(displaymode);
}

void SmartDGGenerator::Display(bool showwiki) {

	if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_DUAL_MODE)) {
		cout
				<< "----------------------------Current System----SmartDependencyObjects"
				<< endl;
		XE.Display(SystemViews, 1, showwiki);
		cout << "----------------------------Current System----SmartComponents"
				<< endl;
		XE.Display(SystemNodes, 1, showwiki);
		cout
				<< "----------------------------Current System----SmartComponentsCIMs"
				<< endl;
		XE.Display(SystemNodesCIMDisplayStrings, 2, false);
		cout << "----------------------------Current System----SmartConnectors"
				<< endl;
		XE.Display(SystemConnectors, 1, showwiki);
		cout << "----------------------------Current System----Dependencies"
				<< endl;
	}
	if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_DUAL_MODE)) {
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it) {
			cout << "----------------------------View " << it->second << endl;
			DependencyMonitors[it->second]->DG.DisplayDependencyMini(
					it->second);
		}
	}
	if ((Mode == SmartDG_OBJECT_MODE) || (Mode == SmartDG_DUAL_MODE)) {
		cout << "----------------------------Current System----ObjectViews"
				<< endl;
		for (map<string, string>::const_iterator it = SystemViews.begin();
				it != SystemViews.end(); ++it)
			cout << "----------------------------ObjectView " << it->first
					<< endl;
	}
	if ((Mode == SmartDG_COMPONENT_MODE) || (Mode == SmartDG_DUAL_MODE)) {
		cout << "----------------------------Current System----ComponentViews"
				<< endl;
		for (map<string, string>::const_iterator it = SystemNodes.begin();
				it != SystemNodes.end(); ++it)
			cout << "----------------------------ComponentView " << it->first
					<< endl;
	}
	if (Mode == SmartDG_COMPONENT_DEVELOPER_MODE) {
		cout
				<< "----------------------------COMPONENT DEVELOPER MODE for Component: "
				<< ComponentName << endl;
		cout
				<< "----------------------------COMPONENT DEVELOPER MODE----Dependencies"
				<< endl;
		for (unsigned int i = 0; i < DD.size(); i++)
			DD[i].Display();
	}
}
SmartDGGenerator::~SmartDGGenerator() {
}

} /* namespace SmartDG */
