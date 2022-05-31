#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	int m_iDrawID;
	afx_msg void OnLbnSelchangePicture();
	CStatic m_Picture;
	// ���� �ҷ����� //////////////////////
	afx_msg void OnBnClickedSaveButton();
	///////////////////////////////////////

	/////////////// �̰� ����� ////////////////
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
