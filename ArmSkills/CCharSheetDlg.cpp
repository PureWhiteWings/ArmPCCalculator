/*
Copyright (c) 2018 RunnerScrab

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pch.h"
#include "resource.h"
#include <vector>

#include <atlconv.h>

#include "CCharSheetDlg.h"
#include "afxdialogex.h"

#include "Character.h"

// CCharSheetDlg dialog

IMPLEMENT_DYNAMIC(CCharSheetDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CCharSheetDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_GUILD_COMBO, &CCharSheetDlg::OnCbnSelchangeGuildCombo)
	ON_CBN_SELCHANGE(IDC_SUBGUILD_COMBO, &CCharSheetDlg::OnCbnSelchangeSubguildCombo)
END_MESSAGE_MAP()

CCharSheetDlg::CCharSheetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARSHEET_DIALOG, pParent)
{
	try
	{
		m_spSkillsDB = std::make_unique<SkillsDB>();
	}
	catch (std::exception ex)
	{
		::MessageBoxA(GetSafeHwnd(), ex.what(), "Error", MB_ICONERROR);
		::ExitProcess(0);
	}
}

CCharSheetDlg::~CCharSheetDlg()
{
}

void CCharSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BOOL CCharSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);

	m_pGuildCombobox = static_cast<CComboBox*>(GetDlgItem(IDC_GUILD_COMBO));
	m_pSubguildCombobox = static_cast<CComboBox*>(GetDlgItem(IDC_SUBGUILD_COMBO));
	m_pEdit = static_cast<CEdit*>(GetDlgItem(IDC_TEXTEDIT));

	memset(&lfLogFont, 0, sizeof(lfLogFont));

	lfLogFont.lfHeight = 16;
	lfLogFont.lfWeight = FW_NORMAL;
	lfLogFont.lfUnderline = FALSE;

	wcscpy_s(lfLogFont.lfFaceName, 32, L"Courier New");

	m_editfont.CreateFontIndirect(&lfLogFont);

	m_pEdit->SetFont(&m_editfont);

	const auto& rClassMap = m_spSkillsDB->GetClassMap();
	for (auto& clpair : rClassMap)
	{
		if (!clpair.second.IsSubclass())
		{
			m_pGuildCombobox->AddString(CA2T(clpair.first.c_str()));
		}
		else
		{
			m_pSubguildCombobox->AddString(CA2T(clpair.first.c_str()));
		}
	}

	return TRUE;
}

void CCharSheetDlg::UpdateTextEdit()
{
	CString guildstr;
	if (CB_ERR != m_pGuildCombobox->GetCurSel())
		m_pGuildCombobox->GetLBText(m_pGuildCombobox->GetCurSel(), guildstr);

	CString subguildstr;
	if (CB_ERR != m_pSubguildCombobox->GetCurSel())
		m_pSubguildCombobox->GetLBText(m_pSubguildCombobox->GetCurSel(), subguildstr);

	std::shared_ptr<Character> pChar = m_spSkillsDB->CreateCharacter(CT2A(guildstr.GetString()), CT2A(subguildstr.GetString()));
	if (pChar)
	{
		std::string report = pChar->GetCombinedReport();
		std::vector<wchar_t> wreport;
		wreport.resize(report.size() + 1, 0);
		::MultiByteToWideChar(CP_UTF8, 0, report.c_str(), report.length(),
			&wreport[0], wreport.size());

		m_pEdit->SetWindowTextW(&wreport[0]);
	}
}

void CCharSheetDlg::OnCbnSelchangeGuildCombo()
{
	UpdateTextEdit();
}


void CCharSheetDlg::OnCbnSelchangeSubguildCombo()
{
	UpdateTextEdit();
}
