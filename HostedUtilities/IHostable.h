#pragma once
///////////////////////////////////////////////////////////////////////
// IHostable.h - Provides the interface for declaring hostable		 //
//				 resources											 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - IHostable  Provides an interface for the user to implement hostable version of their resource.
*
* Maintenance History:
* --------------------
* ver 2.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none 
*/

namespace HostedUtilities
{
	template<class T>
	class IHostable
	{
	public:
		virtual bool execute(T value) = 0;
	};
}
