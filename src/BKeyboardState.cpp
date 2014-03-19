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
#include "BKeyboardState.h"


IMPLEMENT_PERSISTENT(CBKeyboardState, false);

//////////////////////////////////////////////////////////////////////////
CBKeyboardState::CBKeyboardState(CBGame* inGame):CBScriptable(inGame)
{
	m_CurrentPrintable = false;
	m_CurrentCharCode = 0;
	m_CurrentKeyData = 0;

	m_CurrentShift = false;
	m_CurrentAlt = false;
	m_CurrentControl = false;
}


//////////////////////////////////////////////////////////////////////////
CBKeyboardState::~CBKeyboardState()
{

}


//////////////////////////////////////////////////////////////////////////
// high level scripting interface
//////////////////////////////////////////////////////////////////////////
HRESULT CBKeyboardState::ScCallMethod(CScScript* Script, CScStack *Stack, CScStack *ThisStack, char *Name)
{
	//////////////////////////////////////////////////////////////////////////
	// IsKeyDown
	//////////////////////////////////////////////////////////////////////////
	if (strcmp(Name, "IsKeyDown")==0)
	{
		Stack->CorrectParams(1);
		CScValue* val = Stack->Pop();
		int vKey;

		if (val->m_Type==VAL_STRING && strlen(val->GetString())>0)
		{
			char* str = val->GetString();
			if(str[0]>='A' && str[0]<='Z') str[0] += ('a' - 'A');
			vKey = (int)str[0];
		}
		else vKey = val->GetInt();

    	const Uint8* state = SDL_GetKeyboardState(NULL);
		SDL_Scancode scanCode = SDL_GetScancodeFromKey(VKeyToKeyCode(vKey));
		bool isDown = state[scanCode] > 0;

		Stack->PushBool(isDown);
		return S_OK;
	}

	else return CBScriptable::ScCallMethod(Script, Stack, ThisStack, Name);
}



int CBKeyboardState::ConvertSDLCodeToWME(DWORD sdlCode)
{


	switch (sdlCode)
	{
		case SDLK_F1:
			return 112;
			break;
		case SDLK_F2:
			return 113;
			break;
		case SDLK_F3:
			return 114;
			break;
		case SDLK_F4:
			return 115;
			break;
		case SDLK_F5:
			return 116;
			break;
		case SDLK_F6:
			return 117;
			break;
		case SDLK_F7:
			return 118;
			break;
		case SDLK_F8:
			return 119;
			break;
		case SDLK_F9:
			return 120;
			break;
		case SDLK_F10:
			return 121;
			break;
		case SDLK_F11:
			return 122;
			break;
		case SDLK_F12:
			return 123;
			break;
// ARROWS
		case SDLK_LEFT:
			return 37;
			break;
		case SDLK_UP:
			return 38;
			break;
		case SDLK_RIGHT:
			return 39;
			break;
		case SDLK_DOWN:
			return 40;
			break;
// Numpad keys
		case SDLK_KP_0:
			return 96;
			break;
		case SDLK_KP_1:
			return 97;
			break;
		case SDLK_KP_2:
			return 98;
			break;
		case SDLK_KP_3:
			return 99;
			break;
		case SDLK_KP_4:
			return 100;
			break;
		case SDLK_KP_5:
			return 101;
			break;
		case SDLK_KP_6:
			return 102;
			break;
		case SDLK_KP_7:
			return 103;
			break;
		case SDLK_KP_8:
			return 104;
			break;
		case SDLK_KP_9:
			return 105;
			break;

// Silent keys
		case SDLK_BACKSPACE:
			return 8;
			break;
		case SDLK_TAB:
			return 9;
			break;
		case SDLK_SPACE:
			return 32;
			break;
		case SDLK_ESCAPE:
			return 27;
			break;
		case SDLK_LSHIFT:
			return 160;
			break; 
		case SDLK_RSHIFT:
			return 161;
			break;
		case SDLK_LCTRL:
			return 162;
			break; 
		case SDLK_RCTRL:
			return 163;
			break; 
		case SDLK_INSERT:
			return 45;
			break; 
		case SDLK_DELETE:
			return 46;
			break;
		case SDLK_HOME:
			return 36;
			break; 
		case SDLK_END:
			return 35;
			break;

	}

	return sdlCode;
}


char CBKeyboardState::ConvertWMEChars()
{
	char key[1];

	switch (m_CurrentCharCode)
	{
		case SDLK_KP_0:
			key[0] = '0';
			break;
		case SDLK_KP_1:
			key[0] = '1';
			break;
		case SDLK_KP_2:
			key[0] = '2';
			break;
		case SDLK_KP_3:
			key[0] = '3';
			break;
		case SDLK_KP_4:
			key[0] = '4';
			break;
		case SDLK_KP_5:
			key[0] = '5';
			break;
		case SDLK_KP_6:
			key[0] = '6';
			break;
		case SDLK_KP_7:
			key[0] = '7';
			break;
		case SDLK_KP_8:
			key[0] = '8';
			break;
		case SDLK_KP_9:
			key[0] = '9';
			break;
		default:
			key[0] = (char)m_CurrentCharCode;
			break;
	}

	return key[0];	
}

//////////////////////////////////////////////////////////////////////////
CScValue* CBKeyboardState::ScGetProperty(char *Name)
{
	m_ScValue->SetNULL();

	//////////////////////////////////////////////////////////////////////////
	// Type
	//////////////////////////////////////////////////////////////////////////
	if(strcmp(Name, "Type")==0){
		m_ScValue->SetString("keyboard");
		return m_ScValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// Key
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "Key")==0){
		if(m_CurrentPrintable){
			char key[2];
			key[0] = ConvertWMEChars();
			key[1] = '\0';
			m_ScValue->SetString(key);
		}
		else m_ScValue->SetString("");

		return m_ScValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// Printable
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "Printable")==0){
		m_ScValue->SetBool(m_CurrentPrintable);
		return m_ScValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// KeyCode
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "KeyCode")==0){
		m_ScValue->SetInt(ConvertSDLCodeToWME(m_CurrentCharCode));
		return m_ScValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// IsShift
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "IsShift")==0){
		m_ScValue->SetBool(m_CurrentShift);
		return m_ScValue;
	}
	//////////////////////////////////////////////////////////////////////////
	// IsAlt
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "IsAlt")==0){
		m_ScValue->SetBool(m_CurrentAlt);
		return m_ScValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// IsControl
	//////////////////////////////////////////////////////////////////////////
	else if(strcmp(Name, "IsControl")==0){
		m_ScValue->SetBool(m_CurrentControl);
		return m_ScValue;
	}

	else return CBScriptable::ScGetProperty(Name);
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBKeyboardState::ScSetProperty(char *Name, CScValue *Value)
{
	/*
	//////////////////////////////////////////////////////////////////////////
	// Name
	//////////////////////////////////////////////////////////////////////////
	if(strcmp(Name, "Name")==0){
		SetName(Value->GetString());
		if(m_Renderer) SetWindowText(m_Renderer->m_Window, m_Name);
		return S_OK;
	}

	else*/ return CBScriptable::ScSetProperty(Name, Value);
}


//////////////////////////////////////////////////////////////////////////
char* CBKeyboardState::ScToString()
{
	return "[keyboard state]";
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBKeyboardState::ReadKey(SDL_Event* event)
{
	m_CurrentPrintable = (event->type == SDL_TEXTINPUT);
	int code = KeyCodeToVKey(event);
	
	if (code != 0)
		m_CurrentCharCode = code; 
	//m_CurrentKeyData = KeyData;

	m_CurrentControl = IsControlDown();
	m_CurrentAlt     = IsAltDown();
	m_CurrentShift   = IsShiftDown();

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBKeyboardState::Persist(CBPersistMgr *PersistMgr)
{
	//if(!PersistMgr->m_Saving) Cleanup();
	CBScriptable::Persist(PersistMgr);

	PersistMgr->Transfer(TMEMBER(m_CurrentAlt));
	PersistMgr->Transfer(TMEMBER(m_CurrentCharCode));
	PersistMgr->Transfer(TMEMBER(m_CurrentControl));
	PersistMgr->Transfer(TMEMBER(m_CurrentKeyData));
	PersistMgr->Transfer(TMEMBER(m_CurrentPrintable));
	PersistMgr->Transfer(TMEMBER(m_CurrentShift));

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
bool CBKeyboardState::IsShiftDown()
{
	int mod = SDL_GetModState();
	return (mod & KMOD_LSHIFT) || (mod & KMOD_RSHIFT);
}	

//////////////////////////////////////////////////////////////////////////
bool CBKeyboardState::IsControlDown()
{
	int mod = SDL_GetModState();
	return (mod & KMOD_LCTRL) || (mod & KMOD_RCTRL);
}

//////////////////////////////////////////////////////////////////////////
bool CBKeyboardState::IsAltDown()
{
	int mod = SDL_GetModState();
	return (mod & KMOD_LALT) || (mod & KMOD_RALT);
}

//////////////////////////////////////////////////////////////////////////
DWORD CBKeyboardState::KeyCodeToVKey(SDL_Event* event)
{
	if (event->type != SDL_KEYDOWN) return 0;

	switch (event->key.keysym.sym)
	{
	case SDLK_KP_ENTER:
		return SDLK_RETURN;
	default:
		return event->key.keysym.sym;
	}
}

//////////////////////////////////////////////////////////////////////////
SDL_Keycode CBKeyboardState::VKeyToKeyCode(DWORD vkey)
{
	// todo
	return (SDL_Keycode)vkey;
}
