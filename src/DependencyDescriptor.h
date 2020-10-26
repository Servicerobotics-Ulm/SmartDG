////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyDescriptor.h
/// \brief	Header file for DependencyDescriptor class
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

#ifndef DEPENDENCYDESCRIPTOR_H_
#define DEPENDENCYDESCRIPTOR_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyDescriptor
/// \brief DependencyDescriptor class describes a data dependency over a connection
///
/// This class encapsulates names of a source and target dependency node.port.object instances
/// over a named connection.
////////////////////////////////////////////////////////////////////////////////
class DependencyDescriptor {
public:
	string DependencyName; ///< Name of connector over which the dependency is established
	string FromDependencyNodeName;	///< Name of source node
	string FromDependencyPortName;	///< Name of source port
	string DependencyObjectName;	///< Name of dependency object being sent
	string ToDependencyNodeName;	///< Name of target node
	string ToDependencyPortName;	///< Name of target port
	//////////////////////////////////////////////////
	/// \fn DependencyDescriptor(string DependencyName_Arg,
	///		string FromDependencyNodeName_Arg,
	///		string FromDependencyPortName_Arg, string DependencyObjectName_Arg,
	///		string ToDependencyNodeName_Arg, string ToDependencyPortName_Arg)
	/// \brief Constructor
	///
	/// - Sets argument values to member data\n
	///
	/// \param [in] DependencyName_Arg is argument for DependencyName
	/// \param [in] FromDependencyNodeName_Arg is argument for FromDependencyNodeName
	/// \param [in] FromDependencyPortName_Arg is argument for FromDependencyPortName
	/// \param [in] DependencyObjectName_Arg is argument for DependencyObjectName
	/// \param [in] ToDependencyNodeName_Arg is argument for ToDependencyNodeName
	/// \param [in] ToDependencyPortName_Arg is argument for ToDependencyPortName
	//////////////////////////////////////////////////
	DependencyDescriptor(string DependencyName_Arg,
			string FromDependencyNodeName_Arg,
			string FromDependencyPortName_Arg, string DependencyObjectName_Arg,
			string ToDependencyNodeName_Arg, string ToDependencyPortName_Arg) :
			DependencyName(DependencyName_Arg), FromDependencyNodeName(
					FromDependencyNodeName_Arg), FromDependencyPortName(
					FromDependencyPortName_Arg), DependencyObjectName(
					DependencyObjectName_Arg), ToDependencyNodeName(
					ToDependencyNodeName_Arg), ToDependencyPortName(
					ToDependencyPortName_Arg) {
	}
	;
	//////////////////////////////////////////////////
	/// \fn void Display()
	/// \brief Display function
	///
	/// - Connector : Source DependencyNode . Source DependencyPort --- DependencyObject ---> Target DependencyNode . Target DependencyPort
	//////////////////////////////////////////////////
	inline void Display() {
		cout << DependencyName << " : " << FromDependencyNodeName << "."
				<< FromDependencyPortName << " -- " << DependencyObjectName
				<< " --> " << ToDependencyNodeName << "."
				<< ToDependencyPortName << endl;
	}
	//////////////////////////////////////////////////
	/// \fn ~DependencyDescriptor()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyDescriptor();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYDESCRIPTOR_H_ */
