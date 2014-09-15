//////////////////////////////////////////////////////////////////////////////
//// Steam Support highly inspired by steam plugin by Jan 'Mnemonic' Nedoma
///////////////////////////////////////////////////////////////////////////////


#include "dcgf.h"
#include "SteamSupport.h"
#include "Steam_api.h"

IMPLEMENT_PERSISTENT(SteamAPI, false);

SteamAPI::SteamAPI(CBGame* inGame, CScStack* Stack):CBScriptable(inGame)
{
	Stack->CorrectParams(0);

	m_AppId = 0;
	m_Length = 0;
	m_Values = new CScValue(Game);

	bool result = SteamAPI_Init();
	m_LoggedIn = result;
	if (m_LoggedIn)
	{
		m_AppId = SteamUtils()->GetAppID();
	}

}


SteamAPI::SteamAPI(CBGame* inGame):CBScriptable(inGame)
{
	m_AppId = 0;
	m_Length = 0;
	m_Values = new CScValue(Game);

	bool result = SteamAPI_Init();
	m_LoggedIn = result;
	if (m_LoggedIn)
	{
		m_AppId = SteamUtils()->GetAppID();
	}
}


SteamAPI::~SteamAPI(void)
{
	SteamAPI_Shutdown();
	SAFE_DELETE(m_Values);

}


bool SteamAPI::SetAchievement(const char* id)
{
	if (!m_LoggedIn) return false;

	// if (m_StatsInitialized) return false;
	// Game->LOG(0,id);
	if (!SteamUser())
	{
		bool result = SteamAPI_Init();
		if (!result)
		{
			Game->LOG(0,"We don't have a steam user.");
			return false;
		}
	}
	
	if (!SteamUserStats()->SetAchievement(id)) return false;

//	Game->LOG(0,"And we even set that");
	
	return SteamUserStats()->StoreStats();
}


HRESULT SteamAPI::ScCallMethod(CScScript* Script, CScStack *Stack, CScStack *ThisStack, char *Name)
{
	if(strcmp(Name, "SetAchievement")==0){
		Stack->CorrectParams(1);

		char* achievement = Stack->Pop()->GetString();
		bool result = this->SetAchievement(achievement);
		Stack->PushBool(result);

		return S_OK;
	}

		
	return S_OK;
}

CScValue* SteamAPI::ScGetProperty(char *Name)
{
	m_ScValue->SetNULL();
	
	if(strcmp(Name, "Type")==0){
		m_ScValue->SetString("steam");
		return m_ScValue;
	}

	if(strcmp(Name, "AppId")==0){
		m_ScValue->SetInt(m_AppId);
		return m_ScValue;
	}

	if(strcmp(Name, "IsLogged")==0){
		m_ScValue->SetBool(m_LoggedIn);
		return m_ScValue;
	}


	return m_ScValue;
}

HRESULT SteamAPI::ScSetProperty(char *Name, CScValue *Value)
{
			return S_OK;
}


HRESULT SteamAPI::Persist(CBPersistMgr* PersistMgr)
{
	CBScriptable::Persist(PersistMgr);

	PersistMgr->Transfer(TMEMBER(m_Values));

	return S_OK;
}


char* SteamAPI::ScToString()
{
	static char Dummy[32768];
	strcpy(Dummy, "");
	char PropName[20];
	for(int i=0; i<m_Length; i++){
		sprintf(PropName, "%d", i);
		CScValue* val = m_Values->GetProp(PropName);
		if(val){
			if(strlen(Dummy) + strlen(val->GetString()) < 32768){
				strcat(Dummy, val->GetString());
			}
		}

		if(i<m_Length-1 && strlen(Dummy)+1 < 32768) strcat(Dummy, ",");
	}
	return Dummy;
}

