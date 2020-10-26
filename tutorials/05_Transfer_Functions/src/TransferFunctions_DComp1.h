#ifndef TRANSFERFUNCTIONS_DCOMP1
#define TRANSFERFUNCTIONS_DCOMP1

#include <SmartDG.h>

namespace SmartDG	{
namespace TransferFunctions_DComp1{
	inline string Name()	{
		return "DComp1";
	}

	bool Get(vector< vector<SmartDG::DependencyPort> >& DP, string IO, string Port, string Obj)	{
		unsigned int i = 0;
		if (IO == "InputPort") i = 0;
		if (IO == "OutputPort") i = 1;
		for(unsigned int j = 0; j< DP[i].size(); j++)	{
			if ( DP[i][j].Name == Port)	{
				for(unsigned int k = 0; k< DP[i][j].DO.size(); k++)	{
					if (DP[i][j].DO[k].Name == Obj)
						return DP[i][j].DO[k].Get().b;
				}
			}
		}
		return false;
	}

	void Set(vector< vector<SmartDG::DependencyPort> >& DP, string IO, string Port, string Obj, bool val)	{
		unsigned int i = 0;
		if (IO == "InputPort") i = 0;
		if (IO == "OutputPort") i = 1;
		for(unsigned int j = 0; j< DP[i].size(); j++)	{
			if ( DP[i][j].Name == Port)	{
				for(unsigned int k = 0; k< DP[i][j].DO.size(); k++)	{
					if (DP[i][j].DO[k].Name == Obj)	{
						DependencyDataPackage ddp;
						ddp.b = val;
						DP[i][j].DO[k].Set(ddp);
					}
				}
			}
		}
	}


	inline void TF(vector<string> &Return, vector< vector<SmartDG::DependencyPort> >& DP)	{
		// TF Business logic goes here
		bool inDObj1 = Get(DP,"InputPort","In","DObj1");
		bool inDObj2 = Get(DP,"InputPort","In","DObj2");
		Set(DP,"OutputPort","Out","DObj1", inDObj1);
		Set(DP,"OutputPort","Out","DObj2", inDObj2);
		Return.push_back(SmartDG_OK);
	}

	inline void FT(vector<string> &Return, vector< vector<SmartDG::DependencyPort> >& DP)	{
		Return.push_back(SmartDG_OK);
		// FT Business logic goes here
		bool inDObj1 = Get(DP,"OutputPort","Out","DObj1");
		bool inDObj2 = Get(DP,"OutputPort","Out","DObj2");
		Set(DP,"InputPort","In","DObj1", inDObj1);
		Set(DP,"InputPort","In","DObj2", inDObj2);
	}

	inline void TFT(string Fun, vector<string> &Return, vector< vector<SmartDG::DependencyPort> >& DP)	{
		cout << "SmartComponent " << Name() << "TFT  Call to : " << Fun  << endl;
		if(Fun == "List")	{
			Return.push_back(SmartDG_OK);
			Return.push_back("List");
			Return.push_back("Name");
			Return.push_back("TF");
			Return.push_back("FT");
			return;
		}
		if(Fun == "Name")	{
			Return.push_back(SmartDG_OK);
			Return.push_back(Name());
			return;
		}
		if(Fun == "TF")	{ TF(Return, DP);	return;	}
		if(Fun == "FT")	{ FT(Return, DP);	return;	}

		Return.push_back(SmartDG_NOT_OK); // Function Not Found
		return;
	}
} /* namespace TransferFunctions_DComp1 */
} /* namespace SmartDG */

#endif /* TRANSFERFUNCTIONS_DCOMP1 */
