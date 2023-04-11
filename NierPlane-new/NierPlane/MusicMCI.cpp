#include "MusicMCI.h"


/****************************************************************************************************************
 *  class MusicMCI																								*
 ****************************************************************************************************************/

/****************************************************************
 * MusicMci public method										*
 ****************************************************************/

MusicMCI::MusicMCI()noexcept
{
	nDeviceID = -1;
}

MusicMCI::~MusicMCI()
{
	if (nDeviceID != -1) this->close();
}

// ���ļ�
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::open(LPCWSTR strSongPath)noexcept
{
	MCI_OPEN_PARMS mciOP;

	mciOP.lpstrDeviceType = nullptr;
	mciOP.lpstrElementName = strSongPath;
	const DWORD dwReturn = mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE, (DWORD_PTR)(static_cast<LPVOID>(&mciOP)));


	if (dwReturn == 0)
	{
		nDeviceID = mciOP.wDeviceID;
		return true;
	}
	else
	{
		nDeviceID = -1;
		return false;
	}
}

// ����
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::play()noexcept
{
	MCI_PLAY_PARMS mciPP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PLAY,
		MCI_NOTIFY, (DWORD_PTR)(static_cast<LPVOID>(&mciPP)));
	if (dwReturn == 0)
		return true;
	else
		return false;
}

// ��ͣ����
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::pause()noexcept
{
	MCI_GENERIC_PARMS mciGP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PAUSE,
		MCI_NOTIFY | MCI_WAIT, (DWORD_PTR)(static_cast<LPVOID>(&mciGP)));
	if (dwReturn == 0)
		return true;
	else
		return false;
}

// ֹͣ���Ų�ʹ���ȷ��ص���ͷ
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::stop()noexcept
{
	MCI_SEEK_PARMS mciSP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SEEK,
		MCI_WAIT | MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD_PTR)(static_cast<LPVOID>(&mciSP)));
	if (dwReturn == 0)
		return true;
	else
		return false;
}

// �ر�MCI�豸
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::close()noexcept
{
	MCI_GENERIC_PARMS mciGP{};

	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_CLOSE,
		MCI_NOTIFY | MCI_WAIT, (DWORD_PTR)(static_cast<LPVOID>(&mciGP)));
	if (dwReturn == 0)
	{
		nDeviceID = -1;
		return true;
	}
	else
		return false;
}

// ��õ�ǰ���Ž��ȣ�pos �� ms Ϊ��λ
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::getCurrentTime(DWORD& pos)noexcept
{
	MCI_STATUS_PARMS mciSP{};

	mciSP.dwItem = MCI_STATUS_POSITION;
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_STATUS,
		MCI_STATUS_ITEM, (DWORD_PTR)(static_cast<LPVOID>(&mciSP)));
	if (dwReturn == 0)
	{
		pos = static_cast<DWORD>(mciSP.dwReturn);
		return true;
	}
	else
	{
		pos = 0;
		return false;
	}
}

// ��ȡ������ʱ����time ��ms Ϊ��λ
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::getTotalTime(DWORD& time)noexcept
{
	MCI_STATUS_PARMS mciSP{};

	mciSP.dwItem = MCI_STATUS_LENGTH;
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_STATUS,
		MCI_WAIT | MCI_STATUS_ITEM, (DWORD_PTR)(static_cast<LPVOID>(&mciSP)));		// �ؼ���ȡ�ó���
	if (dwReturn == 0)
	{
		time = static_cast<DWORD>(mciSP.dwReturn);
		return true;
	}
	else
	{
		time = 0;
		return false;
	}
}

// ����������С������ֵ��Χ�� 0 �� 1000
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::setVolume(size_t nVolumeValue)noexcept
{
	if (nVolumeValue > 1000)
	{
		nVolumeValue = 1000;
	}
	else if (nVolumeValue < 0)
	{
		nVolumeValue = 0;
	}

	MCI_DGV_SETAUDIO_PARMS mciDSP;
	mciDSP.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciDSP.dwValue = static_cast<DWORD>(nVolumeValue);
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_SETAUDIO,
		MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD_PTR)(static_cast<LPVOID>(&mciDSP)));
	if (dwReturn == 0)
		return true;
	else
		return false;
}

// ���ò�����ʼλ��
// �ɹ����� true��ʧ�ܷ��� false
bool MusicMCI::setStartTime(size_t start_time) noexcept
{
	DWORD end_time = 0;
	this->getTotalTime(end_time);

	if (start_time > end_time)
		return false;

	MCI_PLAY_PARMS mciPlay{};
	mciPlay.dwFrom = static_cast<DWORD>(start_time);
	mciPlay.dwTo = static_cast<DWORD>(end_time);
	const DWORD dwReturn = mciSendCommand(nDeviceID, MCI_PLAY,
		MCI_TO | MCI_FROM, (DWORD_PTR)(static_cast<LPVOID>(&mciPlay)));

	if (dwReturn == 0)
		return true;
	else
		return false;
}