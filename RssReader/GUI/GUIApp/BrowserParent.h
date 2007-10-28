// BrowserParent.h : interface of the CBrowserParent class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CBrowserParent : public CWindowImpl<CBrowserParent>
{
public:
	DECLARE_WND_CLASS(_T("CBrowserParent"))
	
	CBrowserParent();
	~CBrowserParent();
	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CBrowserParent)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
