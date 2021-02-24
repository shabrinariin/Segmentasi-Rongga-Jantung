
// BismillahSegmentasiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BismillahSegmentasi.h"
#include "BismillahSegmentasiDlg.h"
#include "afxdialogex.h"

//inisialisasi
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <math.h>
#include <iomanip>
#define M_PI 3.14
# include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
using namespace std;
using namespace cv;

int tes=0,tis=0;
Mat matframe,src,ln,align, segmen;
vector<Point2f> coor, d0,d1,d2,d3,points[2];
vector<Point> jnt[100], anyar, ac, ay[25], ai,oi,tr[100],alin[25];
FileNode ab[100], ali[25],dt[100];
Point ar, alg, alg1, alg2, alg3, alg4 ;

vector<int> compression_params;
bool pause;
bool bSuccess;
CString txt,teks,teks1,teks2,mc,cnz,ca, status,setmin,setmax;
unsigned int onStart;
bool killThread = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBismillahSegmentasiDlg dialog




CBismillahSegmentasiDlg::CBismillahSegmentasiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBismillahSegmentasiDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	modeTampil =0;
	openProcess =0;
	openProcess1 =0;
	modeAuto =0;

}

void CBismillahSegmentasiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, m_name);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_name2);
	DDX_Control(pDX, IDC_BUTTON1, m_open);
	DDX_Control(pDX, IDC_BUTTON2, m_load);
	DDX_Control(pDX, IDC_BUTTON3, m_play);

	//DDX_Control(pDX, ID_STATIC, m_pic);
	DDX_Control(pDX, IDC_EDIT, m_area);
	DDX_Control(pDX, IDC_EDIT1, m_medfil);
	DDX_Control(pDX, IDC_EDIT2, m_thres);
	DDX_Control(pDX, IDC_EDIT3, m_segmen);
	//DDX_Control(pDX, ID_STATIC, m_pic1);
	DDX_Control(pDX, IDC_EDIT4, m_montec);
	DDX_Control(pDX, IDC_EDIT5, m_count);
	DDX_Control(pDX, IDC_EDIT6, m_contour);
	DDX_Control(pDX, IDC_EDIT7, m_stts);
	//DDX_Control(pDX, IDC_EDIT8, m_max);
	//DDX_Control(pDX, IDC_EDIT9, m_min);
	DDX_Control(pDX, IDC_EDIT8, m_max);
	DDX_Control(pDX, IDC_EDIT9, m_min);
}

BEGIN_MESSAGE_MAP(CBismillahSegmentasiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBismillahSegmentasiDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBismillahSegmentasiDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO4, &CBismillahSegmentasiDlg::OnBnClickedRadio4)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CBismillahSegmentasiDlg::OnEnChangeMfceditbrowse2)
	ON_BN_CLICKED(IDC_BUTTON1, &CBismillahSegmentasiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CBismillahSegmentasiDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CBismillahSegmentasiDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CBismillahSegmentasiDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CBismillahSegmentasiDlg message handlers

BOOL CBismillahSegmentasiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Menampilkan gambar ke Picture Control
	namedWindow("Segmentasi",1);
	HWND h3Wnd = (HWND) cvGetWindowHandle("Segmentasi");
	HWND h3Parent = ::GetParent(h3Wnd);
	::SetParent(h3Wnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(h3Parent,SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBismillahSegmentasiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBismillahSegmentasiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBismillahSegmentasiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD CBismillahSegmentasiDlg::ThreadPro1(LPVOID *lpvParam) //thread
{
	CBismillahSegmentasiDlg *thr = (CBismillahSegmentasiDlg*)lpvParam;
	thr->threadProcess1();
	return NULL;
}


DWORD CBismillahSegmentasiDlg::ThreadPro(LPVOID *lpvParam) //thread
{
	CBismillahSegmentasiDlg *thr = (CBismillahSegmentasiDlg*)lpvParam;
	thr->threadProcess();
	return NULL;
}

int random(int min, int max){
	return rand() % (max-min) + min;
}
int xmin=1000,xmax=0,ymin=1000,ymax=0;

void CBismillahSegmentasiDlg::threadProcess1(void){
	CString filenames;
	CString txt,txt1;
	m_name2.GetWindowTextW(filenames);
	string sufix = ".jpg";
	
	Mat md,th,sg,ln,align;	
		
	std::string name = sufix;
	CT2CA tamp(filenames);
	string result(tamp);

	Mat img = imread(result,1);

	while(!killThread){
		if(modeTampil==0) imshow("Segmentasi",img);

		if(modeTampil==1){
			int64 tm1 = cv::getTickCount();
			medianBlur(img,md,3);
			imshow("Segmentasi",md);
			int64 tm2 = cv::getTickCount();
			double sec = (tm2-tm1)/cv::getTickFrequency();
			teks.Format(_T("%f"),sec);
			m_medfil.SetWindowTextW(teks);
		}
		if(modeTampil==2){
			int64 tm11 = cv::getTickCount();
			//threshold(md,th,42,130,CV_THRESH_BINARY);
			md.convertTo(th,-1,0.75,0);
			imshow("Segmentasi",th);
			int64 tm22 = cv::getTickCount();
			double sec2 = (tm22-tm11)/cv::getTickFrequency();
			teks1.Format(_T("%f"),sec2);
			m_thres.SetWindowTextW(teks1);
		}
		if(modeTampil==3){
			int64 tm111 = cv::getTickCount();
			Point pt;
			FileStorage sv0("nea0.txt", cv::FileStorage::READ);
			FileStorage sv1("neb0.txt", cv::FileStorage::READ);
			FileStorage sv2("nec0.txt", cv::FileStorage::READ);
			FileStorage sv3("ned0.txt", cv::FileStorage::READ);
			FileStorage sv4("nee0.txt", cv::FileStorage::READ);
			dt[0] = sv0["Point"];
			dt[1] = sv1["Point"];
			dt[2] = sv2["Point"];
			dt[3] = sv3["Point"];
			dt[4] = sv4["Point"];

			//==========read dat ================
			FileStorage savi0("align.txt", cv::FileStorage::READ);
			FileStorage savi1("align1.txt", cv::FileStorage::READ);
			FileStorage savi2("align2.txt", cv::FileStorage::READ);
			FileStorage savi3("align3.txt", cv::FileStorage::READ);
			FileStorage savi4("align4.txt", cv::FileStorage::READ);
			ali[0] = savi0["Point"];
			ali[1] = savi1["Point"];
			ali[2] = savi2["Point"];
			ali[3] = savi3["Point"];
			ali[4] = savi4["Point"];

	
			th.copyTo(ln);
			th.copyTo(align);

			for(int b=0; b<5; b++){
				read(dt[b], tr[b]);
				polylines(ln, tr[b],false,Scalar(255,255,0),2,150,0);
			}
			//imshow("Segmentasi",ln);
		//=================ALIGNMENT================
			double s60 = sin(10*M_PI /180.0);
			double c60 = cos(10*M_PI /180.0);
			int d=1;
				for (int d=1; d<5; d++){
					for(int aa=0; aa<tr[0].size(); aa++){
						alg = tr[0].at(aa); //ref
						alg1 = tr[d].at(aa);
						alg1.x = c60 * (alg.x - alg1.x) - s60 * (alg.y - alg1.y) + alg1.x;
						alg1.y =  s60 * (alg.x - alg1.x) + c60 * (alg.y - alg1.y) + alg1.y;
						ay[0].push_back(alg);
						ay[d].push_back(alg1);
						polylines(ln, ay[0], false, Scalar(0,0,255),1,8);
						polylines(ln, ay[d], false, Scalar(0,0,255),1,8);
					}
				}
			//=============read me
			for(int b=0; b<5; b++){
				read(ali[b], alin[b]);
			}

			cout<<"\n\n============Mean Shape============\n";
			Mat total; Point mn;
			total =  Mat(alin[1])+Mat(alin[2])+Mat(alin[3])+Mat(alin[0])+Mat(alin[4]);
			Mat rata = total/5;
			cout << rata << endl;
			
			cout<<"\n\n==========Standard Deviasi==========";
			Mat dev[5];
			dev[0] = Mat(tr[0])-rata;
			for (int a=1;a<5;a++){
				dev[a] = Mat(alin[a])-rata;
			}
			for(int b=0; b<5;b++){
				printf("\n\n Dev%d\n",b);
				cout<<dev[b];
				dev[b].convertTo(dev[b],CV_32F);
			}
			cout<<"\n\n============Covariance Matrix============";
			
			Mat test[10], tf[10], cov, covrata, coba;
			for(int ca=0; ca<5; ca++){
				test[ca] = dev[ca].reshape(0,5);
				
				test[ca].convertTo(test[ca], CV_32F);
				tf[ca] = test[ca].t();
				cov = cov + (test[ca].mul(tf[ca]));
				covrata = cov / (ca);
			}
			
			cout << "\nCovariance Result \n"<< covrata << endl;

			cout << "\n==============Eigenv=============" << endl;
			Mat eig = covrata.reshape(0,1);
			Mat egnvecx = Mat(5,5,CV_32F);
			Mat egnvalx = Mat(5,1,CV_32F);
			Mat egnvecy = Mat(5,5,CV_32F);
			Mat egnvaly = Mat(5,1,CV_32F);
			vector<Point2f> pc;
			Mat eig_x, eig_y, ex, ey;
			Point2f egn;
			eig.copyTo(pc);
			for(int d=0; d<pc.size(); d++){
				egn = pc.at(d);
				eig_x.push_back(egn.x);
				eig_y.push_back(egn.y);
			}
			ex = eig_x.reshape(0,5);
			ey = eig_y.reshape(0,5);
			eigen(ex,egnvalx,egnvecx);
			eigen(ey,egnvaly,egnvecy);

			Mat eigen_vector = Mat(5,5, CV_32F), eigen_val=Mat(5,1, CV_32F);
			Mat ch[2] = {egnvecx,egnvecy}, mr[2] = {egnvalx,egnvaly};
			merge(ch,2,eigen_vector);
			merge(mr,2,eigen_val);
   
			cout<< eigen_vector;
			cout <<"\n\n========= Eigen Value=========\n"<< "\n"<<
			eigen_val;


			//======================FITTING======================//
			Mat Qnew, yminq, evecs,etranss,b_barss, q_new,qbarus, inputs, y_bars;
			Mat nyars,q_bars, fit;
			Point t0,t1;
			vector<Point2f> t2, pointz1,t,lagi;
			vector<Point> tot;

			FileStorage sv5("mall.txt", cv::FileStorage::READ);
			FileStorage sv6("evecall.txt", cv::FileStorage::READ);
			FileStorage sv7("nea0.txt", cv::FileStorage::READ);
			FileStorage sv8("neb0.txt", cv::FileStorage::READ);
			FileStorage sv9("nec0.txt", cv::FileStorage::READ);
			FileStorage sv10("ned1.txt", cv::FileStorage::READ);
			FileStorage sv11("nee0.txt", cv::FileStorage::READ);
			dt[0] = sv5["Point"];
			dt[1] = sv6["Point"];
			dt[2] = sv7["Point"];
			dt[3] = sv8["Point"];
			dt[4] = sv9["Point"];
			dt[5] = sv10["Point"];
			dt[6] = sv11["Point"];
			
			read(dt[0],pointz1);
			read(dt[1],evecs);
			read(dt[2],tr[5]);
			read(dt[3],tr[6]);
			read(dt[4],tr[7]);
			read(dt[5],tr[8]);
			read(dt[6],tr[9]);

			for (int sn=0; sn<2; sn++){
				th.copyTo(fit);
				for(int as=0; as<tr[5].size(); as++){
					t1 = pointz1.at(as);
					t0 = tr[5].at(as); //ref
					t1.x = c60 * (t0.x - t1.x) - s60 * (t0.y - t1.y) + t1.x;
					t1.y =  s60 * (t0.x - t1.x) + c60 * (t0.y - t1.y) + t1.y;
					t.push_back(t1);
				}
				t2=t;
				t.clear();
				etranss = evecs.t();
				Qnew = Mat (t2).reshape(0,5);
				yminq = Qnew - q_bars;
				b_barss = etranss.mul(yminq);
				q_new = q_bars +( b_barss.mul(evecs));
				qbarus = q_new.reshape(0,1);
				y_bars = qbarus;
				pointz1 = t2;
				q_bars = Mat(t2).reshape(0,5);
		
			}
			for(int ao=0; ao<t2.size(); ao++){
				Point pt = t2.at(ao);
				tot.push_back(t2.at(ao));
			}
			cvtColor(fit, fit, COLOR_BGR2GRAY);
			//polylines(fit,tot,false,Scalar(255,255,255),2,150,0);
			fillConvexPoly(fit,tot,Scalar(255,255,255),1,0);
			threshold(fit,fit,254,255,CV_THRESH_BINARY);
			int coba11 = cv::countNonZero(fit);
			cnz.Format(_T("%d"),coba11);
			m_count.SetWindowTextW(cnz);

			imshow("Segmentasi",fit);
			
			//=====================MONTE CARLO=======================
			CvPoint2D32f pt2;
			double ri2,nd2=0,nt2=0,out2;
			int A2,x2,y2;
			int jumRandom2=10000;
			vector<vector<Point> > contours2;
			vector<Vec4i> hierarchy2;
			CvSeq *c2=NULL;
	
			findContours( fit, contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
			for(unsigned int i=0;i<contours2.size();i++)
			{
				for(unsigned int j=0;j<contours2[i].size();j++)
				{
					if(xmin < contours2[i][j].x) {	xmin = xmin; } else { xmin = contours2[i][j].x; }
					if(xmax > contours2[i][j].x) {	xmax = xmax; } else { xmax = contours2[i][j].x; }
					if(ymin < contours2[i][j].y) {	ymin = ymin; } else { ymin = contours2[i][j].y; }
					if(ymax > contours2[i][j].y) {	ymax = ymax; } else { ymax = contours2[i][j].y; }
				}

			}
			printf("Xmin =%d xmax = %d ymin = %d ymax = %d",xmin,xmax,ymin,ymax);
				  vector<Moments> mu(contours2.size() );
				  for( size_t i = 0; i < contours2.size(); i++ )
					 { mu[i] = moments( contours2[i], false ); }

				   /// Draw contours
				  Mat drawing = Mat::zeros( fit.size(), CV_8UC3 );
  
				  for( int i = 0; i< contours2.size(); i++ )
					 {	
							Scalar color = Scalar(255,255,255);
							drawContours( drawing, contours2, i, color, 1, 8, hierarchy2, 0, Point() );
							ca.Format(_T("%g"),contourArea(contours2[0]));
							m_contour.SetWindowTextW(ca);
					 }

				  for(int a=0; a<jumRandom2;a++){
						x2=random(xmin,xmax);
						y2=random(ymin,ymax);
						pt.x = (float)x2; pt.y= (float)y2;
						circle(drawing,pt,1,Scalar(255,255,255),1,1,0);
						out2 = pointPolygonTest(contours2[0],pt,0);
						if(out2>=0.0){
							nd2++;
						}
						nt2++;
					}
					rectangle(drawing,Point(xmin,ymin),Point(xmax,ymax),Scalar(255,255,255),1,1,0);
					A2 = (int)(nd2/nt2*(xmax-xmin)*(ymax-ymin));
					mc.Format(_T("%d"),A2);
					m_montec.SetWindowTextW(mc);
				
	
				   contours2[0].clear();
				   xmin=1000;xmax=0;ymin=1000;ymax=0;

			int64 tm222 = cv::getTickCount();
			double sec1 = (tm222-tm111)/cv::getTickFrequency();
			teks2.Format(_T("%.3f"),sec1);
			m_segmen.SetWindowTextW(teks2);

			waitKey(0);


		}
	}


}
/*int random(int min, int max){
	return rand() % (max-min) + min;
}
int xmin=1000,xmax=0,ymin=1000,ymax=0;*/
int modeChange=0;
int amin=1000, amax=0;
void CBismillahSegmentasiDlg::threadProcess(void){
	killThread= true;
	int count=0,countframe=0,flag=0;
	CString filename;
	m_name.GetWindowTextW(filename);
	string sufix = ".avi";
	
	std::string name = sufix;
		CT2CA tamp(filename);
		string result(tamp);

	VideoCapture cap(result);
	cap>>matframe;
	if(!cap.isOpened())
	{
		cout<<"FAILED"<<endl;
	}
	modeChange=0;
	while(1){

		if(pause) 
		{
			bSuccess=cap.read(matframe); 
			countframe++;
			tis=0;modeChange = 1;
		}
		if(!bSuccess)
		{
			cout << "Cannot read the frame from video file" <<endl;				
		}

		if(modeChange == 0) {
			matframe.copyTo(src);
			imshow("Segmentasi",src);
		} 

		if( modeChange == 1) {
		
			matframe.copyTo(src);
			medianBlur(src,src,3);
			src.convertTo(src,-1,0.75,0);
			//threshold(src,src,42,130,CV_THRESH_BINARY);
			cvtColor(src, src, COLOR_BGR2GRAY);

		src.copyTo(align);
		
		if (tes){
			int64 tm1 = cv::getTickCount();
			Mat rata, Qnew, yminq, evec,etrans,b_bar, q_new,qbaru, input, y_bar;
			Mat image, q_bar;
			Point t0,t1;
			vector<Point2f> t2, pointz,t;
			vector<Point> tot;
			
			double s60 = sin(10*M_PI /180.0);
			double c60 = cos(10*M_PI /180.0);
			
			FileStorage smp0("mall.txt", cv::FileStorage::READ);
			FileStorage smp1("evecall.txt", cv::FileStorage::READ);
			FileStorage smp2("nee0.txt", cv::FileStorage::READ);
			FileStorage smp3("nee1.txt", cv::FileStorage::READ);
			FileStorage smp4("nee2.txt", cv::FileStorage::READ);
			FileStorage smp5("nee3.txt", cv::FileStorage::READ);
			FileStorage smp6("nee4.txt", cv::FileStorage::READ);
			FileStorage smp7("nee5.txt", cv::FileStorage::READ);
			FileStorage smp8("nee6.txt", cv::FileStorage::READ);
			FileStorage smp9("nee7.txt", cv::FileStorage::READ);
			FileStorage smp10("nee8.txt", cv::FileStorage::READ);
			FileStorage smp11("nee9.txt", cv::FileStorage::READ);
			FileStorage smp12("nee10.txt", cv::FileStorage::READ);
			FileStorage smp13("nee11.txt", cv::FileStorage::READ);
			FileStorage smp14("nee12.txt", cv::FileStorage::READ);
			FileStorage smp15("nee13.txt", cv::FileStorage::READ);
			FileStorage smp16("nee14.txt", cv::FileStorage::READ);
			FileStorage smp17("nee15.txt", cv::FileStorage::READ);
			FileStorage smp18("nee16.txt", cv::FileStorage::READ);
			FileStorage smp19("nee17.txt", cv::FileStorage::READ);
			FileStorage smp20("nee18.txt", cv::FileStorage::READ);
			FileStorage smp21("nee19.txt", cv::FileStorage::READ);
			ab[0] = smp0["Point"];
			ab[1] = smp1["Point"];
			ab[2] = smp2["Point"];
			ab[3] = smp3["Point"];
			ab[4] = smp4["Point"];
			ab[5] = smp5["Point"];
			ab[6] = smp6["Point"];
			ab[7] = smp7["Point"];
			ab[8] = smp8["Point"];
			ab[9] = smp9["Point"];
			ab[10] = smp10["Point"];
			ab[11] = smp11["Point"];
			ab[12] = smp12["Point"];
			ab[13] = smp13["Point"];
			ab[14] = smp14["Point"];
			ab[15] = smp15["Point"];
			ab[16] = smp16["Point"];
			ab[17] = smp17["Point"];
			ab[18] = smp18["Point"];
			ab[19] = smp19["Point"];
			ab[20] = smp20["Point"];
			ab[21] = smp21["Point"];
			read(ab[0],pointz);
			read(ab[1],evec);
			read(ab[2],jnt[0]);
			read(ab[3],jnt[1]);
			read(ab[4],jnt[2]);
			read(ab[5],jnt[3]);
			read(ab[6],jnt[4]);
			read(ab[7],jnt[5]);
			read(ab[8],jnt[6]);
			read(ab[9],jnt[7]);
			read(ab[10],jnt[8]);
			read(ab[11],jnt[9]);
			read(ab[12],jnt[10]);
			read(ab[13],jnt[11]);
			read(ab[14],jnt[12]);
			read(ab[15],jnt[13]);
			read(ab[16],jnt[14]);
			read(ab[17],jnt[15]);
			read(ab[18],jnt[16]);
			read(ab[19],jnt[17]);
			read(ab[20],jnt[18]);
			read(ab[21],jnt[19]);

	
			for (int sn=0; sn<2; sn++){
				align.copyTo(image);
				for(int an=0; an<jnt[0].size(); an++){
					t1 = pointz.at(an);
					t0 = jnt[count].at(an); //ref
					t1.x = c60 * (t0.x - t1.x) - s60 * (t0.y - t1.y) + t1.x;
					t1.y =  s60 * (t0.x - t1.x) + c60 * (t0.y - t1.y) + t1.y;
					t.push_back(t1);
				}
					t2=t;
					t.clear();
					etrans = evec.t();
					Qnew = Mat (t2).reshape(0,5);
					yminq = Qnew - q_bar;
					b_bar = etrans.mul(yminq);
					q_new = q_bar + (b_bar.mul(evec));
					qbaru = q_new.reshape(0,1);
					y_bar = qbaru;
					pointz = t2;
					q_bar = Mat(t2).reshape(0,5);
		
				}
				for(int ao=0; ao<t2.size(); ao++){
					Point pt = t2.at(ao);
					circle(image,pt,2,Scalar(0,0,255),2);
					tot.push_back(t2.at(ao));
				}
				polylines(image,tot,false,Scalar(255,255,255),2,150,0);
				image.copyTo(src);
				imshow("Segmentasi",src);
				threshold(image,image,254,255,CV_THRESH_BINARY);
				waitKey(100);

	//====================NGITUNG LUAS=======================//
				CvPoint2D32f pt;
	double ri,nd=0,nt=0,out;
	int A[100],x,y;
	int jumRandom=10000;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	CvSeq *c=NULL;
	
	findContours( image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	for(unsigned int i=0;i<contours.size();i++)
	{
		for(unsigned int j=0;j<contours[i].size();j++)
		{
			if(xmin < contours[i][j].x) {	xmin = xmin; } else { xmin = contours[i][j].x; }
			if(xmax > contours[i][j].x) {	xmax = xmax; } else { xmax = contours[i][j].x; }
			if(ymin < contours[i][j].y) {	ymin = ymin; } else { ymin = contours[i][j].y; }
			if(ymax > contours[i][j].y) {	ymax = ymax; } else { ymax = contours[i][j].y; }
		}

	}
	printf("Xmin =%d xmax = %d ymin = %d ymax = %d",xmin,xmax,ymin,ymax);
		  vector<Moments> mu(contours.size() );
		  for( size_t i = 0; i < contours.size(); i++ )
			 { mu[i] = moments( contours[i], false ); }

		   /// Draw contours
		  Mat drawing = Mat::zeros( src.size(), CV_8UC3 );
  
		  for( int i = 0; i< contours.size(); i++ )
			 {	
					Scalar color = Scalar(255,255,255);
					drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
			 }

		  for(int a=0; a<500;a++){
				x=random(xmin,xmax);
				y=random(ymin,ymax);
				pt.x = (float)x; pt.y= (float)y;
				circle(drawing,pt,1,Scalar(255,255,255),1,1,0);
				out = pointPolygonTest(contours[0],pt,0);
				if(out>=0.0){
					nd++;
				}
				nt++;
			}
			rectangle(drawing,Point(xmin,ymin),Point(xmax,ymax),Scalar(255,255,255),1,1,0);
			A[count] = (int)(nd/nt*(xmax-xmin)*(ymax-ymin)) * 0.264583333333334;
			txt.Format(_T("%d"),A[count]);
			m_area.SetWindowTextW(txt);
	
		   contours[0].clear();
		   xmin=1000;xmax=0;ymin=1000;ymax=0;
		
		   //=================================================================================

				int64 tm2 = cv::getTickCount();
				double sec = (tm2-tm1)/cv::getTickFrequency();
				teks.Format(_T("%g"),sec);
//				m_process.SetWindowTextW(teks);

				if(amin < A[count]) {	amin = amin; } else { amin = A[count]; }
				if(amax > A[count]) {	amax = amax; } else { amax = A[count]; }

				if(pause==false)count=count;		
				if(pause==true)count++;

				if(count==20) {
				setmax.Format(_T("%d"),amax);
				m_max.SetWindowTextW(setmax);
				setmin.Format(_T("%d"),amin);
				m_min.SetWindowTextW(setmin);
					if(1450<amax && amax<1480){
						if(450<amin && amin<475){
							status.Format(_T("Normal"));
							m_stts.SetWindowTextW(status);
						}
						else {
							status.Format(_T("Abnormal"));
							m_stts.SetWindowTextW(status);
						}
					}
					else 
					{
						status.Format(_T("Abnormal"));
						m_stts.SetWindowTextW(status);	
					}
				AfxMessageBox(L"Out Of Frame");
				return;
				}
		}
		}
		waitKey(1000);
	}
	

}



void CBismillahSegmentasiDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if(!openProcess){
		thread = AfxBeginThread((AFX_THREADPROC) CBismillahSegmentasiDlg::ThreadPro, (LPVOID) this);
		openProcess = 1;

	}else{
		AfxMessageBox(L"Wait or close, up to you!");

		return;
	}
}


void CBismillahSegmentasiDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	if(!onStart){
		m_play.SetWindowTextW(_T("Play"));
		pause=false;
	}
	else {
		m_play.SetWindowTextW(_T("Stop"));
		pause = true;
	}

	onStart ^=1;
}


void CBismillahSegmentasiDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	tes=1;
	tis=1;
	modeChange =1;
}


void CBismillahSegmentasiDlg::OnEnChangeMfceditbrowse2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CBismillahSegmentasiDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if(!openProcess1){
		thread1 = AfxBeginThread((AFX_THREADPROC) CBismillahSegmentasiDlg::ThreadPro1, (LPVOID) this);
		openProcess1 = 1;
	}else{
		AfxMessageBox(L"Wait or close, up to you!");
		return;
	}
}


void CBismillahSegmentasiDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	modeTampil=1;
}


void CBismillahSegmentasiDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	modeTampil=2;
}


void CBismillahSegmentasiDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	modeTampil=3;
}
