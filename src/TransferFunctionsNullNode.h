////////////////////////////////////////////////////////////////////////////////
///	\file	TransferFunctionsNullNode.h
/// \brief	Header file for Transfer Functions for Null Nodes
/// \author Vineet Nagrath
/// \date	July 2, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////
#ifndef TRANSFERFUNCTIONSNULLNODE_H_
#define TRANSFERFUNCTIONSNULLNODE_H_

#include "SmartDG.h"

namespace SmartDG {
namespace TransferFunctionsNullNode {

namespace Instance001 {

inline void TFT(string Fun, vector<string> &Return,
		vector<vector<SmartDG::DependencyPort> >& DP) {
	if (SmartDG_TFV)
		cout << "TransferFunctionsNullNode_Instance001" << "SmartComponent "
				<< " NullNode " << Fun << endl;
	if (Fun == "List") {
		Return.push_back(SmartDG_OK);
		Return.push_back("List");
		return;
	}
	Return.push_back(SmartDG_NOT_OK); // Function Not Found
	return;
}

} /* namespace Instance001 */
} /* namespace TransferFunctionsNullNode */
} /* namespace SmartDG */

#endif /* TRANSFERFUNCTIONSNULLNODE_H_ */
