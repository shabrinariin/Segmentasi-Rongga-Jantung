
// BismillahSegmentasiDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CBismillahSegmentasiDlg dialog
class CBismillahSegmentasiDlg : public CDialogEx
{
// Construction
public:
	CBismillahSegmentasiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BISMILLAHSEGMENTASI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CWinThread* thread;
	CWinThread* thread1;

	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnEnChangeMfceditbrowse2();
	int modeTampil;
	int openProcess;
	int openProcess1;
	int modeAuto;
	static DWORD ThreadPro(LPVOID *x);
	static DWORD ThreadPro1(LPVOID *x);
	afx_msg void threadProcess();
	afx_msg void threadProcess1();



	afx_msg void OnBnClickedButton2();
	CMFCEditBrowseCtrl m_name;
	CMFCEditBrowseCtrl m_name2;
	CButton m_open;
	CButton m_load;
	CButton m_play;
	
	//CStatic m_pic;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio4();
	CStatic m_area;
	CStatic m_medfil;
	CStatic m_thres;
	CStatic m_segmen;
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	//CStatic m_pic1;
	CStatic m_montec;
	CStatic m_count;
	CStatic m_contour;
	CStatic m_stts;
//	CStatic m_max;
//	CStatic m_min;
	CStatic m_max;
	CStatic m_min;
};
