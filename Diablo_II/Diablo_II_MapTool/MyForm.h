#pragma once



// CMyForm �� ���Դϴ�.
#include "UnitTool.h"
#include "MapTool.h"
#include "MonsterTool.h"
#include "ExtractionPath.h"
#include "afxwin.h"
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CUnitTool			m_tUnitTool;
	CMapTool			m_tMapTool;
	CMonsterTool		m_tMonsterTool;
	CExtractionPath		m_tExtractionPath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapTool();

	////////////////////////////�̰� �����////////////////////////
	CButton m_CollidBox;
	afx_msg void OnBnClickedCollidBoxVisible();
	/////////////////////////////////////////////////////////////////
	afx_msg void OnBnClickedUnitToolButton();
	afx_msg void OnBnClickedExtractionPathButton();
	afx_msg void OnBnClickedMonsterToolButton();
};


