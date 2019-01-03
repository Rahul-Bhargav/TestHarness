#pragma once
///////////////////////////////////////////////////////////////////////
// IHostedResource.h - Provides the interface for passing a			 //
//					   Hostable resource to a test				     //
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
* - IHostedResource	Provides an interface for the user to use a IHostable resource.
*
* Required Files:
* ---------------
*   IHostable.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 11 Oct 2018
* first release
*
* Planned Additions and Changes:
* ------------------------------
* - none
*/
#include "IHostable.h"

namespace HostedUtilities
{
	template<class T>
	class IHostedResource
	{
	public:
		virtual ~IHostedResource() {}
		virtual void work(T& value) = 0;
		virtual void setValue(IHostable<T>& value) = 0;
	};
}
