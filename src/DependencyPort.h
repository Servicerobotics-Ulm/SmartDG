////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyPort.h
/// \brief	Header file for DependencyPort class
/// \author Vineet Nagrath
/// \date	June 2, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef DEPENDENCYPORT_H_
#define DEPENDENCYPORT_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyPort
/// \brief DependencyPort class models Input or Output ports of a DependencyNode Component
///
/// This class encapsulates a vector of DependencyObject objects that are available at
/// a DependencyPort. It carries constructors to realize an object of DependencyPort
/// class by name or by copying another DependencyPort object.
////////////////////////////////////////////////////////////////////////////////
class DependencyPort {
public:
	string Name; ///< Name given to uniquely identify a DependencyPort object
	Fl_Group *Shape; ///< Points to Fl_Group object that encapsulates all FLTK elements associated with DependencyPort object
	vector<DependencyObject> DO; ///< a vector of DependencyObject objects that are available at DependencyPort
	//////////////////////////////////////////////////
	/// \fn DependencyPort()
	/// \brief Constructor
	///
	/// - Sets Default DependencyPort::Name\n
	/// - Calls DependencyPort::setNULL()
	///
	/// \see DependencyPort(string DPName) \see DependencyPort(const SmartDG::DependencyPort& dp) \see setNULL()
	//////////////////////////////////////////////////
	DependencyPort();
	//////////////////////////////////////////////////
	/// \fn DependencyPort(string DPName)
	/// \brief Constructor
	///	\param [in] DPName is string argument used to set DependencyPort::Name
	///
	/// - Sets DependencyPort::Name : DPName\n
	/// - Calls DependencyPort::setNULL()
	///
	/// \see DependencyPort() \see DependencyPort(const SmartDG::DependencyPort& dp) \see setNULL()
	//////////////////////////////////////////////////
	DependencyPort(string DPName);
	//////////////////////////////////////////////////
	/// \fn DependencyPort(const SmartDG::DependencyPort& dp)
	/// \brief Constructor
	///	\param [in, out] dp is DependencyPort argument used to set DependencyPort (Copy Constructor)
	///
	/// - Sets DependencyPort::Name : dp.Name\n
	/// - Sets DependencyPort::DO : dp.DO\n
	/// - Calls DependencyPort::setNULL()
	///
	/// \see DependencyPort() \see DependencyPort(string DPName) \see setNULL()
	//////////////////////////////////////////////////
	DependencyPort(const SmartDG::DependencyPort& dp);
	//////////////////////////////////////////////////
	/// \fn setNULL()
	/// \brief Called by all Constructors, sets FLTK graphic pointers to NULL
	///
	/// - sets FLTK graphic pointers to NULL
	///
	/// \see DependencyPort() \see DependencyPort(string DPName) \see DependencyPort(const SmartDG::DependencyPort& dp)
	//////////////////////////////////////////////////
	void setNULL();
	//////////////////////////////////////////////////
	/// \fn ~DependencyPort()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyPort();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYPORT_H_ */
