#ifndef __WmeSteamSupport_H__
#define __WmeSteamSupport_H__

#include "steam_api.h"
#include "BScriptable.h"


class SteamSupport : public CBScriptable  
{

public:
	DECLARE_PERSISTENT(SteamSupport, CBScriptable)

	SteamSupport(CBGame* inGame);
	SteamSupport(CBGame* inGame, CScStack* Stack);
	virtual ~SteamSupport(void);

	HRESULT ScCallMethod(CScScript* Script, CScStack *Stack, CScStack *ThisStack, char *Name);
	CScValue* ScGetProperty(char *Name);
	HRESULT ScSetProperty(char *Name, CScValue *Value);
	bool SetAchievement(const char* id);
	CScValue* m_Values;
	char* ScToString();

	bool m_LoggedIn;
	int m_AppId;
	int m_Length;

	bool m_SteamInitialized;
	bool m_StatsInitialized;
	
};

#endif