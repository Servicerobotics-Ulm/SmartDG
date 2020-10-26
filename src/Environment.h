////////////////////////////////////////////////////////////////////////////////
///	\file	Environment.h
/// \brief	Header file for Environment class
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

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class Environment
/// \brief Environment class models a working Environment
///
/// This class encapsulates lists of Environment elements like Dependency objects,
/// connectors and transfer functions. It also records names of components and
/// names of their ports and dependency object instances.
////////////////////////////////////////////////////////////////////////////////
class Environment {
public:
	vector<string> SmartDependencyObjects; ///< DependencyObjects in the current Environment
	map<string, bool> isMultiSmartDependencyObjects; ///< isMulti flags for DependencyObjects in the current Environment
	vector<string> SmartComponents;	///< Components in the current Environment
	SmartDG__map TransferFunctions;	///< Transfer functions for Components in the current Environment
	map<string, vector<string>> InputPorts; ///< A map from Component name to a string vector of names of its Input ports
	map<string, vector<string>> OutputPorts; ///< A map from Component name to a string vector of names of its Output ports
	map<string, vector<string>> InputObjectInstances; ///< A map from "Component name . Input port name" to a string vector of names of its Dependency object instances
	map<string, vector<string>> OutputObjectInstances; ///< A map from "Component name . Output port name" to a string vector of names of its Dependency object instances
	vector<string> SmartConnectors;	///< Connectors in the current Environment
	map<string, string> Wiki;///< Wiki strings for various elements in the current Environment
	string godstr; ///< god string in use
	//////////////////////////////////////////////////
	/// \fn Environment()
	/// \brief Constructor
	///
	/// - Calls Environment::isMultiSmartDependencyObjectsInit()
	/// - Calls SmartDG_GlobalFunction::EnvironmentGenerator to fetch the current Environment Elements
	/// - Calls Environment::GODInit()
	/// - Calls Environment::SortAll()
	///
	//////////////////////////////////////////////////
	Environment();
	//////////////////////////////////////////////////
	/// \fn isMultiSmartDependencyObjectsInit()
	/// \brief Sets Environment::isMultiSmartDependencyObjects for all Dependency objects to default "false" value
	//////////////////////////////////////////////////
	void isMultiSmartDependencyObjectsInit() {
		for (unsigned int i = 0; i < SmartDependencyObjects.size(); i++)
			isMultiSmartDependencyObjects[SmartDependencyObjects[i]] = false;
	}
	//////////////////////////////////////////////////
	/// \fn god(int ng)
	/// \brief Returns a specific integer variant of Environment::godstr
	/// \param [in] ng Integer to be added to the return string
	/// \returns  string containing the Environment::godstr followed by the integer ng
	//////////////////////////////////////////////////
	string god(int ng) {
		return (godstr + to_string(ng));
	}
	//////////////////////////////////////////////////
	/// \fn GODInitTF(string g)
	/// \brief Associates default transfer function to the given string g
	/// \param [in] g is the string representing DependencyNode::Name
	//////////////////////////////////////////////////
	void GODInitTF(string g);
	//////////////////////////////////////////////////
	/// \fn GODInit()
	/// \brief Sets default values for God components
	//////////////////////////////////////////////////
	void GODInit() {
		godstr = SmartDG_DEFAULT_GODSTR;
		SmartConnectors.push_back(godstr);
		for (unsigned int ng = 0; ng < SmartDG_DEFAULT_NUMGOD; ng++) {
			string g = god(ng);
			SmartComponents.push_back(g);
			Wiki[g] = "ComponentGOD";
			OutputPorts[g].push_back(g);
			InputPorts[g].push_back(g);
			for (unsigned int i = 0; i < SmartDependencyObjects.size(); i++) {
				InputObjectInstances[g + "." + g].push_back(
						SmartDependencyObjects[i]);
				OutputObjectInstances[g + "." + g].push_back(
						SmartDependencyObjects[i]);
			}
			GODInitTF(g);
		}
	}
	//////////////////////////////////////////////////
	/// \fn compareFunction1(char a, char b)
	/// \brief Called by Environment::compareFunction2 to compare a and b lexicographically
	/// \param [in] a is the first character to compare
	/// \param [in] b is the second character to compare
	/// \return bool indicating which of the two characters a and b is smaller
	/// \see compareFunction2(std::string a, std::string b)
	//////////////////////////////////////////////////
	static bool compareFunction1(char a, char b) {
		return tolower(a) < tolower(b);
	}
	//////////////////////////////////////////////////
	/// \fn compareFunction2(std::string a, std::string b)
	/// \brief Compares a and b lexicographically
	/// \param [in] a is the first string to compare
	/// \param [in] b is the second string to compare
	/// \return bool indicating which of the two strings a and b is lexicographically smaller
	/// \see compareFunction1(char a, char b)
	//////////////////////////////////////////////////
	static bool compareFunction2(std::string a, std::string b) {
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
				compareFunction1);
	}
	//////////////////////////////////////////////////
	/// \fn SortAll(map<string, vector<string>> &I)
	/// \brief Sorts all string vector entries in the map I lexicographically
	/// \param [in,out] I is the map of which all entries are to be sorted lexicographically
	/// \see SortAll()
	//////////////////////////////////////////////////
	void SortAll(map<string, vector<string>> &I) {
		for (map<string, vector<string>>::const_iterator it = I.begin();
				it != I.end(); ++it) {
			vector<string> tmp = it->second;
			sort(tmp.begin(), tmp.end(), compareFunction2);
			I[it->first] = tmp;
		}
	}
	//////////////////////////////////////////////////
	/// \fn SortAll()
	/// \brief Sorts all string vector entries in all Environment maps lexicographically
	/// \see SortAll(map<string, vector<string>> &I)
	//////////////////////////////////////////////////
	void SortAll() {
		sort(SmartDependencyObjects.begin(), SmartDependencyObjects.end(),
				compareFunction2);
		sort(SmartComponents.begin(), SmartComponents.end(), compareFunction2);
		SortAll(InputPorts);
		SortAll(OutputPorts);
		SortAll(InputObjectInstances);
		SortAll(OutputObjectInstances);
		sort(SmartConnectors.begin(), SmartConnectors.end(), compareFunction2);
	}
	//////////////////////////////////////////////////
	/// \fn Display(vector<string> I)
	/// \brief Displays content of the vector string I
	/// \param [in] I is the string vector to be displayed
	/// \see Display(SmartDG__map I)
	/// \see Display(map<string, vector<string>> I, bool displaygod = false)
	/// \see Display(map<string, string> I, int join = 0, bool showwiki = true)
	/// \see Display()
	//////////////////////////////////////////////////
	void Display(vector<string> I) {
		for (unsigned int i = 0; i < I.size(); i++) {
			if (Wiki.count(I[i]))
				cout << left << setw(SmartDG_COLUMN_WIDTH) << I[i]
						<< "Wiki: " + Wiki[I[i]] << endl;
			else
				cout << left << setw(SmartDG_COLUMN_WIDTH) << I[i] << endl;
		}
	}
	//////////////////////////////////////////////////
	/// \fn Display(SmartDG__map I)
	/// \brief Displays content of the SmartDG__map I
	/// \param [in] I is SmartDG__map to be displayed
	/// \see Display(vector<string> I)
	/// \see Display(map<string, vector<string>> I, bool displaygod = false)
	/// \see Display(map<string, string> I, int join = 0, bool showwiki = true)
	/// \see Display()
	//////////////////////////////////////////////////
	void Display(SmartDG__map I) {
		for (SmartDG__map::const_iterator it = I.begin(); it != I.end(); ++it) {
			vector<string> Return;
			vector<vector<SmartDG::DependencyPort> > DP;
			it->second("List", Return, DP);
			cout << it->first << ": ";
			if (Return[0] == SmartDG_OK) {
				for (unsigned int i = 1; i < Return.size(); i++)
					cout << Return[i] << "  ";
				cout << endl;
			} else {
				cout << "ERROR: List Function not found." << endl;
			}
		}
	}
	//////////////////////////////////////////////////
	/// \fn Display(map<string, vector<string>> I, bool displaygod = false)
	/// \brief Displays content of the map I of vector strings
	/// \param [in] I is the map of vector strings to be displayed
	/// \param [in] displaygod is a boolean indicator for displaying god components (Default is "false")
	/// \see Display(vector<string> I)
	/// \see Display(SmartDG__map I)
	/// \see Display(map<string, string> I, int join = 0, bool showwiki = true)
	/// \see Display()
	//////////////////////////////////////////////////
	void Display(map<string, vector<string>> I, bool displaygod = false) {
		for (map<string, vector<string>>::const_iterator it = I.begin();
				it != I.end(); ++it) {
			bool notgod = true;
			for (unsigned int ng = 0; ng < SmartDG_DEFAULT_NUMGOD; ng++)
				if (it->first == god(ng))
					notgod = false;
			for (unsigned int ng = 0; ng < SmartDG_DEFAULT_NUMGOD; ng++)
				if (it->first == god(ng) + "." + god(ng))
					notgod = false;
			if (notgod || displaygod)
				for (unsigned int i = 0; i < it->second.size(); i++) {
					string tmp = it->first + "." + it->second[i];
					if (Wiki.count(tmp))
						cout << left << setw(SmartDG_COLUMN_WIDTH) << tmp
								<< "Wiki: " + Wiki[tmp] << endl;
					else
						cout << left << setw(SmartDG_COLUMN_WIDTH) << tmp
								<< endl;
				}
		}
	}
	//////////////////////////////////////////////////
	/// \fn Display(map<string, string> I, int join = 0, bool showwiki = true)
	/// \brief Displays content of the map I of strings
	/// \param [in] I is the map I of strings to be displayed
	/// \param [in] join is an integer indicating which string(s) gets displayed. 1:Map's key 2:Map's Value 0:Map's key and Value (Default)
	/// \param [in] showwiki is a boolean indicator to whether or not to display the wiki
	///
	/// - This is called from outside the class using a temporary object of Environment class
	///
	/// \see Display(vector<string> I)
	/// \see Display(SmartDG__map I)
	/// \see Display(map<string, vector<string>> I, bool displaygod = false)
	/// \see Display()
	//////////////////////////////////////////////////
	void Display(map<string, string> I, int join = 0, bool showwiki = true) {
		for (map<string, string>::const_iterator it = I.begin(); it != I.end();
				++it) {
			string tmp = it->first + "." + it->second;
			if (join == 1)
				tmp = it->first;
			if (join == 2)
				tmp = it->second;
			if (Wiki.count(tmp) && showwiki)
				cout << left << setw(SmartDG_COLUMN_WIDTH) << tmp
						<< "Wiki: " + Wiki[tmp] << endl;
			else {
				if (it == I.begin())
					cout << tmp;
				else
					cout << "," << tmp;
			}
		}
		if (!showwiki)
			cout << endl;
	}
	//////////////////////////////////////////////////
	/// \fn Display()
	/// \brief Displays all elements of the current Environment
	///
	/// \see Display(vector<string> I)
	/// \see Display(SmartDG__map I)
	/// \see Display(map<string, vector<string>> I, bool displaygod = false)
	/// \see Display(map<string, string> I, int join = 0, bool showwiki = true)
	//////////////////////////////////////////////////
	void Display() {
		cout << "----------------------------SmartDependencyObjects" << endl;
		Display(SmartDependencyObjects);
		cout << "----------------------------SmartComponents" << endl;
		Display(SmartComponents);
		cout << "----------------------------TransferFunctions" << endl;
		Display(TransferFunctions);
		cout << "----------------------------InputPorts" << endl;
		Display(InputPorts);
		cout << "----------------------------OutputPorts" << endl;
		Display(OutputPorts);
		cout << "----------------------------InputObjects" << endl;
		Display(InputObjectInstances);
		cout << "----------------------------OutputObjects" << endl;
		Display(OutputObjectInstances);
		cout << "----------------------------SmartConnectors" << endl;
		Display(SmartConnectors);
	}
	//////////////////////////////////////////////////
	/// \fn ~Environment()
	/// \brief Default Destructor
	//////////////////////////////////////////////////
	virtual ~Environment();
};

} /* namespace SmartDG */

#endif /* ENVIRONMENT_H_ */
