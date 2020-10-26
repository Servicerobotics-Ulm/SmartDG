////////////////////////////////////////////////////////////////////////////////
///	\file	Dependency.cpp
/// \brief	Source file for Dependency class
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

Dependency::Dependency() {
	// Sets Default Name
	Name = "NA_DD";
	// Sets Default From and To URLs
	URL z(0, 0, 0, 0);
	From = z;
	To = z;
	// errorflag set to true by default
	errorflag = true;
	setNULL();
}
Dependency::Dependency(string name, URL f, URL t) {
	Name = name;
	From = f;
	To = t;
	// Error if connection originates from an input port or ends at an output port
	if ((f.InOutIndex == 1) || (t.InOutIndex == 0))
		errorflag = true;	// Error
	else
		errorflag = false;	// No Error
	setNULL();
}

Dependency::Dependency(string name, unsigned int fni, unsigned int fioi,
		unsigned int fpi, unsigned int foi, unsigned int tni, unsigned int tioi,
		unsigned int tpi, unsigned int toi) {
	// Sets From and To URLs
	URL f(fni, fioi, fpi, foi);
	URL t(fni, fioi, fpi, foi);
	// errorflag set to true before call to Dependency(string name, URL f, URL t)
	errorflag = true;
	setNULL();
	Dependency(name, f, t);
}

Dependency::Dependency(string name, unsigned int fni, unsigned int fpi,
		unsigned int foi, unsigned int tni, unsigned int tpi,
		unsigned int toi) {
	// Sets From and To URLs
	URL f(fni, 0, fpi, foi);
	URL t(fni, 1, fpi, foi);
	// errorflag set to true before call to Dependency(string name, URL f, URL t)
	errorflag = false;
	setNULL();
	Dependency(name, f, t);
}

void Dependency::setNULL() {
	// Sets Transfer/Inverse transfer Function pointers to ideal connector's Transfer/Inverse transfer Functions
	// In case the connector is a dependency node, these TF and FT function pointers are later assigned to
	// transfer/inverse transfer function associated with the connector.
	TF = &SmartDG::TransferFunctionsIdealConnector::Instance001::TF;
	FT = &SmartDG::TransferFunctionsIdealConnector::Instance001::FT;
	// Sets GUIConnection to null
	con = NULL;
}

void Dependency::Display() {
	// Displays full URLs
	// {Connector} Source URL - DependencyObject -> Target URL
	cout << "{" << Name << "}" << From.str << "----" << From.stro << "---->"
			<< To.str << endl;
}

void Dependency::DisplayMini() {
	// Displays {Connector}
	// Source DependencyNode . Source DependencyPort - DependencyObject -> Target DependencyNode . Target DependencyPort
	cout << "{" << Name << "}" << From.strn << "." << From.strp << "-"
			<< From.stro << "->" << To.strn << "." << To.strp << endl;
}

void Dependency::DisplayValues(vector<DependencyNode> &DN) {
	// Displays full URLs with Values
	// {Connector} Source URL{Source DependencyDataPackage} ---- DependencyObject ----> Target URL{Target DependencyDataPackage}
	DependencyDataPackage FROMVAL =
			DN[From.NodeIndex].DP[From.InOutIndex][From.PortIndex].DO[From.ObjectIndex].udi[To.str];
	DependencyDataPackage TOVAL =
			DN[To.NodeIndex].DP[To.InOutIndex][To.PortIndex].DO[To.ObjectIndex].udi[From.str];

	cout << "{" << Name << "}" << From.str << "{" << FROMVAL << "}" << "----"
			<< From.stro << "---->" << "{" << TOVAL << "}" << To.str << endl;
}

Dependency::~Dependency() {
}

} /* namespace SmartDG */
