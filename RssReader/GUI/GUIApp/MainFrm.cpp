// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"
#include ".\mainfrm.h"

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::SetSplitterPos(int iPos)
{
	if (iPos < -1)
	{
		RECT rc;
		m_wndSplitter.GetClientRect(&rc);
		iPos = (rc.right - rc.left) / (-iPos);
	}
	m_wndSplitter.SetSplitterPos(iPos);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;
		
	if (m_wndView1.PreTranslateMessage(pMsg))
		return TRUE;
		
	if (m_tabbedChildWindow.PreTranslateMessage(pMsg))
		return TRUE;
	// allow typical message processing
	return FALSE;
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	m_CmdBar.SetCommandBarExtendedStyle(0, CBR_EX_SHAREMENU);
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();
	// Creating splitter and views
	m_hWndClient = m_wndSplitter.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		
	//m_wndView1.Create(m_wndSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
	m_wndView1.Create(m_wndSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASLINES | TVS_LINESATROOT|TVS_HASBUTTONS | TVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);

	HTREEITEM hRoot= m_wndView1.InsertItem(_T("RSS"),TVI_ROOT,TVI_ROOT);
	m_wndView1.InsertItem(_T("Some URL"),hRoot,TVI_SORT);
	m_wndView1.InsertItem(_T("Some URL 2"),hRoot,TVI_SORT);


	m_tabbedChildWindow.Create(m_wndSplitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);



	m_wndSplitter.SetSplitterPanes(m_wndView1, m_tabbedChildWindow);



//	m_window1.Create(m_tabbedChildWindow, rcDefault, NULL,
//		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT,
//		0);



//	m_tabbedChildWindow.AddTabWithIcon(m_window1, _T("List View"), IDR_MAINFRAME);
	PostMessage(MSG_POSTCREATE);

	// End creating splitter and views

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);



	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}

LRESULT CMainFrame::OnPostCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SetSplitterPos(-4);
	return 0;
}
LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}


LRESULT CMainFrame::OnChildViewNotification(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	//m_window1.Create(m_tabbedChildWindow, rcDefault, NULL,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT,
	//	0);
	//m_tabbedChildWindow.AddTabWithIcon(m_window1, _T("List View"), IDR_MAINFRAME);
	HTREEITEM hItem = reinterpret_cast<HTREEITEM>(lParam);
	TItem2ViewMap::iterator it = m_spViewsMap.find(hItem);
	if( m_spViewsMap.end()!= it )
	{
		//CHTMLView* 
		m_tabbedChildWindow.DisplayTab((*it).second->m_hWnd);
	}
	else
	{
		TCHAR lpszTabName[512];
		SPHtmlView spView = SPHtmlView(new CHTMLView);
		spView->Create(m_tabbedChildWindow, rcDefault, NULL,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT,0);
		spView->OpenFile(_T("E:\\library\\boost_1_34_0\\libs\\function\\index.html"));
		m_spViewsMap.insert(std::make_pair(hItem,spView));
		_stprintf(lpszTabName,"%s_%x",_T("List View"),hItem);
		m_tabbedChildWindow.AddTabWithIcon( spView->m_hWnd , lpszTabName, IDR_MAINFRAME);
	}
	m_hCurrentTabItem = hItem;
	return 0;
}
LRESULT CMainFrame::OnBackTo(WORD wNotifyCode, WORD wID, HWND hWndCtl)
{
	TItem2ViewMap::iterator it = m_spViewsMap.find(m_hCurrentTabItem);
	if( m_spViewsMap.end()!= it )
	{
		SPHtmlView spActiveView = (*it).second;
		//spActiveView->
		//m_tabbedChildWindow.DisplayTab((*it).second->m_hWnd);
	}
	return 0;
}
