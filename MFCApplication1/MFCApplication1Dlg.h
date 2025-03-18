#pragma once
#include <mysql.h>  // ✅ MySQL 헤더 추가

class CMFCApplication1Dlg : public CDialogEx
{
public:
    CMFCApplication1Dlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()

public:
    void CheckDBConnection();  // ✅ DB 연결 확인 함수 추가
};
