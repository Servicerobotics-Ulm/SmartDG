////////////////////////////////////////////////////////////////////////////////
///	\file	GUILine.h
/// \brief	Header file for Dependency class
/// \author Vineet Nagrath
/// \date	June 15, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef GUILINE_H_
#define GUILINE_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class GUILine
/// \brief GUILine class models and manages FLTK graphic elements to draw and refresh a line.
/// \todo Detailed code comments will be added in a later version [Pending finalization of GUI]
////////////////////////////////////////////////////////////////////////////////
class GUILine: public Fl_Box {
public:
	string L;
	//Lines
	GUILine(int x1, int y1, int x2, int y2) :
			Fl_Box(x1, y1, x2, y2) {
		L = "";
		color(SmartDG_LCOLOR);
		box(FL_FLAT_BOX);
	}
	//Connection Point Label
	GUILine(int x1, int y1, int x2, int y2, string l) :
			Fl_Box(x1, y1, x2, y2) {
		L = l;
		label(L.c_str());
		color(SmartDG_LCOLOR);
		box(FL_BORDER_FRAME);
		labelcolor(SmartDG_LLCOLOR);
		align(FL_ALIGN_INSIDE);
	}
	//GUIText
	GUILine(int x1, int y1, int x2, int y2, string l, unsigned int fontheight,
			unsigned int col) :
			Fl_Box(x1, y1, x2, y2) {
		L = l;
		label(L.c_str());
		labelsize(fontheight);
		color(col);
		box(FL_NO_BOX);
		labelcolor(col);
		align(FL_ALIGN_RIGHT);
	}
	//Center Label
	GUILine(int xm, int ym, int ls, string c, string l = 0) :
			Fl_Box(xm - ls / 2, ym - ls / 2, ls, ls) {
		L = l;
		label(L.c_str());
		color(SmartDG_LLCOLOR);
		box(FL_BORDER_FRAME);
		labelcolor(SmartDG_LLCOLOR);

		if ("TOP" == c) {
			align(FL_ALIGN_TOP);
		}
		if ("TOP_LEFT" == c) {
			align(FL_ALIGN_TOP_LEFT);
		}
		if ("RIGHT" == c) {
			align(FL_ALIGN_RIGHT);
		}
		if ("LEFT" == c) {
			align(FL_ALIGN_LEFT);
		}
		if ("BOTTOM" == c) {
			align(FL_ALIGN_BOTTOM);
		}
		if ("BOTTOM_LEFT" == c) {
			align(FL_ALIGN_BOTTOM_LEFT);
		}
		if ("INSIDE" == c) {
			align(FL_ALIGN_INSIDE);
		}
	}
	//////////////////////////////////////////////////
	/// \fn ~GUILine()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~GUILine();
};

} /* namespace SmartDG */

#endif /* GUILINE_H_ */
