////////////////////////////////////////////////////////////////////////////////
///	\file	Dependency.h
/// \brief	Header file for Dependency class
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

#ifndef DEPENDENCY_H_
#define DEPENDENCY_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class Dependency
/// \brief Dependency class models data dependency over a connection
///
/// This class encapsulates URLs of a source and target dependency object instance
/// over a named connection.
////////////////////////////////////////////////////////////////////////////////
class Dependency {
public:
	string Name;///< Name of connector over which the dependency is established
	URL From;		///< Source Dependency URL
	URL To;			///< Target Dependency URL
	bool errorflag;	///< Set to true when InOutIndex for either of the two URLs is wrong
	GUIConnection *con;	///< Points to GUIConnection object that materializes this dependency
	//////////////////////////////////////////////////
	/// \fn Dependency()
	/// \brief Constructor
	///
	/// - Sets Default Name\n
	/// - Sets Default From and To URLs\n
	/// - errorflag set to true by default
	///
	/// \see Dependency(string name, URL f, URL t)
	/// \see Dependency(string name, unsigned int fni, unsigned int fioi,unsigned int fpi, unsigned int foi, unsigned int tni,unsigned int tioi, unsigned int tpi, unsigned int toi)
	/// \see Dependency(string name, unsigned int fni, unsigned int fpi,unsigned int foi, unsigned int tni, unsigned int tpi,unsigned int toi)
	//////////////////////////////////////////////////
	Dependency();
	//////////////////////////////////////////////////
	/// \fn Dependency(string name, URL f, URL t)
	/// \brief Constructor using Name and URLs (To and From)
	/// \param [in] name 	is connector over which the dependency is established
	/// \param [in] f 		is URL of source
	/// \param [in] t		is URL of target
	///
	/// - Error if connection originates from an input port or ends at an output port
	///
	/// \see Dependency()
	/// \see Dependency(string name, unsigned int fni, unsigned int fioi,unsigned int fpi, unsigned int foi, unsigned int tni,unsigned int tioi, unsigned int tpi, unsigned int toi)
	/// \see Dependency(string name, unsigned int fni, unsigned int fpi,unsigned int foi, unsigned int tni, unsigned int tpi,unsigned int toi)
	//////////////////////////////////////////////////
	Dependency(string name, URL f, URL t);
	//////////////////////////////////////////////////
	/// \fn Dependency(string name, unsigned int fni, unsigned int fioi,
	///		unsigned int fpi, unsigned int foi, unsigned int tni,
	///		unsigned int tioi, unsigned int tpi, unsigned int toi)
	/// \brief Constructor using Name and individual indexes  (To and From)
	/// \param [in] name 	is connector over which the dependency is established
	/// \param [in] fni		is node index of source
	/// \param [in] fioi	is i/o index of source
	/// \param [in] fpi		is port index of source
	/// \param [in] foi		is object index of source
	/// \param [in] tni		is node index of target
	/// \param [in] tioi	is i/o index of target
	/// \param [in] tpi		is port index of target
	/// \param [in] toi		is object index of target
	///
	/// - Sets From and To URLs\n
	/// - errorflag set to true before call to Dependency(string name, URL f, URL t)
	///
	/// \see Dependency()
	/// \see Dependency(string name, URL f, URL t)
	/// \see Dependency(string name, unsigned int fni, unsigned int fpi,unsigned int foi, unsigned int tni, unsigned int tpi,unsigned int toi)
	//////////////////////////////////////////////////
	Dependency(string name, unsigned int fni, unsigned int fioi,
			unsigned int fpi, unsigned int foi, unsigned int tni,
			unsigned int tioi, unsigned int tpi, unsigned int toi);
	//////////////////////////////////////////////////
	/// \fn Dependency(string name, unsigned int fni, unsigned int fpi,
	///		unsigned int foi, unsigned int tni, unsigned int tpi,
	///		unsigned int toi)
	/// \brief Constructor using Name and individual indexes  (To and From) without i/o index and errorcheck
	/// \param [in] name 	is connector over which the dependency is established
	/// \param [in] fni		is node index of source
	/// \param [in] fpi		is port index of source
	/// \param [in] foi		is object index of source
	/// \param [in] tni		is node index of target
	/// \param [in] tpi		is port index of target
	/// \param [in] toi		is object index of target
	///
	/// - Sets From and To URLs\n
	/// - errorflag set to true before call to Dependency(string name, URL f, URL t)
	///
	/// \see Dependency()
	/// \see Dependency(string name, URL f, URL t)
	/// \see Dependency(string name, unsigned int fni, unsigned int fioi,unsigned int fpi, unsigned int foi, unsigned int tni,unsigned int tioi, unsigned int tpi, unsigned int toi)
	//////////////////////////////////////////////////
	Dependency(string name, unsigned int fni, unsigned int fpi,
			unsigned int foi, unsigned int tni, unsigned int tpi,
			unsigned int toi);
	//////////////////////////////////////////////////
	/// \var void (*TF)(vector<vector<DependencyPort> >&,
	///		vector<vector<DependencyPort> >&, Dependency &)
	/// \brief Function pointer to connector's transfer function
	///
	/// By default this is assigned to point to &SmartDG::TransferFunctionsIdealConnector::Instance001::TF\n
	/// In case the connector is a dependency node, this function pointer is later assigned to
	/// transfer function associated with the connector.
	///
	/// \param [in, out] SourcePorts
	/// \param [in, out] TargetPorts
	/// \param [in, out] this Dependency class object
	/// \see void (*FT)(vector<vector<DependencyPort> >&,vector<vector<DependencyPort> >&, Dependency &);
	//////////////////////////////////////////////////
	void (*TF)(vector<vector<DependencyPort> >&,
			vector<vector<DependencyPort> >&, Dependency &);
	//////////////////////////////////////////////////
	/// \var void (*FT)(vector<vector<DependencyPort> >&,
	///		vector<vector<DependencyPort> >&, Dependency &)
	/// \brief Function pointer to connector's inverse transfer function
	///
	/// By default this is assigned to point to &SmartDG::TransferFunctionsIdealConnector::Instance001::FT\n
	/// In case the connector is a dependency node, this function pointer is later assigned to
	/// inverse transfer function associated with the connector.
	///
	/// \param [in, out] SourcePorts
	/// \param [in, out] TargetPorts
	/// \param [in, out] this Dependency class object
	/// \see void (*TF)(vector<vector<DependencyPort> >&,vector<vector<DependencyPort> >&, Dependency &);
	//////////////////////////////////////////////////
	void (*FT)(vector<vector<DependencyPort> >&,
			vector<vector<DependencyPort> >&, Dependency &);
	//////////////////////////////////////////////////
	/// \fn void setNULL()
	///
	/// - Sets Transfer/Inverse transfer Function pointers to ideal connector's Transfer/Inverse transfer Functions\n
	/// - Sets GUIConnection con to null
	///
	/// \brief Sets default values for TF, FT and con pointers
	//////////////////////////////////////////////////
	void setNULL();
	//////////////////////////////////////////////////
	/// \fn void Display()
	/// \brief Display function
	///
	/// - Displays full URLs\n
	/// - {Connector} Source URL --- DependencyObject ---> Target URL
	///
	/// \see DisplayMini()
	/// \see DisplayValues(vector<DependencyNode> &DN)
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn void DisplayMini()
	/// \brief Display function mini version
	///
	/// - Displays {Connector} Source DependencyNode . Source DependencyPort --- DependencyObject ---> Target DependencyNode . Target DependencyPort
	///
	/// \see Display()
	/// \see DisplayValues(vector<DependencyNode> &DN)
	//////////////////////////////////////////////////
	void DisplayMini();
	//////////////////////////////////////////////////
	/// \fn void DisplayValues(vector<DependencyNode> &DN)
	/// \brief Display function with values across the dependency
	///
	/// - Displays full URLs with Values\n
	/// - {Connector} Source URL{Source DependencyDataPackage} --- DependencyObject ---> Target URL{Target DependencyDataPackage}
	///
	/// \see Display()
	/// \see DisplayMini()
	//////////////////////////////////////////////////
	void DisplayValues(vector<DependencyNode> &DN);
	//////////////////////////////////////////////////
	/// \fn ~Dependency()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~Dependency();
};

} /* namespace SmartDG */

#endif /* DEPENDENCY_H_ */
