// RssSubscriptionTree.cpp : implementation of the CRssSubscriptionTree class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "RssSubscriptionTree.h"
#include ".\rsssubscriptiontree.h"

CRssSubscriptionTree::CRssSubscriptionTree()
{
}

CRssSubscriptionTree::~CRssSubscriptionTree()
{
}

BOOL CRssSubscriptionTree::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
}

LRESULT CRssSubscriptionTree::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	// Put your intitialization code here
	
	return 0;
}

LRESULT CRssSubscriptionTree::OnNMDblClk(LPNMHDR pnmh)
{
	//for ListView - (LPNMITEMACTIVATE)pnmh
	//for StatusBar	- (LPNMMOUSE)pnmh
	HTREEITEM hSelItem=GetSelectedItem();
	if( hSelItem == GetRootItem() )
		return 0;
	SendMessage( ::GetParent(GetParent()) , WM_TREE_ITEM_DBCLICK , 0,(LPARAM)hSelItem );
	return 0;
}
