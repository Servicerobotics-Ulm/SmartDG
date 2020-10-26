////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyDataPackage.h
/// \brief	Header file for DependencyDataPackage class
/// \author Vineet Nagrath
/// \date	June 16, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef DEPENDENCYDATAPACKAGE_H_
#define DEPENDENCYDATAPACKAGE_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyDataPackage
/// \brief DependencyDataPackage class models dependency object data package sent over a connection
///
/// This class encapsulates data items in a dependency object instance
/// that may be sent over a named connection.
/// \todo At present we only support a single boolean data item, this will be expanded later
/// \see inline std::ostream& operator << (std::ostream& os, const DependencyDataPackage& var)
////////////////////////////////////////////////////////////////////////////////
class DependencyDataPackage {
public:
	static unsigned long delta; ///< Part of a mechanism to detect any change across all objects of DependencyDataPackage class
	//#TODO  At present we only support a single boolean data item, this will be expanded later
	bool b; ///< Single boolean data item \todo At present we only support a single boolean data item, this will be expanded later
	//////////////////////////////////////////////////
	/// \fn DependencyDataPackage()
	/// \brief Constructor
	///
	/// - Sets Default value for data items
	//////////////////////////////////////////////////
	DependencyDataPackage();
	//////////////////////////////////////////////////
	/// \fn void Set(bool in)
	/// \brief Sets value to data items
	/// \param [in] in is the value to be set
	///
	/// - Sets argument value to data items
	/// - In case there is a change in value, static variable delta is incremented
	//////////////////////////////////////////////////
	void Set(bool in);
	//////////////////////////////////////////////////
	/// \fn bool Get()
	/// \brief Gets value of data items
	/// \return [bool] Value of the data item
	///
	/// - Returns value of data items
	//////////////////////////////////////////////////
	bool Get();
	//////////////////////////////////////////////////
	/// \fn string toStr()
	/// \brief Gets value of data items converted to a string
	/// \return [string] Value of the data item converted to a string
	///
	/// - Returns value of data items converted to string
	//////////////////////////////////////////////////
	string toStr();
	//////////////////////////////////////////////////
	/// \fn ~DependencyDataPackage()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyDataPackage();
};

////////////////////////////////////////////////////////////////////////////////
/// \fn inline std::ostream& operator << (std::ostream& os, const DependencyDataPackage& var)
/// \param [in] os is source ostream object
/// \param [in] var is an object of DependencyDataPackage
/// \return [std::ostream] an ostream object that contains var converted to string
///
/// - Doesn't Utilizes DependencyDataPackage::toStr() function for conversion\n
/// - Utilizes default << operators associated with ostream class for conversion\n
/// - For example boolean true is converted to "1"(Default conversion) and not "T"(Using DependencyDataPackage::toStr())
///
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator <<(std::ostream& os,
		const DependencyDataPackage& var) {
	// Utilizes default << operators associated with ostream class for conversion
	os << var.b;
	return os;
}

} /* namespace SmartDG */

#endif /* DEPENDENCYDATAPACKAGE_H_ */
