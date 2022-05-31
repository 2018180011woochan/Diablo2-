
// Diablo_II_MapToolView.cpp : CDiablo_II_MapToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Diablo_II_MapTool.h"
#endif

#include "Diablo_II_MapToolDoc.h"
#include "Diablo_II_MapToolView.h"
#include "Single_Texture.h"
#include "Texture_Manager.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "MyForm.h"
#include "Obj.h"
#include "Monster.h"
#include "StartTerrain.h"
#include "StartObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiablo_II_MapToolView

IMPLEMENT_DYNCREATE(CDiablo_II_MapToolView, CScrollView)
HWND g_hWND;
bool isBoxVisible;
bool isCollidRect;
bool ObjSortMode;
BEGIN_MESSAGE_MAP(CDiablo_II_MapToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CDiablo_II_MapToolView ����/�Ҹ�

CDiablo_II_MapToolView::CDiablo_II_MapToolView()
	: m_pTerrain(nullptr), m_pObj(nullptr), m_pMonster(nullptr), m_pStartObj(nullptr), m_pStartTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CDiablo_II_MapToolView::~CDiablo_II_MapToolView()
{
	Safe_Delete(m_pTerrain);
	Safe_Delete(m_pObj);
	Safe_Delete(m_pMonster);

	Safe_Delete(m_pStartObj);
	Safe_Delete(m_pStartTerrain);

	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();
}

BOOL CDiablo_II_MapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CDiablo_II_MapToolView �׸���

void CDiablo_II_MapToolView::OnDraw(CDC* /*pDC*/)
{
	CDiablo_II_MapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pGraphic_Device->Render_Begin();
	m_pTerrain->Render_Terrain(); 
	m_pMonster->Render_Object();
	m_pObj->Render_Object();

	//m_pStartTerrain->Render_Terrain();
	//m_pStartObj->Render_Object();

	m_pGraphic_Device->Render_End();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CDiablo_II_MapToolView �μ�

BOOL CDiablo_II_MapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CDiablo_II_MapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CDiablo_II_MapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CDiablo_II_MapToolView ����

#ifdef _DEBUG
void CDiablo_II_MapToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDiablo_II_MapToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDiablo_II_MapToolDoc* CDiablo_II_MapToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiablo_II_MapToolDoc)));
	return (CDiablo_II_MapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CDiablo_II_MapToolView �޽��� ó����


void CDiablo_II_MapToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWND = m_hWnd;
	m_pGraphic_Device = CGraphic_Device::Get_Instance();
	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device()))
		return;
	SetScrollSizes(MM_TEXT, CSize((TILECX * TILEX), TILEY * (TILECY >> 1)));
	// //1.������������ ������! 
	// CMainApp�� �ּҰ��� ��ȯ���ִ� �����Լ�.
	CMainFrame* pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();

	RECT rcMain = {};
	pMain->GetWindowRect(&rcMain);
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top);

	RECT rcView = {};
	GetClientRect(&rcView);

	DWORD dwWidth = rcMain.right - rcView.right;
	DWORD dwHeight = rcMain.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + dwWidth, WINCY + dwHeight, SWP_NOZORDER);


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 32)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Object/Object/LairObject_%d.png", L"Object", L"Object", 53)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/ConturyTile/Tile%d.png", L"Texture", L"ConturyTile", 108)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/struct/struct%d.png", L"Texture", L"struct", 10)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/MonsterSample/%d.png", L"Monster", L"Sample", 5)))
		return;

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain;
		m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(this);
	}
	if (nullptr == m_pObj)
	{
		m_pObj = new CObj;
		m_pObj->Ready_Object();
		m_pObj->Set_View(this);
	}

	if (nullptr == m_pStartTerrain)
	{
		m_pStartTerrain = new CStartTerrain;
		m_pStartTerrain->Ready_Terrain();
		m_pStartTerrain->Set_View(this);
	}
	if (nullptr == m_pStartObj)
	{
		m_pStartObj = new CStartObj;
		m_pStartObj->Ready_Object();
		m_pStartObj->Set_View(this);
	}

	if (nullptr == m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Ready_Object();
		m_pMonster->Set_View(this);
	}


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CDiablo_II_MapToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	// �̰� Ÿ�� ������� ���°� 
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMain->m_tSecondSplitter.GetPane(1, 0));
	// �̰� �̴Ϻ� �����Ҷ�� ���°�. 
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_tSecondSplitter.GetPane(0, 0));

	int iDrawID = pMyForm->m_tMapTool.m_iDrawID;
	_vec3 vMouse = { (float)point.x + GetScrollPos(0), (float)point.y + GetScrollPos(1), 0.f };
	m_pTerrain->TileChange_Terrain(vMouse, iDrawID);
	//m_pStartTerrain->TileChange_Terrain(vMouse, iDrawID);



	int iObjDrawID = pMyForm->m_tMapTool.m_iObjDrawID;
	m_pObj->Obj_Insert(vMouse, iObjDrawID);
	//m_pStartObj->Obj_Insert(vMouse, iObjDrawID);
	
	int iMonsterDrawID = pMyForm->m_tMonsterTool.m_iDrawID;
	m_pMonster->Obj_Insert(vMouse, iMonsterDrawID);

	InvalidateRect(nullptr, FALSE);
	pMiniView->InvalidateRect(nullptr, FALSE);


	CView::OnLButtonDown(nFlags, point);
}

void CDiablo_II_MapToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}


void CDiablo_II_MapToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMain->m_tSecondSplitter.GetPane(1, 0));
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_tSecondSplitter.GetPane(0, 0));

	_vec3 vMouse = { (float)point.x + GetScrollPos(0), (float)point.y + GetScrollPos(1), 0.f };
	// ������ Ŭ���ϸ� �׳� �⺻Ÿ�Ϸ� �ٲ��ֱ�(����...)
	//m_pTerrain->InitTile(vMouse, 0);
	m_pStartTerrain->InitTile(vMouse, 0);

	// Ÿ�ϱ� ��� ������
	//m_pObj->Delete_Obj();
	m_pStartObj->Delete_Obj();

	InvalidateRect(nullptr, FALSE);
	pMiniView->InvalidateRect(nullptr, FALSE);


	CView::OnLButtonDown(nFlags, point);
}
