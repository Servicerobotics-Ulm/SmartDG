////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyMonitor.cpp
/// \brief	Source file for DependencyMonitor class
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

#include "SmartDG.h"

namespace SmartDG {

//														Public Member Functions
// Default Constructor
DependencyMonitor::DependencyMonitor() {
	// Initializes data
	Name = "NA_DM";
	currentView = "NA_V";
	// Calls DependencyMonitor::setup()
	setup();
}

// Constructor that fills [Name], [DG.Name] and [Mode] from user arguments
DependencyMonitor::DependencyMonitor(string GraphAndMonitorName, string mode) {
	// Initializes data
	Name = GraphAndMonitorName;
	DG.Name = GraphAndMonitorName;
	Mode = mode;
	if (Mode == SmartDG_OBJECT_MODE)
		currentView = "NA_V";
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE))
		currentComponent = "NA_C";
	// Calls DependencyMonitor::setup()
	setup();
}

// Constructor that fills [Name], [DG.Name], [currentView or currentComponent] and [Mode] from user arguments
DependencyMonitor::DependencyMonitor(string MonitorName, string GraphName,
		string ViewName, string mode) {
	// Initializes data
	Name = MonitorName;
	DG.Name = GraphName;
	Mode = mode;
	currentView = "NA_V";
	currentComponent = "NA_C";
	if (Mode == SmartDG_OBJECT_MODE)
		currentView = ViewName;
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE))
		currentComponent = ViewName;
	// Calls DependencyMonitor::setup()
	setup();
}

// Constructor that fills [DG], [Name], [DG.Name], [currentView or currentComponent] and [Mode] from user arguments
DependencyMonitor::DependencyMonitor(DependencyMonitor from, string MonitorName,
		string GraphName, string ViewName, string mode) {
	// Initializes data
	Name = MonitorName;
	DG.Name = GraphName;
	Mode = mode;
	currentView = "NA_V";
	currentComponent = "NA_C";
	if (Mode == SmartDG_OBJECT_MODE)
		currentView = ViewName;
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE))
		currentComponent = ViewName;
	// Calls DependencyMonitor::setup()
	setup();
	// Copies from.DG --> DG
	DG = from.DG;
}

void DependencyMonitor::Init() {
	MonitorWindow = new Fl_Double_Window(lox, loy,
	SmartDG_BusinessViewWindowWIDTH, SmartDG_BusinessViewWindowHEIGHT,
			BusinessViewWindowTitle.c_str());
	MonitorWindow->resizable(MonitorWindow);
	MonitorWindow->color(SmartDG_BACKGROUND_COLOR);
	MonitorWindowMenuBar = new Fl_Menu_Bar(0, 0, MonitorWindow->w(),
	SmartDG_MENUHEIGHT);
	MonitorWindowMenuBar->color(SmartDG_MENU_COLOR);
	MonitorWindowMenuBar->textcolor(SmartDG_MENU_TEXT_COLOR);

	// Adding MonitorWindowMenuBar Items
	// DGMonitor
	MonitorWindowMenuBar->add("DGMonitor/Wiki", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartDependencyObjects", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartComponents", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/TransferFunctions", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/InputPorts", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/OutputPorts", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add(
			"DGMonitor/Environment/ObjectInstance/InputObjectInstances", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add(
			"DGMonitor/Environment/ObjectInstance/OutputObjectInstances", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/ObjectInstance/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartConnectors", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Print Screen", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Sync/Allow", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Sync/Block", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Exit All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Exit", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	// Debug
	if (SmartDG_DEBUG_ToggleAll) {
		MonitorWindowMenuBar->add("Debug/ToggleAll/True", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/False", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/SyncOut", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/SyncIn", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
	}
	// Business
	MonitorWindowMenuBar->add("Business/Forward", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Business/Reverse", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	// Edit
	if (Mode == SmartDG_OBJECT_MODE) {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].obj == currentView) {
				string tmp3 = "Edit/" + DG.DOI.I[i].amidL + "/true";
				MonitorWindowMenuBar->add(tmp3.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
				string tmp4 = "Edit/" + DG.DOI.I[i].amidL + "/false";
				MonitorWindowMenuBar->add(tmp4.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
			}
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].obj == currentView) {
				string tmp1 = "Edit/" + DG.DOI.I[i].midL + "/true";
				MonitorWindowMenuBar->add(tmp1.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
				string tmp2 = "Edit/" + DG.DOI.I[i].midL + "/false";
				MonitorWindowMenuBar->add(tmp2.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
			}
		}
	}
	// Sync
	MonitorWindowMenuBar->add("Sync/Refresh", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/Attach", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/Detach", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/⟰ Upload", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/⟱ Download", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/SolverSync/Enable", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Sync/SolverSync/Disable", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	if (!SmartDG_View2ViewFlag_DEFAULT_VALUE) {
		ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", false);
		ShowHideMonitorWindowMenuBar("Sync/⟱ Download", false);
		ShowHideMonitorWindowMenuBar("Sync/SolverSync", false);
	}
	ResetDOIFlags(false, 0);
	RefreshEditMenu();
	RefreshNodeEditMenu();
	//Adding DG
	BigGroup = new Fl_Group(2, SmartDG_MENUHEIGHT + 2,
	SmartDG_BusinessViewWindowWIDTH - 4, SmartDG_BusinessViewWindowHEIGHT - 4);
	BigGroup->align(FL_ALIGN_INSIDE);
	MonitorWindowScroll = new Fl_Scroll(2, SmartDG_MENUHEIGHT + 20,
	SmartDG_BusinessViewWindowWIDTH - 4, SmartDG_BusinessViewWindowHEIGHT - 4);
	MonitorWindowScroll->box(FL_FLAT_BOX);
	MonitorWindowScroll->color(SmartDG_CANVAS_COLOR);
	MonitorWindowScroll->align(FL_ALIGN_TOP);
	GenDispStr();
	MonitorWindowScroll->label(DispString.c_str());
	MonitorWindowScroll->begin();

	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		DG.DN[i].Shape = new Fl_Group(DG.DN[i].x, DG.DN[i].y,
		SmartDG_COMPWIDTH, SmartDG_COMPHEIGHT, DG.DN[i].Name.c_str());
		DG.DN[i].Shape->box(FL_UP_BOX);
		DG.DN[i].Shape->align(FL_ALIGN_BOTTOM_RIGHT);
		DG.DN[i].Shape->color(SmartDG_NODE_COLOR);

		DG.DN[i].BarIn = new Fl_Menu_Bar(DG.DN[i].x, DG.DN[i].y,
		SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT, DG.DN[i].Name.c_str());
		DG.DN[i].BarIn->color(SmartDG_NODE_MENU_COLOR);
		DG.DN[i].BarIn->textcolor(SmartDG_NODE_MENU_TEXT_COLOR);
		if (Mode == SmartDG_OBJECT_MODE) {
			for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
				if (DG.DOI.I[j].obj == currentView) {
					if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
							&& (DG.DOI.I[j].pou.strio == "In")) {
						DG.DN[i].BarIn->add(
								string("✎/" + DG.DOI.I[j].amid + "/true").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
						DG.DN[i].BarIn->add(
								string("✎/" + DG.DOI.I[j].amid + "/false").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
					}
				}
			}
			for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
				if (DG.DOI.I[j].obj == currentView) {
					if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
							&& (DG.DOI.I[j].pou.strio == "In")) {
						DG.DN[i].BarIn->add(
								string("✎/" + DG.DOI.I[j].mid + "/true").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
						DG.DN[i].BarIn->add(
								string("✎/" + DG.DOI.I[j].mid + "/false").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
					}
				}
			}
		}

		DG.DN[i].BarOut = new Fl_Menu_Bar(
				DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_NMENUWIDTH, DG.DN[i].y,
				SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT, DG.DN[i].Name.c_str());
		DG.DN[i].BarOut->color(SmartDG_NODE_MENU_COLOR);
		DG.DN[i].BarOut->textcolor(SmartDG_NODE_MENU_TEXT_COLOR);
		if (Mode == SmartDG_OBJECT_MODE) {
			for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
				if (DG.DOI.I[j].obj == currentView) {
					if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
							&& (DG.DOI.I[j].pou.strio == "Out")) {
						DG.DN[i].BarOut->add(
								string("✎/" + DG.DOI.I[j].amid + "/true").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
						DG.DN[i].BarOut->add(
								string("✎/" + DG.DOI.I[j].amid + "/false").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
					}
				}
			}
			for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
				if (DG.DOI.I[j].obj == currentView) {
					if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
							&& (DG.DOI.I[j].pou.strio == "Out")) {
						DG.DN[i].BarOut->add(
								string("✎/" + DG.DOI.I[j].mid + "/true").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
						DG.DN[i].BarOut->add(
								string("✎/" + DG.DOI.I[j].mid + "/false").c_str(),
								0, Static_NodeMenuBar_Callback, (void*) this);
					}
				}
			}
		}

		DG.DN[i].ShapeI = new Fl_Group(DG.DN[i].x + SmartDG_IX, DG.DN[i].y + 2,
		SmartDG_IW, SmartDG_COMPHEIGHT - 4, "In");
		DG.DN[i].ShapeI->box(FL_BORDER_FRAME);
		DG.DN[i].ShapeI->color(SmartDG_GUIDECOLOR);
		DG.DN[i].ShapeI->align(FL_ALIGN_TOP);
		unsigned int CursorI = DG.DN[i].y + 2;
		for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
			DG.DN[i].DP[0][j].Shape = new Fl_Group(DG.DN[i].x + SmartDG_IX,
					CursorI, SmartDG_IW, SmartDG_IW,
					DG.DN[i].DP[0][j].Name.c_str());
			unsigned int t;
			if (SmartDG_COMPRESSFLAG)
				t = CursorI + SmartDG_IW;
			else
				CursorI += SmartDG_IW;
			DG.DN[i].DP[0][j].Shape->box(SmartDG_INOUTPORT_SHAPE);
			DG.DN[i].DP[0][j].Shape->color(SmartDG_NODE_IN_USE_COLOR);
			DG.DN[i].DP[0][j].Shape->labelcolor(SmartDG_NODE_IN_USE_COLOR);
			DG.DN[i].DP[0][j].Shape->align(FL_ALIGN_LEFT);
			for (unsigned int l = 0; l < DG.DN[i].DP[0][j].DO.size(); l++) {
				DG.DN[i].DP[0][j].DO[l].Shape = new Fl_Group(
						DG.DN[i].x + SmartDG_IXX, CursorI, SmartDG_IWW,
						SmartDG_IWW, DG.DN[i].DP[0][j].DO[l].Name.c_str());
				CursorI += SmartDG_IWW + 1;
				DG.DN[i].DP[0][j].DO[l].Shape->box(SmartDG_INOUTOBJECT_SHAPE);
				if (Mode == SmartDG_OBJECT_MODE) {
					if (DG.DN[i].DP[0][j].DO[l].Name == currentView) {
						DG.DN[i].DP[0][j].DO[l].Shape->color(
						SmartDG_NODE_IN_USE_COLOR);
						DG.DN[i].DP[0][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_IN_USE_COLOR);
					} else {
						DG.DN[i].DP[0][j].DO[l].Shape->color(
						SmartDG_NODE_IN_NOUSE_COLOR);
						DG.DN[i].DP[0][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_IN_NOUSE_COLOR);
					}
				}
				DG.DN[i].DP[0][j].DO[l].Shape->align(FL_ALIGN_RIGHT);
			}
			if (SmartDG_COMPRESSFLAG) {
				if (CursorI <= t)
					CursorI = t;
				else
					CursorI += SmartDG_IWW;
			}
		}

		DG.DN[i].ShapeO = new Fl_Group(
				DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
				DG.DN[i].y + 2,
				SmartDG_IW, SmartDG_COMPHEIGHT - 4, "Out");
		DG.DN[i].ShapeO->box(FL_BORDER_FRAME);
		DG.DN[i].ShapeO->color(SmartDG_GUIDECOLOR);
		DG.DN[i].ShapeO->align(FL_ALIGN_TOP);
		unsigned int CursorO = DG.DN[i].y + 2;
		for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
			DG.DN[i].DP[1][j].Shape = new Fl_Group(
					DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
					CursorO, SmartDG_IW, SmartDG_IW,
					DG.DN[i].DP[1][j].Name.c_str());
			unsigned int t;
			if (SmartDG_COMPRESSFLAG)
				t = CursorO + SmartDG_IW;
			else
				CursorO += SmartDG_IW;
			DG.DN[i].DP[1][j].Shape->box(SmartDG_INOUTPORT_SHAPE);
			DG.DN[i].DP[1][j].Shape->color(SmartDG_NODE_OUT_USE_COLOR);
			DG.DN[i].DP[1][j].Shape->labelcolor(SmartDG_NODE_OUT_USE_COLOR);
			DG.DN[i].DP[1][j].Shape->align(FL_ALIGN_RIGHT);
			for (unsigned int l = 0; l < DG.DN[i].DP[1][j].DO.size(); l++) {
				DG.DN[i].DP[1][j].DO[l].Shape = new Fl_Group(
						DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_IXX
								- SmartDG_IWW, CursorO, SmartDG_IWW,
						SmartDG_IWW, DG.DN[i].DP[1][j].DO[l].Name.c_str());
				CursorO += SmartDG_IWW + 1;
				DG.DN[i].DP[1][j].DO[l].Shape->box(SmartDG_INOUTOBJECT_SHAPE);
				if (Mode == SmartDG_OBJECT_MODE) {
					if (DG.DN[i].DP[1][j].DO[l].Name == currentView) {
						DG.DN[i].DP[1][j].DO[l].Shape->color(
						SmartDG_NODE_OUT_USE_COLOR);
						DG.DN[i].DP[1][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_OUT_USE_COLOR);
					} else {
						DG.DN[i].DP[1][j].DO[l].Shape->color(
						SmartDG_NODE_OUT_NOUSE_COLOR);
						DG.DN[i].DP[1][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_OUT_NOUSE_COLOR);
					}
				}
				DG.DN[i].DP[1][j].DO[l].Shape->align(FL_ALIGN_LEFT);
			}
			if (SmartDG_COMPRESSFLAG) {
				if (CursorO <= t)
					CursorO = t;
				else
					CursorO += SmartDG_IWW;
			}
		}
		unsigned int CursorMax = max(CursorI, CursorO);

		if ((CursorMax > SmartDG_COMPHEIGHT)
				|| !(SmartDG_FIX_COMP_MIN_HEIGHT)) {
			DG.DN[i].Shape->resize(DG.DN[i].x, DG.DN[i].y,
			SmartDG_COMPWIDTH, CursorMax - DG.DN[i].y + SmartDG_IW);
			// Readjusts after Node Shape resize
			DG.DN[i].ShapeI->resize(DG.DN[i].x + SmartDG_IX, DG.DN[i].y + 2,
			SmartDG_IW, CursorMax - DG.DN[i].y + SmartDG_IW - 4);
			DG.DN[i].BarIn->resize(DG.DN[i].x, DG.DN[i].y,
			SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT);
			if (DG.DN[i].DP[0].size() > 0)
				DG.DN[i].DP[0][0].Shape->resize(DG.DN[i].x + SmartDG_IX,
						DG.DN[i].y + 2,
						SmartDG_IW, SmartDG_IW);
			DG.DN[i].ShapeO->resize(
					DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
					DG.DN[i].y + 2,
					SmartDG_IW, CursorMax - DG.DN[i].y + SmartDG_IW - 4);
			DG.DN[i].BarOut->resize(
					DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_NMENUWIDTH,
					DG.DN[i].y,
					SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT);
			if (DG.DN[i].DP[1].size() > 0)
				DG.DN[i].DP[1][0].Shape->resize(
						DG.DN[i].x + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
						DG.DN[i].y + 2,
						SmartDG_IW, SmartDG_IW);
		}
		DG.DN[i].Shape->end();
	}
	Generate_Dependency_Tabs();
	ShowLines();
	//Cleanup
	MonitorWindowScroll->end();
	BigGroup->end();
	MonitorWindow->end();
}

void DependencyMonitor::InitComponent() {
	MonitorWindow = new Fl_Double_Window(lox, loy,
	SmartDG_COMPONENTMODE_BusinessViewWindowWIDTH,
	SmartDG_COMPONENTMODE_BusinessViewWindowHEIGHT,
			BusinessViewWindowTitle.c_str());
	MonitorWindow->resizable(MonitorWindow);
	MonitorWindow->color(SmartDG_BACKGROUND_COLOR);
	MonitorWindowMenuBar = new Fl_Menu_Bar(0, 0, MonitorWindow->w(),
	SmartDG_MENUHEIGHT);
	MonitorWindowMenuBar->color(SmartDG_MENU_COLOR);
	MonitorWindowMenuBar->textcolor(SmartDG_MENU_TEXT_COLOR);

	//Adding MonitorWindowMenuBar Items
	// DGMonitor
	MonitorWindowMenuBar->add("DGMonitor/Wiki", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartDependencyObjects", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartComponents", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/TransferFunctions", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/InputPorts", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/OutputPorts", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/Ports/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add(
			"DGMonitor/Environment/ObjectInstance/InputObjectInstances", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add(
			"DGMonitor/Environment/ObjectInstance/OutputObjectInstances", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/ObjectInstance/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/SmartConnectors", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Environment/All", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("DGMonitor/Print Screen", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	if (Mode != SmartDG_COMPONENT_DEVELOPER_MODE) {
		MonitorWindowMenuBar->add("DGMonitor/Sync/Allow", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("DGMonitor/Sync/Block", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("DGMonitor/Exit All", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
	}
	MonitorWindowMenuBar->add("DGMonitor/Exit", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	// Debug
	if (SmartDG_DEBUG_ToggleAll) {
		MonitorWindowMenuBar->add("Debug/ToggleAll/True", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/False", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/SyncOut", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Debug/ToggleAll/SyncIn", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
	}
	// Business
	MonitorWindowMenuBar->add("Business/Forward", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	MonitorWindowMenuBar->add("Business/Reverse", 0,
			Static_MonitorWindowMenuBar_Callback, (void*) this);
	// Edit
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].pou.strn == currentComponent) {
				string tmp3 = "Edit/" + DG.DOI.I[i].amidL + "/true";
				MonitorWindowMenuBar->add(tmp3.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
				string tmp4 = "Edit/" + DG.DOI.I[i].amidL + "/false";
				MonitorWindowMenuBar->add(tmp4.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
			}
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].pou.strn == currentComponent) {
				string tmp1 = "Edit/" + DG.DOI.I[i].midL + "/true";
				MonitorWindowMenuBar->add(tmp1.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
				string tmp2 = "Edit/" + DG.DOI.I[i].midL + "/false";
				MonitorWindowMenuBar->add(tmp2.c_str(), 0,
						Static_MonitorWindowMenuBar_Callback, (void*) this);
			}
		}
	}
	// Sync
	if (Mode != SmartDG_COMPONENT_DEVELOPER_MODE) {
		MonitorWindowMenuBar->add("Sync/Refresh", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/Attach", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/Detach", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/⟰ Upload", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/⟱ Download", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/SolverSync/Enable", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		MonitorWindowMenuBar->add("Sync/SolverSync/Disable", 0,
				Static_MonitorWindowMenuBar_Callback, (void*) this);
		if (!SmartDG_View2ViewFlag_DEFAULT_VALUE) {
			ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", false);
			ShowHideMonitorWindowMenuBar("Sync/⟱ Download", false);
			ShowHideMonitorWindowMenuBar("Sync/SolverSync", false);
		}
	}
	ResetDOIFlags(false, 0);
	RefreshEditMenu();
	RefreshNodeEditMenu();
	//Adding DG
	BigGroup = new Fl_Group(2, SmartDG_MENUHEIGHT + 2,
	SmartDG_COMPONENTMODE_BusinessViewWindowWIDTH - 4,
	SmartDG_COMPONENTMODE_BusinessViewWindowHEIGHT - 4);
	BigGroup->align(FL_ALIGN_INSIDE);
	MonitorWindowScroll = new Fl_Scroll(2, SmartDG_MENUHEIGHT + 20,
	SmartDG_COMPONENTMODE_BusinessViewWindowWIDTH - 4,
	SmartDG_COMPONENTMODE_BusinessViewWindowHEIGHT - 4);
	MonitorWindowScroll->box(FL_FLAT_BOX);
	MonitorWindowScroll->color(SmartDG_CANVAS_COLOR);
	MonitorWindowScroll->align(FL_ALIGN_TOP);
	GenDispStr();
	MonitorWindowScroll->label(DispString.c_str());
	MonitorWindowScroll->begin();

	unsigned int midx = SmartDG_COMPONENTMODE_BusinessViewWindowWIDTH/2;
	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		if (DG.DN[i].Name == currentComponent) {

			unsigned int nodex = midx - SmartDG_COMPWIDTH / 2;
			unsigned int nodey = SmartDG_COMPONENTMODE_MARGIN_TOP;

			DG.DN[i].Shape = new Fl_Group(nodex, nodey,
			SmartDG_COMPWIDTH, SmartDG_COMPHEIGHT, DG.DN[i].Name.c_str());
			DG.DN[i].Shape->box(FL_UP_BOX);
			DG.DN[i].Shape->align(FL_ALIGN_BOTTOM_RIGHT);
			DG.DN[i].Shape->color(SmartDG_NODE_COLOR);

			DG.DN[i].BarIn = new Fl_Menu_Bar(nodex, nodey,
			SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT, DG.DN[i].Name.c_str());
			DG.DN[i].BarIn->color(SmartDG_NODE_MENU_COLOR);
			DG.DN[i].BarIn->textcolor(SmartDG_NODE_MENU_TEXT_COLOR);
			if ((Mode == SmartDG_COMPONENT_MODE)
					|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
				for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
					if (DG.DOI.I[j].pou.strn == currentComponent) {
						if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
								&& (DG.DOI.I[j].pou.strio == "In")) {
							DG.DN[i].BarIn->add(
									string("✎/" + DG.DOI.I[j].amid + "/true").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
							DG.DN[i].BarIn->add(
									string("✎/" + DG.DOI.I[j].amid + "/false").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
						}
					}
				}
				for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
					if (DG.DOI.I[j].pou.strn == currentComponent) {
						if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
								&& (DG.DOI.I[j].pou.strio == "In")) {
							DG.DN[i].BarIn->add(
									string("✎/" + DG.DOI.I[j].mid + "/true").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
							DG.DN[i].BarIn->add(
									string("✎/" + DG.DOI.I[j].mid + "/false").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
						}
					}
				}
			}

			DG.DN[i].BarOut = new Fl_Menu_Bar(
					nodex + SmartDG_COMPWIDTH - SmartDG_NMENUWIDTH, nodey,
					SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT,
					DG.DN[i].Name.c_str());
			DG.DN[i].BarOut->color(SmartDG_NODE_MENU_COLOR);
			DG.DN[i].BarOut->textcolor(SmartDG_NODE_MENU_TEXT_COLOR);
			if ((Mode == SmartDG_COMPONENT_MODE)
					|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
				for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
					if (DG.DOI.I[j].pou.strn == currentComponent) {
						if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
								&& (DG.DOI.I[j].pou.strio == "Out")) {
							DG.DN[i].BarOut->add(
									string("✎/" + DG.DOI.I[j].amid + "/true").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
							DG.DN[i].BarOut->add(
									string("✎/" + DG.DOI.I[j].amid + "/false").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
						}
					}
				}
				for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
					if (DG.DOI.I[j].pou.strn == currentComponent) {
						if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
								&& (DG.DOI.I[j].pou.strio == "Out")) {
							DG.DN[i].BarOut->add(
									string("✎/" + DG.DOI.I[j].mid + "/true").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
							DG.DN[i].BarOut->add(
									string("✎/" + DG.DOI.I[j].mid + "/false").c_str(),
									0, Static_NodeMenuBar_Callback,
									(void*) this);
						}
					}
				}
			}
			DG.DN[i].ShapeI = new Fl_Group(nodex + SmartDG_IX, nodey + 2,
			SmartDG_IW, SmartDG_COMPHEIGHT - 4, "In");
			DG.DN[i].ShapeI->box(FL_BORDER_FRAME);
			DG.DN[i].ShapeI->color(SmartDG_GUIDECOLOR);
			DG.DN[i].ShapeI->align(FL_ALIGN_TOP);
			unsigned int CursorI = nodey + 2;
			for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
				DG.DN[i].DP[0][j].Shape = new Fl_Group(nodex + SmartDG_IX,
						CursorI, SmartDG_IW, SmartDG_IW,
						DG.DN[i].DP[0][j].Name.c_str());
				unsigned int t;
				if (SmartDG_COMPRESSFLAG)
					t = CursorI + SmartDG_IW;
				else
					CursorI += SmartDG_IW;
				DG.DN[i].DP[0][j].Shape->box(SmartDG_INOUTPORT_SHAPE);
				DG.DN[i].DP[0][j].Shape->color(SmartDG_NODE_IN_USE_COLOR);
				DG.DN[i].DP[0][j].Shape->labelcolor(SmartDG_NODE_IN_USE_COLOR);
				DG.DN[i].DP[0][j].Shape->align(FL_ALIGN_LEFT);
				for (unsigned int l = 0; l < DG.DN[i].DP[0][j].DO.size(); l++) {
					DG.DN[i].DP[0][j].DO[l].Shape = new Fl_Group(
							nodex + SmartDG_IXX, CursorI, SmartDG_IWW,
							SmartDG_IWW, DG.DN[i].DP[0][j].DO[l].Name.c_str());
					CursorI += SmartDG_IWW + 1;
					DG.DN[i].DP[0][j].DO[l].Shape->box(
					SmartDG_INOUTOBJECT_SHAPE);
					if ((Mode == SmartDG_COMPONENT_MODE)
							|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
						DG.DN[i].DP[0][j].DO[l].Shape->color(
						SmartDG_NODE_IN_USE_COLOR);
						DG.DN[i].DP[0][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_IN_USE_COLOR);
					}
					DG.DN[i].DP[0][j].DO[l].Shape->align(FL_ALIGN_RIGHT);
				}
				if (SmartDG_COMPRESSFLAG) {
					if (CursorI <= t)
						CursorI = t;
					else
						CursorI += SmartDG_IWW;
				}
			}

			DG.DN[i].ShapeO = new Fl_Group(
					nodex + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
					nodey + 2,
					SmartDG_IW, SmartDG_COMPHEIGHT - 4, "Out");
			DG.DN[i].ShapeO->box(FL_BORDER_FRAME);
			DG.DN[i].ShapeO->color(SmartDG_GUIDECOLOR);
			DG.DN[i].ShapeO->align(FL_ALIGN_TOP);
			unsigned int CursorO = nodey + 2;
			for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
				DG.DN[i].DP[1][j].Shape = new Fl_Group(
						nodex + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
						CursorO, SmartDG_IW, SmartDG_IW,
						DG.DN[i].DP[1][j].Name.c_str());
				unsigned int t;
				if (SmartDG_COMPRESSFLAG)
					t = CursorO + SmartDG_IW;
				else
					CursorO += SmartDG_IW;
				DG.DN[i].DP[1][j].Shape->box(SmartDG_INOUTPORT_SHAPE);
				DG.DN[i].DP[1][j].Shape->color(SmartDG_NODE_OUT_USE_COLOR);
				DG.DN[i].DP[1][j].Shape->labelcolor(SmartDG_NODE_OUT_USE_COLOR);
				DG.DN[i].DP[1][j].Shape->align(FL_ALIGN_RIGHT);
				for (unsigned int l = 0; l < DG.DN[i].DP[1][j].DO.size(); l++) {
					DG.DN[i].DP[1][j].DO[l].Shape = new Fl_Group(
							nodex + SmartDG_COMPWIDTH - SmartDG_IXX
									- SmartDG_IWW, CursorO, SmartDG_IWW,
							SmartDG_IWW, DG.DN[i].DP[1][j].DO[l].Name.c_str());
					CursorO += SmartDG_IWW + 1;
					DG.DN[i].DP[1][j].DO[l].Shape->box(
					SmartDG_INOUTOBJECT_SHAPE);
					if ((Mode == SmartDG_COMPONENT_MODE)
							|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
						DG.DN[i].DP[1][j].DO[l].Shape->color(
						SmartDG_NODE_OUT_USE_COLOR);
						DG.DN[i].DP[1][j].DO[l].Shape->labelcolor(
						SmartDG_NODE_OUT_USE_COLOR);
					}
					DG.DN[i].DP[1][j].DO[l].Shape->align(FL_ALIGN_LEFT);
				}
				if (SmartDG_COMPRESSFLAG) {
					if (CursorO <= t)
						CursorO = t;
					else
						CursorO += SmartDG_IWW;
				}
			}
			unsigned int CursorMax = max(CursorI, CursorO);
			if ((CursorMax > SmartDG_COMPHEIGHT)
					|| !(SmartDG_FIX_COMP_MIN_HEIGHT)) {
				DG.DN[i].Shape->resize(nodex, nodey,
				SmartDG_COMPWIDTH, CursorMax - nodey + SmartDG_IW);
				// Readjusts after Node Shape resize
				DG.DN[i].ShapeI->resize(nodex + SmartDG_IX, nodey + 2,
				SmartDG_IW, CursorMax - nodey + SmartDG_IW - 4);
				DG.DN[i].BarIn->resize(nodex, nodey,
				SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT);
				if (DG.DN[i].DP[0].size() > 0)
					DG.DN[i].DP[0][0].Shape->resize(nodex + SmartDG_IX,
							nodey + 2,
							SmartDG_IW, SmartDG_IW);
				DG.DN[i].ShapeO->resize(
						nodex + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
						nodey + 2,
						SmartDG_IW, CursorMax - nodey + SmartDG_IW - 4);
				DG.DN[i].BarOut->resize(
						nodex + SmartDG_COMPWIDTH - SmartDG_NMENUWIDTH, nodey,
						SmartDG_NMENUWIDTH, SmartDG_NMENUHEIGHT);
				if (DG.DN[i].DP[1].size() > 0)
					DG.DN[i].DP[1][0].Shape->resize(
							nodex + SmartDG_COMPWIDTH - SmartDG_IX - SmartDG_IW,
							nodey + 2,
							SmartDG_IW, SmartDG_IW);
			}
			DG.DN[i].Shape->end();
		}
	}
	Generate_Dependency_Tabs();
	ShowLines();
	//Cleanup
	MonitorWindowScroll->end();
	BigGroup->end();
	MonitorWindow->end();
}

void DependencyMonitor::Show(string displaymode) {
	DisplayMode = displaymode;
	MenuJointRefresh();
	if (DisplayMode == SmartDG_FLTK_DISPLAYMODE)
		MonitorWindow->show();
	else {
		InitMT();
		makelitejs();
		SyncOutLiteInit();
		if (DisplayMode == SmartDG_DUAL_DISPLAYMODE)
			MonitorWindow->show();
		if (DisplayMode == SmartDG_LITE_DISPLAYMODE) {
			if (!DependencyMonitor::MTLiteOn) {
				DependencyMonitor::MTLiteOn = true;
				MTWindow->show();
			}
		}
	}
}

//														Private Member Functions

void DependencyMonitor::MonitorWindowMenuBar_Callback() {
	// Identifies selected option from the menu
	char sel[1000];
	MonitorWindowMenuBar->item_pathname(sel, sizeof(sel) - 1);
	string Selection(sel);
	if (SmartDG_MonitorWindowMenuBarVerbose)
		cout << "MonitorWindowMenuBar: " + Selection << endl;
	// Performs action according to selection for the following
	// DGMonitor
	if (Selection == "DGMonitor/Wiki") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Wiki" << endl;
		cout << SmartDG_WIKI << endl;
	}
	if (Selection == "DGMonitor/Environment/SmartDependencyObjects") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/SmartDependencyObjects" << endl;
		cout << "----------------------------SmartDependencyObjects" << endl;
		currentEnvironment.Display(currentEnvironment.SmartDependencyObjects);
	}
	if (Selection == "DGMonitor/Environment/SmartComponents") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/SmartComponents" << endl;
		cout << "----------------------------SmartComponents" << endl;
		currentEnvironment.Display(currentEnvironment.SmartComponents);
	}
	if (Selection == "DGMonitor/Environment/TransferFunctions") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/TransferFunctions" << endl;
		cout << "----------------------------TransferFunctions" << endl;
		currentEnvironment.Display(currentEnvironment.TransferFunctions);
	}
	if (Selection == "DGMonitor/Environment/Ports/InputPorts") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/InputPorts" << endl;
		cout << "----------------------------InputPorts" << endl;
		currentEnvironment.Display(currentEnvironment.InputPorts);
	}
	if (Selection == "DGMonitor/Environment/Ports/OutputPorts") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/OutputPorts" << endl;
		cout << "----------------------------OutputPorts" << endl;
		currentEnvironment.Display(currentEnvironment.OutputPorts);
	}
	if (Selection == "DGMonitor/Environment/Ports/All") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/Ports" << endl;
		cout << "----------------------------Ports" << endl;
		cout << "----------------------------InputPorts" << endl;
		currentEnvironment.Display(currentEnvironment.InputPorts);
		cout << "----------------------------OutputPorts" << endl;
		currentEnvironment.Display(currentEnvironment.OutputPorts);
	}
	if (Selection
			== "DGMonitor/Environment/ObjectInstance/InputObjectInstances") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/InputObjectInstances" << endl;
		cout << "----------------------------InputObjectInstances" << endl;
		currentEnvironment.Display(currentEnvironment.InputObjectInstances);
	}
	if (Selection
			== "DGMonitor/Environment/ObjectInstance/OutputObjectInstances") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/OutputObjectInstances" << endl;
		cout << "----------------------------OutputObjectInstances" << endl;
		currentEnvironment.Display(currentEnvironment.OutputObjectInstances);
	}
	if (Selection == "DGMonitor/Environment/ObjectInstance/All") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/ObjectInstance" << endl;
		cout << "----------------------------ObjectInstance" << endl;
		cout << "----------------------------InputObjectInstances" << endl;
		currentEnvironment.Display(currentEnvironment.InputObjectInstances);
		cout << "----------------------------OutputObjectInstances" << endl;
		currentEnvironment.Display(currentEnvironment.OutputObjectInstances);
	}
	if (Selection == "DGMonitor/Environment/SmartConnectors") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment/SmartConnectors" << endl;
		cout << "----------------------------SmartConnectors" << endl;
		currentEnvironment.Display(currentEnvironment.SmartConnectors);
	}
	if (Selection == "DGMonitor/Environment/All") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Environment" << endl;
		currentEnvironment.Display();
	}
	if (Selection == "DGMonitor/Print Screen") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Print Screen" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(
		SmartDG_SLEEP_BEFORE_PRINT_SCREEN_COMMAND));
		system(SmartDG_PRINT_SCREEN_COMMAND);
	}
	if (Selection == "DGMonitor/Sync/Allow") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "DGMonitor/Sync/Allow" << endl;
		bool tmpval = true;
		View2ViewFlag = tmpval;
		SolverSync = tmpval;
		SmartDG_GlobalData::View2ViewFlag = tmpval;
		ShowHideMonitorWindowMenuBar("Sync/Attach", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/Detach", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/⟱ Download", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/SolverSync", tmpval);
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "DGMonitor/Sync/Block") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "DGMonitor/Sync/Block" << endl;
		bool tmpval = false;
		View2ViewFlag = tmpval;
		SolverSync = tmpval;
		SmartDG_GlobalData::View2ViewFlag = tmpval;
		ShowHideMonitorWindowMenuBar("Sync/Attach", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/Detach", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/⟱ Download", tmpval);
		ShowHideMonitorWindowMenuBar("Sync/SolverSync", tmpval);
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "DGMonitor/Exit") {
		if (SmartDG_MonitorWindowMenuBarVerbose) {
			if (Mode == SmartDG_OBJECT_MODE)
				cout << "Exit ObjectView " << currentView << endl;
			if ((Mode == SmartDG_COMPONENT_MODE)
					|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE))
				cout << "Exit ComponentView " << currentComponent << endl;
		}
		MonitorWindow->hide();
	}
	if (Selection == "DGMonitor/Exit All") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Exit42" << endl;
		exit(0);
	}
	// Debug
	if (SmartDG_DEBUG_ToggleAll) {
		if (SmartDG_GlobalData::GlobalDebug.find("Debug")
				== SmartDG_GlobalData::GlobalDebug.end()) {
			SmartDG::DependencyDataPackage tmp;
			tmp.Set(true);
			SmartDG_GlobalData::GlobalDebug["Debug"] = tmp;
		}
		bool tmpval = true;
		if (Selection == "Debug/ToggleAll/True") {
			cout << "Debug: GlobalDebug[Debug] was "
					<< SmartDG_GlobalData::GlobalDebug["Debug"] << endl;
			tmpval = true;
			SmartDG_GlobalData::GlobalDebug["Debug"].Set(true);
			for (unsigned int n = 0; n < DG.DN.size(); n++) {
				for (unsigned int io = 0; io < DG.DN[n].DP.size(); io++) {
					for (unsigned int p = 0; p < DG.DN[n].DP[io].size(); p++) {
						for (unsigned int o = 0;
								o < DG.DN[n].DP[io][p].DO.size(); o++) {
							for (map<string, DependencyDataPackage>::const_iterator it =
									DG.DN[n].DP[io][p].DO[o].udi.begin();
									it != DG.DN[n].DP[io][p].DO[o].udi.end();
									++it) {
								DG.DN[n].DP[io][p].DO[o].udi[it->first].Set(
										tmpval);
							}
						}
					}
				}
			}
			cout << "Debug: GlobalDebug[Debug] is "
					<< SmartDG_GlobalData::GlobalDebug["Debug"] << endl;
		}
		if (Selection == "Debug/ToggleAll/False") {
			cout << "Debug: GlobalDebug[Debug] was "
					<< SmartDG_GlobalData::GlobalDebug["Debug"] << endl;
			tmpval = false;
			SmartDG_GlobalData::GlobalDebug["Debug"].Set(false);
			for (unsigned int n = 0; n < DG.DN.size(); n++) {
				for (unsigned int io = 0; io < DG.DN[n].DP.size(); io++) {
					for (unsigned int p = 0; p < DG.DN[n].DP[io].size(); p++) {
						for (unsigned int o = 0;
								o < DG.DN[n].DP[io][p].DO.size(); o++) {
							for (map<string, DependencyDataPackage>::const_iterator it =
									DG.DN[n].DP[io][p].DO[o].udi.begin();
									it != DG.DN[n].DP[io][p].DO[o].udi.end();
									++it) {
								DG.DN[n].DP[io][p].DO[o].udi[it->first].Set(
										tmpval);
							}
						}
					}
				}
			}
			cout << "Debug: GlobalDebug[Debug] is "
					<< SmartDG_GlobalData::GlobalDebug["Debug"] << endl;
		}
		if (Selection == "Debug/ToggleAll/SyncOut") {
			SyncOut();
		}
		if (Selection == "Debug/ToggleAll/SyncIn") {
			SyncIn();
		}
		RefreshMonitorData(currentView);
	}
	// Business
	if (Selection == "Business/Forward") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Business/Forward" << endl;
		currentDirection = 1;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Business/Reverse") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Business/Reverse" << endl;
		currentDirection = -1;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	// Edit
	if (Mode == SmartDG_OBJECT_MODE) {
		resetConDirection();
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].obj == currentView) {
				DependencyDataPackage d;
				if (Selection == "Edit/" + DG.DOI.I[i].amidL + "/true") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					d.Set(true);
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
							d);
					Solver(i);
					RefreshMonitorData(currentView);
				}
				if (Selection == "Edit/" + DG.DOI.I[i].amidL + "/false") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					d.Set(false);
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
							d);
					Solver(i);
					RefreshMonitorData(currentView);
				}
			}
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].obj == currentView) {
				if (Selection == "Edit/" + DG.DOI.I[i].midL + "/true") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
							true);
					resetConDirection();
					Solver(i);
					RefreshMonitorData(currentView);
				}
				if (Selection == "Edit/" + DG.DOI.I[i].midL + "/false") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
							false);
					resetConDirection();
					Solver(i);
					RefreshMonitorData(currentView);
				}
			}
		}
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		resetConDirection();
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].pou.strn == currentComponent) {
				DependencyDataPackage d;
				if (Selection == "Edit/" + DG.DOI.I[i].amidL + "/true") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					d.Set(true);
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
							d);
					Solver(i);
					RefreshMonitorData(currentView);
				}
				if (Selection == "Edit/" + DG.DOI.I[i].amidL + "/false") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					d.Set(false);
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
							d);
					Solver(i);
					RefreshMonitorData(currentView);
				}
			}
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			if (DG.DOI.I[i].pou.strn == currentComponent) {
				if (Selection == "Edit/" + DG.DOI.I[i].midL + "/true") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
							true);
					resetConDirection();
					Solver(i);
					RefreshMonitorData(currentView);
				}
				if (Selection == "Edit/" + DG.DOI.I[i].midL + "/false") {
					URL f = DG.DOI.I[i].pou;
					URL t = DG.DOI.I[i].tou;
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
							false);
					resetConDirection();
					Solver(i);
					RefreshMonitorData(currentView);
				}
			}
		}
	}
	// Sync
	if (Selection == "Sync/Refresh") { //#TODO Auto Refresh
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/Refresh" << endl;
		if (SmartDG_GlobalData::View2ViewFlag) {
			ShowHideMonitorWindowMenuBar("Sync/Attach", true);
			ShowHideMonitorWindowMenuBar("Sync/Detach", true);
			ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", View2ViewFlag);
			ShowHideMonitorWindowMenuBar("Sync/⟱ Download", View2ViewFlag);
			ShowHideMonitorWindowMenuBar("Sync/SolverSync", View2ViewFlag);
		} else {
			ShowHideMonitorWindowMenuBar("Sync/Attach", false);
			ShowHideMonitorWindowMenuBar("Sync/Detach", false);
			ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", false);
			ShowHideMonitorWindowMenuBar("Sync/⟱ Download", false);
			ShowHideMonitorWindowMenuBar("Sync/SolverSync", false);
		}
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Sync/Attach") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/Attach" << endl;
		ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", true);
		ShowHideMonitorWindowMenuBar("Sync/⟱ Download", true);
		ShowHideMonitorWindowMenuBar("Sync/SolverSync", true);
		View2ViewFlag = true;
		SolverSync = true;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Sync/Detach") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/Detach" << endl;
		ShowHideMonitorWindowMenuBar("Sync/⟰ Upload", false);
		ShowHideMonitorWindowMenuBar("Sync/⟱ Download", false);
		ShowHideMonitorWindowMenuBar("Sync/SolverSync", false);
		View2ViewFlag = false;
		SolverSync = false;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Sync/⟰ Upload") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/⟰ Upload" << endl;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
		SyncOut();
	}
	if (Selection == "Sync/⟱ Download") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/⟱ Download" << endl;
		SyncIn();
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Sync/SolverSync/Enable") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/SolverSync/Enable" << endl;
		SolverSync = true;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
	if (Selection == "Sync/SolverSync/Disable") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Sync/SolverSync/Disable" << endl;
		SolverSync = false;
		GenDispStr();
		MonitorWindowScroll->label(DispString.c_str());
		MenuJointRefresh();
		RefreshMonitorData(currentView);
	}
}

void DependencyMonitor::MTWindowMenuBar_Callback() {
	// Identifies selected option from the menu
	char sel[1000];
	MTWindowMenuBar->item_pathname(sel, sizeof(sel) - 1);
	string Selection(sel);
	// Performs action according to selection for the following
	if (Selection == "DGMonitor/Wiki") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Wiki" << endl;
		cout << SmartDG_WIKI << endl;
		cout << "Litemode !!" << endl;
	}
	if (Selection == "DGMonitor/Exit") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "Exit42" << endl;
		exit(0);
	}
	if (Selection == "DGlite/Launch/Chrome") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "DGlite/Launch/Chrome" << endl;
		system(SmartDG_Lite_Launch_COMMAND_Chrome);
	}
	if (Selection == "DGlite/Launch/Firefox") {
		if (SmartDG_MonitorWindowMenuBarVerbose)
			cout << "DGlite/Launch/Firefox" << endl;
		system(SmartDG_Lite_Launch_COMMAND_Firefox);
	}
}

void DependencyMonitor::NodeMenuBar_Callback() {
	for (unsigned int tog = 0; tog <= 1; tog++) { // tog is toggle between Input and Output NodeMenuBar
		for (unsigned int i = 0; i < DG.DN.size(); i++) {
			// Identifies selected option from the DependencyNode::BarIn and DependencyNode::BarOut menu bars
			char sel[1000];
			string label = "";
			string Selection = "";
			if (0 == tog) {
				if (DG.DN[i].BarIn) {
					DG.DN[i].BarIn->item_pathname(sel, sizeof(sel) - 1);
					label = DG.DN[i].BarIn->label();
					Selection = string(sel);
					if (Selection != "")
						DG.DN[i].BarIn->value(0);
				}
			} else {
				if (DG.DN[i].BarOut) {
					DG.DN[i].BarOut->item_pathname(sel, sizeof(sel) - 1);
					label = DG.DN[i].BarOut->label();
					Selection = string(sel);
					if (Selection != "")
						DG.DN[i].BarOut->value(0);
				}
			}
			if (Selection == "✎")
				Selection = "";
			if (Selection != "") {
				// Edit DependencyObject object's all or specific instance as true/false
				string portname = extractPortName(Selection);
				if (label == DG.DN[i].Name) {
					if (Mode == SmartDG_OBJECT_MODE) {
						resetConDirection();
						for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
							if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
									&& (DG.DOI.I[j].pou.strio == tog2str(tog))
									&& (DG.DOI.I[j].pou.strp == portname)
									&& (DG.DOI.I[j].pou.stro == currentView)
									&& (DG.DOI.I[j].direction
											== currentDirection)) {
								URL f = DG.DOI.I[j].pou;
								URL t = DG.DOI.I[j].tou;
								DependencyDataPackage d;
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].amid
														+ "/true")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									d.Set(true);
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
											d);
									Solver(j);
									RefreshMonitorData(currentView);
								}
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].amid
														+ "/false")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									d.Set(false);
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
											d);
									Solver(j);
									RefreshMonitorData(currentView);
								}
							}
						}
						for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
							if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
									&& (DG.DOI.I[j].pou.strio == tog2str(tog))
									&& (DG.DOI.I[j].pou.strp == portname)
									&& (DG.DOI.I[j].pou.stro == currentView)
									&& (DG.DOI.I[j].direction
											== currentDirection)) {
								URL f = DG.DOI.I[j].pou;
								URL t = DG.DOI.I[j].tou;
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].mid
														+ "/true")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
											true);
									resetConDirection();
									Solver(j);
									RefreshMonitorData(currentView);
									break;
								}
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].mid
														+ "/false")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
											false);
									resetConDirection();
									Solver(j);
									RefreshMonitorData(currentView);
									break;
								}
							}
						}
					}
					if ((Mode == SmartDG_COMPONENT_MODE)
							|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
						resetConDirection();
						for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
							if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
									&& (DG.DOI.I[j].pou.strio == tog2str(tog))
									&& (DG.DOI.I[j].pou.strp == portname)
									&& (DG.DOI.I[j].pou.strn == currentComponent)
									&& (DG.DOI.I[j].direction
											== currentDirection)) {
								URL f = DG.DOI.I[j].pou;
								URL t = DG.DOI.I[j].tou;
								DependencyDataPackage d;
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].amid
														+ "/true")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									d.Set(true);
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
											d);
									Solver(j);
									RefreshMonitorData(currentView);
								}
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].amid
														+ "/false")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									d.Set(false);
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Set(
											d);
									Solver(j);
									RefreshMonitorData(currentView);
								}
							}
						}
						for (unsigned int j = 0; j < DG.DOI.I.size(); j++) {
							if ((DG.DOI.I[j].pou.strn == DG.DN[i].Name)
									&& (DG.DOI.I[j].pou.strio == tog2str(tog))
									&& (DG.DOI.I[j].pou.strp == portname)
									&& (DG.DOI.I[j].pou.strn == currentComponent)
									&& (DG.DOI.I[j].direction
											== currentDirection)) {
								URL f = DG.DOI.I[j].pou;
								URL t = DG.DOI.I[j].tou;
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].mid
														+ "/true")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
											true);
									resetConDirection();
									Solver(j);
									RefreshMonitorData(currentView);
									break;
								}
								if (Selection
										== string(
												"✎/" + DG.DOI.I[j].mid
														+ "/false")) {
									if (SmartDG_NodeMenuBarVerbose)
										cout << DG.DN[i].Name
												<< " NodeMenuBar: " + Selection
												<< endl;
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
											false);
									resetConDirection();
									Solver(j);
									RefreshMonitorData(currentView);
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void DependencyMonitor::setup() {
	// Initiates lox and loy (Position of GUI window) based on current DependencyMonitor::count
	DependencyMonitor::count++;
	lox = SmartDG_LOX + count * SmartDG_LOXs;
	loy = SmartDG_LOY + count * SmartDG_LOYs;
	// Initiates FLTK GUI pointer objects with NULL
	MonitorWindow = NULL;
	MonitorWindowMenuBar = NULL;
	MTWindowMenuBar = NULL;
	MonitorWindowScroll = NULL;
	BigGroup = NULL;
	// Makes appropriate titles for GUI windows
	BusinessViewWindowTitle = "";
	MTWindowTitle = SmartDG_BaseLite;
	currentDirection = 1;
	if (Mode == SmartDG_OBJECT_MODE) {
		BusinessViewWindowTitle = string(SmartDG_BusinessViewWindowTitleBase)
				+ string(" System [ ") + Name + string(" ]	ObjectView[ ")
				+ currentView + string(" ]");
		//MTWindowTitle = string(SmartDG_BusinessViewWindowTitleBaseLite) +
		//		string("_") + string("_ObjectView_") + currentView;
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		BusinessViewWindowTitle = string(SmartDG_BusinessViewWindowTitleBase)
				+ string(" System [ ") + Name + string(" ]	ComponentView[ ")
				+ currentComponent + string(" ]");
		//MTWindowTitle = string(SmartDG_BusinessViewWindowTitleBaseLite) +
		//string("_") + string("_ComponentView_") + currentComponent;
	}
	// Sets default values for View2ViewFlag and SolverSync (Sync action flags)
	View2ViewFlag = SmartDG_View2ViewFlag_DEFAULT_VALUE;
	SolverSync = SmartDG_SolverSync_DEFAULT_VALUE;

	if (Mode != SmartDG_COMPONENT_DEVELOPER_MODE)
		if (!DependencyMonitor::MTLiteInit) {
			DependencyMonitor::MTLiteInit = true;

			DGliteDir = string(SmartDG_LiteFolderLocation) + string("/")
					+ string(SmartDG_LiteFoldername);
			std::system(string("mkdir -p " + DGliteDir).c_str());

			ofstream htmlfile;
			htmlfile.open(DGliteDir + "/" + MTWindowTitle + ".html",
					ios::trunc);
			htmlfile << "<!--------------------------------------------------\n"
					<< SmartDG_WIKI << endl;
			htmlfile
					<< "SmartDGlite Auto Generated \n-------------------------------------------------->"
					<< endl;
			htmlfile << "<!DOCTYPE html>" << endl;
			htmlfile << "<html>" << endl;
			htmlfile << "<head>" << endl;
			htmlfile << "<link href=\"style.css\" rel=\"stylesheet\" />"
					<< endl;
			htmlfile << "<meta charset=utf-8 />" << endl;
			htmlfile
					<< "<meta name=\"viewport\" content=\"user-scalable=no, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, minimal-ui\">"
					<< endl;
			htmlfile << "<title>" << MTWindowTitle << "</title>" << endl;
			htmlfile
					<< "<script src=\"/usr/local/include/SmartDG/js/cytoscape.min.js\"></script>"
					<< endl;
			htmlfile
					<< "<script src=\"/usr/local/include/SmartDG/js/jquery.min.js\"></script>"
					<< endl;
			htmlfile << "</head>" << endl;
			htmlfile << "<body>" << endl;
			htmlfile << "<div id=\"cy\"></div>" << endl;
			htmlfile << "<script src=\"" << MTWindowTitle << ".js\"></script>"
					<< endl;
			htmlfile << "<script src=\"Looper.js\"></script>" << endl;
			htmlfile << "<script> LooperDG(1000); </script>" << endl;
			htmlfile << "</body>" << endl;
			htmlfile << "</html>" << endl;
			htmlfile.close();

			ofstream jsfile1;
			jsfile1.open(DGliteDir + "/Looper.js", ios::trunc);
			jsfile1 << "/*****************************************\n"
					<< SmartDG_WIKI << endl;
			jsfile1
					<< "SmartDGlite Auto Generated \n*****************************************/"
					<< endl;
			jsfile1
					<< "function LooperDG (i) {	setTimeout(function () { ViewDG(); LooperDG(i);	}, i); }"
					<< endl;
			jsfile1.close();

			ofstream jsfile2;
			jsfile2.open(DGliteDir + "/" + MTWindowTitle + ".js", ios::trunc);
			jsfile2 << "/*****************************************\n"
					<< SmartDG_WIKI << endl;
			jsfile2
					<< "SmartDGlite Auto Generated \n*****************************************/"
					<< endl;
			jsfile2.close();

			ofstream jsonfile;
			jsonfile.open(DGliteDir + "/" + MTWindowTitle + ".json",
					ios::trunc);
			jsonfile << "var dgdata = []" << endl;
			jsonfile.close();

			ofstream stylefile;
			stylefile.open(DGliteDir + "/style.css", ios::trunc);
			stylefile
					<< "SmartDGlite Auto Generated \n*****************************************/"
					<< endl;
			stylefile
					<< "body { font: 14px helvetica neue, helvetica, arial, sans-serif; }"
					<< endl;
			stylefile
					<< "#cy { height: 100%; width: 100%; position: absolute; left: 0; top: 0; }"
					<< endl;
			stylefile.close();
		}
}

void DependencyMonitor::makelitejs() {
	// Creates Java Script file in DGlite directory  (In all except DependencyMonitor::Mode : SmartDG_COMPONENT_DEVELOPER_MODE)
	if (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)
		return;
	map<unsigned int, unsigned int> gx;
	map<unsigned int, unsigned int> gy;
	vector<unsigned int> Lnodes;
	vector<unsigned int> Rnodes;
	vector<unsigned int> Mnodes;

	unsigned int tab = 100;
	unsigned int spacenodex = 500;
	unsigned int spaceobjiy = 150;
	unsigned int spacenodey = 800;
	unsigned int numcolsx = 3;
	unsigned int Lprevy = 0;
	unsigned int Rprevy = 0;
	unsigned int Mprevy = 0;
	unsigned int nsz = DG.DN.size();
	if (nsz > 3) {
		numcolsx = nsz;
		if (nsz % 2 == 0)
			numcolsx = nsz + 1;
	}
	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		unsigned int Lnumobji = 0;
		if (DG.DN[i].DP[0].size() == 0) {
			for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
				for (unsigned int k = 0; k < DG.DN[i].DP[1][j].DO.size(); k++) {
					Lnumobji += DG.DN[i].DP[1][j].DO[k].udi.size();
				}
			}
			unsigned int Lsz = Lnodes.size();
			gx[i] = tab;
			if (Lsz == 0) {
				gy[i] = tab;
			} else {
				gy[i] = Lprevy + spacenodey + Lnumobji * spaceobjiy;
				Lprevy = gy[i];
			}
			Lnodes.push_back(i);
			continue;
		}
		unsigned int Rnumobji = 0;
		if (DG.DN[i].DP[1].size() == 0) {
			for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
				for (unsigned int k = 0; k < DG.DN[i].DP[0][j].DO.size(); k++) {
					Rnumobji += DG.DN[i].DP[0][j].DO[k].udi.size();
				}
			}
			unsigned int Rsz = Rnodes.size();
			gx[i] = (numcolsx - 1) * spacenodex + tab;
			if (Rsz == 0) {
				gy[i] = tab;
			} else {
				gy[i] = Rprevy + spacenodey + Rnumobji * spaceobjiy;
				Rprevy = gy[i];
			}
			Rnodes.push_back(i);
			continue;
		}
		unsigned int Mnumobji = 0;
		for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
			for (unsigned int k = 0; k < DG.DN[i].DP[1][j].DO.size(); k++) {
				Mnumobji += DG.DN[i].DP[1][j].DO[k].udi.size();
			}
		}
		for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
			for (unsigned int k = 0; k < DG.DN[i].DP[0][j].DO.size(); k++) {
				Mnumobji += DG.DN[i].DP[0][j].DO[k].udi.size();
			}
		}
		unsigned int Msz = Mnodes.size();
		gx[i] = ((numcolsx - 1) / 2) * spacenodex + tab;
		if (Msz == 0) {
			gy[i] = tab;
		} else {
			gy[i] = Mprevy + spacenodey + Mnumobji * spaceobjiy;
			Mprevy = gy[i];
		}
		Mnodes.push_back(i);
	}
	ofstream jsfile;
	jsfile.open(DGliteDir + "/" + MTWindowTitle + ".js", ios::trunc);
	jsfile << "/*****************************************\n" << SmartDG_WIKI
			<< endl;
	jsfile
			<< "SmartDGlite Auto Generated \n*****************************************/"
			<< endl;
	jsfile << "var cy = cytoscape({" << endl;
	jsfile << "  container: document.getElementById('cy')," << endl;
	jsfile << "  boxSelectionEnabled: false," << endl;
	jsfile << "" << endl;
	jsfile << "  style: cytoscape.stylesheet()" << endl;
	jsfile << "    .selector('node')" << endl;
	jsfile << "      .css({" << endl;
	jsfile << "        'width': '50px'," << endl;
	jsfile << "        'height': '50px'," << endl;
	jsfile << "        'content': 'data(LAB)'," << endl;
	jsfile << "        'pie-size': '98%'," << endl;
	jsfile << "        'pie-1-background-color': '#FF0000'," << endl;
	jsfile
			<< "        'pie-1-background-size': 'mapData(False, 0, 10, 0, 100)',"
			<< endl;
	jsfile << "        'pie-2-background-color': '#00FF00'," << endl;
	jsfile << "        'pie-2-background-size': 'mapData(True, 0, 10, 0, 100)',"
			<< endl;
	jsfile << "      })" << endl;
	jsfile << "    .selector('parent')" << endl;
	jsfile << "      .css({" << endl;
	jsfile << "        'content': 'data(LAB)'," << endl;
	jsfile << "        'text-valign': 'top'," << endl;
	jsfile << "        'text-halign': 'center'," << endl;
	jsfile << "      })" << endl;
	jsfile << "    .selector('edge')" << endl;
	jsfile << "      .css({" << endl;
	jsfile << "        'content': 'data(LAB)'," << endl;
	jsfile << "        'curve-style': 'segments'," << endl;
	jsfile << "        'width': 2," << endl;
	jsfile << "        'target-arrow-shape': 'triangle'," << endl;
	jsfile << "        'opacity': 1.0" << endl;
	jsfile << "      })" << endl;
	jsfile << "    .selector(':selected')" << endl;
	jsfile << "      .css({" << endl;
	jsfile << "        'background-color': 'black'," << endl;
	jsfile << "        'line-color': 'black'," << endl;
	jsfile << "        'target-arrow-color': 'black'," << endl;
	jsfile << "        'source-arrow-color': 'black'," << endl;
	jsfile << "        'opacity': 1" << endl;
	jsfile << "      })" << endl;
	jsfile << "    .selector('.faded')" << endl;
	jsfile << "      .css({" << endl;
	jsfile << "        'opacity': 0.25," << endl;
	jsfile << "        'text-opacity': 0" << endl;
	jsfile << "      })," << endl;
	jsfile << "" << endl;
	jsfile << "  elements: {" << endl;
	jsfile << "    nodes: [" << endl;
	jsfile
			<< "      { data: { id: 'BLINKY' , LAB: 'Live', True: 0, False: 0   },"
			<< " position: { x: 50, y: 50 } }," << endl;
	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		string n = DG.DN[i].Name;
		string nl = "Node " + DG.DN[i].Name;
		jsfile << "      { data: { id: '" << n << "' , LAB: '" << nl << "' } },"
				<< endl;
		unsigned int coi = 0;
		for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
			string p = n + "xInx" + DG.DN[i].DP[0][j].Name;
			string pl = "Port " + DG.DN[i].DP[0][j].Name;
			jsfile << "      { data: { id: '" << p << "', LAB: '" << pl
					<< "', parent: '" << n << "' } }," << endl;
			for (unsigned int k = 0; k < DG.DN[i].DP[0][j].DO.size(); k++) {
				string o = p + "x" + DG.DN[i].DP[0][j].DO[k].Name;
				string ol = "Object " + DG.DN[i].DP[0][j].DO[k].Name;
				jsfile << "      { data: { id: '" << o << "', LAB: '" << ol
						<< "', parent: '" << p << "' } }," << endl;
				string oi = o + "xAllx";
				string oil = "All";
				coi++;
				jsfile << "      { data: { id: '" << oi << "', LAB: '" << oil
						<< "', parent: '" << o << "', True: 0, False: 0  }"
						<< ", position: { x: " << gx[i] << ", y: "
						<< gy[i] + (coi * spaceobjiy) << " }" << " }," << endl;
				for (map<string, DependencyDataPackage>::const_iterator it =
						DG.DN[i].DP[0][j].DO[k].udi.begin();
						it != DG.DN[i].DP[0][j].DO[k].udi.end(); ++it) {
					string dotless = it->first;
					replace(dotless.begin(), dotless.end(), '.', 'x');
					string oi = o + "x" + dotless + "x";
					string oil = "From " + it->first;
					coi++;
					jsfile << "      { data: { id: '" << oi << "', LAB: '"
							<< oil << "', parent: '" << o
							<< "', True: 0, False: 0  }" << ", position: { x: "
							<< gx[i] << ", y: " << gy[i] + (coi * spaceobjiy)
							<< " }" << " }," << endl;
				}
			}
		}
		coi = 0;
		for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
			string p = n + "xOutx" + DG.DN[i].DP[1][j].Name;
			string pl = "Port " + DG.DN[i].DP[1][j].Name;
			jsfile << "      { data: { id: '" << p << "', LAB: '" << pl
					<< "', parent: '" << n << "' } }," << endl;
			for (unsigned int k = 0; k < DG.DN[i].DP[1][j].DO.size(); k++) {
				string o = p + "x" + DG.DN[i].DP[1][j].DO[k].Name;
				string ol = "Object " + DG.DN[i].DP[1][j].DO[k].Name;
				jsfile << "      { data: { id: '" << o << "', LAB: '" << ol
						<< "', parent: '" << p << "' } }," << endl;
				string oi = o + "xAllx";
				string oil = "All";
				coi++;
				jsfile << "      { data: { id: '" << oi << "', LAB: '" << oil
						<< "', parent: '" << o << "', True: 0, False: 0  }"
						<< ", position: { x: " << gx[i] + spacenodex << ", y: "
						<< gy[i] + (coi * spaceobjiy) << " }" << " }," << endl;
				for (map<string, DependencyDataPackage>::const_iterator it =
						DG.DN[i].DP[1][j].DO[k].udi.begin();
						it != DG.DN[i].DP[1][j].DO[k].udi.end(); ++it) {
					string dotless = it->first;
					replace(dotless.begin(), dotless.end(), '.', 'x');
					string oi = o + "x" + dotless + "x";
					string oil = "To " + it->first;
					coi++;
					jsfile << "      { data: { id: '" << oi << "', LAB: '"
							<< oil << "', parent: '" << o
							<< "', True: 0, False: 0  }" << ", position: { x: "
							<< gx[i] + spacenodex << ", y: "
							<< gy[i] + (coi * spaceobjiy) << " }" << " },"
							<< endl;
				}
			}
		}
	}
	jsfile << "    ]," << endl;
	jsfile << "" << endl;
	jsfile << "    edges: [" << endl;
	for (unsigned int objs = 0; objs < DG.dobjs.size(); objs++) {
		string obj = DG.dobjs[objs];
		for (unsigned int dep = 0; dep < DG.View[obj].size(); dep++) {
			string id = DG.View[obj][dep].From.dotless() + "xxx"
					+ DG.View[obj][dep].To.dotless();
			string lab = DG.View[obj][dep].Name;
			string source = DG.View[obj][dep].From.dotless() + "x"
					+ DG.View[obj][dep].To.dotless() + "x";
			string target = DG.View[obj][dep].To.dotless() + "x"
					+ DG.View[obj][dep].From.dotless() + "x";
			jsfile << "      { data: { id: '" << id << "', LAB: '" << lab
					<< "', weight: 1, source: '" << source << "', target: '"
					<< target << "' } }," << endl;
		}
	}
	jsfile << "    ]" << endl;
	jsfile << "  }," << endl;
	jsfile << "" << endl;
	jsfile << "  layout: {" << endl;
	jsfile << "    name: 'preset'," << endl;
	jsfile << "    padding: 5" << endl;
	jsfile << "  }," << endl;
	jsfile << "" << endl;
	jsfile << "  ready: function(){" << endl;
	jsfile << "    window.cy = this;" << endl;
	jsfile << "  }" << endl;
	jsfile << "});" << endl;
	jsfile << "" << endl;
	jsfile << "function ViewDG(){" << endl;
	jsfile
			<< "  $.getScript( \"http://localhost:3000/DGlite.json\", function( data, textStatus, jqxhr ) {"
			<< endl;
	jsfile << "  for(var i=0; i< dgdata.length; i++){" << endl;
	jsfile
			<< "    if(dgdata[i].val == \"NA\")     {  cy.$(dgdata[i].id).data('False', 0); cy.$(dgdata[i].id).data('True', 0); }"
			<< endl;
	jsfile
			<< "    else if(dgdata[i].val == \"T\")     {  cy.$(dgdata[i].id).data('False', 0); cy.$(dgdata[i].id).data('True', 10); }"
			<< endl;
	jsfile
			<< "    else if(dgdata[i].val == \"F\"){  cy.$(dgdata[i].id).data('False', 10); cy.$(dgdata[i].id).data('True', 0); }"
			<< endl;
	jsfile
			<< "    else {  cy.$(dgdata[i].id).data('False', 10-dgdata[i].val); cy.$(dgdata[i].id).data('True', 1+dgdata[i].val-1); }"
			<< endl;
	jsfile << "  }	" << endl;
	jsfile << "  });" << endl;
	jsfile << "}" << endl;
	jsfile.close();
}

void DependencyMonitor::InitMT() {
	MTWindow = new Fl_Double_Window(lox, loy, SmartDG_BusinessViewWindowWIDTH,
	SmartDG_MENUHEIGHT + 2, MTWindowTitle.c_str());
	MTWindow->resizable(MTWindow);
	MTWindow->color(SmartDG_BACKGROUND_COLOR);
	MTWindowMenuBar = new Fl_Menu_Bar(0, 0, MTWindow->w(), SmartDG_MENUHEIGHT);
	MTWindowMenuBar->color(SmartDG_MENU_COLOR);
	MTWindowMenuBar->textcolor(SmartDG_MENU_TEXT_COLOR);
	MTWindowMenuBar->add("DGMonitor/Wiki", 0, Static_MTWindowMenuBar_Callback,
			(void*) this);
	MTWindowMenuBar->add("DGMonitor/Exit", 0, Static_MTWindowMenuBar_Callback,
			(void*) this);
	MTWindowMenuBar->add("DGlite/Launch/Chrome", 0,
			Static_MTWindowMenuBar_Callback, (void*) this);
	MTWindowMenuBar->add("DGlite/Launch/Firefox", 0,
			Static_MTWindowMenuBar_Callback, (void*) this);
}

void DependencyMonitor::SyncOI() {
	if (View2ViewFlag && SmartDG_GlobalData::View2ViewFlag) {
		SyncOut();
		if (DisplayMode != SmartDG_FLTK_DISPLAYMODE) {
			SyncOutLite(true);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(
		SmartDG_SLEEP_BETWEEN_SYNCOUT_SYNCIN));
		SyncIn();
	}
}

void DependencyMonitor::SyncOut() {
	if (View2ViewFlag && SmartDG_GlobalData::View2ViewFlag) {
		system(SmartDG_XMESSAGE_SYNC_COMMAND);
		if (SmartDG_SyncVerbose) {
			if (Mode == SmartDG_OBJECT_MODE)
				cout << Name << " ObjectView " << currentView << ":SyncOut"
						<< endl;
			if (Mode == SmartDG_COMPONENT_MODE)
				cout << Name << " ComponentView " << currentComponent
						<< ":SyncOut" << endl;
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			URL f = DG.DOI.I[i].pou;
			URL t = DG.DOI.I[i].tou;
			SmartDG_GlobalData::GlobalPackage[f.str][t.str].Set(
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Get());
			if (SmartDG_SyncVerbose)
				cout
						<< DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Get();
		}
		if (SmartDG_SyncVerbose)
			cout << endl;
	}
}

void DependencyMonitor::SyncIn() {
	if (View2ViewFlag && SmartDG_GlobalData::View2ViewFlag) {
		system(SmartDG_XMESSAGE_SYNC_COMMAND);
		if (SmartDG_SyncVerbose) {
			if (Mode == SmartDG_OBJECT_MODE)
				cout << Name << " ObjectView " << currentView << ":SyncIn"
						<< endl;
			if (Mode == SmartDG_COMPONENT_MODE)
				cout << Name << " ComponentView " << currentComponent
						<< ":SyncIn" << endl;
		}
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			URL f = DG.DOI.I[i].pou;
			URL t = DG.DOI.I[i].tou;
			DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Set(
					SmartDG_GlobalData::GlobalPackage[f.str][t.str].Get());
			if (SmartDG_SyncVerbose)
				cout
						<< DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].Get();
		}
		if (SmartDG_SyncVerbose)
			cout << endl;
	}
}

void DependencyMonitor::SyncOutLiteInit() {
	for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
		URL f = DG.DOI.I[i].pou;
		URL t = DG.DOI.I[i].tou;
		SmartDG_GlobalData::GlobalPackageLite["#" + f.dotless("x") + "x"
				+ t.dotless("x") + "x"] = "F";
		SmartDG_GlobalData::GlobalPackageLite["#" + f.dotless("x") + "xAllx"] =
				"F";
	}
}

void DependencyMonitor::SyncOutLite(bool useglobal) {
	if (DisplayMode != SmartDG_FLTK_DISPLAYMODE) {
		if (SmartDG_SyncLiteVerbose)
			cout << DisplayMode << " SyncOutLite::";
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			URL f = DG.DOI.I[i].pou;
			URL t = DG.DOI.I[i].tou;
			if (useglobal)
				SmartDG_GlobalData::GlobalPackageLite["#" + f.dotless("x") + "x"
						+ t.dotless("x") + "x"] =
						SmartDG_GlobalData::GlobalPackage[f.str][t.str].toStr();
			else
				SmartDG_GlobalData::GlobalPackageLite["#" + f.dotless("x") + "x"
						+ t.dotless("x") + "x"] =
						DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str].toStr();
			if (SmartDG_SyncLiteVerbose)
				cout << "|"
						<< SmartDG_GlobalData::GlobalPackageLite["#"
								+ f.dotless("x") + "x" + t.dotless("x") + "x"];
		}
		if (SmartDG_SyncLiteVerbose)
			cout << endl;
		for (unsigned int n = 0; n < DG.DN.size(); n++)
			for (unsigned int io = 0; io < 2; io++)
				for (unsigned int p = 0; p < DG.DN[n].DP[io].size(); p++)
					for (unsigned int o = 0; o < DG.DN[n].DP[io][p].DO.size();
							o++) {
						DependencyObject tmpObj = DG.DN[n].DP[io][p].DO[o];
						for (map<string, DependencyDataPackage>::const_iterator it =
								tmpObj.udi.begin(); it != tmpObj.udi.end();
								++it)
							tmpObj.udi[it->first] =
									SmartDG_GlobalData::GlobalPackage[tmpObj.url.str][it->first];
						string id = "#" + tmpObj.url.dotless("x") + "xAllx";
						if (tmpObj.GetBias() >= 0)
							SmartDG_GlobalData::GlobalPackageLite[id] =
									to_string(tmpObj.GetBias());
						else
							SmartDG_GlobalData::GlobalPackageLite[id] = "NA";
					}
	}
}

void DependencyMonitor::SyncInLite() {
	//#TODO Implement when DGlite takes user inputs
}

void DependencyMonitor::ShowLines() {
	if (Mode == SmartDG_OBJECT_MODE) {
		for (unsigned int j = 0; j < DG.dobjs.size(); j++) {
			string obj = DG.dobjs[j];
			if (obj == currentView)
				for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
					URL f = DG.View[obj][i].From;
					unsigned int fx =
							DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Shape->x();
					unsigned int fy =
							DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Shape->y();
					URL t = DG.View[obj][i].To;
					unsigned int tx =
							DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].Shape->x();
					unsigned int ty =
							DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].Shape->y();
					unsigned int lmx = (fx + tx + SmartDG_IWW) / 2;
					unsigned int lmy = (fy + ty + SmartDG_IWW) / 2;
					if (USEGRID)
						Snap2Grid(lmx, lmy);
					GridXY[f.str][t.str].push_back(lmx);
					GridXY[f.str][t.str].push_back(lmy);
					if (USEGRID)
						AdjustGridXY();
					DG.View[obj][i].con = new GUIConnection(
							DG.View[obj][i].Name, fx + SmartDG_IWW,
							fy + SmartDG_IWW / 2, tx, ty + SmartDG_IWW / 2,
							string(
									DG.View[obj][i].From.strp + "."
											+ DG.View[obj][i].From.stro),
							string(
									DG.View[obj][i].To.strp + "."
											+ DG.View[obj][i].To.stro),
							fcount[DG.View[obj][i].From.str]--,
							tcount[DG.View[obj][i].To.str]--,
							GridXY[f.str][t.str][0], GridXY[f.str][t.str][1],
							SmartDG_LCOLOR, SmartDG_LINETHICKNESS);
					DG.View[obj][i].con->Fill(
							DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str],
							DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].udi[f.str]);
				}
		}
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		int compmode = 1;
		if (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)
			compmode = 2;
		unsigned int fcounter = 0;
		unsigned int tcounter = 0;

		for (unsigned int j = 0; j < DG.dobjs.size(); j++) {
			string obj = DG.dobjs[j];
			for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
				URL f = DG.View[obj][i].From;
				URL t = DG.View[obj][i].To;
				if (f.strn == currentComponent)
					fcounter++;
				if (t.strn == currentComponent)
					tcounter++;
			}
		}
		unsigned int ftab = 0;
		unsigned int ttab = 0;
		if (fcounter > 0)
			ftab = (MonitorWindowScroll->h() - SmartDG_COMPONENTMODE_MARGIN_TOP)
					/ fcounter;
		if (tcounter > 0)
			ttab = (MonitorWindowScroll->h() - SmartDG_COMPONENTMODE_MARGIN_TOP)
					/ tcounter;
		unsigned int ttargetx =
				MonitorWindowScroll->x() + SmartDG_COMPONENTMODE_MARGIN_SIDE;
		unsigned int ftargetx = MonitorWindowScroll->x()
				+ MonitorWindowScroll->w() - SmartDG_COMPONENTMODE_MARGIN_SIDE;
		unsigned int ftabcounter = 0;
		unsigned int ttabcounter = 0;

		map<string, unsigned int> FX, FY, TX, TY;

		for (unsigned int i = 0; i < DG.DN.size(); i++) {
			if (DG.DN[i].Name == currentComponent) {
				for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
					for (unsigned int l = 0; l < DG.DN[i].DP[1][j].DO.size();
							l++) {
						URL f = DG.DN[i].DP[1][j].DO[l].url;
						for (map<string, DependencyDataPackage>::const_iterator it =
								DG.DN[i].DP[1][j].DO[l].udi.begin();
								it != DG.DN[i].DP[1][j].DO[l].udi.end(); ++it) {
							string kstr = f.str + it->first;
							FX[kstr] =
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Shape->x()+SmartDG_IWW;
							FY[kstr] =
									DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].Shape->y()
											+ SmartDG_IWW / 2;
							TX[kstr] = ftargetx
									- SmartDG_COMPONENTMODE_MARGIN_WIRE
											* ftabcounter - 40 * (j - 1);
							TY[kstr] = SmartDG_COMPONENTMODE_MARGIN_TOP
									+ ftabcounter * ftab;
							ftabcounter++;
						}
					}
				}
				for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
					for (unsigned int l = 0; l < DG.DN[i].DP[0][j].DO.size();
							l++) {
						URL t = DG.DN[i].DP[0][j].DO[l].url;
						for (map<string, DependencyDataPackage>::const_iterator it =
								DG.DN[i].DP[0][j].DO[l].udi.begin();
								it != DG.DN[i].DP[0][j].DO[l].udi.end(); ++it) {
							string kstr = t.str + it->first;
							TX[kstr] =
									DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].Shape->x();
							TY[kstr] =
									DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].Shape->y()
											+ SmartDG_IWW / 2;
							FX[kstr] = ttargetx
									+ SmartDG_COMPONENTMODE_MARGIN_WIRE
											* ttabcounter + 40 * (j - 1);
							FY[kstr] = SmartDG_COMPONENTMODE_MARGIN_TOP
									+ ttabcounter * ttab;
							ttabcounter++;
						}
					}
				}
			}
		}
		for (unsigned int j = 0; j < DG.dobjs.size(); j++) {
			string obj = DG.dobjs[j];
			for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
				URL f = DG.View[obj][i].From;
				URL t = DG.View[obj][i].To;
				unsigned int fx, fy, tx, ty, lmx, lmy;
				if (f.strn == currentComponent) {
					string kstr = f.str + t.str;
					fx = FX[kstr];
					fy = FY[kstr];
					tx = TX[kstr];
					ty = TY[kstr];
					lmx = (fx + 2 * tx) / 3;
					lmy = ty;
					if (USEGRID)
						Snap2Grid(lmx, lmy);
					GridXY[f.str][t.str].push_back(lmx);
					GridXY[f.str][t.str].push_back(lmy);
					if (USEGRID)
						AdjustGridXY();
					string lab = DG.View[obj][i].To.strn + "."
							+ DG.View[obj][i].To.strp;
					DG.View[obj][i].con = new GUIConnection(
							DG.View[obj][i].Name, compmode, lab, fx, fy, tx, ty,
							string(
									DG.View[obj][i].From.strp + "."
											+ DG.View[obj][i].From.stro),
							string(
									DG.View[obj][i].To.strp + "."
											+ DG.View[obj][i].To.stro),
							fcount[DG.View[obj][i].From.str]--,
							tcount[DG.View[obj][i].To.str]--,
							GridXY[f.str][t.str][0], GridXY[f.str][t.str][1],
							SmartDG_LCOLOR, SmartDG_LINETHICKNESS);
					DG.View[obj][i].con->Fill(
							DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str],
							DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].udi[f.str]);
				} else {
					if (t.strn == currentComponent) {
						string kstr = t.str + f.str;
						tx = TX[kstr];
						ty = TY[kstr];
						fx = FX[kstr];
						fy = FY[kstr];
						lmx = (2 * fx + tx) / 3;
						lmy = fy;
						if (USEGRID)
							Snap2Grid(lmx, lmy);
						GridXY[f.str][t.str].push_back(lmx);
						GridXY[f.str][t.str].push_back(lmy);
						if (USEGRID)
							AdjustGridXY();
						string lab = DG.View[obj][i].From.strn + "."
								+ DG.View[obj][i].From.strp;
						DG.View[obj][i].con = new GUIConnection(
								DG.View[obj][i].Name, compmode, lab, fx, fy, tx,
								ty,
								string(
										DG.View[obj][i].From.strp + "."
												+ DG.View[obj][i].From.stro),
								string(
										DG.View[obj][i].To.strp + "."
												+ DG.View[obj][i].To.stro),
								fcount[DG.View[obj][i].From.str]--,
								tcount[DG.View[obj][i].To.str]--,
								GridXY[f.str][t.str][0],
								GridXY[f.str][t.str][1],
								SmartDG_LCOLOR, SmartDG_LINETHICKNESS);
						DG.View[obj][i].con->Fill(
								DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str],
								DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].udi[f.str]);
					} else {
						DG.View[obj][i].con = new GUIConnection();
					}
				}
			}
		}
	}
}

void DependencyMonitor::Snap2Grid(unsigned int &x, unsigned int &y) {
	// Snaps to the closest floor coordinates on the Grid
	unsigned int tx = x - x % SmartDG_GRIDBLOCKSIZE;
	unsigned int ty = y - y % SmartDG_GRIDBLOCKSIZE;
	// Snaps to closest ceiling coordinates if that is closer to the input coordinate
	if (x % SmartDG_GRIDBLOCKSIZE > SmartDG_GRIDBLOCKSIZE / 2)
		tx = tx + SmartDG_GRIDBLOCKSIZE;
	if (y % SmartDG_GRIDBLOCKSIZE > SmartDG_GRIDBLOCKSIZE / 2)
		ty = ty + SmartDG_GRIDBLOCKSIZE;
	// If the location is already occupied, Snap to nearest orthogonal neighbor on the Grid
	// !Grid[tx][ty] will be true if Grid map has no entry for [tx][ty] OR when the entry is true
	if (!Grid[tx][ty])
		tx = tx - SmartDG_GRIDBLOCKSIZE;
	if (!Grid[tx][ty])
		tx = tx + SmartDG_GRIDBLOCKSIZE;
	if (!Grid[tx][ty])
		ty = ty - SmartDG_GRIDBLOCKSIZE;
	if (!Grid[tx][ty])
		ty = ty + SmartDG_GRIDBLOCKSIZE;
	if (!Grid[tx][ty]) {
		tx = tx - SmartDG_GRIDBLOCKSIZE;
		ty = ty - SmartDG_GRIDBLOCKSIZE;
		if (!Grid[tx][ty]) {
			tx = tx + SmartDG_GRIDBLOCKSIZE;
			ty = ty - SmartDG_GRIDBLOCKSIZE;
			if (!Grid[tx][ty]) {
				tx = tx - SmartDG_GRIDBLOCKSIZE;
				ty = ty + SmartDG_GRIDBLOCKSIZE;
				if (!Grid[tx][ty]) {
					x = tx + SmartDG_GRIDBLOCKSIZE;
					y = ty + SmartDG_GRIDBLOCKSIZE;
					Grid[x][y] = true;
					return;
				}
			}
		}
	}
	x = tx;
	y = ty;
	Grid[x][y] = true;
	return;
}

void DependencyMonitor::AdjustGridXY() {
	// #TODO
	// DependencyMonitor::AdjustGridXY() needs to be implemented to make sure
	// the GUIText objects from different GUIConnection objects don't occlude one another.
}

void DependencyMonitor::Generate_Dependency_Tabs() {
	if (Mode == SmartDG_OBJECT_MODE) {
		for (unsigned int i = 0; i < DG.View[currentView].size(); i++) {
			if (fcount[DG.View[currentView][i].From.str])
				fcount[DG.View[currentView][i].From.str]++;
			else
				fcount[DG.View[currentView][i].From.str] = 1;

			if (tcount[DG.View[currentView][i].To.str])
				tcount[DG.View[currentView][i].To.str]++;
			else
				tcount[DG.View[currentView][i].To.str] = 1;
		}
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		for (unsigned int s = 0; s < DG.dobjs.size(); s++) {
			string obj = DG.dobjs[s];
			for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
				if (fcount[DG.View[obj][i].From.str])
					fcount[DG.View[obj][i].From.str]++;
				else
					fcount[DG.View[obj][i].From.str] = 1;

				if (tcount[DG.View[obj][i].To.str])
					tcount[DG.View[obj][i].To.str]++;
				else
					tcount[DG.View[obj][i].To.str] = 1;
			}
		}
	}
}

void DependencyMonitor::RefreshMonitorData(string obj, bool refreshGUI) {
	if (Mode == SmartDG_OBJECT_MODE) {
		for (unsigned int i = 0; i < DG.View[string(obj)].size(); i++) {
			URL f = DG.View[obj][i].From;
			URL t = DG.View[obj][i].To;
			// Fills latest DependencyObject instance data (Name : obj) to GUI connections
			DG.View[obj][i].con->Fill(
					DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str],
					DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].udi[f.str]);
		}
		if (refreshGUI)
			RefreshMonitor();
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		for (unsigned int s = 0; s < DG.dobjs.size(); s++) {
			obj = DG.dobjs[s];
			for (unsigned int i = 0; i < DG.View[string(DG.dobjs[s])].size();
					i++) {
				URL f = DG.View[obj][i].From;
				URL t = DG.View[obj][i].To;
				// Fills latest DependencyObject instance data (Name : obj) to GUI connections
				DG.View[obj][i].con->Fill(
						DG.DN[f.NodeIndex].DP[f.InOutIndex][f.PortIndex].DO[f.ObjectIndex].udi[t.str],
						DG.DN[t.NodeIndex].DP[t.InOutIndex][t.PortIndex].DO[t.ObjectIndex].udi[f.str]);
			}
		}
		if (refreshGUI)
			RefreshMonitor();
	}
}

void DependencyMonitor::RefreshMonitorData(bool refreshGUI) {
	if (Mode == SmartDG_OBJECT_MODE) {
		// For all objects in DependencyGraph DG (DependencyGraph::dobjs)
		for (unsigned int i = 0; i < DG.dobjs.size(); i++) {
			// Calls RefreshMonitorData(obj, refreshGUI)
			RefreshMonitorData(DG.dobjs[i], false);
		}
		if (refreshGUI)
			RefreshMonitor();
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		// Calls RefreshMonitorData("DUMMY", refreshGUI) to handle
		// Mode : SmartDG_COMPONENT_MODE or SmartDG_COMPONENT_DEVELOPER_MODE
		RefreshMonitorData(string("DUMMY"), false);
		if (refreshGUI)
			RefreshMonitor();
	}
}

void DependencyMonitor::RefreshMonitor() {
	// Redraws the current GUI window through a call to Fl_Double_Window::redraw()
	MonitorWindow->redraw();
}

void DependencyMonitor::ResetDOIFlags(bool b, unsigned int c) {
	DG.DOI.ResetContext(b);
	DG.DOI.SetFlagContext(b, c);
	RefreshEditMenu();
	RefreshNodeEditMenu();
}

void DependencyMonitor::RefreshDOIFlags(string v, string n, string i, string p,
		string o, bool b, unsigned int c) {
	DG.DOI.SetContext(v, n, i, p, o);
	DG.DOI.SetFlagContext(b, c);
	RefreshEditMenu();
	RefreshNodeEditMenu();
}

void DependencyMonitor::RefreshDOIFlagsHierarchy(string v, string n, string i,
		string p, string o, bool b, unsigned int c) {
	DG.DOI.SetContextHierarchy(v, n, i, p, o);
	DG.DOI.SetFlagContext(b, c);
	RefreshEditMenu();
	RefreshNodeEditMenu();
}

void DependencyMonitor::RefreshDOIFlagsURL(string u, bool b, unsigned int c) {
	DG.DOI.SetFlagURL(u, b, c);
	RefreshEditMenu();
	RefreshNodeEditMenu();
}

void DependencyMonitor::RefreshDOIFlagsMenuIDString(string m, bool b,
		unsigned int c) {
	DG.DOI.SetFlagMenuIDString(m, b, c);
	RefreshEditMenu();
	RefreshNodeEditMenu();
}

void DependencyMonitor::RefreshEditMenu() {
	if (SmartDG_RefreshEditMenuVerbose) {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			string str1 = "Edit/" + DG.DOI.I[i].midL + "/true";
			cout << str1 << " set " << DG.DOI.I[i].editable << endl;
			ShowHideMonitorWindowMenuBar(str1, DG.DOI.I[i].editable);
			string str2 = "Edit/" + DG.DOI.I[i].midL + "/false";
			cout << str2 << " set " << DG.DOI.I[i].editable << endl;
			ShowHideMonitorWindowMenuBar(str2, DG.DOI.I[i].editable);
		}
	} else {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DOI.I[i].midL + "/true",
					DG.DOI.I[i].editable);
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DOI.I[i].midL + "/false",
					DG.DOI.I[i].editable);
		}
	}
}

void DependencyMonitor::ShowHideMonitorWindowMenuBar(string item, bool b) {
	Fl_Menu_Item *p = (Fl_Menu_Item*) MonitorWindowMenuBar->find_item(
			item.c_str());
	if (p) {
		if (b)
			p->activate();
		else
			p->deactivate();
	}
}

void DependencyMonitor::RefreshNodeEditMenu() {
	if (SmartDG_RefreshNodeEditMenuVerbose) {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			string str1 = "✎/" + DG.DOI.I[i].mid + "/true";
			cout << DG.DOI.I[i].pou.strio << " " << str1 << " set "
					<< DG.DOI.I[i].editable << endl;
			ShowHideNodeMenuBar(str2tog(DG.DOI.I[i].pou.strio), str1,
					DG.DOI.I[i].editable);

			string str2 = "✎/" + DG.DOI.I[i].mid + "/false";
			cout << DG.DOI.I[i].pou.strio << " " << str2 << " set "
					<< DG.DOI.I[i].editable << endl;
			ShowHideNodeMenuBar(str2tog(DG.DOI.I[i].pou.strio), str2,
					DG.DOI.I[i].editable);
		}
	} else {
		for (unsigned int i = 0; i < DG.DOI.I.size(); i++) {
			ShowHideNodeMenuBar(str2tog(DG.DOI.I[i].pou.strio),
					"✎/" + DG.DOI.I[i].mid + "/true", DG.DOI.I[i].editable);
			ShowHideNodeMenuBar(str2tog(DG.DOI.I[i].pou.strio),
					"✎/" + DG.DOI.I[i].mid + "/false", DG.DOI.I[i].editable);
		}
	}
}

void DependencyMonitor::ShowHideNodeMenuBar(unsigned int tog, string item,
		bool b) {
	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		if (0 == tog) {
			if (DG.DN[i].BarIn) {
				Fl_Menu_Item *p = (Fl_Menu_Item*) DG.DN[i].BarIn->find_item(
						item.c_str());
				if (p) {
					if (b)
						p->activate();
					else
						p->deactivate();
				}
			}
		} else {
			if (DG.DN[i].BarOut) {
				Fl_Menu_Item *p = (Fl_Menu_Item*) DG.DN[i].BarOut->find_item(
						item.c_str());
				if (p) {
					if (b)
						p->activate();
					else
						p->deactivate();
				}
			}
		}
	}
}

void DependencyMonitor::MenuJointRefresh() {
	if (Mode == SmartDG_OBJECT_MODE) {
		RefreshDOIFlags(currentView, "ALL", "ALL", "ALL", currentView, false);
		RefreshDOIFlags(currentView, "ALL", dir2str(currentDirection).c_str(),
				"ALL", currentView, true);
		RefreshDOIFlags(currentView, "ALL",
				dir2str(-1 * currentDirection).c_str(), "ALL", currentView,
				false);
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		RefreshDOIFlags("ALL", "ALL", "ALL", "ALL", currentView, false);
		RefreshDOIFlags("ALL", "ALL", dir2str(currentDirection).c_str(), "ALL",
				"ALL", true);
		RefreshDOIFlags("ALL", "ALL", dir2str(-1 * currentDirection).c_str(),
				"ALL", "ALL", false);
	}
	//Edit Menu
	if (currentDirection > 0) {
		for (unsigned int i = 0; i < DG.DN.size(); i++) {
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DN[i].Name + "/In",
					false);
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DN[i].Name + "/Out",
					true);
		}
	} else {
		for (unsigned int i = 0; i < DG.DN.size(); i++) {
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DN[i].Name + "/In", true);
			ShowHideMonitorWindowMenuBar("Edit/" + DG.DN[i].Name + "/Out",
					false);
		}
	}

	//Node Menu
	for (unsigned int i = 0; i < DG.DN.size(); i++) {
		if (currentDirection > 0) {
			for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
				ShowHideNodeMenuBar(0,
						string("✎/" + DG.DN[i].DP[0][j].Name).c_str(), false);
			}
			for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
				ShowHideNodeMenuBar(1,
						string("✎/" + DG.DN[i].DP[1][j].Name).c_str(), true);
			}
		} else {
			for (unsigned int j = 0; j < DG.DN[i].DP[0].size(); j++) {
				ShowHideNodeMenuBar(0,
						string("✎/" + DG.DN[i].DP[0][j].Name).c_str(), true);
			}
			for (unsigned int j = 0; j < DG.DN[i].DP[1].size(); j++) {
				ShowHideNodeMenuBar(1,
						string("✎/" + DG.DN[i].DP[1][j].Name).c_str(), false);
			}
		}
	}

}

void DependencyMonitor::resetConDirection() {
	if (Mode == SmartDG_OBJECT_MODE) {
		for (unsigned int i = 0; i < DG.View[currentView].size(); i++)
			DG.View[currentView][i].con->setDirection(0); // Resets Connection directions to 0
		RefreshMonitor();
	}
}

string DependencyMonitor::extractPortName(string s) {
	unsigned t = s.substr(4).find("/");
	return s.substr(4, t);
}

string DependencyMonitor::tog2str(int tog) {
	if (0 == tog)
		return "In";
	return "Out";
}

int DependencyMonitor::str2tog(string str) {
	if ("In" == str)
		return 0;
	return 1;
}

int DependencyMonitor::toginv(int tog) {
	if (0 == tog)
		return 1;
	return 0;
}

string DependencyMonitor::dir2str(int dir) {
	if (-1 == dir)
		return "In";
	if (1 == dir)
		return "Out";
	return "ALL";
}

void DependencyMonitor::GenDispStr() {
	if (Mode == SmartDG_OBJECT_MODE) {
		if (currentDirection > 0)
			DispString = string(
					"ObjectView:" + currentView + " | Forward Business");
		else if (currentDirection < 0)
			DispString = string(
					"ObjectView:" + currentView + " | Reverse Business");
	}
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		if (currentDirection > 0)
			DispString = string(
					"ComponentView:" + currentComponent
							+ " | Forward Business");
		else if (currentDirection < 0)
			DispString = string(
					"ComponentView:" + currentComponent
							+ " | Reverse Business");
	}
	if (View2ViewFlag && SmartDG_GlobalData::View2ViewFlag) {
		DispString = "Σ  Attached | " + DispString;
	}
	if (SolverSync) {
		DispString = DispString + " | Solver Synced    ҉";
	}
}

void DependencyMonitor::Solver(unsigned int doiindex) {
	cout << endl << "S	O	L	V	E	R" << endl;
	// #TODO Smarter Solver
	string obj = DG.DOI.I[doiindex].obj;
	vector<string> Return;

	// Component GUI Windows
	if ((Mode == SmartDG_COMPONENT_MODE)
			|| (Mode == SmartDG_COMPONENT_DEVELOPER_MODE)) {
		unsigned int nodeindex = DG.DOI.I[doiindex].pou.NodeIndex;
		int direction = DG.DOI.I[doiindex].direction;
		// Call Component TFs followed by All Connector TFs
		if (direction > 0) {
			cout << DG.DN[nodeindex].Name << "[<<] ";
			DG.DN[nodeindex].TFT("FT", Return, DG.DN[nodeindex].DP);
		}
		if (direction < 0) {
			cout << DG.DN[nodeindex].Name << "[>>] ";
			DG.DN[nodeindex].TFT("TF", Return, DG.DN[nodeindex].DP);
		}
		// Call All Connector TFs
		for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
			if (DG.View[obj][i].From.NodeIndex == nodeindex) {
				cout << DG.DN[nodeindex].Name << "{>>" << DG.View[obj][i].Name
						<< " ";
				DG.View[obj][i].TF(DG.DN[nodeindex].DP,
						DG.DN[DG.View[obj][i].To.NodeIndex].DP,
						DG.View[obj][i]);
			}
			if (DG.View[obj][i].To.NodeIndex == nodeindex) {
				cout << DG.View[obj][i].Name << "<<}" << DG.DN[nodeindex].Name
						<< " ";
				DG.View[obj][i].FT(DG.DN[DG.View[obj][i].From.NodeIndex].DP,
						DG.DN[nodeindex].DP, DG.View[obj][i]);
			}
		}
		cout << endl;
	}
	// System GUI Windows
	if (Mode == SmartDG_OBJECT_MODE) {
		// Call All Connector TFs and All Component TFs till values stabilize
		for (unsigned int loop = 0;
				loop < SmartDG_CIRCULAR_DEPENDENCY_BREAKOUT_COUNT; loop++) {
			DependencyDataPackage::delta = 0;
			// Call Connector TFs
			for (unsigned int i = 0; i < DG.View[obj].size(); i++) {
				if (currentDirection > 0) {
					cout << DG.View[obj][i].Name << ">> ";
					DG.View[obj][i].TF(DG.DN[DG.View[obj][i].From.NodeIndex].DP,
							DG.DN[DG.View[obj][i].To.NodeIndex].DP,
							DG.View[obj][i]);
				}
				if (currentDirection < 0) {
					cout << "<<" << DG.View[obj][i].Name << " ";
					DG.View[obj][i].FT(DG.DN[DG.View[obj][i].From.NodeIndex].DP,
							DG.DN[DG.View[obj][i].To.NodeIndex].DP,
							DG.View[obj][i]);
				}
			}
			// Call All Component TFs
			for (unsigned int j = 0; j < DG.DN.size(); j++) {
				if (currentDirection > 0) {
					cout << DG.DN[j].Name << "[>>] ";
					DG.DN[j].TFT("TF", Return, DG.DN[j].DP);
				}
				if (currentDirection < 0) {
					cout << DG.DN[j].Name << "[<<] ";
					DG.DN[j].TFT("FT", Return, DG.DN[j].DP);
				}
			}
			cout << "DependencyDataPackage::delta = "
					<< DependencyDataPackage::delta << endl;
			if (DependencyDataPackage::delta == 0)
				break;
			if (loop + 1 == SmartDG_CIRCULAR_DEPENDENCY_BREAKOUT_COUNT)
				cout << "ERROR[CIRCULAR_DEPENDENCY_BREAKOUT_COUNT]: Reached"
						<< endl;
		}
	}
	// Sync with other views
	if (View2ViewFlag && SmartDG_GlobalData::View2ViewFlag && SolverSync) {
		if (Mode != SmartDG_COMPONENT_DEVELOPER_MODE) {
			SyncOI();
		}
	}
}

// A static unsigned integer that keeps count of DependencyMonitor objects created
unsigned int DependencyMonitor::count = 0;
// A static boolean variable part of the mechanism to indicate SmartDG_LITE_DISPLAYMODE
bool DependencyMonitor::MTLiteOn = false;
// A static boolean variable part of the mechanism to indicate initialization of SmartDG_LITE_DISPLAYMODE
bool DependencyMonitor::MTLiteInit = false;

DependencyMonitor::~DependencyMonitor() {
}

} /* namespace SmartDG */
