#ifndef TRANSFERFUNCTIONS_DCOMP2
#define TRANSFERFUNCTIONS_DCOMP2

#include <SmartDG.h>

namespace SmartDG	{
namespace TransferFunctions_DComp2{
	inline string Name()	{
		return "DComp2";
	}

	inline void TF(vector<string> &Return, vector< vector<SmartDG::DependencyPort> >& DP)	{
		Return.push_back(SmartDG_OK);
		// TF Business logic goes here
	}

	inline void FT(vector<string> &Return, vector< vector<SmartDG::DependencyPort> >& DP)	{
		Return.push_back(SmartDG_OK);
		// FT Business logic goes here
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
} /* namespace TransferFunctions_DComp2 */
} /* namespace SmartDG */

#endif /* TRANSFERFUNCTIONS_DCOMP2 */
