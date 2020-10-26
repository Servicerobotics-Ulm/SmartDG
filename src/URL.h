////////////////////////////////////////////////////////////////////////////////
///	\file	URL.h
/// \brief	Header file for URL class
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

#ifndef URL_H_
#define URL_H_

using namespace std;

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class URL
/// \brief URL class models a Uniform Resource Locator for a deployed DependencyObject object.
///
/// This class encapsulates 4 integers and corresponding 4 string identifiers to
/// Uniquely identify a DependencyObject object deployed at a DependencyPort object
/// of a DependencyNode object.
////////////////////////////////////////////////////////////////////////////////
class URL {
public:
	unsigned int NodeIndex;	///< Index of current DependencyNode object in DependencyGraph::DN
	unsigned int InOutIndex;///< 1 of 2 Indexes of current DependencyPort object in DependencyNode::DP (2D Vector)
	unsigned int PortIndex;	///< 2 of 2 Indexes of current DependencyPort object in DependencyNode::DP (2D Vector)
	unsigned int ObjectIndex;///< Index of current DependencyObject object in DependencyPort::DO
	string str;	///< Complete URL string <URL::strn>.<URL::strio>.<URL::strp>.<URL::stro>
	string strn;	///< DependencyNode::Name
	string strio;	///< "In" or "Out"
	string strp;	///< DependencyPort::Name
	string stro;	///< DependencyObject::Name
	//////////////////////////////////////////////////
	/// \fn URL()
	/// \brief Constructor
	///
	/// - Sets all 4 index to 0
	///
	/// \see URL(unsigned int ni, unsigned int ioi, unsigned int pi, unsigned int oi)
	//////////////////////////////////////////////////
	URL();
	//////////////////////////////////////////////////
	/// \fn URL(unsigned int ni, unsigned int ioi, unsigned int pi, unsigned int oi)
	/// \brief Constructor
	///	\param [in] ni is input NodeIndex
	///	\param [in] ioi is input InOutIndex
	///	\param [in] pi is input PortIndex
	///	\param [in] oi is input ObjectIndex
	///
	/// - Sets all 4 indexes to input values
	///
	/// \see URL()
	//////////////////////////////////////////////////
	URL(unsigned int ni, unsigned int ioi, unsigned int pi, unsigned int oi);
	//////////////////////////////////////////////////
	/// \fn string dotless(string d = "x")
	/// \brief Returns a version of str with all dots replaced by the string d
	///	\param [in] d is the string that replaces the dot separator (Default value for d is "x").
	/// \return string <URL::strn> d <URL::strio> d <URL::strp> d <URL::stro>
	///
	/// - Returns string <URL::strn> d <URL::strio> d <URL::strp> d <URL::stro>
	/// - Returns string <URL::strn> x <URL::strio> x <URL::strp> x <URL::stro> when argument d is not provided
	///
	//////////////////////////////////////////////////
	string dotless(string d = "x");
	//////////////////////////////////////////////////
	/// \fn Display()
	/// \brief Display function
	///
	/// - Displays [<URL::NodeIndex> , <URL::InOutIndex> , <URL::PortIndex> , <URL::ObjectIndex>] <URL::str>
	//////////////////////////////////////////////////
	void Display();
	//////////////////////////////////////////////////
	/// \fn ~URL()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~URL();
};

} /* namespace SmartDG */

#endif /* URL_H_ */
