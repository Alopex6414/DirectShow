/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Alopex/Helium
*     All rights reserved.
*
* @file		DirectShow.h
* @brief	This Program is DirectShow DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-11-1
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

public:
	DirectShow();	//DirectShow Constructor Function
	~DirectShow();	//DirectShow Destructor Function

	HRESULT WINAPI DirectShowInit(void);	//DirectShow Initialize
	HRESULT WINAPI DirectShowLoadFile(LPWSTR lpszFileName);	//DirectShow Load Audio/Video File
	HRESULT WINAPI DirectShowLoadMP3(LPWSTR lpszFileName);	//DirectShow Load MP3 File
	HRESULT WINAPI DirectShowLoadAudio(LPWSTR lpszFileName);	//DirectShow Load Audio File
	HRESULT WINAPI DirectShowLoadVideo(LPWSTR lpszFileName);	//DirectShow Load Video File

	void WINAPI DirectShowMP3Play(void);	//DirectShow MP3 Play
	void WINAPI DirectShowMP3Pause(void);	//DirectShow MP3 Pause
	void WINAPI DirectShowMP3Stop(void);	//DirectShow MP3 Stop
	void WINAPI DirectShowMP3GetDuration(REFTIME* pRefDuration) const;	//DirectShow MP3 GetDuration
	void WINAPI DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow MP3 GetCurrentPosition
	void WINAPI DirectShowMP3SetCurrentPosition(REFTIME RefPosition);	//DirectShow MP3 SetCurrentPosition

	void WINAPI DirectShowAudioPlay(void);	//DirectShow Audio Play
	void WINAPI DirectShowAudioPause(void);	//DirectShow Audio Pause
	void WINAPI DirectShowAudioStop(void);	//DirectShow Audio Stop
	void WINAPI DirectShowAudioGetDuration(REFTIME* pRefDuration) const;//DirectShow Audio GetDuration
	void WINAPI DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Audio GetCurrentPosition
	void WINAPI DirectShowAudioSetCurrentPosition(REFTIME RefPosition);	//DirectShow Audio SetCurrentPosition

	HRESULT WINAPI DirectShowGetVideoInfo(HWND hWnd);	//DirectShow Get Video Information
	HRESULT WINAPI DirectShowVideoPlay(void);	//DirectShow Video Play
	HRESULT WINAPI DirectShowVideoPause(void);	//DirectShow Video Pause
	HRESULT WINAPI DirectShowVideoStop(void);	//DirectShow Video Stop
	HRESULT WINAPI DirectShowVideoGetDuration(REFTIME* pRefDuration) const;	//DirectShow Video GetDuration
	HRESULT WINAPI DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Video GetCurrentPosition
	HRESULT WINAPI DirectShowVideoSetCurrentPosition(REFTIME RefPosition);	//DirectShow Video SetCurrentPosition
};

#endif