// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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


// CUnitTool 메시지 처리기입니다.
