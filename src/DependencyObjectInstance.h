////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObjectInstance.h
/// \brief	Header file for DependencyObjectInstance class
/// \author Vineet Nagrath
/// \date	June 19, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef DEPENDENCYOBJECTINSTANCE_H_
#define DEPENDENCYOBJECTINSTANCE_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyObjectInstance
/// \brief DependencyObjectInstance class models Dependency Object's Unique Dependency Instance
///
/// This class encapsulates unique integer id, source DependencyObject name, data flow direction,
/// parent and corresponding DependencyObject URL objects. GUI menu bar strings and flags associated
/// with menu visibility and editability for DependencyObjectInstance are also stored in this class.
////////////////////////////////////////////////////////////////////////////////
class DependencyObjectInstance {
public:
	unsigned long id; ///< Unique long integer to identify a DependencyObjectInstance object
	string obj; ///< DependencyObject::Name of DependencyObject object which DependencyObjectInstance instantiates
	int direction; ///< Integer representing if DependencyObjectInstance is outward or inward w.r.t DependencyNode
	URL pou; ///< Parent Object URL
	URL tou; ///< Corresponding Object URL
	string cuk; ///< Corresponding udi key
	string mid; ///< Menu ID String
	string midL; ///< Menu ID String Long
	string amid; ///< Menu ID String (for all instances)
	string amidL; ///< Menu ID String Long (for all instances)
	bool editable; ///< Menu edit enabling flag
	bool visible; ///< Menu display enabling flag
	//////////////////////////////////////////////////
	/// \fn DependencyObjectInstance(unsigned long i, URL p, URL t, int d)
	/// \brief Constructor
	///
	/// - Sets DependencyObjectInstance::id : i\n
	/// - Sets DependencyObjectInstance::obj : p.stro\n
	/// - Sets DependencyObjectInstance::direction : d\n
	/// - Sets DependencyObjectInstance::pou : p\n
	/// - Sets DependencyObjectInstance::tou : t\n
	/// - Sets DependencyObjectInstance::cuk : t.str\n
	/// - Sets Default value for DependencyObjectInstance::mid\n
	/// - Sets Default value for DependencyObjectInstance::midL\n
	/// - Sets Default value for DependencyObjectInstance::amid\n
	/// - Sets Default value for DependencyObjectInstance::amidL\n
	/// - Sets Default value for DependencyObjectInstance::editable\n
	/// - Sets Default value for DependencyObjectInstance::visible
	///
	//////////////////////////////////////////////////
	DependencyObjectInstance(unsigned long i, URL p, URL t, int d);
	//////////////////////////////////////////////////
	/// \fn Display()
	/// \brief Displays DependencyObjectInstance object
	/// \see DisplayIf(unsigned int c=0)
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn DisplayIf(unsigned int c=0)
	/// \brief Condition based Displays DependencyObjectInstance object
	/// \param c is condition selector on DependencyObjectInstance::visible and
	/// DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see Display()
	//////////////////////////////////////////////////
	void DisplayIf(unsigned int c = 0);
	virtual ~DependencyObjectInstance();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYOBJECTINSTANCE_H_ */
