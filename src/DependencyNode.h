////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyNode.h
/// \brief	Header file for DependencyNode class
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

#ifndef DEPENDENCYNODE_H_
#define DEPENDENCYNODE_H_

#include "SmartDG.h"

///> Smart Transfer/InverseTransfer Function Pointer Type
typedef void (*SFPT)(string, vector<string>&,
		vector<vector<SmartDG::DependencyPort> >&);
///> A string map from DependencyNode::Name string to associated SFPT (Smart Transfer/InverseTransfer Function Pointer Type)
typedef std::unordered_map<std::string, SFPT> SmartDG__map;

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyNode
/// \brief DependencyNode class models a Node in the DependencyGraph
///
/// This class encapsulates DependencyPort objects representing various Input and Output
/// ports of the component. The class also manages FLTK graphic objects to populate the GUI.
////////////////////////////////////////////////////////////////////////////////
class DependencyNode {
public:
	string Name;	///< Name given to uniquely identify a DependencyNode object
	//////////////////////////////////////////////////
	/// \var isInstanceOf
	/// \brief Name of current component instance's source Component.
	///
	/// - Name of DependencyNode object that identifies the source Component.
	/// - This is same as DependencyNode::Name for source Components.
	///
	//////////////////////////////////////////////////
	string isInstanceOf;
	SFPT TFT; ///< Smart Transfer/InverseTransfer Function Pointer Type that gets assigned outside SmartDG library
	unsigned int x;	///< Stores x coordinate of location where FLTK elements associated with DependencyNode objects are initiated
	unsigned int y;	///< Stores y coordinate of location where FLTK elements associated with DependencyNode objects are initiated
	Fl_Group *Shape;///< Points to Fl_Group object that encapsulates all FLTK elements associated with DependencyNode object
	Fl_Group *ShapeI;///< Points to Fl_Group object that encapsulates all FLTK elements associated with Input DependencyPort objects
	Fl_Group *ShapeO;///< Points to Fl_Group object that encapsulates all FLTK elements associated with Output DependencyPort objects
	Fl_Menu_Bar *BarIn;	///< Points to Fl_Menu_Bar object that handles Node Edit menu associated with Input DependencyPorts
	Fl_Menu_Bar *BarOut;///< Points to Fl_Menu_Bar object that handles Node Edit menu associated with Output DependencyPorts
	//////////////////////////////////////////////////
	/// \var DP_In
	/// \brief A vector of input DependencyPort objects
	/// - DependencyNode::DP is filled from DependencyNode::DP_In and DependencyNode::DP_Out in function DependencyNode::Generate_DP\n
	/// - Once DependencyNode::DP is filled DependencyNode::DP_In and DependencyNode::DP_Out are cleared
	///
	/// \see DependencyNode::DP
	/// \see DependencyNode::DP_Out
	/// \see DependencyNode::Generate_DP()
	//////////////////////////////////////////////////
	vector<DependencyPort> DP_In;
	//////////////////////////////////////////////////
	/// \var DP_Out
	/// \brief A vector of output DependencyPort objects
	/// - DependencyNode::DP is filled from DependencyNode::DP_In and DependencyNode::DP_Out in function DependencyNode::Generate_DP\n
	/// - Once DependencyNode::DP is filled DependencyNode::DP_In and DependencyNode::DP_Out are cleared
	///
	/// \see DependencyNode::DP
	/// \see DependencyNode::DP_In
	/// \see DependencyNode::Generate_DP()
	//////////////////////////////////////////////////
	vector<DependencyPort> DP_Out;
	//////////////////////////////////////////////////
	/// \var DP
	/// \brief A 2 dimensional vector of input and output DependencyPort objects
	///
	/// - DP[0] ... Input DependencyPort objects\n
	/// - DP[1] ... Output DependencyPort objects\n
	/// - DependencyNode::DP is filled from DependencyNode::DP_In and DependencyNode::DP_Out in function DependencyNode::Generate_DP\n
	/// - Once DependencyNode::DP is filled DependencyNode::DP_In and DependencyNode::DP_Out are cleared
	///
	/// \see DependencyNode::DP_In
	/// \see DependencyNode::DP_Out
	/// \see DependencyNode::Generate_DP()
	//////////////////////////////////////////////////
	vector<vector<DependencyPort> > DP;
	//////////////////////////////////////////////////
	/// \fn DependencyNode()
	/// \brief Constructor
	///
	/// - Sets Default DependencyNode::Name\n
	/// - Calls DependencyNode::setNULL()
	///
	/// \see DependencyNode(string NodeName) \see setNULL()
	//////////////////////////////////////////////////
	DependencyNode();
	//////////////////////////////////////////////////
	/// \fn DependencyNode(string NodeName)
	/// \brief Constructor
	///
	/// - Sets DependencyNode::Name : argument NodeName\n
	/// - Calls DependencyNode::setNULL()
	///
	/// \see DependencyNode() \see setNULL()
	//////////////////////////////////////////////////
	DependencyNode(string NodeName);
	//////////////////////////////////////////////////
	/// \fn setNULL()
	/// \brief Called by Constructors, Sets FLTK graphic object pointers to NULL
	///
	/// - Called by all Constructors
	/// - Sets DependencyNode::Shape  : NULL\n
	/// - Sets DependencyNode::ShapeI : NULL\n
	/// - Sets DependencyNode::ShapeO : NULL\n
	/// - Sets DependencyNode::BarIn  : NULL\n
	/// - Sets DependencyNode::BarOut : NULL
	///
	/// \see DependencyNode() \see DependencyNode(string NodeName)
	//////////////////////////////////////////////////
	void setNULL();
	//////////////////////////////////////////////////
	/// \var Generate_DP()
	/// \brief Fills DependencyNode::DP from DependencyNode::DP_In and DependencyNode::DP_Out
	///
	/// - DP_In Input DependencyPort objects ---> DP[0]
	/// - DP_Out Output DependencyPort objects ---> DP[1]
	/// - DependencyNode::DP is filled from DependencyNode::DP_In and DependencyNode::DP_Out
	/// - Once DependencyNode::DP is filled DependencyNode::DP_In and DependencyNode::DP_Out are cleared
	///
	/// \see DependencyNode::DP
	/// \see DependencyNode::DP_In
	/// \see DependencyNode::DP_Out
	//////////////////////////////////////////////////
	void Generate_DP();
	//////////////////////////////////////////////////
	/// \fn Display()
	/// \brief Displays all DependencyPort objects in DependencyNode and their DependencyObject objects
	/// \see Display_URLs()
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn Display_URLs()
	/// \brief For all DependencyPort objects in DependencyNode, displays URL of their DependencyObject objects
	/// \see Display()
	//////////////////////////////////////////////////
	void Display_URLs();
	//////////////////////////////////////////////////
	/// \fn ~DependencyNode()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~DependencyNode();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYNODE_H_ */
