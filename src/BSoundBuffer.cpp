/*
This file is part of WME Lite.
http://dead-code.org/redir.php?target=wmelite

Copyright (c) 2011 Jan Nedoma

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "dcgf.h"
#include "BSoundBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MAX_NONSTREAMED_FILE_SIZE 1024*1024

//////////////////////////////////////////////////////////////////////////
CBSoundBuffer::CBSoundBuffer(CBGame* inGame):CBBase(inGame)
{
	m_Stream = NULL;
	m_Sync = NULL;

	m_Streamed = false;
	m_Filename = NULL;
	m_File = NULL;
	m_PrivateVolume = 100;

	m_Looping = false;
	m_LoopStart = 0;

	m_Type = SOUND_SFX;

	m_FreezePaused = false;
}


//////////////////////////////////////////////////////////////////////////
CBSoundBuffer::~CBSoundBuffer()
{
	Stop();

	if (m_Stream)
	{
		BASS_StreamFree(m_Stream);
		m_Stream = NULL;
	}

	if(m_File)
	{
		Game->m_FileManager->CloseFile(m_File);
		m_File = NULL;
	}

	SAFE_DELETE_ARRAY(m_Filename);
}


//////////////////////////////////////////////////////////////////////////
void CBSoundBuffer::SetStreaming(bool Streamed, DWORD NumBlocks, DWORD BlockSize)
{
	m_Streamed = Streamed;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::LoadFromFile(const char* Filename, bool ForceReload)
{
	if (m_Stream)
	{
		BASS_StreamFree(m_Stream);
		m_Stream = NULL;
	}

	if (m_File) Game->m_FileManager->CloseFile(m_File);
	
	m_File = Game->m_FileManager->OpenFile(Filename);
	if (!m_File)
	{
		Game->LOG(0, "Error opening sound file '%s'", Filename);
		return E_FAIL;
	}
	
	BASS_FILEPROCS fileProc;
	fileProc.close = CBSoundBuffer::FileCloseProc;
	fileProc.read = CBSoundBuffer::FileReadProc;
	fileProc.seek = CBSoundBuffer::FileSeekProc;
	fileProc.length = CBSoundBuffer::FileLenProc;

	m_Stream = BASS_StreamCreateFileUser(STREAMFILE_NOBUFFER, BASS_STREAM_DECODE, &fileProc, (void*)m_File);
	if (!m_Stream)
	{
		Game->LOG(0, "BASS error: %d while loading '%s'", BASS_ErrorGetCode(), Filename);
		return E_FAIL;
	}
	
	m_Stream = BASS_FX_TempoCreate(m_Stream,BASS_SAMPLE_LOOP|BASS_FX_FREESOURCE);

	CBUtils::SetString(&m_Filename, Filename);

	/*
	HRESULT res;
	bool NewlyCreated = false;

	if(!m_SoundBuffer || ForceReload || m_Streamed){
		if(!m_File) m_File = Game->m_FileManager->OpenFile(Filename);
		if(!m_File){
			Game->LOG(0, "Error opening sound file '%s'", Filename);
			return E_FAIL;
		}
		// switch to streamed for big files
		if(!m_Streamed && (m_File->GetSize() > MAX_NONSTREAMED_FILE_SIZE && !Game->m_ForceNonStreamedSounds)) SetStreaming(true);
	}

	// create buffer
	if(!m_SoundBuffer){
		NewlyCreated = true;
		
		res = InitializeBuffer(m_File);
		if(FAILED(res)){
			Game->LOG(res, "Error creating sound buffer for file '%s'", Filename);
			return res;
		}
	}



	// store filename
	if(!m_Filename){
		m_Filename = new char[strlen(Filename)+1];
		strcpy(m_Filename, Filename);
	}

	// close file (if not streaming)
	if(!m_Streamed && m_File){
		Game->m_FileManager->CloseFile(m_File);
		m_File = NULL;
	}
	*/

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::Play(bool Looping, DWORD StartSample)
{
	if (m_Stream)
	{
		SetLooping(Looping);
		BASS_ChannelPlay(m_Stream, TRUE);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
void CBSoundBuffer::SetLooping(bool looping)
{
	m_Looping = looping;

	if (m_Stream)
	{
		BASS_ChannelFlags(m_Stream, looping ? BASS_SAMPLE_LOOP : 0, BASS_SAMPLE_LOOP);
	}
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::Resume()
{
	if (m_Stream)
	{
		BASS_ChannelPlay(m_Stream, FALSE);
	}
	return S_OK;
}

HRESULT CBSoundBuffer::SetPitch(float pitch)
{
	int result = 0;
	if (m_Stream)
	{
		if (!BASS_ChannelSetAttribute(m_Stream,BASS_ATTRIB_TEMPO_PITCH, pitch))
		{
			if (result != 0) return E_FAIL;
		}
	}
	else
	{
		return E_FAIL;
	}
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::Stop()
{
	if (m_Stream)
	{
		BASS_ChannelStop(m_Stream);
	}
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::Pause()
{
	if (m_Stream)
	{
		BASS_ChannelPause(m_Stream);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
DWORD CBSoundBuffer::GetLength()
{
	QWORD len = BASS_ChannelGetLength(m_Stream, BASS_POS_BYTE);
	return 1000 * BASS_ChannelBytes2Seconds(m_Stream, len);
}


//////////////////////////////////////////////////////////////////////////
void CBSoundBuffer::SetType(TSoundType Type)
{
	m_Type = Type;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::SetVolume(int Volume)
{
	if (m_Stream)
	{
		// compute the "weighted" value (volume relatively to TSoundType category's volume)
		float resultingVolumePerCent = ((float)Volume / 100.0f) * m_PrivateVolume;
		BASS_ChannelSetAttribute(m_Stream, BASS_ATTRIB_VOL, resultingVolumePerCent / 100.0f);
		// Game->LOG(0, "BASS_Setvolume occurred, integer=%d, privVolume=%d, resulting float value=%f.\n", Volume, m_PrivateVolume, resultingVolumePerCent / 100.0f);
	}
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::SetPrivateVolume(int Volume)
{
	m_PrivateVolume = Volume;

	switch(m_Type)
	{
	case SOUND_SFX:
		Volume = Game->m_SoundMgr->m_VolumeSFX;
		break;
	case SOUND_SPEECH:
		Volume = Game->m_SoundMgr->m_VolumeSpeech;
		break;
	case SOUND_MUSIC:
		Volume = Game->m_SoundMgr->m_VolumeMusic;
		break;
	}
	return SetVolume(Volume);
}


//////////////////////////////////////////////////////////////////////////
bool CBSoundBuffer::IsPlaying()
{
	return m_FreezePaused || BASS_ChannelIsActive(m_Stream) == BASS_ACTIVE_PLAYING;
}


//////////////////////////////////////////////////////////////////////////
DWORD CBSoundBuffer::GetPosition()
{
	if (m_Stream)
	{
		QWORD len = BASS_ChannelGetPosition(m_Stream, BASS_POS_BYTE);
		return 1000 * BASS_ChannelBytes2Seconds(m_Stream, len);
	}
	else return 0;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::SetPosition(DWORD Pos)
{
	if (m_Stream)
	{
		QWORD pos = BASS_ChannelSeconds2Bytes(m_Stream, (float)Pos / 1000.0f);		
		BASS_ChannelSetPosition(m_Stream, pos, BASS_POS_BYTE);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::SetLoopStart(DWORD Pos)
{
	m_LoopStart = Pos;

	if (m_Stream)
	{
		if (m_Sync)
		{
			BASS_ChannelRemoveSync(m_Stream, m_Sync);
			m_Sync = NULL;
		}
		if (m_LoopStart > 0)
		{
			QWORD len = BASS_ChannelGetLength(m_Stream, BASS_POS_BYTE);
			m_Sync = BASS_ChannelSetSync(m_Stream, BASS_SYNC_POS | BASS_SYNC_MIXTIME, len, CBSoundBuffer::LoopSyncProc, (void*)this);
		}
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
void CBSoundBuffer::LoopSyncProc(HSYNC handle, DWORD channel, DWORD data, void* user)
{
	CBSoundBuffer* soundBuf = static_cast<CBSoundBuffer*>(user);
	QWORD pos = BASS_ChannelSeconds2Bytes(channel, (float)soundBuf->GetLoopStart() / 1000.0f);
	
	if (!BASS_ChannelSetPosition(channel, pos, BASS_POS_BYTE))
		BASS_ChannelSetPosition(channel, 0, BASS_POS_BYTE);
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::SetPan(float Pan)
{
	if (m_Stream)
	{
		BASS_ChannelSetAttribute(m_Stream, BASS_ATTRIB_PAN, Pan);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundBuffer::ApplyFX(TSFXType Type, float Param1, float Param2, float Param3, float Param4)
{
	switch(Type)
	{
	case SFX_ECHO:
		break;

	case SFX_REVERB:
		break;

	default:
		break;
	}

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
void CBSoundBuffer::FileCloseProc(void* user)
{
	/*
	CBFile* file = static_cast<CBFile*>(user);
	file->Game->m_FileManager->CloseFile(file);
	*/
}

//////////////////////////////////////////////////////////////////////////
QWORD CBSoundBuffer::FileLenProc(void* user)
{
	CBFile* file = static_cast<CBFile*>(user);
	return file->GetSize();
}

//////////////////////////////////////////////////////////////////////////
DWORD CBSoundBuffer::FileReadProc(void *buffer, DWORD length, void* user)
{
	CBFile* file = static_cast<CBFile*>(user);
	DWORD oldPos = file->GetPos();
	file->Read(buffer, length);
	return file->GetPos() - oldPos;
}

//////////////////////////////////////////////////////////////////////////
BOOL CBSoundBuffer::FileSeekProc(QWORD offset, void *user)
{
	CBFile* file = static_cast<CBFile*>(user);
	return SUCCEEDED(file->Seek(offset));
}



