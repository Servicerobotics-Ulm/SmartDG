////////////////////////////////////////////////////////////////////////////////
///	\file	GUIPoint.h
/// \brief	Header file for Dependency class
/// \author Vineet Nagrath
/// \date	July 3, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef GUIPOINT_H_
#define GUIPOINT_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class GUIPoint
/// \brief GUIPoint class models and manages FLTK graphic elements to draw and refresh a point.
/// \todo Detailed code comments will be added in a later version [Pending finalization of GUI]
////////////////////////////////////////////////////////////////////////////////
class GUIPoint {
public:
	string Name;
	unsigned int x;
	unsigned int y;
	GUIPoint() :
			Name("NA"), x(0), y(SmartDG_MENUHEIGHT) {
	}
	;
	GUIPoint(string name) :
			Name(name), x(0), y(SmartDG_MENUHEIGHT) {
	}
	;
	GUIPoint(unsigned int ix, unsigned int iy, string name = "NA") :
			Name(name), x(ix), y(iy + SmartDG_MENUHEIGHT) {
	}
	;
	GUIPoint(string name, unsigned int ix, unsigned int iy) :
			Name(name), x(ix), y(iy + SmartDG_MENUHEIGHT) {
	}
	;
	//////////////////////////////////////////////////
	/// \fn ~GUIPoint()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~GUIPoint();
};

} /* namespace SmartDG */

#endif /* GUIPOINT_H_ */
