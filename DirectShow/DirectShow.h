/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectShow.h
* @brief	This Program is DirectShow DLL Project.
* @author	Alopex/Helium
* @version	v1.21a
* @date		2017-11-1	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-2	v1.11a	alopex	Make Demo And Add Video Play In Window Mode.
* @date		2018-1-2	v1.21a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-3	v1.22a	alopex	Add Thread Safe Variable Makesure Thread Safe(DirectSafe).
*/
#pragma once

#ifndef __DIRECTSHOW_H_
#define __DIRECTSHOW_H_

//Include DirectShow Header File
#include <dshow.h>

//Include Static Library File
#pragma comment(lib,"Strmiids.lib") 

//Macro Definition
#ifdef  DIRECTSHOW_EXPORTS
#define DIRECTSHOW_API	__declspec(dllexport)
#else
#define DIRECTSHOW_API	__declspec(dllimport)
#endif

//Class Definition

//Class
class DIRECTSHOW_API DirectShow
{
private:
	IGraphBuilder* m_pDirectShowGraphBuilder;	//IGraphBuilder Interface Pointer
	IMediaControl* m_pDirectShowMediaControl;	//IMediaControl Interface Pointer
	IMediaPosition* m_pDirectShowMediaPosition;	//IMediaPosition Interface Pointer
	IMediaEvent* m_pDirectShowMediaEvent;		//IMediaEvent Interface Pointer

	IBasicAudio* m_pDirectShowBasicAudio;		//IBasicAudio Interface Pointer
	IBasicVideo* m_pDirectShowBasicVideo;		//IBasicVideo Interface Pointer
	IVideoWindow* m_pDirectShowVideoWindow;		//IVideoWindow Interface Pointer

	long m_lVideoWidth;							//Video Origin Width
	long m_lVideoHeight;						//Video Origin Height
	float m_fVideofps;							//Video Origin Frame Per Second(fps)

public:
	DirectShow();	//DirectShow Constructor Function(DirectShow���캯��)
	~DirectShow();	//DirectShow Destructor Function(DirectShow��������)

	//DirectShow����
	long WINAPI DirectShowGetVideoWidth(void) const;	//DirectShow Get Video Width(��ȡ��Ƶ���)
	long WINAPI DirectShowGetVideoHeight(void) const;	//DirectShow Get Video Height(��ȡ��Ƶ�߶�)
	float WINAPI DirectShowGetVideoFramePerSecond(void) const;	//DirectShow Get Video fps(��ȡ��Ƶ��Ƶ)

	//DirectShow��ʼ��
	HRESULT WINAPI DirectShowInit(void);	//DirectShow Initialize(DirectShow��ʼ��)

	//DirectShow�����ļ�(·��)
	HRESULT WINAPI DirectShowLoadFile(LPWSTR lpszFileName);	//DirectShow Load Audio/Video File(DirectShow�����ļ�)
	HRESULT WINAPI DirectShowLoadMP3(LPWSTR lpszFileName);	//DirectShow Load MP3 File(DirectShow����MP3�ļ�)
	HRESULT WINAPI DirectShowLoadAudio(LPWSTR lpszFileName);	//DirectShow Load Audio File(DirectShow������Ƶ�ļ�)
	HRESULT WINAPI DirectShowLoadVideo(LPWSTR lpszFileName);	//DirectShow Load Video File(DirectShow������Ƶ�ļ�)

	//DirectShow����MP3�ļ���ʽ
	void WINAPI DirectShowMP3Play(void);	//DirectShow MP3 Play(DirectShow����)
	void WINAPI DirectShowMP3Pause(void);	//DirectShow MP3 Pause(DirectShow��ͣ)
	void WINAPI DirectShowMP3Stop(void);	//DirectShow MP3 Stop(DirectShowֹͣ)
	void WINAPI DirectShowMP3GetDuration(REFTIME* pRefDuration) const;	//DirectShow MP3 GetDuration(DirectShow��ȡʱ���ܳ���)
	void WINAPI DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow MP3 GetCurrentPosition(DirectShow��ȡ��ǰ����)
	void WINAPI DirectShowMP3SetCurrentPosition(REFTIME RefPosition);	//DirectShow MP3 SetCurrentPosition(DirectShow���õ�ǰ����)

	//DirectShow������Ƶ�ļ���ʽ
	void WINAPI DirectShowAudioPlay(void);	//DirectShow Audio Play(DirectShow����)
	void WINAPI DirectShowAudioPause(void);	//DirectShow Audio Pause(DirectShow��ͣ)
	void WINAPI DirectShowAudioStop(void);	//DirectShow Audio Stop(DirectShowֹͣ)
	void WINAPI DirectShowAudioGetDuration(REFTIME* pRefDuration) const;//DirectShow Audio GetDuration(DirectShow��ȡʱ���ܳ���)
	void WINAPI DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Audio GetCurrentPosition(DirectShow��ȡ��ǰ����)
	void WINAPI DirectShowAudioSetCurrentPosition(REFTIME RefPosition);	//DirectShow Audio SetCurrentPosition(DirectShow���õ�ǰ����)

	//DirectShow������Ƶ�ļ���ʽ
	HRESULT WINAPI DirectShowGetVideoInfo(void);	//DirectShow Get Video Information(DirectShow��ȡ��Ƶ��ʽ)
	HRESULT WINAPI DirectShowSetVideoPlayInWindow(HWND hWnd);	//DirectShow Set Video Play In Window(DirectShow������Ƶ��ָ�������ڲ���)(~����)
	HRESULT WINAPI DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect);	//DirectShow Set Video Play In Window(DirectShow������Ƶ��ָ�������ڲ���)(~ָ����������)
	HRESULT WINAPI DirectShowVideoPlayWait(void);	//DirectShow Video Play Wait(DirectShow����)(�ȴ�)
	HRESULT WINAPI DirectShowVideoPlay(void);	//DirectShow Video Play(DirectShow����)
	HRESULT WINAPI DirectShowVideoPause(void);	//DirectShow Video Pause(DirectShow��ͣ)
	HRESULT WINAPI DirectShowVideoStop(void);	//DirectShow Video Stop(DirectShowֹͣ)
	HRESULT WINAPI DirectShowVideoGetDuration(REFTIME* pRefDuration) const;	//DirectShow Video GetDuration(DirectShow��ȡʱ���ܳ���)
	HRESULT WINAPI DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Video GetCurrentPosition(DirectShow��ȡ��ǰ����)
	HRESULT WINAPI DirectShowVideoSetCurrentPosition(REFTIME RefPosition);	//DirectShow Video SetCurrentPosition(DirectShow���õ�ǰ����)
};

#endif