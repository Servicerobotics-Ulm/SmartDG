////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyDataPackage.cpp
/// \brief	Source file for DependencyDataPackage class
/// \author Vineet Nagrath
/// \date	June 16, 2020
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

DependencyDataPackage::DependencyDataPackage() {
	// Sets Default value for data items
	b = false;
}

void DependencyDataPackage::Set(bool in) {
	if (b != in) {
		// Sets argument value to data items
		b = in;
		// In case there is a change in value, static variable delta is incremented
		DependencyDataPackage::delta++;
	}
}

bool DependencyDataPackage::Get() {
	// Returns value of data items
	return b;
}

string DependencyDataPackage::toStr() {
	// Returns value of data items converted to string
	if (b)
		return string("T");
	else
		return string("F");
}

DependencyDataPackage::~DependencyDataPackage() {
}

// This static variable is part of a mechanism to detect any change across all objects of DependencyDataPackage class
// Here it is assigned to its default value
unsigned long DependencyDataPackage::delta = 0;

} /* namespace SmartDG */
