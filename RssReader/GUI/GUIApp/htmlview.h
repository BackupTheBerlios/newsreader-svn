// htmlview.h: interface for the CHTMLView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLVIEW_H__8CEA139E_1C20_4B40_836F_71864F34F919__INCLUDED_)
#define AFX_HTMLVIEW_H__8CEA139E_1C20_4B40_836F_71864F34F919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wtl_htmlayout.h>
#include <wtl_htmlayouthost.h>
#include "htmlayout_aux.h"

class CHTMLView : 
    public CWindowImpl<CHTMLView, CHTMLayoutCtrl>,
    public CHTMLayoutHost<CHTMLView>,
    public htmlayout::event_handler
    {
      bool      m_probeMode;
      CString   m_currentUrl;
      HELEMENT  m_mouseOver;
public:
      CHTMLView() : event_handler( HANDLE_BEHAVIOR_EVENT ) {}

	    BOOL PreTranslateMessage(MSG* pMsg)
	    {
        // HTMEngine needs tabs for TAB navigation

        if((pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP) && ::GetFocus() == m_hWnd)
        {
          if(pMsg->wParam == VK_TAB) // always need this
          {
            ::SendMessage(m_hWnd,pMsg->message,pMsg->wParam,pMsg->lParam);
            return TRUE;
          }
          /*if() // others - only when we are in focus
          {
            ::SendMessage(m_hWnd,pMsg->message,pMsg->wParam,pMsg->lParam);
            return TRUE;
          }*/
        }
        return FALSE;
        //return ::IsDialogMessage(m_hWnd,pMsg);
	    }

      BEGIN_MSG_MAP(CHTMLView)
		    MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        HTML_HYPERLINK_HANDLER(OnHyperlink)
	    END_MSG_MAP()

      LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
      {
        m_probeMode = false;
        DefWindowProc();
        // HTMLayout stuff
        SetCallback(); // reroute all notifications here
        SetEventHandler(this); // set this as a "zero level" event handler, all not handled HTML DOM events will go here

        LoadHtmlResource(MAKEINTRESOURCE(IDR_HTML1));
        return 0;
      }

      LRESULT OnHyperlink(NMHL_HYPERLINK* pnmhl, BOOL& bHandled)
      {
		    ATLTRACE(_T("CHTMLayoutHost::OnHyperLink: href='%.256s' target='%s' action=%u\n"), 
          CString(pnmhl->szHREF), CString(pnmhl->szTarget), pnmhl->action);

		    switch (pnmhl->action) {
          case NMHL_HYPERLINK::ENTER: 
            break;
			    case NMHL_HYPERLINK::LEAVE: 
            break;
			    case NMHL_HYPERLINK::CLICK: 
            {
              CString url(pnmhl->szHREF);
            //AtlMessageBox(m_hWnd, (LPCTSTR)CString(pnmhl->szHREF), TEXT("href"));
//              ::SendMessage( GetParent(),WM_HTML_NAVIGATE,0, LPARAM((LPCTSTR)url));
#ifdef _DEBUG
              /*
              htmlayout::dom::element root = htmlayout::dom::element::root_element(m_hWnd);
              htmlayout::dom::element el = root.find_first("#test-of-insertion");
              if(el.is_valid())
              {
                const char *t = "<p><a href=\"\">some text</a></p>";
                el.element::set_html((LPBYTE)t,strlen(t),SIH_REPLACE_CONTENT);
                root.update(true);
                Invalidate();
                UpdateWindow();
              }*/
#endif
            }
            break;

		    }
        return 0;
      }


      virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
      { 
        switch( params.cmd )
        {
        case BUTTON_CLICK:              // click on button
             OnButtonClick( params.heTarget );   break;
        case BUTTON_PRESS:              break;// mouse down or key down in button
        case BUTTON_STATE_CHANGED:      
             OnButtonState( params.heTarget );   break;// checkbox/radio/slider changed its state/value 
        case EDIT_VALUE_CHANGING:       break;// before text change
        case EDIT_VALUE_CHANGED:        break;// after text change
        case SELECT_SELECTION_CHANGED:  break;// selection in <select> changed
        case SELECT_STATE_CHANGED:      break;// node in select expanded/collapsed, heTarget is the node

        case POPUP_REQUEST: 
             OnPopupRequest( params.he, params.heTarget );
                                        break;// request to show popup just received, 
                                              //     here DOM of popup element can be modifed.
        case POPUP_READY:               break;// popup element has been measured and ready to be shown on screen,
                                              //     here you can use functions like ScrollToView.
        case POPUP_DISMISSED:           break;// popup element is closed,
                                              //     here DOM of popup element can be modifed again - e.g. some items can be removed
                                              //     to free memory.

        case MENU_ITEM_ACTIVE:          break;// menu item activated by mouse hover or by keyboard
        case MENU_ITEM_CLICK:                 // menu item click 
             OnMenuClick( params.he, params.heTarget );     break;


            // "grey" event codes  - notfications from behaviors from this SDK 
        case HYPERLINK_CLICK:           break;// hyperlink click
        case TABLE_HEADER_CLICK:        break;// click on some cell in table header, 
                                              //     target = the cell, 
                                              //     reason = index of the cell (column number, 0..n)
        case TABLE_ROW_CLICK:           break;// click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)
        case TABLE_ROW_DBL_CLICK:       break;// mouse dbl click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)

        case ELEMENT_COLLAPSED:         break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
        case ELEMENT_EXPANDED:          break;// element was expanded,

        }
        return FALSE; 
      }

      bool set_string( std::wstring& stupid_std_string, const wchar_t* str )
      {
         if(!str) return false;
         stupid_std_string = str;
         return true;
      }

      std::wstring id_or_name_or_text( HELEMENT he )
      {
        htmlayout::dom::element el = he;

        std::wstring name;
        if(set_string( name, el.get_attribute("id")) ) return name;
        if(set_string( name, el.get_attribute("name")) ) return name;

        name = L"{";
        const wchar_t* str = el.text();
        if( str )
          name += str;
        name += L"}";
        return name;
      }

      void OnButtonClick(HELEMENT button)
      {
        htmlayout::debug_output_console dc;
        dc.printf("BUTTON_CLICK: %S\n", id_or_name_or_text(button).c_str() );
      }

      void OnButtonState(HELEMENT button)
      {
        //htmlayout::debug_output_console dc;
        //dc.printf("BUTTON_STATE_CHANGED: %S\n", id_or_name_or_text(button).c_str() );
      }

      
      LRESULT OnMenuClick(HELEMENT anchor, HELEMENT menuItem)
      {
        htmlayout::debug_output_console dc;
        dc.printf("MENU_ITEM_CLICK: %S for %S\n", id_or_name_or_text(menuItem).c_str(), id_or_name_or_text(anchor).c_str() );
        return 0;
      }

      LRESULT OnPopupRequest(HELEMENT heAnchor, HELEMENT hePopup)
      {
        //htmlayout::debug_output_console dc;

        //htmlayout::dom::element popup = hePopup;
        //htmlayout::dom::element anchor = heAnchor;

        //dc.printf("POPUP_REQUEST: popup=%s, anchor=%s\n", popup.get_element_type(), anchor.get_element_type() );
        return 0;
      }

      void Open( LPCTSTR url = 0)
      {
        if( url )
          m_currentUrl = url;
        else
          url = m_currentUrl;
        OpenFile(url);
      }


      // switch probe mode on - will show tag stack in status bar
      void ProbeMode()
      {
        m_probeMode = true;
      }


      // printTagName - fill buf with tag stack.
      char* printTag( char* buf, HELEMENT he )
      {
        htmlayout::dom::element el = he;
        if(el.is_valid())
        {
          char* p = printTag( buf, el.parent() );
          
          const wchar_t* id = el.get_attribute("id");

          
          if(id)
            p += sprintf(p,"<%s#%S%s%s> ", el.get_element_type(), id, 
              el.get_state(STATE_COLLAPSED)?":collapsed":"",
              el.get_state(STATE_EXPANDED)?":expanded":""
              );
          else
            p += sprintf(p,"<%s%s%s> ", el.get_element_type(),
              el.get_state(STATE_COLLAPSED)?":collapsed":"",
              el.get_state(STATE_EXPANDED)?":expanded":""
              );
          return p;
        }
        return buf;
      }

      LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
      {
        if(m_probeMode)
        {
          POINT pt;
            pt.x = GET_X_LPARAM(lParam); 
            pt.y = GET_Y_LPARAM(lParam); 
          
          HELEMENT he = htmlayout::dom::element::find_element(m_hWnd,pt);
          if(m_mouseOver != he)
          {
            m_mouseOver = he;
            char buf[2048]; // may overflow, not for use in production code
            printTag(buf,he);
//            ::SendMessage( GetParent(),WM_SHOW_STATUS,0, LPARAM(buf));
          }
        }
        bHandled = FALSE;
        return 0;
      }

      /*virtual LRESULT OnLoadData(LPNMHL_LOAD_DATA pnmld)
      {
        // <include> in <table> testing.
        if( aux::wcseq(pnmld->uri,L"rowdata:1") )
        {
           char data[] = {
               "<tr style=\"background-color:yellow\"><td>Test</td></tr>"
           };
    
           HTMLayoutDataReady(pnmld->uri, (LPBYTE)data, strlen(data));
           return LOAD_OK;
          
        }
        return CHTMLayoutHost<CHTMLView>::OnLoadData(pnmld);
      }*/

    };

#endif // !defined(AFX_HTMLVIEW_H__8CEA139E_1C20_4B40_836F_71864F34F919__INCLUDED_)
