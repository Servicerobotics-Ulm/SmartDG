////////////////////////////////////////////////////////////////////////////////
///	\file	SmartDGGenerator.h
/// \brief	Header file for SmartDGGenerator class
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

#ifndef SMARTDGGENERATOR_H_
#define SMARTDGGENERATOR_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class SmartDGGenerator
/// \brief SmartDGGenerator class models a GUI System generator
///
/// This class encapsulates lists of GUI System elements to be generated. It carries
/// details of the current Mode, referenced Environment, Views, Nodes, Connectors and
/// a vector of DependencyDescriptor objects.
////////////////////////////////////////////////////////////////////////////////
class SmartDGGenerator {
	string Mode; ///< SmartDG_OBJECT_MODE or SmartDG_COMPONENT_MODE or SmartDG_DUAL_MODE
	Environment XE; ///< Referenced Environment object
	map<string, string> SystemViews; ///< DependencyObject specific views maps DependencyDescriptor::DependencyObjectName to itself
	map<string, string> SystemNodes; ///< DependencyNode instances in the current system mapped onto itself
	map<string, string> SystemNodesCIMDisplayStrings; ///< Component Instance Map (CIM) maps a component instance name string to its base component name string
	map<string, string> SystemConnectors; ///< Connectors in the current system mapped onto itself
	map<string, DependencyObject*> DependencyObjects; ///< DependencyObject in the current system mapped from string names to corresponding DependencyObject objects
	map<string, DependencyMonitor*> DependencyMonitors; ///< DependencyMonitor objects to handle DependencyObject specific views in System projects
	map<string, DependencyMonitor*> ComponentMonitors; ///< DependencyMonitor objects to handle DependencyNode views in System projects
	vector<SmartDG::DependencyDescriptor> DD; ///< A vector of DependencyDescriptor objects in System projects
	string ComponentName; ///< Component name in Component development project
	DependencyMonitor* ComponentDeveloper; ///< DependencyMonitor object to handle Component development project
	int setexit; ///< Environment Consistency Check result sets this value to indicate program exit
	//////////////////////////////////////////////////
	/// \fn SystemDevelopmentMode(string &SystemProjectName, vector<DependencyDescriptor> &DD, map<string, GUIPoint> &GUI, map<string, string> CIM)
	/// \brief Generates GUI System elements for System project
	///	\param [in] SystemProjectName is the name of system project
	///	\param [in] DD is a vector of DependencyDescriptor objects
	///	\param [in] GUI is a map from Component/DependencyNode name to its coordinate in the component architecture diagram
	///	\param [in] CIM is Component Instance Map is component instance name string to its base component name string
	/// \see ComponentDevelopmentMode()
	//////////////////////////////////////////////////
	void SystemDevelopmentMode(string &SystemProjectName,
			vector<DependencyDescriptor> &DD, map<string, GUIPoint> &GUI,
			map<string, string> CIM);
	//////////////////////////////////////////////////
	/// \fn ComponentDevelopmentMode()
	/// \brief Generates GUI System elements for Component development project
	/// \see SystemDevelopmentMode(string &SystemProjectName, vector<DependencyDescriptor> &DD, map<string, GUIPoint> &GUI, map<string, string> CIM)
	//////////////////////////////////////////////////
	void ComponentDevelopmentMode();
	//////////////////////////////////////////////////
	/// \fn VFind(const vector<T> & V, const T & E)
	/// \brief Checks presence of an element E in a vector V of type T
	/// \param [in] V is the vector of type T
	/// \param [in] E is the element of type T which is to be searched in vector V
	/// \return boolean indicating if element E is found in V or not
	//////////////////////////////////////////////////
	template<typename T>
	bool VFind(const vector<T> & V, const T & E);
	//////////////////////////////////////////////////
	/// \fn ErrorExit(const T Item, string Message = "ITEM")
	/// \brief Prints error message when Item is not found in Environment (SmartDGGenerator::XE)
	/// \param [in] Item is the item not found in SmartDGGenerator::XE
	/// \param [in] Message is string that is printed alongside the error message (Default value "ITEM")
	//////////////////////////////////////////////////
	template<typename T>
	void ErrorExit(const T Item, string Message = "ITEM");
public:
	//////////////////////////////////////////////////
	/// \fn SmartDGGenerator(string SystemProjectName, vector<DependencyDescriptor> DD,	map<string, GUIPoint> GUI, map<string, string> CIM, string mode)
	/// \brief Constructor
	///	\param [in] SystemProjectName is the name of system project
	///	\param [in] DD is a vector of DependencyDescriptor objects
	///	\param [in] GUI is a map from Component/DependencyNode name to its coordinate in the component architecture diagram
	///	\param [in] CIM is Component Instance Map is component instance name string to its base component name string
	///	\param [in] mode is SmartDG_OBJECT_MODE or SmartDG_COMPONENT_MODE or SmartDG_DUAL_MODE
	///
	/// - Constructor for System Project
	///
	/// \see  SmartDGGenerator(string componentName, string mode)
	//////////////////////////////////////////////////
	SmartDGGenerator(string SystemProjectName, vector<DependencyDescriptor> DD,
			map<string, GUIPoint> GUI, map<string, string> CIM, string mode);
	//////////////////////////////////////////////////
	/// \fn SmartDGGenerator(string componentName, string mode)
	/// \brief Constructor
	/// \param [in] componentName is the name of component development project
	/// \param [in] mode is SmartDG_OBJECT_MODE or SmartDG_COMPONENT_MODE or SmartDG_DUAL_MODE
	///
	/// - Constructor for Component development Project
	///
	/// \see  SmartDGGenerator(string SystemProjectName, vector<DependencyDescriptor> DD,	map<string, GUIPoint> GUI, map<string, string> CIM, string mode)
	//////////////////////////////////////////////////
	SmartDGGenerator(string componentName, string mode);
	//////////////////////////////////////////////////
	/// \fn Show(string displaymode = SmartDG_DUAL_DISPLAYMODE)
	/// \brief Calls appropriate DependencyMonitor::Show for System or Component development project
	/// \param [in] displaymode is SmartDG_FLTK_DISPLAYMODE or SmartDG_LITE_DISPLAYMODE or SmartDG_DUAL_DISPLAYMODE (Default)
	//////////////////////////////////////////////////
	void Show(string displaymode = SmartDG_DUAL_DISPLAYMODE);
	//////////////////////////////////////////////////
	/// \fn Display(bool showwiki = false)
	/// \brief Displays Current System elements
	/// \param [in] showwiki is a boolean flag indicating whether to display Wiki or not
	//////////////////////////////////////////////////
	void Display(bool showwiki = false);
	//////////////////////////////////////////////////
	/// \fn ~SmartDGGenerator()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~SmartDGGenerator();
};

} /* namespace SmartDG */

#endif /* SMARTDGGENERATOR_H_ */
