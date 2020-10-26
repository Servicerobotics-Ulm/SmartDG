////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObject.cpp
/// \brief	Source file for DependencyObject class
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

DependencyObject::DependencyObject() {
	Name = "NA_DO";
	setup();
}

DependencyObject::DependencyObject(string DOName) {
	Name = DOName;
	setup();
}

void DependencyObject::setup() {
	Shape = NULL;
}

void DependencyObject::Set(DependencyDataPackage d, string instance) {
	udi[instance] = d;
}

void DependencyObject::Set(DependencyDataPackage d) {
	for (map<string, DependencyDataPackage>::const_iterator it = udi.begin();
			it != udi.end(); ++it)
		udi[it->first] = d;
}

DependencyDataPackage DependencyObject::Get(string instance) {
	return udi[instance];
}

DependencyDataPackage DependencyObject::Get() {
	// Returns DependencyDataPackage get value of the first udi entry irrespective of number of udi entries
	map<string, DependencyDataPackage>::const_iterator it = udi.begin();
	return udi[it->first];
}

int DependencyObject::GetBias() {
	double tot = 0;
	for (map<string, DependencyDataPackage>::const_iterator it = udi.begin();
			it != udi.end(); ++it)
		if (it->second.b)
			tot++;
	if (udi.size() == 0)
		return -1; // Returns -1 when there are no udi entries
	// Returns round ( ((Number of true values in udi entries) / (total number of udi entries)) * 10 )
	return round((tot / udi.size()) * 10);
}

DependencyObject::~DependencyObject() {
}

} /* namespace SmartDG */
