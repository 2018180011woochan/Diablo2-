// MyForm.cpp : ���� �����Դϴ�.
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


// CMyForm �����Դϴ�.

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



// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnBnClickedMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tMapTool.GetSafeHwnd())
		m_tMapTool.Create(IDD_MAPTOOL);

	m_tMapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedCollidBoxVisible()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_CollidBox.GetCheck())
		isBoxVisible = true;
	if (!m_CollidBox.GetCheck())
		isBoxVisible = false;
}


void CMyForm::OnBnClickedUnitToolButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tUnitTool.GetSafeHwnd())
		m_tUnitTool.Create(IDD_UNITTOOL);

	m_tUnitTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedExtractionPathButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tExtractionPath.GetSafeHwnd())
		m_tExtractionPath.Create(IDD_EXTRACTIONPATH);

	m_tExtractionPath.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedMonsterToolButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tMonsterTool.GetSafeHwnd())
		m_tMonsterTool.Create(IDD_MONSTERTOOL);

	m_tMonsterTool.ShowWindow(SW_SHOW);
}
