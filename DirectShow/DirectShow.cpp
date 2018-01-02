/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectShow.cpp
* @brief	This Program is DirectShow DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-11-1	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-2	v1.11a	alopex	Make Demo And Add Video Play In Window Mode.
*/
#include "DirectCommon.h"
#include "DirectShow.h"

//------------------------------------------------------------------
// @Function:	 DirectShow()
// @Purpose: DirectShow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::DirectShow()
{
	CoInitialize(NULL);					//COM初始化
	m_pDirectShowGraphBuilder = NULL;	//IGraphBuilder接口对象指针初始化(NULL)
	m_pDirectShowMediaControl = NULL;	//IMediaControl接口对象指针初始化(NULL)
	m_pDirectShowMediaPosition = NULL;	//IMediaPosition接口对象指针初始化(NULL)
	m_pDirectShowMediaEvent = NULL;		//IMediaEvent接口对象指针初始化(NULL)
	m_pDirectShowBasicAudio = NULL;		//IBasicAudio接口对象指针初始化(NULL)
	m_pDirectShowBasicVideo = NULL;		//IBasicVideo接口对象指针初始化(NULL)
	m_pDirectShowVideoWindow = NULL;	//IVideoWindow接口对象指针初始化(NULL)

	m_lVideoWidth = 0;					//Video Origin Width(视频源宽度)
	m_lVideoHeight = 0;					//Video Origin Height(视频源高度)
	m_fVideofps = 0.0f;					//Video Origin Frame Per Second(fps)(~视频源场频)
}

//------------------------------------------------------------------
// @Function:	 ~DirectShow()
// @Purpose: DirectShow析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::~DirectShow()
{
	SAFE_RELEASE(m_pDirectShowVideoWindow);		//IVideoWindow释放
	SAFE_RELEASE(m_pDirectShowBasicVideo);		//IBasicVideo释放
	SAFE_RELEASE(m_pDirectShowBasicAudio);		//IBasicAudio释放
	SAFE_RELEASE(m_pDirectShowMediaEvent);		//IMediaEvent释放
	SAFE_RELEASE(m_pDirectShowMediaPosition);	//IMediaPosition释放
	SAFE_RELEASE(m_pDirectShowMediaControl);	//IMediaControl释放
	SAFE_RELEASE(m_pDirectShowGraphBuilder);	//IGraphBuilder释放
	CoUninitialize();							//COM释放
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoWidth(void) const
// @Purpose: DirectShow 获取视频宽度
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
long WINAPI DirectShow::DirectShowGetVideoWidth(void) const
{
	return m_lVideoWidth;
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoHeight(void) const
// @Purpose: DirectShow 获取视频高度
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
long WINAPI DirectShow::DirectShowGetVideoHeight(void) const
{
	return m_lVideoHeight;
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoFramePerSecond(void) const
// @Purpose: DirectShow 获取视频场频
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
float WINAPI DirectShow::DirectShowGetVideoFramePerSecond(void) const
{
	return m_fVideofps;
}

//------------------------------------------------------------------
// @Function:	 DirectShowInit(void)
// @Purpose: DirectShow 初始化
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowInit(void)
{
	//创建IGraphBuilder接口对象
	VERIFY(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pDirectShowGraphBuilder));

	//创建IMediaControl和IMediaPosition接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pDirectShowMediaControl));//IMediaControl接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pDirectShowMediaPosition));//IMediaPosition接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&m_pDirectShowMediaEvent));//m_pDirectShowMediaEvent接口对象

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadFile(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载音频视频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadFile(LPWSTR lpszFileName)
{
	//加载音频视频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadAudio(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载音频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadAudio(LPWSTR lpszFileName)
{
	//加载音频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadVideo(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载视频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadVideo(LPWSTR lpszFileName)
{
	//加载视频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3音源文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadMP3(LPWSTR lpszFileName)
{
	//加载MP3音源文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPlay(void)
// @Purpose: DirectShow 播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioPlay(void)
{
	m_pDirectShowMediaControl->Run();
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPause(void)
// @Purpose: DirectShow 暂停播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioPause(void)
{
	m_pDirectShowMediaControl->Pause();
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioStop(void)
// @Purpose: DirectShow 停止播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioStop(void)
{
	m_pDirectShowMediaControl->Stop();
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取音源文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioGetDuration(REFTIME* pRefDuration) const
{
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
{
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
{
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Play(void)
// @Purpose: DirectShow 播放MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3Play(void)
{
	m_pDirectShowMediaControl->Run();
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Pause(void)
// @Purpose: DirectShow 暂停MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3Pause(void)
{
	m_pDirectShowMediaControl->Pause();
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Stop(void)
// @Purpose: DirectShow 停止MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3Stop(void)
{
	m_pDirectShowMediaControl->Stop();
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取MP3音源文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3GetDuration(REFTIME* pRefDuration) const
{
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取MP3音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
{
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置MP3音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
{
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoInfo(void)
// @Purpose: DirectShow 获取视频格式信息
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowGetVideoInfo(void)
{
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd)
// @Purpose: DirectShow 设置视频在指定窗口内播放
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd)
{
	RECT WindowRect;
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	//音频Audio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//创建IBasicAudio接口

	//窗口Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//创建IVideoWindow接口
	GetClientRect(hWnd, &WindowRect);	//读取当前窗口区域
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//设置视频窗口句柄
	m_pDirectShowVideoWindow->put_Left(0);	//视频原点X坐标
	m_pDirectShowVideoWindow->put_Top(0);	//视频原点Y坐标
	m_pDirectShowVideoWindow->put_Width(WindowRect.right - WindowRect.left);	//视频宽度
	m_pDirectShowVideoWindow->put_Height(WindowRect.bottom - WindowRect.top);	//视频高度
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//窗口模式
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//设置接受窗口信息句柄  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
// @Purpose: DirectShow 设置视频在指定窗口内播放
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: RECT sRect(视频播放区域)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
{
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	//音频Audio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//创建IBasicAudio接口

	//窗口Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//创建IVideoWindow接口
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//设置视频窗口句柄
	m_pDirectShowVideoWindow->put_Left(sRect.left);	//视频原点X坐标
	m_pDirectShowVideoWindow->put_Top(sRect.top);	//视频原点Y坐标
	m_pDirectShowVideoWindow->put_Width(sRect.right - sRect.left);	//视频宽度
	m_pDirectShowVideoWindow->put_Height(sRect.bottom - sRect.top);	//视频高度
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//窗口模式
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//设置接受窗口信息句柄  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlayWait(void)
// @Purpose: DirectShow 播放视频文件(等待)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoPlayWait(void)
{
	long evCode = 0;

	VERIFY(m_pDirectShowMediaControl->Run());
	while (evCode != EC_COMPLETE)
	{
		m_pDirectShowMediaEvent->WaitForCompletion(1000, &evCode);
	}

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlay(void)
// @Purpose: DirectShow 播放视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoPlay(void)
{
	VERIFY(m_pDirectShowMediaControl->Run());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPause(void)
// @Purpose: DirectShow 暂停视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoPause(void)
{
	VERIFY(m_pDirectShowMediaControl->Pause());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoStop(void)
// @Purpose: DirectShow 停止视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoStop(void)
{
	VERIFY(m_pDirectShowMediaControl->Stop());

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取视频文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoGetDuration(REFTIME* pRefDuration) const
{
	VERIFY(m_pDirectShowMediaPosition->get_Duration(pRefDuration));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取视频文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(当前播放位置)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
{
	VERIFY(m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置视频文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
{
	VERIFY(m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition));

	return S_OK;//OK
}