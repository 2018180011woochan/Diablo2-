// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "MiniView.h"
#include "MainFrm.h"
#include "Diablo_II_MapToolView.h"
#include "Terrain.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CDiablo_II_MapToolView* pView = (CDiablo_II_MapToolView*)pMain->m_tMainSplitter.GetPane(0, 1);
	CTerrain* pTerrain = pView->m_pTerrain;
	CGraphic_Device::Get_Instance()->Render_Begin();
	pTerrain->Mini_Render_Terrain();
	CGraphic_Device::Get_Instance()->Render_End(m_hWnd);
}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.
