////////////////////////////////////////////////////////////////////////////////
///	\file	GUIConnection.cpp
/// \brief	Source file for Dependency class
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

#include "SmartDG.h"

namespace SmartDG {

void GUIConnection::Common(string name, string tx1, string tx2, unsigned int fc,
		unsigned int tc, unsigned int gx, unsigned int gy,
		unsigned int inlcolor, unsigned int inlthick) {
	dummy = false;
	counter = count;
	GUIConnection::count++;
	Name = name;
	lcolor = inlcolor;
	lthick = inlthick;
	y2igty1 = true;
	txt1 = tx1;
	txt2 = tx2;
	txt = txt1 + "|" + txt2;
	S1 = "";
	S2 = "";
	Direction = "";
	fcount = fc;
	tcount = tc;
	gridx = gx;
	gridy = gy;
	mx = 1;
	my = 1;
}

GUIConnection::GUIConnection() {
	dummy = true;
	ComponentMode = 1;
	counter = 0;
	Name = "DUMMY";
	lcolor = 0;
	lthick = 0;
	y2igty1 = false;
	txt1 = "";
	txt2 = "";
	txt = "";
	S1 = "";
	S2 = "";
	Direction = "";
	fcount = 0;
	tcount = 0;
	gridx = 0;
	gridy = 0;
	mx = 0;
	my = 0;
	ctxt = "0";
	Prep(0, 0, 0, 0);
}

GUIConnection::GUIConnection(string name, unsigned int inx1, unsigned int iny1,
		unsigned int inx2, unsigned int iny2, string tx1, string tx2,
		unsigned int fc, unsigned int tc, unsigned int gx, unsigned int gy,
		unsigned int inlcolor, unsigned int inlthick) {
	ComponentMode = 0;
	Common(name, tx1, tx2, fc, tc, gx, gy, inlcolor, inlthick);
	ctxt = std::to_string(counter);
	Draw(inx1, iny1, inx2, iny2);
}

GUIConnection::GUIConnection(string name, int componentmode, string tr,
		unsigned int inx1, unsigned int iny1, unsigned int inx2,
		unsigned int iny2, string tx1, string tx2, unsigned int fc,
		unsigned int tc, unsigned int gx, unsigned int gy,
		unsigned int inlcolor, unsigned int inlthick) {
	ComponentMode = componentmode;
	Common(name, tx1, tx2, fc, tc, gx, gy, inlcolor, inlthick);
	if (ComponentMode > 0)
		ctxt = tr;
	else
		ctxt = std::to_string(counter);
	Draw(inx1, iny1, inx2, iny2);
}

void GUIConnection::Draw(unsigned int inx1, unsigned int iny1,
		unsigned int inx2, unsigned int iny2) {
	if (!dummy) {
		Prep(inx1, iny1, inx2, iny2);
		fl_color(lcolor);
		//Lines
		for (unsigned int p = 0; p < pts.size(); p++) {
			GUILine *t = new GUILine(pts[p][0], pts[p][1], pts[p][2],
					pts[p][3]);
			lines.push_back(t);
		}
		//Connection Point Label
		if ((ComponentMode == 0) || ((ComponentMode == 2))) {
			GUILine *t1 = new GUILine(
					pts[0][0] + 1.2 * (fcount - 1) * SmartDG_IWW,
					pts[0][1] - SmartDG_IWW,
					SmartDG_IWW, SmartDG_IWW, to_string(counter).c_str());
			t1->labelsize(SmartDG_IWW / 1.5);
			lines.push_back(t1);
			unsigned int t = pts.size() - 1;
			GUILine *t2 = new GUILine(
					pts[t][0] + pts[t][2]-(1.2*(tcount-1)+1)*SmartDG_IWW,
					pts[t][1] - SmartDG_IWW,
					SmartDG_IWW, SmartDG_IWW, to_string(counter).c_str());
			t2->labelsize(SmartDG_IWW / 1.5);
			lines.push_back(t2);
		}
		//Center Label
		txtboxName = new GUILine(l[0], l[1], SmartDG_LSIZE, "TOP", "Name");
		txtboxtxt = new GUILine(l[0], l[1], SmartDG_LSIZE, "BOTTOM", "");
		txtboxS1 = new GUILine(l[0], l[1], SmartDG_LSIZE, "LEFT", "S1");
		txtboxS2 = new GUILine(l[0], l[1], SmartDG_LSIZE, "RIGHT", "S2");
		txtboxDirection = new GUILine(l[0], l[1], SmartDG_LSIZE, "INSIDE",
				"S2");
		if (ComponentMode > 0) {
			if (ctxt.length() > 15) {
				int fontwidth = 10;
				int fontheight = 10;
				txtboxtxt2 = new GUIText(l[0] - fontwidth * ctxt.length() / 2,
						l[1] + SmartDG_LSIZE, ctxt, fontheight, fontwidth);
			}
		}
		MakeTxt();
	}
}

void GUIConnection::Prep(unsigned int inx1, unsigned int iny1,
		unsigned int inx2, unsigned int iny2) {
	pts.clear();
	x1 = inx1;
	y1 = iny1;
	x2 = inx2;
	y2 = iny2;
	y2igty1 = true;
	if (y1 >= y2)
		y2igty1 = false;

	unsigned int x = x2 - x1;
	unsigned int xm = (x2 - x1) / 2;
	int y = 0;

	if (y2igty1)
		y = y2 - y1;
	else
		y = y1 - y2;

	//if x==0 or x2<x1 #TODO
	if (0 == y) {
		vector<unsigned int> tmp1, tmp2, tmp3;
		tmp1.push_back(x1);
		tmp1.push_back(y1);
		tmp1.push_back(5);
		tmp1.push_back(lthick);
		tmp2.push_back(x1 + 6);
		tmp2.push_back(y1);
		tmp2.push_back(x - 10);
		tmp2.push_back(lthick);
		tmp3.push_back(x2 - 5);
		tmp3.push_back(y1);
		tmp3.push_back(5);
		tmp3.push_back(lthick);
		pts.push_back(tmp1);
		pts.push_back(tmp2);
		pts.push_back(tmp3);
		mx = 0;
		my = -1;
	} else if (y2igty1) {
		vector<unsigned int> tmp1, tmp2, tmp3;
		tmp1.push_back(x1);
		tmp1.push_back(y1);
		tmp1.push_back(xm);
		tmp1.push_back(lthick);
		pts.push_back(tmp1);
		tmp2.push_back(x1 + xm);
		tmp2.push_back(y1);
		tmp2.push_back(lthick);
		tmp2.push_back(y);
		pts.push_back(tmp2);
		tmp3.push_back(x1 + xm);
		tmp3.push_back(y1 + y);
		tmp3.push_back(xm);
		tmp3.push_back(lthick);
		pts.push_back(tmp3);
		pts.push_back(tmp1);
		pts.push_back(tmp2);
		pts.push_back(tmp3);
		if (counter % 2) {
			mx = -1;
			my = 0;
		} else {
			mx = 1;
			my = 0;
		}
	} else {
		vector<unsigned int> tmp1, tmp2, tmp3;
		tmp1.push_back(x1);
		tmp1.push_back(y1);
		tmp1.push_back(xm);
		tmp1.push_back(lthick);
		pts.push_back(tmp1);
		tmp2.push_back(x1 + xm);
		tmp2.push_back(y1 - y + lthick);
		tmp2.push_back(lthick);
		tmp2.push_back(y);
		pts.push_back(tmp2);
		tmp3.push_back(x1 + xm);
		tmp3.push_back(y1 - y);
		tmp3.push_back(xm);
		tmp3.push_back(lthick);
		pts.push_back(tmp3);
		pts.push_back(tmp1);
		pts.push_back(tmp2);
		pts.push_back(tmp3);
		if (counter % 2) {
			mx = -1;
			my = 0;
		} else {
			mx = 1;
			my = 0;
		}
	}
	l.clear();
	if (ComponentMode > 0) {
		l.push_back(gridx);
		l.push_back(gridy + 0.7 * SmartDG_LSIZE);
	} else {
		l.push_back(gridx + (mx * 1.5 * SmartDG_LSIZE));
		l.push_back(gridy + (my * 1.5 * SmartDG_LSIZE));
	}
}

void GUIConnection::MakeTxt() {
	if (!dummy) {
		txtboxName->L = Name;
		if ((ComponentMode > 0) && (ctxt.length() > 15))
			txtboxtxt2->text = ctxt;
		else
			txtboxtxt->L = ctxt;
		txtboxS1->L = S1;
		txtboxS2->L = S2;
		txtboxDirection->L = Direction;
	}
}

inline void GUIConnection::Fill(string s) {
	Fill(s, s);
}

void GUIConnection::Fill(string s1, string s2) {
	S1 = s1;
	S2 = s2;
	MakeTxt();
}

inline void GUIConnection::Fill(DependencyDataPackage s) {
	Fill(s, s);
}

void GUIConnection::Fill(DependencyDataPackage s1, DependencyDataPackage s2) {
	S1 = s1.toStr();
	S2 = s2.toStr();
	MakeTxt();
}

void GUIConnection::setDirection(int d) {
	Direction = "";
	if (d > 0)
		Direction = ">";
	else if (d < 0)
		Direction = "<";
}

GUIConnection::~GUIConnection() {
}

unsigned long GUIConnection::count = 0;

} /* namespace SmartDG */
