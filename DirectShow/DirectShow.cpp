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
// @Purpose: DirectShow���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::DirectShow()
{
	CoInitialize(NULL);					//COM��ʼ��
	m_pDirectShowGraphBuilder = NULL;	//IGraphBuilder�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowMediaControl = NULL;	//IMediaControl�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowMediaPosition = NULL;	//IMediaPosition�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowMediaEvent = NULL;		//IMediaEvent�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowBasicAudio = NULL;		//IBasicAudio�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowBasicVideo = NULL;		//IBasicVideo�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectShowVideoWindow = NULL;	//IVideoWindow�ӿڶ���ָ���ʼ��(NULL)

	m_lVideoWidth = 0;					//Video Origin Width(��ƵԴ���)
	m_lVideoHeight = 0;					//Video Origin Height(��ƵԴ�߶�)
	m_fVideofps = 0.0f;					//Video Origin Frame Per Second(fps)(~��ƵԴ��Ƶ)
}

//------------------------------------------------------------------
// @Function:	 ~DirectShow()
// @Purpose: DirectShow��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::~DirectShow()
{
	SAFE_RELEASE(m_pDirectShowVideoWindow);		//IVideoWindow�ͷ�
	SAFE_RELEASE(m_pDirectShowBasicVideo);		//IBasicVideo�ͷ�
	SAFE_RELEASE(m_pDirectShowBasicAudio);		//IBasicAudio�ͷ�
	SAFE_RELEASE(m_pDirectShowMediaEvent);		//IMediaEvent�ͷ�
	SAFE_RELEASE(m_pDirectShowMediaPosition);	//IMediaPosition�ͷ�
	SAFE_RELEASE(m_pDirectShowMediaControl);	//IMediaControl�ͷ�
	SAFE_RELEASE(m_pDirectShowGraphBuilder);	//IGraphBuilder�ͷ�
	CoUninitialize();							//COM�ͷ�
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoWidth(void) const
// @Purpose: DirectShow ��ȡ��Ƶ���
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
// @Purpose: DirectShow ��ȡ��Ƶ�߶�
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
// @Purpose: DirectShow ��ȡ��Ƶ��Ƶ
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
// @Purpose: DirectShow ��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowInit(void)
{
	//����IGraphBuilder�ӿڶ���
	VERIFY(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pDirectShowGraphBuilder));

	//����IMediaControl��IMediaPosition�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pDirectShowMediaControl));//IMediaControl�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pDirectShowMediaPosition));//IMediaPosition�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&m_pDirectShowMediaEvent));//m_pDirectShowMediaEvent�ӿڶ���

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadFile(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ��Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadFile(LPWSTR lpszFileName)
{
	//������Ƶ��Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadAudio(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadAudio(LPWSTR lpszFileName)
{
	//������Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadVideo(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadVideo(LPWSTR lpszFileName)
{
	//������Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow ����MP3��Դ�ļ�(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3��Դ�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowLoadMP3(LPWSTR lpszFileName)
{
	//����MP3��Դ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPlay(void)
// @Purpose: DirectShow ������Դ�ļ�
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
// @Purpose: DirectShow ��ͣ������Դ�ļ�
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
// @Purpose: DirectShow ֹͣ������Դ�ļ�
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
// @Purpose: DirectShow ��ȡ��Դ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioGetDuration(REFTIME* pRefDuration) const
{
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡ��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
{
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ������Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
{
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Play(void)
// @Purpose: DirectShow ����MP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ��ͣMP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ֹͣMP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ��ȡMP3��Դ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3GetDuration(REFTIME* pRefDuration) const
{
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡMP3��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
{
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ����MP3��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void WINAPI DirectShow::DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
{
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoInfo(void)
// @Purpose: DirectShow ��ȡ��Ƶ��ʽ��Ϣ
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowGetVideoInfo(void)
{
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd)
// @Purpose: DirectShow ������Ƶ��ָ�������ڲ���
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd)
{
	RECT WindowRect;
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	//��ƵAudio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//����IBasicAudio�ӿ�

	//����Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//����IVideoWindow�ӿ�
	GetClientRect(hWnd, &WindowRect);	//��ȡ��ǰ��������
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//������Ƶ���ھ��
	m_pDirectShowVideoWindow->put_Left(0);	//��Ƶԭ��X����
	m_pDirectShowVideoWindow->put_Top(0);	//��Ƶԭ��Y����
	m_pDirectShowVideoWindow->put_Width(WindowRect.right - WindowRect.left);	//��Ƶ���
	m_pDirectShowVideoWindow->put_Height(WindowRect.bottom - WindowRect.top);	//��Ƶ�߶�
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//����ģʽ
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//���ý��ܴ�����Ϣ���  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
// @Purpose: DirectShow ������Ƶ��ָ�������ڲ���
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: RECT sRect(��Ƶ��������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
{
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	//��ƵAudio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//����IBasicAudio�ӿ�

	//����Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//����IVideoWindow�ӿ�
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//������Ƶ���ھ��
	m_pDirectShowVideoWindow->put_Left(sRect.left);	//��Ƶԭ��X����
	m_pDirectShowVideoWindow->put_Top(sRect.top);	//��Ƶԭ��Y����
	m_pDirectShowVideoWindow->put_Width(sRect.right - sRect.left);	//��Ƶ���
	m_pDirectShowVideoWindow->put_Height(sRect.bottom - sRect.top);	//��Ƶ�߶�
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//����ģʽ
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//���ý��ܴ�����Ϣ���  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlayWait(void)
// @Purpose: DirectShow ������Ƶ�ļ�(�ȴ�)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
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
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoPlay(void)
{
	VERIFY(m_pDirectShowMediaControl->Run());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPause(void)
// @Purpose: DirectShow ��ͣ��Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoPause(void)
{
	VERIFY(m_pDirectShowMediaControl->Pause());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoStop(void)
// @Purpose: DirectShow ֹͣ��Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoStop(void)
{
	VERIFY(m_pDirectShowMediaControl->Stop());

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow ��ȡ��Ƶ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoGetDuration(REFTIME* pRefDuration) const
{
	VERIFY(m_pDirectShowMediaPosition->get_Duration(pRefDuration));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡ��Ƶ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(��ǰ����λ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
{
	VERIFY(m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ������Ƶ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT WINAPI DirectShow::DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
{
	VERIFY(m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition));

	return S_OK;//OK
}