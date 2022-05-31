#pragma once
#include "afxwin.h"


// CMonsterTool ��ȭ �����Դϴ�.

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonsterTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
