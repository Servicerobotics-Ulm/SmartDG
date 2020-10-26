////////////////////////////////////////////////////////////////////////////////
///	\file	URL.cpp
/// \brief	Source file for URL class
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

URL::URL() {
	NodeIndex = 0;
	InOutIndex = 0;
	PortIndex = 0;
	ObjectIndex = 0;
}

URL::URL(unsigned int ni, unsigned int ioi, unsigned int pi, unsigned int oi) {
	NodeIndex = ni;
	InOutIndex = ioi;
	PortIndex = pi;
	ObjectIndex = oi;
}

string URL::dotless(string d) {
	return (strn + d + strio + d + strp + d + stro);
}
void URL::Display() {
	cout << "[" << NodeIndex << "," << InOutIndex << "," << PortIndex << ","
			<< ObjectIndex << "] " << str << endl;
}

URL::~URL() {
}

} /* namespace SmartDG */
