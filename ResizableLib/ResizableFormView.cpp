// ResizableFormView.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000 by Paolo Messina
// (ppescher@yahoo.com)
//
// Free for non-commercial and commercial use,
// provided that the original author's name
// and copyright is quoted somewhere in the
// final executable and in the program's help
// or documentation.
// You may change the code to your needs,
// provided that credits to the original
// author are given in the modified files.
// Also a copy of your enhancements would
// be nice, but it's not required. Please,
// consider to share your work on CodeProject.
//  
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResizableFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizableFormView

IMPLEMENT_DYNAMIC(CResizableFormView, CFormView)

inline void CResizableFormView::Construct()
{
	m_bInitDone = FALSE;
}

CResizableFormView::CResizableFormView(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{
	Construct();
}

CResizableFormView::CResizableFormView(LPCTSTR lpszTemplateName)
	: CFormView(lpszTemplateName)
{
	Construct();
}

CResizableFormView::~CResizableFormView()
{
}


BEGIN_MESSAGE_MAP(CResizableFormView, CFormView)
	//{{AFX_MSG_MAP(CResizableFormView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizableFormView diagnostics

#ifdef _DEBUG
void CResizableFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CResizableFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizableFormView message handlers

void CResizableFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (m_bInitDone)
		ArrangeLayout();
}

void CResizableFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_bInitDone = TRUE;

	// MDI child need this
	ArrangeLayout();
}


void CResizableFormView::GetTotalClientRect(LPRECT lpRect)
{
	// before initialization, give dialog template size

	if (!m_bInitDone)
	{
		// UNDOC - CScrollView::m_totalLog protected member
		// holds template size set during CFormView::Create
		// by a call to CScrollView::SetScrollSizes
		lpRect->left = 0;
		lpRect->top = 0;
		lpRect->right = m_totalLog.cx;
		lpRect->bottom = m_totalLog.cy;
		return;
	}

	// otherwise, give correct size if scrollbars active

	GetClientRect(lpRect);
	CRect rect(lpRect);

	// get scrollable size
	CSize size = GetTotalSize();

	// enlarge client area when needed
	if (rect.Width() < size.cx)
		lpRect->right = lpRect->left + size.cx;
	if (rect.Height() < size.cy)
		lpRect->bottom = lpRect->top + size.cy;
}

BOOL CResizableFormView::OnEraseBkgnd(CDC* pDC) 
{
	ClipChildren(pDC);	// avoid flickering

	return CFormView::OnEraseBkgnd(pDC);
}