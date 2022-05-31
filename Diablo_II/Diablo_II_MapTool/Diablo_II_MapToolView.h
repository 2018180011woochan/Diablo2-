
// Diablo_II_MapToolView.h : CDiablo_II_MapToolView 클래스의 인터페이스
//

#pragma once

class CGraphic_Device;
class CDiablo_II_MapToolDoc;
class CTerrain;
class CObj;
class CMonster;
class CStartTerrain;
class CStartObj;
class CDiablo_II_MapToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CDiablo_II_MapToolView();
	DECLARE_DYNCREATE(CDiablo_II_MapToolView)

// 특성입니다.
public:
	CDiablo_II_MapToolDoc* GetDocument() const;

// 작업입니다.
public:
	CGraphic_Device* m_pGraphic_Device;

	CTerrain* m_pTerrain;
	CObj*	  m_pObj;
	CMonster* m_pMonster;

	CStartTerrain* m_pStartTerrain;
	CStartObj*	   m_pStartObj;
public:
	CTerrain* Get_ToolViewTerrain() { return m_pTerrain; }
	CObj*	  Get_ToolViewObj() { return m_pObj; }

	CStartTerrain* Get_ToolViewStartTerrain() { return m_pStartTerrain; }
	CStartObj*	  Get_ToolViewStartObj() { return m_pStartObj; }

	CMonster* Get_ToolViewMonster() { return m_pMonster; }
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDiablo_II_MapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Diablo_II_MapToolView.cpp의 디버그 버전
inline CDiablo_II_MapToolDoc* CDiablo_II_MapToolView::GetDocument() const
   { return reinterpret_cast<CDiablo_II_MapToolDoc*>(m_pDocument); }
#endif

