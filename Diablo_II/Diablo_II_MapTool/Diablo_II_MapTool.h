
// Diablo_II_MapTool.h : Diablo_II_MapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CDiablo_II_MapToolApp:
// �� Ŭ������ ������ ���ؼ��� Diablo_II_MapTool.cpp�� �����Ͻʽÿ�.
//

class CDiablo_II_MapToolApp : public CWinAppEx
{
public:
	CDiablo_II_MapToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDiablo_II_MapToolApp theApp;
