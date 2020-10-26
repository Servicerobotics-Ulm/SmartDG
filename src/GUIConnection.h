////////////////////////////////////////////////////////////////////////////////
///	\file	GUIConnection.h
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

#ifndef GUICONNECTION_H_
#define GUICONNECTION_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class GUIConnection
/// \brief GUIConnection class models and manages FLTK graphic elements to draw and refresh a connection.
/// \todo Detailed code comments will be added in a later version [Pending finalization of GUI]
////////////////////////////////////////////////////////////////////////////////
class GUIConnection {
	void MakeTxt();
public:
	static unsigned long count;
	unsigned long counter;
	string Name;
	unsigned int x1, y1, x2, y2, lcolor, lthick;
	float mx, my;
	unsigned int fcount, tcount;
	unsigned int gridx, gridy;
	vector<vector<unsigned int> > pts;
	vector<unsigned int> l;
	bool y2igty1;
	vector<GUILine*> lines;
	GUILine* txtboxName;
	GUILine* txtboxtxt;
	GUIText* txtboxtxt2;
	GUILine* txtboxS1;
	GUILine* txtboxS2;
	GUILine* txtboxDirection;
	string txt1, txt2, txt, S1, S2, Direction, ctxt;
	int ComponentMode;
	bool dummy;
	void Common(string name, string tx1, string tx2, unsigned int fc,
			unsigned int tc, unsigned int gx, unsigned int gy,
			unsigned int inlcolor, unsigned int inlthick);
	GUIConnection();
	GUIConnection(string name, unsigned int inx1, unsigned int iny1,
			unsigned int inx2, unsigned int iny2, string tx1, string tx2,
			unsigned int fc, unsigned int tc, unsigned int gx, unsigned int gy,
			unsigned int inlcolor, unsigned int inlthick);
	GUIConnection(string name, int componentmode, string tr, unsigned int inx1,
			unsigned int iny1, unsigned int inx2, unsigned int iny2, string tx1,
			string tx2, unsigned int fc, unsigned int tc, unsigned int gx,
			unsigned int gy, unsigned int inlcolor, unsigned int inlthick);
	void Draw(unsigned int inx1, unsigned int iny1, unsigned int inx2,
			unsigned int iny2);
	void Prep(unsigned int inx1, unsigned int iny1, unsigned int inx2,
			unsigned int iny2);
	void Fill(string s);
	void Fill(string s1, string s2);
	void Fill(DependencyDataPackage s1, DependencyDataPackage s2);
	void Fill(DependencyDataPackage s);
	void setDirection(int d);
	//////////////////////////////////////////////////
	/// \fn ~GUIConnection()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~GUIConnection();
};

} /* namespace SmartDG */

#endif /* GUICONNECTION_H_ */
