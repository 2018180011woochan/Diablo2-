// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CharListBox);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.
