// BrowserParent.cpp : implementation of the CBrowserParent class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "BrowserParent.h"

CBrowserParent::CBrowserParent()
{
}

CBrowserParent::~CBrowserParent()
{
}

BOOL CBrowserParent::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
}

LRESULT CBrowserParent::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	// Put your intitialization code here
	
	return 0;
}

LRESULT CBrowserParent::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here
	dc.Rectangle(10, 10, 100, 100);
	
	return 0;
}
