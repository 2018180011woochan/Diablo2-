#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	int m_iDrawID;
	afx_msg void OnLbnSelchangePicture();
	CStatic m_Picture;
	// 저장 불러오기 //////////////////////
	afx_msg void OnBnClickedSaveButton();
	///////////////////////////////////////

	/////////////// 이거 만들기 ////////////////
	CButton m_CheckBox;
	afx_msg void OnBnClickedChangeRedBox();
	////////////////////////////////////////////
	CListBox m_ObjectListBox;
	afx_msg void OnLbnSelchangeObjectChange();
	int m_iObjDrawID;

	afx_msg void OnBnClickedInitialze();
	afx_msg void OnBnClickedMapObjSaveButton();
	afx_msg void OnBnClickedObjSortMode();
	afx_msg void OnBnClickedTileLoadButton();
	afx_msg void OnBnClickedMapObjLoadButton();
};
