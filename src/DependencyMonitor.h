////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyMonitor.h
/// \brief	Header file for DependencyMonitor class
/// \author Vineet Nagrath
/// \date	June 9, 2020
///
/// \copyright	Service Robotics Research Center\n
/// University of Applied Sciences Ulm\n
/// Prittwitzstr. 10\n
/// 89075 Ulm (Germany)\n
///
/// Information about the SmartSoft MDSD Toolchain is available at:\n
/// www.servicerobotik-ulm.de
////////////////////////////////////////////////////////////////////////////////

#ifndef DEPENDENCYMONITOR_H_
#define DEPENDENCYMONITOR_H_

#include "SmartDG.h"

namespace SmartDG {
////////////////////////////////////////////////////////////////////////////////
///	\class DependencyMonitor
/// \brief DependencyMonitor class generates and manages the GUI for DependencyGraph
///
/// This class encapsulates a DependencyGraph object  and various FLTK Graphics objects,
/// Menu bar handlers and DependencyGraph data Sync handlers (Multi-View).\n
/// The class includes several functions and data containers to initiate, record, manage
/// and  display the aforementioned  entities.
////////////////////////////////////////////////////////////////////////////////
class DependencyMonitor {
private:
	// Static data members
	static unsigned int count; ///< A static unsigned integer that keeps count of DependencyMonitor objects created
	static bool MTLiteOn; ///< A static boolean variable part of the mechanism to indicate SmartDG_LITE_DISPLAYMODE
	static bool MTLiteInit; ///< A static boolean variable part of the mechanism to indicate initialization of SmartDG_LITE_DISPLAYMODE

	string BusinessViewWindowTitle;	///< Title of GUI window for the view DependencyMonitor object generates
	string MTWindowTitle; ///<  Title string used at various places in DGlite ( Web Browser View )
	string DGliteDir; ///<  String used to store directory path where DGlite ( Web Browser View ) is populated
	Fl_Double_Window *MonitorWindow; ///< Points to Fl_Double_Window object that handles GUI window
	Fl_Double_Window *MTWindow; ///< Points to Fl_Double_Window object that handles GUI window in SmartDG_LITE_DISPLAYMODE
	Fl_Menu_Bar *MonitorWindowMenuBar; ///< Points to Fl_Menu_Bar object that handles GUI window
	Fl_Menu_Bar *MTWindowMenuBar; ///< Points to Fl_Menu_Bar object that handles GUI window in SmartDG_LITE_DISPLAYMODE
	Fl_Scroll *MonitorWindowScroll; ///< Points to Fl_Scroll object that handles all GUI window elements
	Fl_Group *BigGroup; ///< Points to Fl_Group object that handles all GUI window elements
	unsigned int lox; ///< Stores x coordinate of location where GUI window is initiated
	unsigned int loy; ///< Stores y coordinate of location where GUI window is initiated
	Environment currentEnvironment; ///< Environment object used to display current Environment elements
	string DispString; ///< A dynamically changing information string displayed as label of MonitorWindowScroll
	string currentView; ///< Stores name of the current DependencyObject object being displayed in SmartDG_OBJECT_MODE
	string currentComponent; ///< Stores name of the current DependencyNode object being displayed in SmartDG_COMPONENT_MODE or SmartDG_COMPONENT_DEVELOPER_MODE
	//////////////////////////////////////////////////
	/// \var currentDirection
	/// \brief Indicated business direction -1: Reverse Business 1: Forward Business
	/// \todo Add support for dual direction (currentDirection : 0) where transfer/inverse transfer functions
	/// are smartly triggered to traverse through the node graph.
	//////////////////////////////////////////////////
	//#TODO Add support for dual direction (currentDirection : 0) where transfer/inverse transfer functions
	// are smartly triggered to traverse through the node graph.
	int currentDirection;
	bool View2ViewFlag; ///< A boolean value that stores weather data Sync is allowed between Views
	map<string, unsigned int> fcount; ///< A string map that counts the number of connections originating from an Output Port DependencyObject object
	map<string, unsigned int> tcount; ///< A string map that counts the number of connections terminating at an Input Port DependencyObject object
	map<unsigned int, map<unsigned int, bool> > Grid; ///< A 2 dimensional integer map to indicate is a grid position is available or occupied
	//////////////////////////////////////////////////
	/// \var GridXY
	/// \brief A 2 dimensional string map that stores x and y coordinates (in order)
	/// for a pair (Source and Target in order) of URL::str strings indicating a position
	/// in the grid at which the GUIText object associated with the GUIConnection object should
	/// be initialized
	/// \todo DependencyMonitor::AdjustGridXY() needs to be implemented to make sure
	/// the GUIText objects from different GUIConnection objects don't occlude one another.
	//////////////////////////////////////////////////
	map<string, map<string, vector<unsigned int> > > GridXY;
	bool SolverSync; ///< A boolean flag which (when set true) initiates data Sync between Views after every local change

	// Static menu callback functions and their non-static carry-forwards
	//////////////////////////////////////////////////
	/// \fn static void Static_MonitorWindowMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	/// \brief Static callback function for DependencyMonitor::MonitorWindowMenuBar (Fl_Menu_Bar *)
	/// \param WIDGET	Fl_Widget* locating the Fl_Menu_Bar
	/// \param DATA		Data associated with the Fl_Menu_Bar object
	///
	/// - Calls DependencyMonitor::MonitorWindowMenuBar_Callback()
	///
	/// \see void MonitorWindowMenuBar_Callback()
	//////////////////////////////////////////////////
	static void Static_MonitorWindowMenuBar_Callback(Fl_Widget*WIDGET,
			void*DATA) {
		DependencyMonitor *TMP = (DependencyMonitor*) DATA;
		TMP->MonitorWindowMenuBar_Callback();
	}
	//////////////////////////////////////////////////
	/// \fn void MonitorWindowMenuBar_Callback()
	/// \brief Callback function for DependencyMonitor::MonitorWindowMenuBar (Fl_Menu_Bar *)
	///
	/// - Identifies selected option from the menu\n
	/// - Performs action according to selection for the following:\n
	///		- DGMonitor\n
	///		- DGMonitor / Wiki\n
	///		- DGMonitor / Environment / SmartDependencyObjects\n
	///		- DGMonitor / Environment / SmartComponents\n
	///		- DGMonitor / Environment / TransferFunctions\n
	///		- DGMonitor / Environment / Ports / InputPorts\n
	///		- DGMonitor / Environment / Ports / OutputPorts\n
	///		- DGMonitor / Environment / Ports / All\n
	///		- DGMonitor / Environment / ObjectInstance / InputObjectInstances\n
	///		- DGMonitor / Environment / ObjectInstance / OutputObjectInstances\n
	///		- DGMonitor / Environment / ObjectInstance / All\n
	///		- DGMonitor / Environment / SmartConnectors\n
	///		- DGMonitor / Environment / All\n
	///		- DGMonitor / Print Screen\n
	///		- DGMonitor / Sync / Allow\n
	///		- DGMonitor / Sync / Block\n
	///		- DGMonitor / Exit\n
	///		- DGMonitor / Exit All\n
	///		- Debug\n
	///		- Debug / ToggleAll / True\n
	///		- Debug / ToggleAll / False\n
	///		- Debug / ToggleAll / SyncOut\n
	///		- Debug / ToggleAll / SyncIn\n
	///		- Business\n
	///		- Business / Forward\n
	///		- Business / Reverse\n
	///		- Edit\n
	///		- Edit / "DependencyObject object's all or specific instance" / true\n
	///		- Edit / "DependencyObject object's all or specific instance" / false\n
	///		- Sync\n
	///		- Sync / Refresh\n
	///		- Sync / Attach\n
	///		- Sync / Detach\n
	///		- Sync / Upload\n
	///		- Sync / Download\n
	///		- Sync / SolverSync / Enable\n
	///		- Sync / SolverSync / Disable
	///
	/// \see static void Static_MonitorWindowMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	//////////////////////////////////////////////////
	void MonitorWindowMenuBar_Callback();
	//////////////////////////////////////////////////
	/// \fn static void Static_MTWindowMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	/// \brief Static callback function for DependencyMonitor::MTWindowMenuBar (Fl_Menu_Bar *)
	/// \param WIDGET	Fl_Widget* locating the Fl_Menu_Bar
	/// \param DATA		Data associated with the Fl_Menu_Bar object
	///
	/// - Calls DependencyMonitor::MTWindowMenuBar_Callback()
	///
	/// \see void MTWindowMenuBar_Callback()
	//////////////////////////////////////////////////
	static void Static_MTWindowMenuBar_Callback(Fl_Widget*WIDGET, void*DATA) {
		DependencyMonitor *TMP = (DependencyMonitor*) DATA;
		TMP->MTWindowMenuBar_Callback();
	}
	//////////////////////////////////////////////////
	/// \fn void MTWindowMenuBar_Callback()
	/// \brief Callback function for DependencyMonitor::MTWindowMenuBar (Fl_Menu_Bar *)
	///
	/// - Identifies selected option from the menu\n
	/// - Performs action according to selection for the following:\n
	///		- DGMonitor\n
	///		- DGMonitor / Wiki\n
	///		- DGMonitor / Exit\n
	///		- DGlite\n
	///		- DGlite / Launch / Chrome\n
	///		- DGlite / Launch / Firefox
	///
	/// \see static void Static_MTWindowMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	//////////////////////////////////////////////////
	void MTWindowMenuBar_Callback();
	//////////////////////////////////////////////////
	/// \fn static void Static_NodeMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	/// \brief Static callback function for DependencyNode::BarIn and DependencyNode::BarOut (Fl_Menu_Bar *) of DependencyNode objects
	/// \param WIDGET	Fl_Widget* locating the Fl_Menu_Bar
	/// \param DATA		Data associated with the Fl_Menu_Bar object
	///
	/// - Calls DependencyMonitor::NodeMenuBar_Callback()
	///
	/// \see void NodeMenuBar_Callback()
	//////////////////////////////////////////////////
	static void Static_NodeMenuBar_Callback(Fl_Widget*WIDGET, void*DATA) {
		DependencyMonitor *TMP = (DependencyMonitor*) DATA;
		TMP->NodeMenuBar_Callback();
	}
	//////////////////////////////////////////////////
	/// \fn void NodeMenuBar_Callback
	/// \brief Callback function for DependencyNode::BarIn and DependencyNode::BarOut (Fl_Menu_Bar *) of DependencyNode objects
	///
	/// - Identifies selected option from the DependencyNode::BarIn and DependencyNode::BarOut menu bars\n
	/// - Edit DependencyObject object's all or specific instance as true/false
	///
	/// \see static void Static_NodeMenuBar_Callback(Fl_Widget*WIDGET, void*DATA)
	//////////////////////////////////////////////////
	void NodeMenuBar_Callback();
	//////////////////////////////////////////////////
	/// \fn void setup()
	/// \brief setup operations right after a DependencyMonitor object is constructed
	///
	/// - Called from all constructors\n
	/// - Initiates lox and loy (Position of GUI window) based on current DependencyMonitor::count\n
	/// - Initiates FLTK GUI pointer objects with NULL\n
	/// - Makes appropriate titles for GUI windows\n
	/// - Sets default values for View2ViewFlag and SolverSync (Sync action flags)\n
	/// - Creates and populates DGlite directory (In all except DependencyMonitor::Mode : SmartDG_COMPONENT_DEVELOPER_MODE)
	///
	///	\see DependencyMonitor()
	///	\see DependencyMonitor(string GraphAndMonitorName, string mode)
	///	\see DependencyMonitor(string MonitorName, string GraphName, string ViewName, string mode)
	///	\see DependencyMonitor(DependencyMonitor from, string MonitorName, string GraphName, string ViewName, string mode)
	//////////////////////////////////////////////////
	void setup();
	//////////////////////////////////////////////////
	/// \fn void makelitejs()
	/// \brief Creates Java Script file in DGlite directory  (In all except DependencyMonitor::Mode : SmartDG_COMPONENT_DEVELOPER_MODE)
	//////////////////////////////////////////////////
	void makelitejs();
	//////////////////////////////////////////////////
	/// \fn InitMT()
	/// \brief Initializes GUI for DependencyMonitor::Mode : SmartDG_LITE_DISPLAYMODE
	///
	/// - Initializes GUI\n
	/// - Populates Menu bar items
	///
	/// \see void Init()
	///	\see void InitComponent()
	//////////////////////////////////////////////////
	void InitMT();
	//////////////////////////////////////////////////
	/// \fn SyncOI()
	/// \brief Part of Sync mechanism, Sync out | Pause | Sync in
	///
	/// \see void SyncOut()  \see void SyncIn()
	/// \see void SyncOutLiteInit() \see void SyncOutLite(bool useglobal = true) \see void SyncInLite()
	//////////////////////////////////////////////////
	void SyncOI();
	//////////////////////////////////////////////////
	/// \fn SyncOut()
	/// \brief Part of Sync mechanism, Sync out
	///
	/// \see void SyncOI() \see void SyncIn()
	/// \see void SyncOutLiteInit() \see void SyncOutLite(bool useglobal = true) \see void SyncInLite()
	//////////////////////////////////////////////////
	void SyncOut();
	//////////////////////////////////////////////////
	/// \fn SyncIn()
	/// \brief Part of Sync mechanism, Sync in
	///
	/// \see void SyncOI() \see void SyncOut()
	/// \see void SyncOutLiteInit() \see void SyncOutLite(bool useglobal = true) \see void SyncInLite()
	//////////////////////////////////////////////////
	void SyncIn();
	//////////////////////////////////////////////////
	/// \fn SyncOutLiteInit()
	/// \brief Initialization of Sync mechanism for DGlite ( Web Browser View )
	///
	/// \see void SyncOI() \see void SyncOut()  \see void SyncIn()
	/// \see void SyncOutLite(bool useglobal = true) \see void SyncInLite()
	//////////////////////////////////////////////////
	void SyncOutLiteInit();
	//////////////////////////////////////////////////
	/// \fn SyncOutLite(bool useglobal = true)
	/// \brief Part of Sync mechanism for DGlite ( Web Browser View ) Sync out
	///
	/// \param [in] useglobal is a boolean variable indicating if local (false) or global (true, Default)
	/// version of data should Sync to DGlite
	///
	/// - Default value for useglobal is true i.e the Sync is done using Global Sync data (SmartDG_GlobalData::GlobalPackage)
	///
	/// \see void SyncOI() \see void SyncOut()  \see void SyncIn()
	/// \see void SyncOutLiteInit() \see void SyncInLite()
	//////////////////////////////////////////////////
	void SyncOutLite(bool useglobal = true);
	//////////////////////////////////////////////////
	/// \fn SyncInLite()
	/// \brief Part of Sync mechanism for DGlite ( Web Browser View ) Sync in
	///
	/// \todo DependencyMonitor::SyncInLite to be implemented when DGlite takes user inputs
	///
	/// \see void SyncOI() \see void SyncOut()  \see void SyncIn()
	/// \see void SyncOutLiteInit() \see void SyncOutLite(bool useglobal = true)
	//////////////////////////////////////////////////
	void SyncInLite();
	//////////////////////////////////////////////////
	/// \fn ShowLines()
	/// \brief Initializes GUIConnection objects for the GUI
	//////////////////////////////////////////////////
	void ShowLines();
	//////////////////////////////////////////////////
	/// \fn Snap2Grid(unsigned int &x, unsigned int &y)
	/// \brief Snaps given coordinates to the closest unoccupied location on the grid
	///
	/// \param [in,out] x is x coordinate
	/// \param [in,out] y is y coordinate
	///
	/// - Snaps to the closest floor coordinates on the Grid\n
	/// - Snaps to closest ceiling coordinates if that is closer to the input coordinate\n
	/// - If the location is already occupied, Snap to nearest orthogonal neighbor on the Grid\n
	/// - Note that " ! DependencyMonitor::Grid[tx][ty]" will be true if Grid map has no entry for [tx][ty] OR when the entry is true
	///
	//////////////////////////////////////////////////
	void Snap2Grid(unsigned int &x, unsigned int &y);
	//////////////////////////////////////////////////
	/// \fn AdjustGridXY()
	/// \brief Adjusts GridXY map such that GUIText objects from different
	/// GUIConnection objects don't occlude one another.
	/// \todo DependencyMonitor::AdjustGridXY() needs to be implemented to make sure
	/// the GUIText objects from different GUIConnection objects don't occlude one another.
	//////////////////////////////////////////////////
	void AdjustGridXY();
	//////////////////////////////////////////////////
	/// \fn Generate_Dependency_Tabs()
	/// \brief Generates DependencyMonitor::fcount and DependencyMonitor::tcount maps
	//////////////////////////////////////////////////
	void Generate_Dependency_Tabs();
	//////////////////////////////////////////////////
	/// \fn RefreshMonitorData(string obj, bool refreshGUI = true)
	/// \brief Refreshes data displayed on the connectors in the GUI for a particular DependencyObject View
	///
	/// \param [in] obj is the Name data element of the DependencyObject object
	/// \param [in] refreshGUI is a boolean flag that indicates if Fl_Double_Window::redraw()
	/// function needs to be called (Via a call to DependencyMonitor::RefreshMonitor()) after
	/// the data is refreshed. This is true by default.
	///
	/// - Default value for refreshGUI is set as true\n
	/// - Fills latest DependencyObject instance data (Name : obj) to GUI connections
	///
	/// \see RefreshMonitorData(bool refreshGUI = true)  \see RefreshMonitor()
	//////////////////////////////////////////////////
	void RefreshMonitorData(string obj, bool refreshGUI = true);
	//////////////////////////////////////////////////
	/// \fn RefreshMonitorData(bool refreshGUI = true)
	/// \brief Refreshes data displayed on the connectors in the GUI for all DependencyObject Views
	///
	/// \param [in] refreshGUI is a boolean flag that indicates if Fl_Double_Window::redraw()
	/// function needs to be called (Via a call to DependencyMonitor::RefreshMonitor()) after
	/// the data is refreshed. This is true by default.
	///
	/// - Default value for refreshGUI is set as true\n
	/// - For all objects (obj) in DependencyGraph DG (DependencyGraph::dobjs)\n
	/// - Calls RefreshMonitorData(obj, refreshGUI)\n
	/// - Calls RefreshMonitorData("DUMMY", refreshGUI) to handle\n
	///  DependencyMonitor::Mode : SmartDG_COMPONENT_MODE or SmartDG_COMPONENT_DEVELOPER_MODE
	///
	/// \see RefreshMonitorData(string obj, bool refreshGUI = true)  \see RefreshMonitor()
	//////////////////////////////////////////////////
	void RefreshMonitorData(bool refreshGUI = true);
	//////////////////////////////////////////////////
	/// \fn RefreshMonitor()
	/// \brief Redraws the current GUI window through a call to Fl_Double_Window::redraw()
	/// \see RefreshMonitorData(string obj, bool refreshGUI = true)
	/// \see RefreshMonitorData(bool refreshGUI = true)
	//////////////////////////////////////////////////
	void RefreshMonitor();
	//////////////////////////////////////////////////
	/// \fn ResetDOIFlags(bool b = false, unsigned int c = 0)
	/// \brief Resets DependencyObjectInstance::visible DependencyObjectInstance::editable flags
	/// \param [in] b is the value to be set to flags (Default : false)
	/// \param [in] c is the choice of flag to be set (Default : 0)
	/// (0: both, 1: DependencyObjectInstance::visible, 2: DependencyObjectInstance::editable)
	///
	/// - DOIFlags : DependencyObjectInstances Flags\n
	/// - Default value for b is false\n
	/// - Default value for c is 0 (Both flags)
	///
	/// \see RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \see RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false,	unsigned int c = 0)
	/// \see RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =	0)
	//////////////////////////////////////////////////
	void ResetDOIFlags(bool b = false, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \brief Resets DependencyObjectInstance::visible DependencyObjectInstance::editable flags for given context
	/// \param [in] v is context selector string for DependencyObjectInstances::ViewContext (Default : "ALL")
	/// \param [in] n is context selector string for DependencyObjectInstances::NodeContext (Default : "ALL")
	/// \param [in] i is context selector string for DependencyObjectInstances::IOContext (Default : "ALL")
	/// \param [in] p is context selector string for DependencyObjectInstances::PortContext (Default : "ALL")
	/// \param [in] o is context selector string for DependencyObjectInstances::ObjectContext (Default : "ALL")
	/// \param [in] b is the value to be set to flags (Default : false)
	/// \param [in] c is the choice of flag to be set (Default : 0)
	/// (0: both, 1: DependencyObjectInstance::visible, 2: DependencyObjectInstance::editable)
	///
	/// - DOIFlags : DependencyObjectInstances Flags\n
	/// - Default value for v is "ALL"\n
	/// - Default value for n is "ALL"\n
	/// - Default value for i is "ALL"\n
	/// - Default value for p is "ALL"\n
	/// - Default value for o is "ALL"\n
	/// - Default value for b is false\n
	/// - Default value for c is 0 (Both flags)
	///
	/// \see ResetDOIFlags(bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false,	unsigned int c = 0)
	/// \see RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =	0)
	//////////////////////////////////////////////////
	void RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL",
			string p = "ALL", string o = "ALL", bool b = false, unsigned int c =
					0);
	//////////////////////////////////////////////////
	/// \fn RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \brief Resets DependencyObjectInstance::visible DependencyObjectInstance::editable flags for given context Hierarchically
	/// \param [in] v is context selector string for DependencyObjectInstances::ViewContext (Default : "ALL")
	/// \param [in] n is context selector string for DependencyObjectInstances::NodeContext (Default : "ALL")
	/// \param [in] i is context selector string for DependencyObjectInstances::IOContext (Default : "ALL")
	/// \param [in] p is context selector string for DependencyObjectInstances::PortContext (Default : "ALL")
	/// \param [in] o is context selector string for DependencyObjectInstances::ObjectContext (Default : "ALL")
	/// \param [in] b is the value to be set to flags (Default : false)
	/// \param [in] c is the choice of flag to be set (Default : 0)
	/// (0: both, 1: DependencyObjectInstance::visible, 2: DependencyObjectInstance::editable)
	///
	/// - DOIFlags : DependencyObjectInstances Flags\n
	/// - Default value for v is "ALL"\n
	/// - Default value for n is "ALL"\n
	/// - Default value for i is "ALL"\n
	/// - Default value for p is "ALL"\n
	/// - Default value for o is "ALL"\n
	/// - Default value for b is false\n
	/// - Default value for c is 0 (Both flags)
	///
	/// \see ResetDOIFlags(bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \see RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =	0)
	//////////////////////////////////////////////////
	void RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i =
			"ALL", string p = "ALL", string o = "ALL", bool b = false,
			unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0)
	/// \brief Resets DependencyObjectInstance::visible DependencyObjectInstance::editable flags for all instances under a URL / DependencyObject
	/// \param [in] u is URL of the DependencyObject object, flags of all instances of which will be set
	/// \param [in] b is the value to be set to flags (Default : false)
	/// \param [in] c is the choice of flag to be set (Default : 0)
	/// (0: both, 1: DependencyObjectInstance::visible, 2: DependencyObjectInstance::editable)
	///
	/// - DOIFlags : DependencyObjectInstances Flags\n
	/// - Default value for b is false\n
	/// - Default value for c is 0 (Both flags)
	///
	/// \see ResetDOIFlags(bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \see RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false,	unsigned int c = 0)
	/// \see RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =	0)
	//////////////////////////////////////////////////
	void RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0);
	//////////////////////////////////////////////////
	/// \fn RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =	0)
	/// \brief Resets DependencyObjectInstance::visible DependencyObjectInstance::editable flags for given Menu identifier string
	/// \param [in] m is Menu identifier string of the DependencyObject object instance, flags of all instances of which will be set
	/// \param [in] b is the value to be set to flags (Default : false)
	/// \param [in] c is the choice of flag to be set (Default : 0)
	/// (0: both, 1: DependencyObjectInstance::visible, 2: DependencyObjectInstance::editable)
	///
	/// - DOIFlags : DependencyObjectInstances Flags\n
	/// - Default value for b is false\n
	/// - Default value for c is 0 (Both flags)
	///
	/// \see ResetDOIFlags(bool b = false, unsigned int c = 0)
	/// \see RefreshDOIFlags(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false, unsigned int c =	0)
	/// \see RefreshDOIFlagsHierarchy(string v = "ALL", string n = "ALL", string i = "ALL", string p = "ALL", string o = "ALL", bool b = false,	unsigned int c = 0)
	/// \see RefreshDOIFlagsURL(string u, bool b = false, unsigned int c = 0)
	//////////////////////////////////////////////////
	void RefreshDOIFlagsMenuIDString(string m, bool b = false, unsigned int c =
			0);
	//////////////////////////////////////////////////
	/// \fn RefreshEditMenu()
	/// \brief Refresh Edit menu according to  DependencyObjectInstance::editable flags
	/// \see ShowHideMonitorWindowMenuBar(string item, bool flag)
	//////////////////////////////////////////////////
	void RefreshEditMenu();
	//////////////////////////////////////////////////
	/// \fn ShowHideMonitorWindowMenuBar(string item, bool flag)
	/// \brief Refresh Edit menu according to  DependencyObjectInstance::editable flags
	/// \param [in] item is Menu identifier string of the item to be set
	/// \param [in] flag is the value to be set to the item
	/// \see RefreshEditMenu()
	//////////////////////////////////////////////////
	void ShowHideMonitorWindowMenuBar(string item, bool flag);
	//////////////////////////////////////////////////
	/// \fn RefreshNodeEditMenu()
	/// \brief Refresh Node Edit menu according to  DependencyObjectInstance::editable flags
	/// \see ShowHideNodeMenuBar(unsigned int tog, string item, bool b)
	//////////////////////////////////////////////////
	void RefreshNodeEditMenu();
	//////////////////////////////////////////////////
	/// \fn ShowHideNodeMenuBar(unsigned int tog, string item, bool b)
	/// \brief Refresh Node Edit menu according to  DependencyObjectInstance::editable flags
	/// \param [in] tog is Input/Output Node Edit menu selector (0: Input Node Edit menu, 1: Output Node Edit menu)
	/// \param [in] item is Menu identifier string of the item to be set
	/// \param [in] b is the value to be set to the item
	/// \see RefreshNodeEditMenu()
	//////////////////////////////////////////////////
	void ShowHideNodeMenuBar(unsigned int tog, string item, bool b);
	//////////////////////////////////////////////////
	/// \fn MenuJointRefresh()
	/// \brief Refresh Edit menu and Node Edit menus according to  DependencyObjectInstance::editable flags
	/// \see RefreshEditMenu() \see RefreshNodeEditMenu()
	//////////////////////////////////////////////////
	void MenuJointRefresh();
	//////////////////////////////////////////////////
	/// \fn resetConDirection(int v = 0)
	/// \brief Resets Connection directions to 0
	//////////////////////////////////////////////////
	void resetConDirection();
	//////////////////////////////////////////////////
	/// \fn string extractPortName(string s)
	/// \brief Extracts and returns Port name string from the given Node menu selection string
	/// \param [in] s is the given Node menu selection string
	/// \return Port name string
	//////////////////////////////////////////////////
	string extractPortName(string s);
	//////////////////////////////////////////////////
	/// \fn string tog2str(int tog)
	/// \brief Returns appropriate string(In/Out) for a given tog integer value (0/1)
	/// \param [in] tog is is Input/Output Node Edit menu selector
	/// \return string equivalent for tog : 0-->"In" or 1-->"Out"
	/// \see int str2tog(string str)
	//////////////////////////////////////////////////
	string tog2str(int tog);
	//////////////////////////////////////////////////
	/// \fn int str2tog(string str)
	/// \brief Returns appropriate integer value (0/1) for a given string str(In/Out)
	/// \param [in] str is Input/Output Node string : "In" or "Out"
	/// \return integer equivalent for str "In"-->0 or "Out"-->1
	/// \see string tog2str(int tog)
	//////////////////////////////////////////////////
	int str2tog(string str);
	//////////////////////////////////////////////////
	/// \fn int toginv(int tog)
	/// \brief Returns inverted integer value (1/0) for a given tog integer value (0/1)
	/// \param [in] tog is is Input/Output Node Edit menu selector : 0 or 1
	/// \return inverted value for tog : 0-->1 or 1-->0
	/// \see int str2tog(string str)
	//////////////////////////////////////////////////
	int toginv(int tog);
	//////////////////////////////////////////////////
	/// \fn string dir2str(int dir)
	/// \brief Returns appropriate string(In/Out/ALL) for a given tog integer value (0/1/Other)
	/// \param [in] dir is is DependencyMonitor::currentDirection representation
	/// \return string equivalent for dir : 0-->"In" or 1-->"Out" or "ALL" for other values
	//////////////////////////////////////////////////
	string dir2str(int dir);
	//////////////////////////////////////////////////
	/// \fn GenDispStr()
	/// \brief Generates DispString (dynamically changing information string displayed as label of MonitorWindowScroll)
	//////////////////////////////////////////////////
	void GenDispStr();
	//////////////////////////////////////////////////
	/// \fn Solver(unsigned int doiindex)
	/// \brief Solves the DependencyGraph data by calling appropriate transfer/inverse transfer
	/// functions for DependencyNodes and Connectors
	/// \param [in] doiindex is index for DependencyObjectInstance object, the node where a smart Solver may start
	/// \todo Improve Solver ALgorithm
	/// \todo Replace DependencyMonitor::Solver with a public function pointer
	/// that gets assigned outside SmartDG library
	//////////////////////////////////////////////////
	void Solver(unsigned int doiindex);
public:
	string Name; ///< Name given to uniquely identify a DependencyMonitor object.
	DependencyGraph DG; ///< A DependencyGraph object that models dependency graph associated with the current DependencyGraph object
	string Mode; ///< A string that stores the current Mode of operation (SmartDG_OBJECT_MODE or SmartDG_COMPONENT_MODE or SmartDG_COMPONENT_DEVELOPER_MODE)
	string DisplayMode; ///< A string that stores the current Mode of display (SmartDG_FLTK_DISPLAYMODE or SmartDG_LITE_DISPLAYMODE or SmartDG_DUAL_DISPLAYMODE)

	//////////////////////////////////////////////////
	/// \fn DependencyMonitor()
	/// \brief Constructor
	///
	/// - Initializes data\n
	/// - Calls DependencyMonitor::setup()
	///
	///	\see DependencyMonitor(string GraphAndMonitorName, string mode)
	///	\see DependencyMonitor(string MonitorName, string GraphName, string ViewName, string mode)
	///	\see DependencyMonitor(DependencyMonitor from, string MonitorName, string GraphName, string ViewName, string mode)
	//////////////////////////////////////////////////
	DependencyMonitor();
	//////////////////////////////////////////////////
	/// \fn DependencyMonitor(string GraphAndMonitorName, string mode)
	/// \brief Constructor that fills [Name], [DG.Name] and [Mode] from user arguments
	///
	/// - Initializes data\n
	/// - Calls DependencyMonitor::setup()
	///
	///	\see DependencyMonitor()
	///	\see DependencyMonitor(string MonitorName, string GraphName, string ViewName, string mode)
	///	\see DependencyMonitor(DependencyMonitor from, string MonitorName, string GraphName, string ViewName, string mode)
	//////////////////////////////////////////////////
	DependencyMonitor(string GraphAndMonitorName, string mode);
	//////////////////////////////////////////////////
	/// \fn DependencyMonitor(string MonitorName, string GraphName, string ViewName, string mode)
	/// \brief Constructor that fills [Name], [DG.Name], [currentView or currentComponent] and [Mode] from user arguments
	///
	/// - Initializes data\n
	/// - Calls DependencyMonitor::setup()
	///
	///	\see DependencyMonitor()
	///	\see DependencyMonitor(string GraphAndMonitorName, string mode)
	///	\see DependencyMonitor(DependencyMonitor from, string MonitorName, string GraphName, string ViewName, string mode)
	//////////////////////////////////////////////////
	DependencyMonitor(string MonitorName, string GraphName, string ViewName,
			string mode);
	//////////////////////////////////////////////////
	/// \fn DependencyMonitor(DependencyMonitor from, string MonitorName, string GraphName, string ViewName, string mode)
	/// \brief Constructor that fills [DG], [Name], [DG.Name], [currentView or currentComponent] and [Mode] from user arguments
	///
	/// - Initializes data\n
	/// - Calls DependencyMonitor::setup()\n
	/// - Copies from.DG --> DG
	///
	///	\see DependencyMonitor()
	///	\see DependencyMonitor(string GraphAndMonitorName, string mode)
	///	\see DependencyMonitor(string MonitorName, string GraphName, string ViewName, string mode)
	//////////////////////////////////////////////////
	DependencyMonitor(DependencyMonitor from, string MonitorName,
			string GraphName, string ViewName, string mode);
	//////////////////////////////////////////////////
	/// \fn void Init()
	/// \brief Initializes GUI for DependencyObject View
	///
	/// - Initializes GUI\n
	/// - Populates Menu bar items\n
	/// - Draws
	///
	///	\see void InitComponent()
	/// \see void InitMT()
	//////////////////////////////////////////////////
	void Init();
	//////////////////////////////////////////////////
	/// \fn void InitComponent()
	/// \brief Initializes GUI for DependencyNode View (Component View)
	///
	/// - Initializes GUI\n
	/// - Populates Menu bar items\n
	/// - Draws
	///
	///	\see void InitComponent()
	/// \see void InitMT()
	//////////////////////////////////////////////////
	void InitComponent();
	//////////////////////////////////////////////////
	/// \fn void Show(string displaymode = SmartDG_DUAL_DISPLAYMODE)
	/// \brief Takes DependencyMonitor::Mode as argument and shows GUI accordingly
	/// \param displaymode is SmartDG_FLTK_DISPLAYMODE or SmartDG_LITE_DISPLAYMODE or SmartDG_DUAL_DISPLAYMODE (default)
	///
	/// - Shows GUI\n
	/// - Default value for displaymode argument is SmartDG_DUAL_DISPLAYMODE
	///
	//////////////////////////////////////////////////
	void Show(string displaymode = SmartDG_DUAL_DISPLAYMODE);

	virtual ~DependencyMonitor();
};

} /* namespace SmartDG */

#endif /* DEPENDENCYMONITOR_H_ */
