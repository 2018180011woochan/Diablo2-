
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
class CDiablo_II_MapToolView;
class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	CSplitterWnd m_tMainSplitter;
	CSplitterWnd m_tSecondSplitter;
// 작업입니다.
public:
	CDiablo_II_MapToolView* m_pDiabloMapToolView;

public:
	CDiablo_II_MapToolView* GetDiabloMapToolView() { return m_pDiabloMapToolView; }
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

public:


// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


