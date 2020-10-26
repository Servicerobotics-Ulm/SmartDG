////////////////////////////////////////////////////////////////////////////////
///	\file	SmartDG
/// \brief	Header file for SmartDG library
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

#ifndef SMARTDG_H_
#define SMARTDG_H_

//=============================== Generic CPP
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>

using namespace std;

//=============================== Generic FL
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Tabs.H>

//=============================== Specific FL
namespace SmartDG {

#define SmartDG_WIKI "www.servicerobotik-ulm.de\nSmart Dependency Graph (SmartDG)\nVineet.Nagrath@thu.de"
#define SmartDG_BusinessViewWindowTitleBase "Dependency Graph Business View"
#define SmartDG_BaseLite "DGlite"
#define SmartDG_LiteFolderLocation "."
#define SmartDG_LiteFoldername "SmartDGlite"

// SIGNALS
#define SmartDG_OK string("OK")
#define SmartDG_NOT_OK string("NOTOK")
#define SmartDG_OBJECT_MODE string("OBJECT")
#define SmartDG_COMPONENT_MODE string("COMPONENT")
#define SmartDG_COMPONENT_DEVELOPER_MODE string("COMPONENT_DEVELOPER")
#define SmartDG_DUAL_MODE string("DUAL")
#define SmartDG_FLTK_DISPLAYMODE string("FLTK_DISPLAY")
#define SmartDG_LITE_DISPLAYMODE string("LITE_DISPLAY")
#define SmartDG_DUAL_DISPLAYMODE string("DUAL_DISPLAY")

// #TODO
#define SmartDG_COMPONENT_TEST_MODE string("COMPONENT_TEST")
#define SmartDG_SYSTEM_TEST_MODE string("SYSTEM_TEST")

// Window Geometry
#define SmartDG_BusinessViewWindowWIDTH Fl::w()/2
#define SmartDG_BusinessViewWindowHEIGHT Fl::h()/2
#define SmartDG_MENUHEIGHT SmartDG_BusinessViewWindowHEIGHT/25
//#define MENUHEIGHT 25
#define SmartDG_SCALEFACTOR 1.5
#define SmartDG_COMPWIDTH  150*SmartDG_SCALEFACTOR
#define SmartDG_COMPHEIGHT 200*SmartDG_SCALEFACTOR
#define SmartDG_FIX_COMP_MIN_HEIGHT false
#define SmartDG_IX 50*SmartDG_SCALEFACTOR
#define	SmartDG_IW 20*SmartDG_SCALEFACTOR
#define SmartDG_IXX 0*SmartDG_SCALEFACTOR
#define	SmartDG_IWW 10*SmartDG_SCALEFACTOR
#define SmartDG_TAB 40*SmartDG_SCALEFACTOR
#define SmartDG_LINETHICKNESS 2*SmartDG_SCALEFACTOR
#define SmartDG_COMPRESSFLAG false
#define SmartDG_LSIZE 10*SmartDG_SCALEFACTOR
#define SmartDG_LDSIZEX 80*SmartDG_SCALEFACTOR
#define SmartDG_LDSIZEY 50*SmartDG_SCALEFACTOR
#define SmartDG_NMENUWIDTH	SmartDG_IW
#define SmartDG_NMENUHEIGHT	SmartDG_IW
#define SmartDG_GRIDBLOCKSIZE 20*SmartDG_SCALEFACTOR
#define USEGRID false
// Multi Window Geometry
#define SmartDG_SPACER 200 // 2000 for display in second monitor on the right
#define SmartDG_LOX SmartDG_SPACER
//#define LOX 0
#define SmartDG_LOY 0
#define SmartDG_LOXs 10
#define SmartDG_LOYs 50
// Component Mode
#define SmartDG_COMPONENTMODE_SCALE 1
#define SmartDG_COMPONENTMODE_BusinessViewWindowWIDTH Fl::w()/1.2
#define SmartDG_COMPONENTMODE_BusinessViewWindowHEIGHT Fl::h()/1.2
#define SmartDG_CMS SmartDG_COMPONENTMODE_SCALE
#define SmartDG_COMPONENTMODE_MARGIN_TOP 100
#define SmartDG_COMPONENTMODE_MARGIN_SIDE 50
#define SmartDG_COMPONENTMODE_MARGIN_WIRE 10

//////// Window Color Palettes
#define SmartDG_PALETTE_DGMONITOR	0
#define SmartDG_PALETTE_SMARTSOFT	1

//// DEFINE THE PALETTE TO BE USED
//#define SmartDG_PALETTE SmartDG_PALETTE_DGMONITOR
#define SmartDG_PALETTE SmartDG_PALETTE_SMARTSOFT

//// DO NOT CHANGE 														START
#ifndef SmartDG_PALETTE
#define SmartDG_PALETTE_USE 0
#else
#define SmartDG_PALETTE_USE SmartDG_PALETTE
#endif

// SmartDG_PALETTE_DGMONITOR
#if SmartDG_PALETTE_USE == SmartDG_PALETTE_DGMONITOR
//// Base colors
#define SmartDG_BACKGROUND_COLOR	FL_BACKGROUND_COLOR
#define SmartDG_CANVAS_COLOR FL_DARK1
#define SmartDG_MENU_COLOR	FL_BACKGROUND_COLOR
#define SmartDG_MENU_TEXT_COLOR	FL_FOREGROUND_COLOR
#define SmartDG_NODE_COLOR FL_BACKGROUND_COLOR
#define SmartDG_NODE_IN_USE_COLOR FL_BLUE
#define SmartDG_NODE_IN_NOUSE_COLOR FL_DARK_BLUE
#define SmartDG_NODE_OUT_USE_COLOR FL_RED
#define SmartDG_NODE_OUT_NOUSE_COLOR FL_DARK_RED
#define SmartDG_NODE_MENU_COLOR	FL_BACKGROUND_COLOR
#define SmartDG_NODE_MENU_TEXT_COLOR	FL_FOREGROUND_COLOR
// Port and Object shapes
#define SmartDG_SHAPE_1	FL_DIAMOND_BOX
#define SmartDG_SHAPE_2	FL_FLAT_BOX
#define SmartDG_INOUTPORT_SHAPE	SmartDG_SHAPE_1
#define SmartDG_INOUTOBJECT_SHAPE	SmartDG_SHAPE_1
//// Border color of In and Out bounding boxes
#define SmartDG_GUIDECOLOR FL_NUM_GRAY
//// Color of Connectors Joining Dependency Nodes
// Line Color
#define SmartDG_LCOLOR	FL_GRAY
// Line Label Color
#define SmartDG_LLCOLOR FL_BLACK
#endif

// SmartDG_PALETTE_SMARTSOFT
#if SmartDG_PALETTE_USE == SmartDG_PALETTE_SMARTSOFT
//// Base colors
#define SmartDG_BACKGROUND_COLOR	FL_BACKGROUND_COLOR
#define SmartDG_CANVAS_COLOR FL_WHITE
#define SmartDG_MENU_COLOR	30
#define SmartDG_MENU_TEXT_COLOR	FL_WHITE
#define SmartDG_NODE_COLOR FL_WHITE
#define SmartDG_NODE_IN_USE_COLOR FL_BLUE
#define SmartDG_NODE_IN_NOUSE_COLOR FL_DARK_BLUE
#define SmartDG_NODE_OUT_USE_COLOR FL_RED
#define SmartDG_NODE_OUT_NOUSE_COLOR FL_DARK_RED
#define SmartDG_NODE_MENU_COLOR	FL_WHITE
#define SmartDG_NODE_MENU_TEXT_COLOR	FL_BLACK
// Port and Object shapes
#define SmartDG_SHAPE_1	FL_DIAMOND_BOX
#define SmartDG_SHAPE_2	FL_FLAT_BOX
#define SmartDG_INOUTPORT_SHAPE	SmartDG_SHAPE_2
#define SmartDG_INOUTOBJECT_SHAPE	SmartDG_SHAPE_1
//// Border color of In and Out bounding boxes
#define SmartDG_GUIDECOLOR FL_BLUE
//// Color of Connectors Joining Dependency Nodes
// Line Color
#define SmartDG_LCOLOR	FL_GRAY
// Line Label Color
#define SmartDG_LLCOLOR FL_BLACK
#endif
//// DO NOT CHANGE 														END

// Verbose
#define SmartDG_Verbose false
#define SmartDG_MonitorWindowMenuBarVerbose 	SmartDG_Verbose & false
#define SmartDG_NodeMenuBarVerbose 				SmartDG_Verbose & false
#define SmartDG_SolverVerbose 					SmartDG_Verbose & false
#define SmartDG_SyncVerbose 					SmartDG_Verbose & false
#define SmartDG_SyncLiteVerbose					SmartDG_Verbose & false
#define SmartDG_TransferFunctionsVerbose 		SmartDG_Verbose & false
#define SmartDG_TFV SmartDG_TransferFunctionsVerbose
#define SmartDG_RefreshEditMenuVerbose 			SmartDG_Verbose & false
#define SmartDG_RefreshNodeEditMenuVerbose 		SmartDG_Verbose & false
#define SmartDG_WIDTH_OF_LONGEST_ENTRY 50
#define SmartDG_COLUMN_WIDTH SmartDG_WIDTH_OF_LONGEST_ENTRY + 4

// Debug
#define SmartDG_DEBUG false
#define SmartDG_DEBUG_ToggleAll SmartDG_DEBUG * true

// Solver
#define SmartDG_CIRCULAR_DEPENDENCY_BREAKOUT_COUNT 1000

// Sync
#define SmartDG_SYNC true
#define SmartDG_View2ViewFlag_DEFAULT_VALUE SmartDG_SYNC * true
#define SmartDG_SolverSync_DEFAULT_VALUE 	SmartDG_SYNC * true

// System Commands
#define SmartDG_XMESSAGE_SYNC_COMMAND "xmessage \"Synchronizing... Please Wait.\" -timeout 1 &"
#define SmartDG_PRINT_SCREEN_COMMAND "gnome-screenshot -w &"
#define SmartDG_Lite_Server_Launch_COMMAND "browser-sync start --server --directory --files '**/*'"
#define SmartDG_Lite_Launch_COMMAND_Chrome "google-chrome SmartDGlite/DGlite.html &"
#define SmartDG_Lite_Launch_COMMAND_Firefox "firefox SmartDGlite/DGlite.html &"

// Delays In milliseconds
#define SmartDG_SLEEP_BETWEEN_SYNCOUT_SYNCIN 100
#define SmartDG_SLEEP_BETWEEN_SYNLITE 2000
#define SmartDG_SLEEP_BEFORE_PRINT_SCREEN_COMMAND 1000
#define SmartDG_SLEEP_AFTER_SERVER_LAUNCH_COMMAND 1000

//GOD
#define SmartDG_DEFAULT_NUMGOD 12
#define SmartDG_DEFAULT_GODSTR "#"
} /* namespace SmartDG */

//=============================== Specific CPP
#include "DependencyDescriptor.h"
#include "GUIPoint.h"
#include "URL.h"
#include "DependencyDataPackage.h"
namespace SmartDG_GlobalData {
extern map<string, map<string, SmartDG::DependencyDataPackage> > GlobalPackage;
}
namespace SmartDG_GlobalData {
extern map<string, string> GlobalPackageLite;
}
namespace SmartDG_GlobalData {
extern map<string, SmartDG::DependencyDataPackage> GlobalDebug;
}
namespace SmartDG_GlobalData {
extern bool View2ViewFlag;
}
namespace SmartDG_GlobalData {
extern int togglelive;
}
#include "GUILine.h"
#include "GUIText.h"
#include "GUIConnection.h"
#include "DependencyObject.h"
#include "DependencyPort.h"
#include "DependencyNode.h"
namespace SmartDG_GlobalFunction {
extern void EnvironmentGenerator(vector<string> &SmartDependencyObjects,
		map<string, bool> &isMultiSmartDependencyObjects,
		vector<string> &SmartComponents, SmartDG__map &TransferFunctions,
		map<string, vector<string>> &InputPorts,
		map<string, vector<string>> &OutputPorts,
		map<string, vector<string>> &InputObjectInstances,
		map<string, vector<string>> &OutputObjectInstances,
		vector<string> &SmartConnectors, map<string, string> &Wiki);
extern void Makedgdatajson(string Location = SmartDG_LiteFolderLocation);
}
#include "Dependency.h"
#include "Environment.h"
#include "TransferFunctionsNullNode.h"
#include "TransferFunctionsIdealConnector.h"
#include "DependencyObjectInstance.h"
#include "DependencyObjectInstances.h"
#include "DependencyGraph.h"
#include "DependencyMonitor.h"
#include "SmartDGGenerator.h"

#endif /* SMARTDG_H_ */
