////////////////////////////////////////////////////////////////////////////////
///	\file	GUIText.h
/// \brief	Header file for Dependency class
/// \author Vineet Nagrath
/// \date	July 8, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef GUITEXT_H_
#define GUITEXT_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class GUIText
/// \brief GUIText class models and manages FLTK graphic elements to draw and refresh a piece of text.
/// \todo Detailed code comments will be added in a later version [Pending finalization of GUI]
////////////////////////////////////////////////////////////////////////////////
class GUIText {
public:
	string text;
	unsigned int x;
	unsigned int y;
	unsigned int fontheight;
	unsigned int fontwidth;
	unsigned int fontcolor;
	unsigned int length;
	bool horizontal; //#TODO
	bool forward; //#TODO
	vector<GUILine*> Boxes;
	GUIText(unsigned int xx, unsigned int yy, string txt, unsigned int fh = 12,
			unsigned int fw = 10, unsigned int fc = FL_BLACK, bool h = true,
			bool f = true);
	//////////////////////////////////////////////////
	/// \fn ~GUIText()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~GUIText();
};

} /* namespace SmartDG */

#endif /* GUITEXT_H_ */
