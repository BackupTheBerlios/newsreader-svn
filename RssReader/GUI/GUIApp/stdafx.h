// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define  _CRT_SECURE_NO_DEPRECATE

#include <atlbase.h>

#if _ATL_VER >= 0x0700
#include <atlcoll.h>
#include <atlstr.h>
#include <atltypes.h>
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#else
#define _WTL_USE_CSTRING
#endif

#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlsplit.h>
#include <atlmisc.h>

#include "atlgdix.h"

#include "CustomTabCtrl.h"
#include "DotNetTabCtrl.h"
//#include "SimpleTabCtrls.h"
//#include "SimpleDlgTabCtrls.h"
#include "TabbedFrame.h"

#define WM_TREE_ITEM_DBCLICK WM_USER + 123
