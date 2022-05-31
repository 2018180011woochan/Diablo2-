#pragma once



// CMyForm 폼 뷰입니다.
#include "UnitTool.h"
#include "MapTool.h"
#include "MonsterTool.h"
#include "ExtractionPath.h"
#include "afxwin.h"
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapTool();

	////////////////////////////이거 만들기////////////////////////
	CButton m_CollidBox;
	afx_msg void OnBnClickedCollidBoxVisible();
	/////////////////////////////////////////////////////////////////
	afx_msg void OnBnClickedUnitToolButton();
	afx_msg void OnBnClickedExtractionPathButton();
	afx_msg void OnBnClickedMonsterToolButton();
};


