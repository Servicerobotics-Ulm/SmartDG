////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyGraph.h
/// \brief	Header file for DependencyGraph class
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

#ifndef DEPENDENCYGRAPH_H_
#define DEPENDENCYGRAPH_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyGraph
/// \brief DependencyGraph class models dependency graph over a network
///
/// This class encapsulates a vector of DependencyNode objects  and various maps
/// to encode DependencyObject specific dependencies amongst DependencyNode objects.\n
/// The class includes several functions and data containers to initiate, record, manage
///  and  display the aforementioned  entities.
////////////////////////////////////////////////////////////////////////////////
class DependencyGraph {
public:
	string Name; ///< Name given to uniquely identify a DependencyGraph object
	vector<DependencyNode> DN; ///< A vector of DependencyNode objects
	//////////////////////////////////////////////////
	/// \var ulm
	/// \brief URL list map:\n
	/// A 4 dimensional string map from
	/// [DependencyNode Name]["In"/"Out"][DependencyPort Name][DependencyObject Name]
	/// to corresponding URL.
	//////////////////////////////////////////////////
	map<string, map<string, map<string, map<string, URL> > > > ulm;
	//////////////////////////////////////////////////
	/// \var ulmi
	/// \brief URL list map integer:\n
	/// A 4 dimensional integer map from
	/// [DependencyNode Index][0/1][DependencyPort Index][DependencyObject Index]
	/// to corresponding URL.
	//////////////////////////////////////////////////
	map<unsigned int,
			map<unsigned int, map<unsigned int, map<unsigned int, URL> > > > ulmi;
	vector<string> dobjs; ///< A vector of all unique DependencyObject objects in the DependencyGraph
	map<string, vector<Dependency> > View; ///< A string map from [DependencyObject Name] to a vector of corresponding Dependency objects
	DependencyObjectInstances DOI; ///< A DependencyObjectInstances object to encapsulate all dependency object instances
	//////////////////////////////////////////////////
	/// \fn DependencyGraph()
	/// \brief Constructor
	///
	/// - Sets Default Name\n
	///
	/// \see DependencyGraph(string GraphName)
	//////////////////////////////////////////////////
	DependencyGraph();
	//////////////////////////////////////////////////
	/// \fn DependencyGraph(string GraphName)
	/// \brief Constructor
	///
	/// - Sets Name to GraphName\n
	///
	/// \see DependencyGraph()
	//////////////////////////////////////////////////
	DependencyGraph(string GraphName);
	//////////////////////////////////////////////////
	/// \fn void Generate_URLs()
	/// \brief Generates and fills URL objects for all DependencyObject objects in DN; Generates ulm and ulmi
	///
	/// - Sets URL objects for all DependencyObject objects in DependencyGraph\n
	/// - Fills ulm (URL list map) for all DependencyObject URLs\n
	/// - Fills ulmi (URL list map integer) for all DependencyObject URLs
	///
	/// \see Dependency()
	//////////////////////////////////////////////////
	void Generate_URLs();
	//////////////////////////////////////////////////
	/// \fn AddDependency(string name, string fni, string fpi, string foi, string tni, string tpi, string toi)
	/// \brief Adds a Dependency object using connector name and individual indexes  (To and From) minus i/o index
	/// \param [in] name 	is connector over which the dependency is established
	/// \param [in] fni		is node index of source
	/// \param [in] fpi		is port index of source
	/// \param [in] foi		is object index of source
	/// \param [in] tni		is node index of target
	/// \param [in] tpi		is port index of target
	/// \param [in] toi		is object index of target
	///
	/// - Makes a Dependency object tmp\n
	/// - Calls AddDependency(Dependency &tmp)
	///
	/// \see AddDependency(string name, DependencyNode fn, DependencyPort fp, DependencyObject ob, DependencyNode tn, DependencyPort tp)
	/// \see AddDependency(Dependency &tmp)
	//////////////////////////////////////////////////
	void AddDependency(string name, string fni, string fpi, string foi,
			string tni, string tpi, string toi);
	//////////////////////////////////////////////////
	/// \fn AddDependency(string name, DependencyNode fn, DependencyPort fp, DependencyObject ob, DependencyNode tn, DependencyPort tp)
	/// \brief Adds a Dependency object using connector name and individual objects (DependencyNode, DependencyPort, DependencyObject)
	/// \param [in] name 	is connector over which the dependency is established
	/// \param [in] fn		is DependencyNode object of source
	/// \param [in] fp		is DependencyPort object of source
	/// \param [in] ob		is DependencyObject object of source [Should be same as that of target]
	/// \param [in] tn		is DependencyNode object of target
	/// \param [in] tp		is DependencyPort object of target
	///
	/// - Makes a Dependency object tmp\n
	/// - Calls AddDependency(Dependency &tmp)
	///
	/// \see AddDependency(string name, string fni, string fpi, string foi, string tni, string tpi, string toi)
	/// \see AddDependency(Dependency &tmp)
	//////////////////////////////////////////////////
	void AddDependency(string name, DependencyNode fn, DependencyPort fp,
			DependencyObject ob, DependencyNode tn, DependencyPort tp);
	//////////////////////////////////////////////////
	/// \fn AddDependency(Dependency &tmp)
	/// \brief Adds a Dependency object
	/// \param [in] tmp 	is a Dependency object
	///
	///	- Finds DependencyObject object's Name and sets obName to it\n
	///	- Adds a new udi entry (Dependency Object's Unique Dependency Instance) in Source Node and sets its default value\n
	///	- Adds a new udi entry (Dependency Object's Unique Dependency Instance) in Target Node and sets its default value\n
	///	- Add DependencyObject object to dobjs if not already present in View\n
	///	- Add the new Dependency object to DOI (DependencyObjectInstances object to encapsulate all dependency object instances)\n
	///	- Add the new Dependency object to View (A string map from DependencyObject object's Name to a vector of corresponding Dependency objects)
	///
	/// \see AddDependency(string name, string fni, string fpi, string foi, string tni, string tpi, string toi)
	/// \see AddDependency(string name, DependencyNode fn, DependencyPort fp, DependencyObject ob, DependencyNode tn, DependencyPort tp)
	//////////////////////////////////////////////////
	void AddDependency(Dependency &tmp);
	//////////////////////////////////////////////////
	/// \fn void Display()
	/// \brief Display function for the complete DependencyGraph
	///
	/// - Calls DependencyNode::Display function for each DependencyNode in DN\n
	///
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn void Display_URLs()
	/// \brief Display function for all URL objects in DependencyGraph
	///
	/// - Calls DependencyNode::Display_URLs function for each DependencyNode in DN\n
	///
	/// \see Display()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void Display_URLs();
	//////////////////////////////////////////////////
	/// \fn void Display_ulm()
	/// \brief Display function for ulm (URL list map) in DependencyGraph
	///
	/// - Displays the complete ulm (URL list map)\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void Display_ulm();
	//////////////////////////////////////////////////
	/// \fn void Display_ulmi()
	/// \brief Display function for ulm (URL list map integer) in DependencyGraph
	///
	/// - Displays the complete ulmi (URL list map integer)\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void Display_ulmi();
	//////////////////////////////////////////////////
	/// \fn void DisplayDependency(string ob)
	/// \brief Display function for all Dependency objects corresponding to DependencyObject ob in DependencyGraph
	///
	/// - Calls Dependency::Display function for each Dependency in View[ob]\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void DisplayDependency(string ob);
	//////////////////////////////////////////////////
	/// \fn void DisplayDependencyMini(string ob)
	/// \brief Mini Display function for all Dependency objects corresponding to DependencyObject ob in DependencyGraph
	///
	/// - Calls Dependency::DisplayMini function for each Dependency in View[ob]\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void DisplayDependencyMini(string ob);
	//////////////////////////////////////////////////
	/// \fn void DisplayDependency()
	/// \brief Display function for all Dependency objects in DependencyGraph
	///
	/// - Calls DisplayDependency(string ob) function for all DependencyObject names in View\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependencyValues(string ob)
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void DisplayDependency();
	//////////////////////////////////////////////////
	/// \fn void DisplayDependencyValues(string ob)
	/// \brief Display function for values of all Dependency objects corresponding to DependencyObject ob in DependencyGraph
	///
	/// - Calls Dependency::DisplayValues function for each Dependency in View[ob]\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues()
	//////////////////////////////////////////////////
	void DisplayDependencyValues(string ob);
	//////////////////////////////////////////////////
	/// \fn void DisplayDependencyValues()
	/// \brief Display function for values of all Dependency objects in DependencyGraph
	///
	/// - Calls DisplayDependencyValues(string ob) function for all DependencyObject names in View\n
	///
	/// \see Display()
	/// \see Display_URLs()
	/// \see Display_ulm()
	/// \see Display_ulmi()
	/// \see DisplayDependency(string ob)
	/// \see DisplayDependencyMini(string ob)
	/// \see DisplayDependency()
	/// \see DisplayDependencyValues(string ob)
	//////////////////////////////////////////////////
	void DisplayDependencyValues();
	//////////////////////////////////////////////////
	/// \fn ~DependencyGraph()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyGraph();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYGRAPH_H_ */
