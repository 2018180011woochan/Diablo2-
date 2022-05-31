// MonsterTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"
#include "Diablo_II_MapToolView.h"
#include "Monster.h"
#include "MainFrm.h"

// CMonsterTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialog)

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONSTERTOOL, pParent)
{
	m_iDrawID = 0;
}

CMonsterTool::~CMonsterTool()
{
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_MonsterListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMonsterTool::OnLbnSelchangeMonsterList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CMonsterTool::OnBnClickedSaveMonster)
	ON_BN_CLICKED(IDC_BUTTON3, &CMonsterTool::OnBnClickedLoadMonster)
END_MESSAGE_MAP()


// CMonsterTool 메시지 처리기입니다.


void CMonsterTool::OnLbnSelchangeMonsterList()
{
	UpdateData(TRUE);
	CString strFindName = L"";
	int iIndex = m_MonsterListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	m_MonsterListBox.GetText(iIndex, strFindName);

	int i = 0;
	for (; i < strFindName.GetLength(); ++i)
	{
		if (isdigit(strFindName[i]))
			break;
	}

	strFindName.Delete(0, i);

	m_iDrawID = _wtoi(strFindName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();
	D3DXMATRIX matSacle, matTrans, matWorld;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Monster", L"Sample", m_iDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXMatrixTranslation(&matTrans, float(WINCX >> 1), float(WINCY >> 1), 0.f);
	float fSizeX = WINCX / float(TILECX);
	float fSizeY = WINCY / float(TILECY);
	D3DXMatrixScaling(&matSacle, fSizeX, fSizeY, 0.f);
	matWorld = matSacle * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphic_Device::Get_Instance()->Render_End(m_Picture.GetSafeHwnd());
	UpdateData(FALSE);
}


void CMonsterTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);
	TCHAR szFilePath[MAX_PATH] = L"";
	TCHAR szFileName[MAX_PATH] = L"";
	CString strReletivePath = L"";
	int iSize = DragQueryFile(hDropInfo, -1, nullptr, 0);
	CString strFileNameAndExtant = L"";
	for (int i = 0; i < iSize; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		strReletivePath = CFileInfo::ConvertReletivePath(szFilePath);
		strFileNameAndExtant = PathFindFileName(strReletivePath);
		lstrcpy(szFileName, strFileNameAndExtant.GetString());
		PathRemoveExtension(szFileName);
		m_MonsterListBox.AddString(szFileName);
	}
	//HorizontalScroll();
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}




void CMonsterTool::OnBnClickedSaveMonster()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE,// 모드 지정 -true라면 열기모드, false라면 저장모드
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) |*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		DWORD dwStrByte = 0;
		DWORD dwMonsterByte = 0;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CDiablo_II_MapToolView* pView = dynamic_cast<CDiablo_II_MapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));
		vector<MONSTER*>& vecMonster = pView->m_pMonster->Get_Object();

		for (auto& pObj : vecMonster)
			WriteFile(hFile, pObj, sizeof(MONSTER), &dwMonsterByte, nullptr);

		CloseHandle(hFile);
	}
}


void CMonsterTool::OnBnClickedLoadMonster()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	vector<MONSTER*> vecMonster;

	CMainFrame* pMainPrame = (CMainFrame*)AfxGetMainWnd();
	pMainPrame->GetDiabloMapToolView()->Get_ToolViewMonster()->Release();

	HANDLE hFile = CreateFile(L"../Data/MonsterSaveTest.dat", GENERIC_READ, NULL, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL);

	DWORD dwByte;

	while (true)
	{
		MONSTER* pMonster = new MONSTER;

		ReadFile(hFile, pMonster, sizeof(MONSTER), &dwByte, NULL);

		if (dwByte == NULL)
		{
			Safe_Delete(pMonster);
			break;
		}

		vecMonster.push_back(pMonster);
	}

	//hFile = NULL;
	CloseHandle(hFile);

	pMainPrame->GetDiabloMapToolView()->Get_ToolViewMonster()->Set_Object(vecMonster);

	ERR_MSG(L"Monster Load Success!");

	UpdateData(FALSE);
	Invalidate(TRUE);
}
