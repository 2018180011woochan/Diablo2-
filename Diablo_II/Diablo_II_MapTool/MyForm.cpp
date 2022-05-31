// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_CollidBox);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_CHECK1, &CMyForm::OnBnClickedCollidBoxVisible)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedUnitToolButton)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnBnClickedExtractionPathButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnBnClickedMonsterToolButton)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG



// CMyForm 메시지 처리기입니다.


void CMyForm::OnBnClickedMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tMapTool.GetSafeHwnd())
		m_tMapTool.Create(IDD_MAPTOOL);

	m_tMapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedCollidBoxVisible()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CollidBox.GetCheck())
		isBoxVisible = true;
	if (!m_CollidBox.GetCheck())
		isBoxVisible = false;
}


void CMyForm::OnBnClickedUnitToolButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tUnitTool.GetSafeHwnd())
		m_tUnitTool.Create(IDD_UNITTOOL);

	m_tUnitTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedExtractionPathButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tExtractionPath.GetSafeHwnd())
		m_tExtractionPath.Create(IDD_EXTRACTIONPATH);

	m_tExtractionPath.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedMonsterToolButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tMonsterTool.GetSafeHwnd())
		m_tMonsterTool.Create(IDD_MONSTERTOOL);

	m_tMonsterTool.ShowWindow(SW_SHOW);
}
