////////////////////////////////////////////////////////////////////////////////
///	\file	TransferFunctionHelper.h
/// \brief	Header file for TransferFunctionHelper class
/// \author Vineet Nagrath
/// \date	Nov 5, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef DOC_TRANSFERFUNCTIONHELPER_H_
#define DOC_TRANSFERFUNCTIONHELPER_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class TransferFunctionHelper
/// \brief TransferFunctionHelper contains helper functions for Transfer Functions
////////////////////////////////////////////////////////////////////////////////
class TransferFunctionHelper {
public:
	TransferFunctionHelper();
	bool Get(vector< vector<DependencyPort> >& DP, string IO, string Port, string Obj);
	bool Set(vector< vector<DependencyPort> >& DP, string IO, string Port, string Obj, bool val);
	virtual ~TransferFunctionHelper();
};

} /* namespace SmartDG */

#endif /* DOC_TRANSFERFUNCTIONHELPER_H_ */
