////////////////////////////////////////////////////////////////////////////////
///	\file	TransferFunctionsIdealConnector.h
/// \brief	Header file for Transfer Functions for Ideal Connectors
/// \author Vineet Nagrath
/// \date	June 23, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////
#ifndef TRANSFERFUNCTIONSIDEALCONNECTOR_H_
#define TRANSFERFUNCTIONSIDEALCONNECTOR_H_

#include "SmartDG.h"

namespace SmartDG {
namespace TransferFunctionsIdealConnector {

namespace Instance001 {

inline void TF(vector<vector<SmartDG::DependencyPort> >& DPIn,
		vector<vector<SmartDG::DependencyPort> >& DPOut,
		SmartDG::Dependency &d) {
	if (SmartDG_TFV)
		cout << "TF " << d.Name << endl;
	DPOut[d.To.InOutIndex][d.To.PortIndex].DO[d.To.ObjectIndex].udi[d.From.str].Set(
			DPIn[d.From.InOutIndex][d.From.PortIndex].DO[d.From.ObjectIndex].udi[d.To.str].Get());
	d.con->setDirection(1);
}

inline void FT(vector<vector<SmartDG::DependencyPort> >& DPIn,
		vector<vector<SmartDG::DependencyPort> >& DPOut,
		SmartDG::Dependency &d) {
	if (SmartDG_TFV)
		cout << "FT " << d.Name << endl;
	DPIn[d.From.InOutIndex][d.From.PortIndex].DO[d.From.ObjectIndex].udi[d.To.str].Set(
			DPOut[d.To.InOutIndex][d.To.PortIndex].DO[d.To.ObjectIndex].udi[d.From.str].Get());
	d.con->setDirection(-1);
}

} /* namespace Instance001 */
} /* namespace TransferFunctionsIdealConnector */
} /* namespace SmartDG */

#endif /* TRANSFERFUNCTIONSIDEALCONNECTOR_H_ */
