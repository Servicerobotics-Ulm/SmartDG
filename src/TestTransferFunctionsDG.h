////////////////////////////////////////////////////////////////////////////////
///	\file	TransferFunctionsDGTest.h
/// \brief	Header file for Demo Transfer Functions
/// \author Vineet Nagrath
/// \date	July 16, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef TESTTRANSFERFUNCTIONSDG_H_
#define TESTTRANSFERFUNCTIONSDG_H_

#include "SmartDG.h"

namespace SmartDG {
namespace TransferFunctionsDGTest {
inline string Name() {
	if (SmartDG_TFV)
		cout << "Name" << endl;
	return "TestTF";
}

inline void TF(vector<string> &Return) {
	if (SmartDG_TFV)
		cout << "TF" << endl;
	Return.push_back(SmartDG_OK);
}

inline void FT(vector<string> &Return) {
	if (SmartDG_TFV)
		cout << "FT" << endl;
	Return.push_back(SmartDG_OK);
}

inline void TFT(string Fun, vector<string> &Return,
		vector<vector<SmartDG::DependencyPort> >& DP) {
	if (SmartDG_TFV)
		cout << "TestTransferFunction" << "SmartComponent " << Name() << " "
				<< Fun << endl;
	if (Fun == "List") {
		Return.push_back(SmartDG_OK);
		Return.push_back("List");
		Return.push_back("Name");
		Return.push_back("TF");
		Return.push_back("FT");
		return;
	}
	if (Fun == "Name") {
		Return.push_back(SmartDG_OK);
		Return.push_back(Name());
		return;
	}
	if (Fun == "TF") {
		TF(Return);
		return;
	}
	if (Fun == "FT") {
		FT(Return);
		return;
	}

	Return.push_back(SmartDG_NOT_OK); // Function Not Found
	return;
}
} /* namespace TransferFunctionsDGTest */
} /* namespace SmartDG */

#endif /* TESTTRANSFERFUNCTIONSDG_H_ */
