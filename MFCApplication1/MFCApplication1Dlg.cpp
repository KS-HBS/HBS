// MFCApplication1Dlg.cpp: 구현 파일
#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <mysql.h>  // MySQL 헤더 추가

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();
    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 지원입니다.
    // 구현입니다.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplication1Dlg 대화 상자
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    // List Control과 연결
    DDX_Control(pDX, IDC_LIST_HBS, m_listHBS);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_SELECT, &CMFCApplication1Dlg::OnBnClickedButtonSelect)
END_MESSAGE_MAP()

// DB 연결 확인 함수
void CMFCApplication1Dlg::CheckDBConnection()
{
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        AfxMessageBox(_T("❌ MySQL 초기화 실패!"));
        return;
    }
    // MySQL 연결 시도
    if (!mysql_real_connect(conn, "127.0.0.1", "root", "infonet", "hbs", 3306, NULL, 0)) {
        CString errMsg;
        errMsg.Format(_T("❌ MySQL 연결 실패: %S"), mysql_error(conn));
        AfxMessageBox(errMsg);
        mysql_close(conn);
        return;
    }
    AfxMessageBox(_T("✅ DB 연결 성공!"), MB_ICONEXCLAMATION | MB_OK);  // 연결 성공 메시지
    mysql_close(conn);
}

// 데이터베이스 연결 함수
MYSQL* CMFCApplication1Dlg::ConnectToDatabase()
{
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        AfxMessageBox(_T("❌ MySQL 초기화 실패!"));
        return NULL;
    }

    // MySQL 연결 시도
    if (!mysql_real_connect(conn, "127.0.0.1", "root", "infonet", "hbs", 3306, NULL, 0)) {
        CString errMsg;
        errMsg.Format(_T("❌ MySQL 연결 실패: %S"), mysql_error(conn));
        AfxMessageBox(errMsg);
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

// CMFCApplication1Dlg 메시지 처리기
BOOL CMFCApplication1Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 시스템 메뉴에 "정보..." 메뉴 항목 추가
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 이 대화 상자의 아이콘을 설정합니다.
    SetIcon(m_hIcon, TRUE);   // 큰 아이콘 설정
    SetIcon(m_hIcon, FALSE);  // 작은 아이콘 설정

    // 프로그램 실행 시 DB 연결 확인
    CheckDBConnection();

    // List Control 초기화
    m_listHBS.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // 필요한 만큼 열 추가 (hbs 데이터베이스의 테이블 구조에 따라 수정 필요)
    m_listHBS.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
    m_listHBS.InsertColumn(1, _T("이름"), LVCFMT_LEFT, 100);
    m_listHBS.InsertColumn(2, _T("정보"), LVCFMT_LEFT, 150);
    // 필요에 따라 더 많은 열 추가 가능

    return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 대화 상자에 최소화 버튼을 추가할 경우 아이콘을 그리려면
void CMFCApplication1Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 클라이언트 사각형에서 아이콘을 가운데에 맞춤
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 아이콘을 그림
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// 사용자가 최소화된 창을 끌 때 커서가 표시되도록 시스템에서 이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// 조회 버튼 클릭 이벤트 처리
void CMFCApplication1Dlg::OnBnClickedButtonSelect()
{
    FetchAndDisplayHBSData();
}

// HBS 데이터 조회 및 표시 함수
void CMFCApplication1Dlg::FetchAndDisplayHBSData()
{
    // 기존 데이터 삭제
    m_listHBS.DeleteAllItems();

    // DB 연결
    MYSQL* conn = ConnectToDatabase();
    if (conn == NULL) {
        return;
    }

    // 쿼리 실행
    const char* query = "SELECT * FROM hbs";
    if (mysql_query(conn, query)) {
        CString errMsg;
        errMsg.Format(_T("❌ 쿼리 실행 실패: %S"), mysql_error(conn));
        AfxMessageBox(errMsg);
        mysql_close(conn);
        return;
    }

    // 결과 가져오기
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        CString errMsg;
        errMsg.Format(_T("❌ 결과 가져오기 실패: %S"), mysql_error(conn));
        AfxMessageBox(errMsg);
        mysql_close(conn);
        return;
    }

    // 필드 수 확인
    int numFields = mysql_num_fields(result);
    CString fieldInfo;
    fieldInfo.Format(_T("조회된 필드 수: %d"), numFields);
    AfxMessageBox(fieldInfo);

    // 결과 처리
    MYSQL_ROW row;
    int nItem = 0;

    // 모든 컬럼 삭제
    while (m_listHBS.DeleteColumn(0)) {}

    // 새 컬럼 추가
    MYSQL_FIELD* fields = mysql_fetch_fields(result);
    for (int i = 0; i < numFields; i++) {
        CString colName(fields[i].name);
        m_listHBS.InsertColumn(i, colName, LVCFMT_LEFT, 100);
    }

    // 데이터 표시
    while ((row = mysql_fetch_row(result))) {
        // ID 컬럼 삽입
        int newItem = m_listHBS.InsertItem(nItem, row[0] ? CString(row[0]) : _T("NULL"));

        // 나머지 컬럼 삽입
        for (int i = 1; i < numFields; i++) {
            m_listHBS.SetItemText(newItem, i, row[i] ? CString(row[i]) : _T("NULL"));
        }

        nItem++;
    }

    // 열 너비 자동 조정
    for (int i = 0; i < numFields; i++) {
        m_listHBS.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    // 결과 및 연결 해제
    mysql_free_result(result);
    mysql_close(conn);
}