////////////////////////////////////////////////////////////////////////////////
///	\file	Environment.cpp
/// \brief	Source file for Environment class
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

#include "SmartDG.h"

namespace SmartDG {

Environment::Environment() {
	// Calls isMultiSmartDependencyObjectsInit()
	isMultiSmartDependencyObjectsInit();
	// Calls SmartDG_GlobalFunction::EnvironmentGenerator to fetch the current Environment Elements
	SmartDG_GlobalFunction::EnvironmentGenerator(SmartDependencyObjects,
			isMultiSmartDependencyObjects, SmartComponents, TransferFunctions,
			InputPorts, OutputPorts, InputObjectInstances,
			OutputObjectInstances, SmartConnectors, Wiki);
	// Calls GODInit()
	GODInit();
	// Calls SortAll()
	SortAll();
}

void Environment::GODInitTF(string g) {
	TransferFunctions.emplace(g,
			&SmartDG::TransferFunctionsNullNode::Instance001::TFT);
}

Environment::~Environment() {
}

} /* namespace SmartDG */
