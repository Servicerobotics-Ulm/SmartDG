////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObjectInstance.cpp
/// \brief	Source file for DependencyObjectInstance class
/// \author Vineet Nagrath
/// \date	June 19, 2020
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

DependencyObjectInstance::DependencyObjectInstance(unsigned long i, URL p,
		URL t, int d) {
	id = i;
	obj = p.stro;
	direction = d;
	pou = p;
	tou = t;
	cuk = t.str;
	mid = p.strp + "/" + obj + "[" + cuk + "]";
	midL = p.strn + "/" + p.strio + "/" + mid;
	amid = p.strp + "/" + obj + "[ALL]";
	amidL = p.strn + "/" + p.strio + "/" + amid;
	visible = false;
	editable = false;
}

void DependencyObjectInstance::Display() {
	// Displays DependencyObjectInstance object
	cout << "DependencyObjectInstance:[" << id << "] " << obj << " " << pou.str
			<< " " << tou.str << " " << cuk << " " << endl;
}

void DependencyObjectInstance::DisplayIf(unsigned int c) {
	// Condition based Displays DependencyObjectInstance object
	// c is condition selector on visible and editable flags
	switch (c) {
	// Display if both flags are true
	case 0:
		if (visible && editable)
			Display();
		break;
		// Display if DependencyObjectInstance::visible is true
	case 1:
		if (visible)
			Display();
		break;
		// Display if DependencyObjectInstance::editable is true
	case 2:
		if (editable)
			Display();
		break;
	}
}

DependencyObjectInstance::~DependencyObjectInstance() {
}

} /* namespace SmartDG */
