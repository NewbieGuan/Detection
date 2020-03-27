// ModifyPara.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ModifyPara.h"
#include "afxdialogex.h"
#include<fstream>
using namespace std;

// CModifyPara 对话框

IMPLEMENT_DYNAMIC(CModifyPara, CDialogEx)

CModifyPara::CModifyPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MODIFY_PARA, pParent)
	//3.28夜 删掉这一行
	, m_sGrayThreshold(_T(""))
{

	//3.28下午  
	m_sResolution = _T("5.378");
	m_sDelayTime = _T("0");
	m_sPulseEquivalent = _T("1000");
	m_sThreshold = _T("100");

	m_sSampleCountStrip = _T("2");

	//4.10新加
	m_sGrayThreshold = _T("36");
}

CModifyPara::~CModifyPara()
{
}

void CModifyPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION, m_sResolution);
	DDX_Text(pDX, IDC_EDIT_MODIFY_MOTION_PARA_DELAY, m_sDelayTime);
	DDX_Text(pDX, IDC_EDIT_MODIFY_MOTION_PARA_PULSE, m_sPulseEquivalent);
	DDX_Control(pDX, IDC_STATIC_TIP, m_cTip);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD, m_sThreshold);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP, m_sSampleCountStrip);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD, m_sGrayThreshold);
}


BEGIN_MESSAGE_MAP(CModifyPara, CDialogEx)
	ON_BN_CLICKED(ID_BTN_MODIFY_PARA_OK, &CModifyPara::OnBnClickedBtnModifyParaOk)
	ON_BN_CLICKED(IDD_BTN_MODIFY_PARA_CANCEAL, &CModifyPara::OnBnClickedBtnModifyParaCanceal)
	ON_BN_CLICKED(ID_BTN_MODIFY_PARA_APPLY, &CModifyPara::OnBnClickedBtnModifyParaApply)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



BOOL CModifyPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	// *******************【获取初始化系统参数】***********************
	GetIniSystemPara();

	//4.1修改
	
	ofstream outfile("testFile1.txt", ios::app);

	int m_steps_mm = (int)_ttof(m_sPulseEquivalent);
	double m_delayTime = (int)_ttof(m_sDelayTime);
	double m_resolution = (double)_ttof(m_sResolution);
	int m_threshold = (double)_ttof(m_sThreshold);
	int sampleCountStrip = (int)_ttof(m_sSampleCountStrip);
	//4.10新加
	int graythreshold = (int)_ttof(m_sGrayThreshold);


	outfile << m_steps_mm << endl;
	outfile << m_delayTime << endl;
	outfile << m_resolution << endl;
	outfile << m_threshold << endl;
	outfile << sampleCountStrip << endl << endl;
	//4.10
	outfile << graythreshold << endl << endl;



	//CFont* pFont;
	//pFont = m_cTip.GetFont();//获取CFont对象
	//LOGFONT lf;
	//pFont->GetLogFont(&lf);//获取LOGFONT结构体
	//lf.lfHeight = 20;    //修改字体大小
	//lf.lfItalic = FALSE;        //倾斜
	//lf.lfWeight = 560;   //修改字体的粗细
	//
	//m_font.CreateFontIndirectW(&lf);//创建一个新的字体
	//m_cTip.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



// CModifyPara 消息处理程序


HBRUSH CModifyPara::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
	{
		pDC->SetTextColor(RGB(255, 0, 0));  // 设置文本颜色为红色
		pDC->SetBkMode(OPAQUE);    // 设置文本背景为透明
		// pDC->SetBkColor(RGB(0, 0, 100));   // 设置文本背景为绿色

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CModifyPara::GetIniSystemPara()
{
	/*m_sResolution = _T("5.378");
	m_sDelayTime = _T("0");
	m_sPulseEquivalent = _T("1000");
	m_sThreshold = _T("100");*/

	// 脉冲当量
	CString strPluse;
	::GetPrivateProfileString(_T("SaveInfo"), _T("脉冲当量"), strPluse, strPluse.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_PULSE)->SetWindowText(strPluse);
	m_sPulseEquivalent = strPluse;

	// 延迟
	CString strDelayTime;
	::GetPrivateProfileString(_T("SaveInfo"), _T("延迟"), strDelayTime, strDelayTime.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_DELAY)->SetWindowText(strDelayTime);
	m_sDelayTime = strDelayTime;

	// 分辨率
	CString strResolution;
	::GetPrivateProfileString(_T("SaveInfo"), _T("分辨率"), strResolution, strResolution.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION)->SetWindowText(strResolution);
	m_sResolution = strResolution;

	// 最小粒径阈值
	CString strThreshold;
	::GetPrivateProfileString(_T("SaveInfo"), _T("最小粒径阈值"), strThreshold, strThreshold.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD)->SetWindowText(strThreshold);
	m_sThreshold = strThreshold;

	//3.26修改  3.28下午
	// 每条取样帧数
	CString strSampleCountStrip;  //3.28夜 改命名
	::GetPrivateProfileString(_T("SaveInfo"), _T("每条取样帧数"), strSampleCountStrip, strSampleCountStrip.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP)->SetWindowText(strSampleCountStrip);
	m_sSampleCountStrip = strSampleCountStrip;

	//4.10新加
	// 灰度阈值
	CString strGrayThreshold;
	::GetPrivateProfileString(_T("SaveInfo"), _T("灰度阈值"), strGrayThreshold, strGrayThreshold.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD)->SetWindowText(strGrayThreshold);
	m_sGrayThreshold = strGrayThreshold;
}

void CModifyPara::SaveSystemPara()
{
	// 脉冲当量
	CString strPluse;
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_PULSE)->GetWindowText(strPluse);
	::WritePrivateProfileString(_T("SaveInfo"), _T("脉冲当量"), strPluse, _T("..\\SystemPara.ini"));

	// 延迟
	CString strDelayTime;
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_DELAY)->GetWindowText(strDelayTime);
	::WritePrivateProfileString(_T("SaveInfo"), _T("延迟"), strDelayTime, _T("..\\SystemPara.ini"));

	// 分辨率
	CString strResolution;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION)->GetWindowText(strResolution);
	::WritePrivateProfileString(_T("SaveInfo"), _T("分辨率"), strResolution, _T("..\\SystemPara.ini"));

	// 最小粒径阈值
	CString strThreshold;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD)->GetWindowText(strThreshold);
	::WritePrivateProfileString(_T("SaveInfo"), _T("最小粒径阈值"), strThreshold, _T("..\\SystemPara.ini"));

	//3.26修改  3.28下午
	// 每条取样帧数 
	CString strSampleCountStrip;  	//3.28夜 改命名
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP)->GetWindowText(strSampleCountStrip);
	::WritePrivateProfileString(_T("SaveInfo"), _T("每条取样帧数"), strSampleCountStrip, _T("..\\SystemPara.ini"));

	//4.10新加
	// 灰度阈值
	CString strGrayThreshold;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD)->GetWindowText(strGrayThreshold);
	::WritePrivateProfileString(_T("SaveInfo"), _T("灰度阈值"), strGrayThreshold, _T("..\\SystemPara.ini"));
}


void CModifyPara::OnBnClickedBtnModifyParaOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	SaveSystemPara();

	EndDialog(-1);
}


void CModifyPara::OnBnClickedBtnModifyParaCanceal()
{
	// TODO: 在此添加控件通知处理程序代码

	EndDialog(-1);
}


void CModifyPara::OnBnClickedBtnModifyParaApply()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	SaveSystemPara();
}


//void CModifyPara::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	// CDialogEx::OnOK();
//}
