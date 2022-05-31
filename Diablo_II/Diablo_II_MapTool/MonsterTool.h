#pragma once
#include "afxwin.h"


// CMonsterTool 대화 상자입니다.

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMonsterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_MonsterListBox;
	afx_msg void OnLbnSelchangeMonsterList();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;

	int m_iDrawID;
	afx_msg void OnBnClickedSaveMonster();
	afx_msg void OnBnClickedLoadMonster();
};
