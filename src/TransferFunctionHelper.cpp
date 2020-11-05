////////////////////////////////////////////////////////////////////////////////
///	\file	TransferFunctionHelper.cpp
/// \brief	Source file for TransferFunctionHelper class
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

#include "SmartDG.h"

namespace SmartDG {

TransferFunctionHelper::TransferFunctionHelper() {
}

bool TransferFunctionHelper::Get(vector< vector<DependencyPort> >& DP, string IO, string Port, string Obj)	{
	unsigned int i = 0;
	if (IO == "In") i = 0;
	if (IO == "Out") i = 1;
	for(unsigned int j = 0; j< DP[i].size(); j++)	{
		if ( DP[i][j].Name == Port)	{
			for(unsigned int k = 0; k< DP[i][j].DO.size(); k++)	{
				if (DP[i][j].DO[k].Name == Obj)
					return DP[i][j].DO[k].Get().b;
			}
		}
	}
	return false;
}

bool TransferFunctionHelper::Set(vector< vector<DependencyPort> >& DP, string IO, string Port, string Obj, bool val)	{
	unsigned int i = 0;
	if (IO == "In") i = 0;
	if (IO == "Out") i = 1;
	for(unsigned int j = 0; j< DP[i].size(); j++)	{
		if ( DP[i][j].Name == Port)	{
			for(unsigned int k = 0; k< DP[i][j].DO.size(); k++)	{
				if (DP[i][j].DO[k].Name == Obj)	{
					DependencyDataPackage ddp;
					ddp.b = val;
					DP[i][j].DO[k].Set(ddp);
					return true;
				}
			}
		}
	}
	return false;
}

TransferFunctionHelper::~TransferFunctionHelper() {
}

} /* namespace SmartDG */

