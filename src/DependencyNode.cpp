////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyNode.cpp
/// \brief	Source file for DependencyNode class
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

DependencyNode::DependencyNode() {
	Name = "NA_DN";
	setNULL();
}

DependencyNode::DependencyNode(std::string NodeName) {
	Name = NodeName;
	setNULL();
}

void DependencyNode::setNULL() {
	Shape = NULL;
	ShapeI = NULL;
	ShapeO = NULL;
	BarIn = NULL;
	BarOut = NULL;
}

void DependencyNode::Generate_DP() {
	// DependencyNode::DP is filled from DependencyNode::DP_In and DependencyNode::DP_Out
	DP.clear();
	DP.push_back(DP_In);	// DP_In Input DependencyPort objects ---> DP[0]
	DP.push_back(DP_Out);	// DP_Out Output DependencyPort objects ---> DP[1]
	// Once DependencyNode::DP is filled DependencyNode::DP_In and DependencyNode::DP_Out are cleared
	DP_In.clear();
	DP_Out.clear();
}

void DependencyNode::Display() {
	// Displays all DependencyPort objects in DependencyNode and their DependencyObject objects
	// Input Port
	for (unsigned int i = 0; i < DP[0].size(); i++) {
		cout << "  " << DP[0][i].Name << "[";
		for (unsigned int j = 0; j < DP[0][i].DO.size(); j++)
			cout << DP[0][i].DO[j].Name << " ";
		cout << "]";
	}
	cout << "  ||  " << Name << "  ||  ";
	// Output Port
	for (unsigned int i = 0; i < DP[1].size(); i++) {
		cout << "  " << DP[1][i].Name << "[";
		for (unsigned int j = 0; j < DP[1][i].DO.size(); j++)
			cout << DP[1][i].DO[j].Name << " ";
		cout << "]";
	}
	cout << endl;
}

void DependencyNode::Display_URLs() {
	// For all DependencyPort objects in DependencyNode, displays URL of their DependencyObject objects
	for (unsigned int j = 0; j < DP.size(); j++) {
		for (unsigned int k = 0; k < DP[j].size(); k++) {
			for (unsigned int l = 0; l < DP[j][k].DO.size(); l++) {
				DP[j][k].DO[l].url.Display();
			}
		}
	}
	cout << endl;
}

DependencyNode::~DependencyNode() {
}

} /* namespace SmartDG */
