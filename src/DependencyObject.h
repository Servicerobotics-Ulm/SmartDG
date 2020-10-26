////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObject.h
/// \brief	Header file for DependencyObject class
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

#ifndef DEPENDENCYOBJECT_H_
#define DEPENDENCYOBJECT_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyObject
/// \brief DependencyObject class models a Dependency object in the DependencyGraph
///
/// This class encapsulates DependencyDataPackage objects for all instances of DependencyObject.
/// The class also manages FLTK graphic objects to populate the GUI.
////////////////////////////////////////////////////////////////////////////////
class DependencyObject {
public:
	string Name; ///< Name given to uniquely identify a DependencyObject object
	URL url;	///< URL object to uniquely identify a DependencyObject object
	DependencyDataPackage defaultdata; ///< Default data object for DependencyDataPackage associated with Unique Dependency Instances (udi)
	map<string, DependencyDataPackage> udi;	///< Dependency Object's Unique Dependency Instance mapped through URL::str of correspondent as the key
	map<string, GUIConnection*> udiShape;///< Points to GUIConnection object used to populate Unique Dependency Instance in GUI.
	Fl_Group *Shape;///< Points to Fl_Group object used to group all FLTK graphic elements associated with DependencyObject object.
	//////////////////////////////////////////////////
	/// \fn DependencyObject()
	/// \brief Constructor
	///
	/// - Sets Default DependencyObject::Name\n
	/// - Calls DependencyNode::setup()
	///
	/// \see DependencyObject(string DOName) \see setup()
	//////////////////////////////////////////////////
	DependencyObject();
	//////////////////////////////////////////////////
	/// \fn DependencyObject(string DOName)
	/// \brief Constructor
	///
	/// - Sets DependencyObject::Name : argument DOName\n
	/// - Calls DependencyNode::setup()
	///
	/// \see DependencyObject() \see setup()
	//////////////////////////////////////////////////
	DependencyObject(string DOName);
	//////////////////////////////////////////////////
	/// \fn setup()
	/// \brief Called by Constructors, Sets FLTK graphic object pointers to NULL
	///
	/// - Called by all Constructors\n
	/// - Sets DependencyNode::Shape  : NULL
	///
	/// \see DependencyObject() \see DependencyObject(string DOName)
	//////////////////////////////////////////////////
	void setup();
	//////////////////////////////////////////////////
	/// \fn Set(DependencyDataPackage d, string instance)
	/// \brief Setter function for udi (Dependency Object's Unique Dependency Instances)
	/// \param [in] d is the DependencyDataPackage object to be set to udi
	/// \param [in] instance is the udi to be set
	/// \see Set(DependencyDataPackage d)
	/// \see Get(string instance) \see Get()
	//////////////////////////////////////////////////
	void Set(DependencyDataPackage d, string instance);
	//////////////////////////////////////////////////
	/// \fn Set(DependencyDataPackage d)
	/// \brief Setter function for udi (Dependency Object's Unique Dependency Instances)
	/// \param [in] d is the DependencyDataPackage object to be set to all udi entries
	/// \see Set(DependencyDataPackage d, string instance)
	/// \see Get(string instance) \see Get()
	//////////////////////////////////////////////////
	void Set(DependencyDataPackage d);
	//////////////////////////////////////////////////
	/// \fn Get(string instance)
	/// \brief Getter function for udi (Dependency Object's Unique Dependency Instances)
	/// \param [in] instance is the udi to be get
	/// \return DependencyDataPackage get value
	/// \see Set(DependencyDataPackage d, string instance) \see Set(DependencyDataPackage d)
	/// \see Get()
	//////////////////////////////////////////////////
	DependencyDataPackage Get(string instance);
	//////////////////////////////////////////////////
	/// \fn Get()
	/// \brief Getter function for udi (Dependency Object's Unique Dependency Instances)
	/// \return DependencyDataPackage get value
	///
	/// - Returns DependencyDataPackage get value of the first udi entry irrespective of number of udi entries
	///
	/// \see Set(DependencyDataPackage d, string instance) \see Set(DependencyDataPackage d)
	/// \see Get(string instance)
	//////////////////////////////////////////////////
	DependencyDataPackage Get();
	//////////////////////////////////////////////////
	/// \fn GetBias()
	/// \brief Returns an integer value between 0 and 10 representing the collective Bias towards "true" in all udi entries
	/// \return DependencyDataPackage get value
	///
	/// - Returns round ( ((Number of true values in udi entries) / (total number of udi entries)) * 10 )\n
	/// - Returns -1 when there are no udi entries
	//////////////////////////////////////////////////
	int GetBias();
	//////////////////////////////////////////////////
	/// \fn ~DependencyObject()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyObject();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYOBJECT_H_ */
