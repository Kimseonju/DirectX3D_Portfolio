
#include "Sound.h"
#include "../PathManager.h"

CSound::CSound()	:
	m_Play(false),
	m_Loop(false),
	m_System(nullptr),
	m_Sound(nullptr),
	m_Group(nullptr),
	m_Channel(nullptr),
	m_Scene(nullptr)
{
}

CSound::~CSound()
{
	if (m_Sound)
		m_Sound->release();
}

bool CSound::LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group, 
	bool Loop, const std::string& Name, const char* FileName,
	const std::string& PathName, FMOD_MODE Type)
{
	SetName(Name);

	m_System = System;
	m_Group = Group;
	m_Loop = Loop;

	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->pPathMultibyte);

	strcat_s(FullPath, FileName);

	FMOD_MODE	Mode = FMOD_LOOP_OFF;

	if (Loop)
		Mode = FMOD_LOOP_NORMAL;
	Mode = Mode | Type;
//#define FMOD_2D                        0x00000008  /* Ignores any 3d processing. (DEFAULT). */
//#define FMOD_3D                        0x00000010  /* Makes the sound positionable in 3D.  Overrides FMOD_2D. */

	if (m_System->createSound(FullPath, Mode, nullptr, &m_Sound) != FMOD_OK)
		return false;

	return true;
}

void CSound::Play()
{
	float Volume;
	m_Group->getVolume(&Volume);
	m_System->playSound(m_Sound, m_Group, false, &m_Channel);
	m_Channel->setVolume(Volume);
	m_Play = true;
}

void CSound::Play3D(const Vector3& Pos)
{
	float Volume;
	m_Group->getVolume(&Volume);
	m_System->playSound(m_Sound, m_Group, false, &m_Channel);
	FMOD_VECTOR FPos= Pos.FMODConvert();

	m_Channel->set3DAttributes(&FPos, NULL);
	m_Channel->setVolume(Volume);
	m_Play = true;
}

void CSound::Stop()
{
	if (m_Channel)
	{
		bool	Playing = false;

		m_Channel->isPlaying(&Playing);

		if (Playing)
		{
			m_Channel->stop();
			m_Channel = nullptr;
			m_Play = false;
		}
	}
}

void CSound::Pause()
{
	if (!m_Channel)
		return;

	bool	Playing = false;

	m_Channel->isPlaying(&Playing);

	if (Playing)
		m_Channel->setPaused(true);

	m_Play = false;
}

void CSound::Resume()
{
	if (!m_Channel)
		return;

	bool	Playing = false;

	m_Channel->isPlaying(&Playing);

	if (!Playing)
		m_Channel->setPaused(false);

	m_Play = true;
}
