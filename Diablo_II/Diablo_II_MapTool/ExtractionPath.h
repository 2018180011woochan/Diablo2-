#pragma once
#include "afxwin.h"


// CExtractionPath ��ȭ �����Դϴ�.

class CExtractionPath : public CDialog
{
	DECLARE_DYNAMIC(CExtractionPath)

public:
	CExtractionPath(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CExtractionPath();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRACTIONPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_ListBox;
	list<TEXPATH*> m_listTexPath;
	void HorizontalScroll();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedLoadButton();
};
