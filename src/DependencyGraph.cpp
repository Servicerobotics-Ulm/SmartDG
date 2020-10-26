////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyGraph.cpp
/// \brief	Source file for DependencyGraph class
/// \author Vineet Nagrath
/// \date	June 2, 2020
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

DependencyGraph::DependencyGraph() {
	// Sets Default Name
	Name = "NA_DG";
}

DependencyGraph::DependencyGraph(string GraphName) {
	// Sets Name to GraphName
	Name = GraphName;
}

void DependencyGraph::Generate_URLs() {
	// For all DependencyNode objects in DN
	for (unsigned int i = 0; i < DN.size(); i++) {
		// For Input and Output ports of DependencyNode
		for (unsigned int j = 0; j < DN[i].DP.size(); j++) {
			// For all DependencyPort objects in Input or Output port
			for (unsigned int k = 0; k < DN[i].DP[j].size(); k++) {
				// For all DependencyObject objects in DependencyPort
				for (unsigned int l = 0; l < DN[i].DP[j][k].DO.size(); l++) {
					// Generating URL for DependencyObject
					DN[i].DP[j][k].DO[l].url = URL(i, j, k, l);
					// Sets URL objects for all Input DependencyPort DependencyObject objects
					if (j == 0) {
						// Setting strn, strio, strp, stro and str for URL
						DN[i].DP[j][k].DO[l].url.strn = DN[i].Name;
						DN[i].DP[j][k].DO[l].url.strio = "In";
						DN[i].DP[j][k].DO[l].url.strp = DN[i].DP[j][k].Name;
						DN[i].DP[j][k].DO[l].url.stro =
								DN[i].DP[j][k].DO[l].Name;
						DN[i].DP[j][k].DO[l].url.str = DN[i].Name + ".In."
								+ DN[i].DP[j][k].Name + "."
								+ DN[i].DP[j][k].DO[l].Name;
						// Fills ulm (URL list map) for all DependencyObject URLs
						ulm[DN[i].Name]["In"][DN[i].DP[j][k].Name][DN[i].DP[j][k].DO[l].Name] =
								DN[i].DP[j][k].DO[l].url;
						// Fills ulmi (URL list map integer) for all DependencyObject URLs
						ulmi[i][0][k][l] = DN[i].DP[j][k].DO[l].url;
					}
					// Sets URL objects for all Output DependencyPort DependencyObject objects
					else {
						// Setting strn, strio, strp, stro and str for URL
						DN[i].DP[j][k].DO[l].url.strn = DN[i].Name;
						DN[i].DP[j][k].DO[l].url.strio = "Out";
						DN[i].DP[j][k].DO[l].url.strp = DN[i].DP[j][k].Name;
						DN[i].DP[j][k].DO[l].url.stro =
								DN[i].DP[j][k].DO[l].Name;
						DN[i].DP[j][k].DO[l].url.str = DN[i].Name + ".Out."
								+ DN[i].DP[j][k].Name + "."
								+ DN[i].DP[j][k].DO[l].Name;
						// Fills ulm (URL list map) for all DependencyObject URLs
						ulm[DN[i].Name]["Out"][DN[i].DP[j][k].Name][DN[i].DP[j][k].DO[l].Name] =
								DN[i].DP[j][k].DO[l].url;
						// Fills ulmi (URL list map integer) for all DependencyObject URLs
						ulmi[i][1][k][l] = DN[i].DP[j][k].DO[l].url;
					}
				}
			}
		}
	}
}

void DependencyGraph::AddDependency(string name, string fni, string fpi,
		string foi, string tni, string tpi, string toi) {
	// Makes a Dependency object tmp
	Dependency tmp(name, ulm[fni]["Out"][fpi][foi], ulm[tni]["In"][tpi][toi]);
	// Calls AddDependency(Dependency &tmp)
	AddDependency(tmp);
}

void DependencyGraph::AddDependency(string name, DependencyNode fn,
		DependencyPort fp, DependencyObject ob, DependencyNode tn,
		DependencyPort tp) {
	// Makes a Dependency object tmp
	Dependency tmp(name, ulm[fn.Name]["Out"][fp.Name][ob.Name],
			ulm[tn.Name]["In"][tp.Name][ob.Name]);
	// Calls AddDependency(Dependency &tmp)
	AddDependency(tmp);
}

void DependencyGraph::AddDependency(Dependency &tmp) {
	// Finds DependencyObject object's Name and sets obName to it
	string obName =
			DN[tmp.From.NodeIndex].DP[tmp.From.InOutIndex][tmp.From.PortIndex].DO[tmp.From.ObjectIndex].Name;
	// Adds a new udi entry (Dependency Object's Unique Dependency Instance) in Source Node and sets its default value
	DN[tmp.From.NodeIndex].DP[tmp.From.InOutIndex][tmp.From.PortIndex].DO[tmp.From.ObjectIndex].udi[tmp.To.str] =
			DN[tmp.From.NodeIndex].DP[tmp.From.InOutIndex][tmp.From.PortIndex].DO[tmp.From.ObjectIndex].defaultdata;
	// Adds a new udi entry (Dependency Object's Unique Dependency Instance) in Target Node and sets its default value
	DN[tmp.To.NodeIndex].DP[tmp.To.InOutIndex][tmp.To.PortIndex].DO[tmp.To.ObjectIndex].udi[tmp.From.str] =
			DN[tmp.To.NodeIndex].DP[tmp.To.InOutIndex][tmp.To.PortIndex].DO[tmp.To.ObjectIndex].defaultdata;
	// Add DependencyObject object to dobjs if not already present in View
	if (View.find(obName) == View.end())
		dobjs.push_back(obName);
	// Add the new Dependency object to DOI (DependencyObjectInstances object to encapsulate all dependency object instances)
	DOI.Add(tmp);
	// Add the new Dependency object to View (A string map from DependencyObject object's Name to a vector of corresponding Dependency objects)
	View[obName].push_back(tmp);
}

void DependencyGraph::Display() {
	// Calls DependencyNode::Display function for each DependencyNode in DN
	for (unsigned int i = 0; i < DN.size(); i++)
		DN[i].Display();
}

void DependencyGraph::Display_URLs() {
	// Calls DependencyNode::Display_URLs function for each DependencyNode in DN
	for (unsigned int i = 0; i < DN.size(); i++) {
		DN[i].Display_URLs();
	}
}

void DependencyGraph::Display_ulm() {
	// Displays the complete ulm (URL list map)
	for (unsigned int i = 0; i < DN.size(); i++) {
		for (unsigned int j = 0; j < DN[i].DP.size(); j++) {
			for (unsigned int k = 0; k < DN[i].DP[j].size(); k++) {
				for (unsigned int l = 0; l < DN[i].DP[j][k].DO.size(); l++) {
					DN[i].DP[j][k].DO[l].url = URL(i, j, k, l);
					if (j == 0) {
						cout << "[" << DN[i].Name << "][In]["
								<< DN[i].DP[j][k].Name << "]["
								<< DN[i].DP[j][k].DO[l].Name << "] ";
						cout << "[" << i << "][0][" << k << "][" << l << "] ";
						ulm[DN[i].Name]["In"][DN[i].DP[j][k].Name][DN[i].DP[j][k].DO[l].Name].Display();
					} else {
						cout << "[" << DN[i].Name << "][Out]["
								<< DN[i].DP[j][k].Name << "]["
								<< DN[i].DP[j][k].DO[l].Name << "] ";
						cout << "[" << i << "][1][" << k << "][" << l << "] ";
						ulm[DN[i].Name]["Out"][DN[i].DP[j][k].Name][DN[i].DP[j][k].DO[l].Name].Display();
					}
				}
			}
		}
	}
}

void DependencyGraph::Display_ulmi() {
	// Displays the complete ulmi (URL list map integer)
	for (unsigned int i = 0; i < DN.size(); i++) {
		for (unsigned int j = 0; j < DN[i].DP.size(); j++) {
			for (unsigned int k = 0; k < DN[i].DP[j].size(); k++) {
				for (unsigned int l = 0; l < DN[i].DP[j][k].DO.size(); l++) {
					DN[i].DP[j][k].DO[l].url = URL(i, j, k, l);
					if (j == 0) {
						cout << "[" << DN[i].Name << "][In]["
								<< DN[i].DP[j][k].Name << "]["
								<< DN[i].DP[j][k].DO[l].Name << "] ";
						cout << "[" << i << "][0][" << k << "][" << l << "] ";
						ulmi[i][0][k][l].Display();
					} else {
						cout << "[" << DN[i].Name << "][Out]["
								<< DN[i].DP[j][k].Name << "]["
								<< DN[i].DP[j][k].DO[l].Name << "] ";
						cout << "[" << i << "][1][" << k << "][" << l << "] ";
						ulmi[i][1][k][l].Display();
					}
				}
			}
		}
	}
}

void DependencyGraph::DisplayDependency(string ob) {
	// Calls Dependency::Display function for each Dependency in View[ob]
	for (unsigned int i = 0; i < View[ob].size(); i++)
		View[ob][i].Display();
}

void DependencyGraph::DisplayDependencyMini(string ob) {
	// Calls Dependency::DisplayMini function for each Dependency in View[ob]
	for (unsigned int i = 0; i < View[ob].size(); i++)
		View[ob][i].DisplayMini();
}

void DependencyGraph::DisplayDependency() {
	// Calls DisplayDependency function for all DependencyObject names in View
	for (map<string, vector<Dependency> >::const_iterator it = View.begin();
			it != View.end(); ++it) {
		std::cout << "DView_" << it->first << endl;
		DisplayDependency(it->first);
	}
}

void DependencyGraph::DisplayDependencyValues(string ob) {
	// Calls Dependency::DisplayValues function for each Dependency in View[ob]
	for (unsigned int i = 0; i < View[ob].size(); i++)
		View[ob][i].DisplayValues(DN);
}

void DependencyGraph::DisplayDependencyValues() {
	// Calls DisplayDependencyValues(string ob) function for all DependencyObject names in View
	for (map<string, vector<Dependency> >::const_iterator it = View.begin();
			it != View.end(); ++it) {
		std::cout << "DView_" << it->first << endl;
		DisplayDependencyValues(it->first);
	}
}

DependencyGraph::~DependencyGraph() {
}

} /* namespace SmartDG */
