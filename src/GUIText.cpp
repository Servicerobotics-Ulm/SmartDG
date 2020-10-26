////////////////////////////////////////////////////////////////////////////////
///	\file	GUIText.cpp
/// \brief	Source file for Dependency class
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

#include "SmartDG.h"

namespace SmartDG {

GUIText::GUIText(unsigned int xx, unsigned int yy, string txt, unsigned int fh,
		unsigned int fw, unsigned int fc, bool h, bool f) :
		text(txt), x(xx), y(yy), fontheight(fh), fontwidth(fw), fontcolor(fc), length(
				text.length()), horizontal(h), forward(f) {
	unsigned int tab = 1; //#TODO
	for (unsigned int i = 0; i < length; i += tab) {
		GUILine *t1 = new GUILine(x + fontwidth * i, y, 1, 1,
				text.substr(i, tab).c_str(), fontheight, fontcolor);
		Boxes.push_back(t1);
	}
	// #TODO Make text string editable
}

GUIText::~GUIText() {
}

} /* namespace SmartDG */
