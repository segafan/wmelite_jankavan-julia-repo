#ifndef __WmeSteamAPI_H__
#define __WmeSteamAPI_H__

#include "steam_api.h"
#include "BScriptable.h"


class SteamAPI : public CBScriptable  
{

public:
	DECLARE_PERSISTENT(SteamAPI, CBScriptable)

	SteamAPI(CBGame* inGame);
	SteamAPI(CBGame* inGame, CScStack* Stack);
	virtual ~SteamAPI(void);

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