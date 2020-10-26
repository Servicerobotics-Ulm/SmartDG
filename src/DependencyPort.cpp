////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyPort.cpp
/// \brief	Source file for DependencyPort class
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

DependencyPort::DependencyPort() {
	// Sets Default Name
	Name = "NA_DP";
	// Calls setNULL()
	setNULL();
}

DependencyPort::DependencyPort(string DPName) {
	// Sets Name : DPName
	Name = DPName;
	// Calls setNULL()
	setNULL();
}

DependencyPort::DependencyPort(const SmartDG::DependencyPort& dp) {
	// Copy Constructor
	// Sets Name : dp.Name
	Name = dp.Name;
	// Sets DO : dp.DO
	DO = dp.DO;
	// Calls setNULL()
	setNULL();
}

void DependencyPort::setNULL() {
	// sets FLTK graphic pointers to NULL
	Shape = NULL;
}

DependencyPort::~DependencyPort() {
}

} /* namespace SmartDG */
