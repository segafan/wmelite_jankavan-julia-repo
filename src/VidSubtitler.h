// This file is part of Wintermute Engine
// For conditions of distribution and use, see copyright notice in license.txt
// http://dead-code.org/redir.php?target=wme


#ifndef __WmeVidSubtitler_H__
#define __WmeVidSubtitler_H__

#include "BBase.h"
#include "VidSubtitle.h"

class CVidSubtitler :
	public CBBase
{
public:
	CVidSubtitler(CBGame* inGame);
	virtual ~CVidSubtitler(void);

	bool m_Loaded;
	bool m_ShowSubtitle;
	int m_CurrentSubtitle;
	HRESULT LoadSubtitles(char* Filename, char* SubtitleFile);
	HRESULT Display();
	HRESULT Update(LONG Frame);
	LONG m_LastSample;
	CBArray<CVidSubtitle*, CVidSubtitle*> m_Subtitles;
};

#endif // !__WMEVidSubtitle_H__
