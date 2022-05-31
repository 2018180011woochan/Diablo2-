
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
class CDiablo_II_MapToolView;
class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:
	CSplitterWnd m_tMainSplitter;
	CSplitterWnd m_tSecondSplitter;
// �۾��Դϴ�.
public:
	CDiablo_II_MapToolView* m_pDiabloMapToolView;

public:
	CDiablo_II_MapToolView* GetDiabloMapToolView() { return m_pDiabloMapToolView; }
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

public:


// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};

