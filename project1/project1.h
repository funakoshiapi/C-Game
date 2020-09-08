
// project1.h : main header file for the project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cproject1App:
// See project1.cpp for the implementation of this class
//

/**
 * Class that represents an instance of the application
 */
class Cproject1App : public CWinApp
{
public:
	Cproject1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; ///< Contains startup information for Gdiplus
	ULONG_PTR gdiplusToken = 0; ///< Pointer to the GDI+ Token the app will use
};

extern Cproject1App theApp;
