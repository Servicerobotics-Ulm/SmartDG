////////////////////////////////////////////////////////////////////////////////
///	\file	DependencyObjectInstances.cpp
/// \brief	Source file for DependencyObjectInstances class
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

#include "SmartDG.h"

namespace SmartDG {

DependencyObjectInstances::DependencyObjectInstances() {
	// Calls DependencyObjectInstances::SetContext() with all default values
	ResetContext();
}

void DependencyObjectInstances::Add(Dependency &d) {
	// Adding Dependency::From to I
	DependencyObjectInstance i1(DependencyObjectInstances::count, d.From, d.To,
			1);
	I.push_back(i1);
	DependencyObjectInstances::count += 1;
	// Adding Dependency::To to I
	DependencyObjectInstance i2(DependencyObjectInstances::count, d.To, d.From,
			-1);
	I.push_back(i2);
	DependencyObjectInstances::count += 1;
}

void DependencyObjectInstances::Display() {
	for (unsigned long i = 0; i < I.size(); i++)
		I[i].Display();
}

void DependencyObjectInstances::DisplayIf(unsigned int c) {
	for (unsigned long i = 0; i < I.size(); i++)
		I[i].DisplayIf(c);
}

void DependencyObjectInstances::SetContext(string v, string n, string i,
		string p, string o) {
	ResetContext(true);
	ViewContext = v;
	NodeContext = n;
	IOContext = i;
	PortContext = p;
	ObjectContext = o;
}

void DependencyObjectInstances::SetContextHierarchy(string v, string n,
		string i, string p, string o) {
	if (v == "ALL") {
		ResetContext(true);
	} else {
		ResetContext(true);
		ViewContext = v;
		if (n != "ALL")
			NodeContext = n;
		if (i != "ALL")
			IOContext = i;
		if (p != "ALL")
			PortContext = p;
		if (o != "ALL")
			ObjectContext = o;
	}
}

void DependencyObjectInstances::ResetContext(bool b) {
	UseContext = b;
	ViewContext = "ALL";
	NodeContext = "ALL";
	IOContext = "ALL";
	PortContext = "ALL";
	ObjectContext = "ALL";
}

void DependencyObjectInstances::DisplayContext() {
	cout << ViewContext << "/" << NodeContext << "/" << IOContext << "/"
			<< PortContext << "/" << ObjectContext << "  [" << UseContext << "]"
			<< endl;
}

void DependencyObjectInstances::setf(unsigned int i, bool b, unsigned int c) {
	// Base function called to set DependencyObjectInstance::visible and
	// DependencyObjectInstance::editable flags for all DependencyObjectInstance objects in I
	switch (c) {
	case 0:
		I[i].visible = b;
		I[i].editable = b;
		break;
	case 1:
		I[i].visible = b;
		break;
	case 2:
		I[i].editable = b;
		break;
	}
}

void DependencyObjectInstances::SetFlagContext(bool b, unsigned int c) {
	// Set flag Value:b, Scope: Context, Condition: c
	if (UseContext)
		for (unsigned long i = 0; i < I.size(); i++)
			if ((ViewContext == "ALL") || (ViewContext == I[i].pou.stro))
				if ((NodeContext == "ALL") || (NodeContext == I[i].pou.strn))
					if ((IOContext == "ALL") || (IOContext == I[i].pou.strio))
						if ((PortContext == "ALL")
								|| (PortContext == I[i].pou.strp))
							if ((ObjectContext == "ALL")
									|| (ObjectContext == I[i].pou.stro))
								setf(i, b, c);
}

void DependencyObjectInstances::SetFlagURL(string u, bool b, unsigned int c) {
	// Set flag Value:b, Scope: DependencyObject associated with the given URL, Condition: c
	for (unsigned long i = 0; i < I.size(); i++)
		if (I[i].pou.str == u)
			setf(i, b, c);
}

void DependencyObjectInstances::SetFlagMenuIDString(string m, bool b,
		unsigned int c) {
	// Set flag Value:b, Scope: DependencyObject associated with the given Menu selection string, Condition: c
	for (unsigned long i = 0; i < I.size(); i++)
		if ((I[i].mid == m) || (I[i].midL == m))
			setf(i, b, c);
}

// Static class variable that keeps count for DependencyObjectInstances objects in I
unsigned long DependencyObjectInstances::count = 0;

DependencyObjectInstances::~DependencyObjectInstances() {
}

} /* namespace SmartDG */
