// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Diablo_II_MapTool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "Obj.h"
#include "StartTerrain.h"
#include "StartObj.h"
#include "Diablo_II_MapToolView.h"

// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{
	m_iDrawID = 0;
	m_iObjDrawID = 99;

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox);
	DDX_Control(pDX, IDC_LIST2, m_ObjectListBox);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_CHECK2, &CMapTool::OnBnClickedChangeRedBox)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMapTool::OnLbnSelchangeObjectChange)

	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedInitialze)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedMapObjSaveButton)
	ON_BN_CLICKED(IDC_CHECK3, &CMapTool::OnBnClickedObjSortMode)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::OnBnClickedTileLoadButton)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedMapObjLoadButton)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnDropFiles(HDROP hDropInfo)
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

		//////////////////////////////////////////////저는 타일이랑 오브젝트 이름의 길이가 달라서 이렇게 분류했어요!!////////////////////////////
		if (lstrlen(szFileName) > 6)
			m_ObjectListBox.AddString(szFileName);
		else
			m_ListBox.AddString(szFileName);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
	//HorizontalScroll();
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CMapTool::OnLbnSelchangePicture()
{
	UpdateData(TRUE);
	CString strFindName = L"";
	int iIndex = m_ListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

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
	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_iDrawID);
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Texture", L"ConturyTile", m_iDrawID);
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


void CMapTool::OnLbnSelchangeObjectChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strFindName = L"";
	int iIndex = m_ObjectListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	m_ObjectListBox.GetText(iIndex, strFindName);

	int i = 0;
	for (; i < strFindName.GetLength(); ++i)
	{
		if (isdigit(strFindName[i]))
			break;
	}

	strFindName.Delete(0, i);

	m_iObjDrawID = _wtoi(strFindName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();
	D3DXMATRIX matSacle, matTrans, matWorld;
	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Object", L"Object", m_iObjDrawID);
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Texture", L"struct", m_iObjDrawID);
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





void CMapTool::OnBnClickedChangeRedBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CheckBox.GetCheck())
	{
		isCollidRect = true;
	}
	if (!m_CheckBox.GetCheck())
	{
		isCollidRect = false;
	}
}







void CMapTool::OnBnClickedInitialze()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_iObjDrawID = 99;
	m_iDrawID = 0;
}




void CMapTool::OnBnClickedObjSortMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CheckBox.GetCheck())
	{
		ObjSortMode = true;
	}
	if (!m_CheckBox.GetCheck())
	{
		ObjSortMode = false;
	}
}

void CMapTool::OnBnClickedSaveButton()
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
		DWORD dwTileByte = 0;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CDiablo_II_MapToolView* pView = dynamic_cast<CDiablo_II_MapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTile = pView->m_pStartTerrain->Get_Tile();

		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwTileByte, nullptr);

		CloseHandle(hFile);
	}
}

void CMapTool::OnBnClickedMapObjSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		DWORD dwObjByte = 0;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CDiablo_II_MapToolView* pView = dynamic_cast<CDiablo_II_MapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));
		vector<OBJECT*>& vecObject = pView->m_pStartObj->Get_Object();

		for (auto& pObj : vecObject)
			WriteFile(hFile, pObj, sizeof(OBJECT), &dwObjByte, nullptr);

		CloseHandle(hFile);
	}
}


void CMapTool::OnBnClickedTileLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	vector<TILE*> vecTile;

	CMainFrame* pMainPrame = (CMainFrame*)AfxGetMainWnd();
	pMainPrame->GetDiabloMapToolView()->Get_ToolViewTerrain()->Release();

	HANDLE hFile = CreateFile(L"../Data/SaveTest.dat", GENERIC_READ, NULL, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL);

	//HANDLE hFile = CreateFile(L"../Data/StartTile.dat", GENERIC_READ, NULL, NULL
	//	, OPEN_EXISTING
	//	, FILE_ATTRIBUTE_NORMAL
	//	, NULL);

	DWORD dwByte;

	while (true)
	{
		TILE* pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if (dwByte == NULL)
		{
			Safe_Delete(pTile);
			break;
		}

		vecTile.push_back(pTile);
	}

	//hFile = NULL;
	CloseHandle(hFile);

	//pMainPrame->GetDiabloMapToolView()->Get_ToolViewStartTerrain()->Set_Tile(vecTile);
	pMainPrame->GetDiabloMapToolView()->Get_ToolViewTerrain()->Set_Tile(vecTile);

	ERR_MSG(L"Tile Load Success!");

	UpdateData(FALSE);
	Invalidate(TRUE);
}


void CMapTool::OnBnClickedMapObjLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	vector<OBJECT*> vecMapObj;

	CMainFrame* pMainPrame = (CMainFrame*)AfxGetMainWnd();
	pMainPrame->GetDiabloMapToolView()->Get_ToolViewObj()->Release();

	HANDLE hFile = CreateFile(L"../Data/MapObjSaveTest.dat", GENERIC_READ, NULL, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL);

	//HANDLE hFile = CreateFile(L"../Data/StartObjSave.dat", GENERIC_READ, NULL, NULL
	//	, OPEN_EXISTING
	//	, FILE_ATTRIBUTE_NORMAL
	//	, NULL);

	DWORD dwByte;

	while (true)
	{
		OBJECT* pMapObj = new OBJECT;

		ReadFile(hFile, pMapObj, sizeof(OBJECT), &dwByte, NULL);

		if (dwByte == NULL)
		{
			Safe_Delete(pMapObj);
			break;
		}

		vecMapObj.push_back(pMapObj);
	}

	//hFile = NULL;
	CloseHandle(hFile);

	//pMainPrame->GetDiabloMapToolView()->Get_ToolViewStartObj()->Set_Object(vecMapObj);
	pMainPrame->GetDiabloMapToolView()->Get_ToolViewObj()->Set_Object(vecMapObj);

	ERR_MSG(L"Obj Load Success!");

	UpdateData(FALSE);
	Invalidate(TRUE);
}
