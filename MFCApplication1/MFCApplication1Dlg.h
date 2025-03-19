// MFCApplication1Dlg.h
#pragma once
#include <mysql.h>

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
public:
    CMFCApplication1Dlg(CWnd* pParent = nullptr);

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    // 구현입니다.
protected:
    HICON m_hIcon;

    // 생성된 메시지 맵 함수
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    void CheckDBConnection();
    MYSQL* ConnectToDatabase();

public:
    CListCtrl m_listHBS;
    afx_msg void OnBnClickedButtonSelect();
    void FetchAndDisplayHBSData();
};