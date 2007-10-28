// RssSubscriptionTree.h : interface of the CRssSubscriptionTree class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlcrack.h>

class CRssSubscriptionTree : public CWindowImpl<CRssSubscriptionTree, CTreeViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("CRssSubscriptionTree"), CTreeViewCtrl::GetWndClassName())
	
	CRssSubscriptionTree();
	~CRssSubscriptionTree();
	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP_EX(CRssSubscriptionTree)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_DBLCLK, OnNMDblClk)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNMDblClk(LPNMHDR pnmh);
};
