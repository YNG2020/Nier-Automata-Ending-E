#pragma once
#include "musicPlayer.h"
#include <iostream>

/************************************************
 *                class MusicMCI				*
 * ���ֲ��Ų�����								*
 * ���еײ����ֲ���								*
 * ��ͣ���رգ�������������ȡ����ʱ��Ȳ���		*
 ************************************************/

class MusicMCI
{
private:
	MCIDEVICEID nDeviceID;									// �豸ID

public:
	MusicMCI()noexcept;										// Ĭ�Ϲ��캯��
	virtual ~MusicMCI();									// ����������
	bool open(LPCWSTR music)noexcept;						// ������
	bool play()noexcept;									// ��������
	bool pause()noexcept;									// ��ͣ����
	bool stop()noexcept;									// ֹͣ����
	bool close()noexcept;									// �ر�����
	bool getCurrentTime(DWORD& pos)noexcept;				// ��ȡ��ǰ����ʱ��
	bool getTotalTime(DWORD& time)noexcept;					// ��ȡ������ʱ��
	bool setVolume(size_t volume)noexcept;					// ����������С
	bool setStartTime(size_t start)noexcept;				// ���ò���λ��
};