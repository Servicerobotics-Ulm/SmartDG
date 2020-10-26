////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObjectInstances.h
/// \brief	Header file for DependencyObjectInstances class
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

#ifndef DEPENDENCYOBJECTINSTANCES_H_
#define DEPENDENCYOBJECTINSTANCES_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyObjectInstances
/// \brief DependencyObjectInstances class models and manages a collection of Dependency Object's Unique Dependency Instance
///
/// This class encapsulates a vector of DependencyObjectInstance objects as DependencyObjectInstances::I.
/// An object of this class is found in DependencyGraph as DependencyGraph::DOI which encapsulate all
/// dependency object instances pertaining to a DependencyGraph object.\n
/// This class carries method to derive the two DependencyObjectInstance objects from an
/// input Dependency object. It carries display functions and several data variables and functions to
/// implement menu context visibility and editability for each of the constituent DependencyObjectInstance objects
/// in DependencyObjectInstances::I.
////////////////////////////////////////////////////////////////////////////////
class DependencyObjectInstances {
public:
	static unsigned long count; ///< Static class variable that keeps count for DependencyObjectInstances objects in DependencyObjectInstances::I
	vector<DependencyObjectInstance> I; ///< A vector of of Dependency Object's Unique Dependency Instance.
	bool UseContext; ///< Boolean flag to enable/disable the use of Context based setting of visibility and editability for DependencyObjectInstance objects.
	string ViewContext; ///< Context string for DependencyView selection
	string NodeContext; ///< Context string for DependencyNode selection
	string IOContext; ///< Context string for I/O DependencyPort group selection
	string PortContext; ///< Context string for DependencyPort selection
	string ObjectContext; ///< Context string for DependencyObject selection
	//////////////////////////////////////////////////
	/// \fn DependencyObjectInstances()
	/// \brief Constructor
	///
	/// - Calls DependencyObjectInstances::SetContext() with all default values
	///
	//////////////////////////////////////////////////
	DependencyObjectInstances();
	//////////////////////////////////////////////////
	/// \fn Add(Dependency &d)
	/// \brief method to derive the two DependencyObjectInstance objects from an input Dependency object.
	/// \param [in] d is the input Dependency object
	///
	/// - Adds Dependency::From to DependencyObjectInstances::I\n
	/// - Adds Dependency::To to DependencyObjectInstances::I
	///
	//////////////////////////////////////////////////
	void Add(Dependency &d);
	//////////////////////////////////////////////////
	/// \fn Display()
	/// \brief Calls DependencyObjectInstance::Display() for each DependencyObjectInstance object in DependencyObjectInstances::I
	/// \see DependencyObjectInstance::Display() \see DisplayIf(unsigned int c=0)
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn DisplayIf(unsigned int c=0)
	/// \brief Calls DependencyObjectInstance::DisplayIf(unsigned int c=0) for each DependencyObjectInstance object in DependencyObjectInstances::I
	///
	/// \param [in] c is condition selector on DependencyObjectInstance::visible and
	/// DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see DependencyObjectInstance::DisplayIf(unsigned int c=0) \see Display()
	//////////////////////////////////////////////////
	void DisplayIf(unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn SetContext(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \brief Sets context selector strings from given arguments
	/// \param [in] v is context selector string for DependencyObjectInstances::ViewContext (Default : "ALL")
	/// \param [in] n is context selector string for DependencyObjectInstances::NodeContext (Default : "ALL")
	/// \param [in] i is context selector string for DependencyObjectInstances::IOContext (Default : "ALL")
	/// \param [in] p is context selector string for DependencyObjectInstances::PortContext (Default : "ALL")
	/// \param [in] o is context selector string for DependencyObjectInstances::ObjectContext (Default : "ALL")
	///
	/// - Default value for v is "ALL"\n
	/// - Default value for n is "ALL"\n
	/// - Default value for i is "ALL"\n
	/// - Default value for p is "ALL"\n
	/// - Default value for o is "ALL"
	///
	/// \see SetContextHierarchy(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see ResetContext(bool b=false)
	/// \see DisplayContext()
	//////////////////////////////////////////////////
	void SetContext(string v = "ALL", string n = "ALL", string i = "ALL",
			string p = "ALL", string o = "ALL");
	//////////////////////////////////////////////////
	/// \fn SetContextHierarchy(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \brief Hierarchically sets context selector strings from given arguments
	/// \param [in] v is context selector string for DependencyObjectInstances::ViewContext (Default : "ALL")
	/// \param [in] n is context selector string for DependencyObjectInstances::NodeContext (Default : "ALL")
	/// \param [in] i is context selector string for DependencyObjectInstances::IOContext (Default : "ALL")
	/// \param [in] p is context selector string for DependencyObjectInstances::PortContext (Default : "ALL")
	/// \param [in] o is context selector string for DependencyObjectInstances::ObjectContext (Default : "ALL")
	///
	/// - Default value for v is "ALL"\n
	/// - Default value for n is "ALL"\n
	/// - Default value for i is "ALL"\n
	/// - Default value for p is "ALL"\n
	/// - Default value for o is "ALL"
	///
	/// \see SetContext(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see ResetContext(bool b=false)
	/// \see DisplayContext()
	//////////////////////////////////////////////////
	void SetContextHierarchy(string v = "ALL", string n = "ALL", string i =
			"ALL", string p = "ALL", string o = "ALL");
	//////////////////////////////////////////////////
	/// \fn ResetContext(bool b=false)
	/// \brief Resets selector strings and DependencyObjectInstances::UseContext flag
	/// \param [in] b is value to be set for DependencyObjectInstances::UseContext
	///
	/// - Default value for b is false
	/// - Sets DependencyObjectInstances::UseContext : b\n
	/// - Sets DependencyObjectInstances::ViewContext : "ALL"\n
	/// - Sets DependencyObjectInstances::NodeContext = "ALL"\n
	/// - Sets DependencyObjectInstances::IOContext = "ALL"\n
	/// - Sets DependencyObjectInstances::PortContext = "ALL"\n
	/// - Sets DependencyObjectInstances::ObjectContext = "ALL"
	///
	/// \see SetContextHierarchy(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see SetContext(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see DisplayContext()
	//////////////////////////////////////////////////
	void ResetContext(bool b = false);
	//////////////////////////////////////////////////
	/// \fn DisplayContext()
	/// \brief Display current context selector strings
	/// \see SetContextHierarchy(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see SetContext(string v="ALL",string n="ALL",string i="ALL",string p="ALL",string o="ALL")
	/// \see ResetContext(bool b=false)
	//////////////////////////////////////////////////
	void DisplayContext();
	//////////////////////////////////////////////////
	/// \fn setf(unsigned int i, bool b, unsigned int c=0)
	/// \brief Base function called to set DependencyObjectInstance::visible and DependencyObjectInstance::editable flags for all DependencyObjectInstance objects in DependencyObjectInstances::I
	/// \param [in] i is index of DependencyObjectInstance object to be Set in DependencyObjectInstances::I
	/// \param [in] b is Boolean value to be set to DependencyObjectInstances::I [i]
	/// \param [in] c is condition selector on DependencyObjectInstance::visible and DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see SetFlagContext(bool b, unsigned int c=0)
	/// \see SetFlagURL(string u, bool b, unsigned int c=0)
	/// \see SetFlagMenuIDString(string m, bool b, unsigned int c=0)
	//////////////////////////////////////////////////
	void setf(unsigned int i, bool b, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn SetFlagContext(bool b, unsigned int c=0)
	/// \brief Set flag Value:b, Scope: Context, Condition: c
	/// \param [in] b is Boolean value to be set to DependencyObjectInstances::I [i]
	/// \param [in] c is condition selector on DependencyObjectInstance::visible and DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see setf(unsigned int i, bool b, unsigned int c=0)
	/// \see SetFlagURL(string u, bool b, unsigned int c=0)
	/// \see SetFlagMenuIDString(string m, bool b, unsigned int c=0)
	//////////////////////////////////////////////////
	void SetFlagContext(bool b, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn SetFlagURL(string u, bool b, unsigned int c=0)
	/// \brief Set flag Value:b, Scope: DependencyObject associated with the given URL, Condition: c
	/// \param [in] u is URL string of DependencyObject which is to be set
	/// \param [in] b is Boolean value to be set to DependencyObjectInstances::I [i]
	/// \param [in] c is condition selector on DependencyObjectInstance::visible and DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see setf(unsigned int i, bool b, unsigned int c=0)
	/// \see SetFlagContext(bool b, unsigned int c=0)
	/// \see SetFlagMenuIDString(string m, bool b, unsigned int c=0)
	//////////////////////////////////////////////////
	void SetFlagURL(string u, bool b, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn SetFlagMenuIDString(string m, bool b, unsigned int c=0)
	/// \brief Set flag Value:b, Scope: DependencyObject associated with the given Menu selection string, Condition: c
	/// \param [in] m is Menu selection string of DependencyObject which is to be set
	/// \param [in] b is Boolean value to be set to DependencyObjectInstances::I [i]
	/// \param [in] c is condition selector on DependencyObjectInstance::visible and DependencyObjectInstance::editable flags
	///
	/// - c : 0 : Display if both flags are true\n
	/// - c : 1 : Display if DependencyObjectInstance::visible is true\n
	/// - c : 2 : Display if DependencyObjectInstance::editable is true
	///
	/// \see setf(unsigned int i, bool b, unsigned int c=0)
	/// \see SetFlagContext(bool b, unsigned int c=0)
	/// \see SetFlagURL(string u, bool b, unsigned int c=0)
	//////////////////////////////////////////////////
	void SetFlagMenuIDString(string m, bool b, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn ~DependencyObjectInstances()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyObjectInstances();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYOBJECTINSTANCES_H_ */
