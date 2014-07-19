// This file is part of Wintermute Engine
// For conditions of distribution and use, see copyright notice in license.txt
// http://dead-code.org/redir.php?target=wme


#ifndef __WmeVidSubtitle_H__
#define __WmeVidSubtitle_H__

#include "BBase.h"

class CVidSubtitle : public CBBase  
{
public:
	LONG m_EndFrame;
	LONG m_StartFrame;
	char* m_Text;
	CVidSubtitle(CBGame* inGame);
	CVidSubtitle(CBGame* inGame, char* Text, LONG StartFrame, LONG EndFrame);
	virtual ~CVidSubtitle();

};

#endif // !__WMEVidSubtitle_H__
