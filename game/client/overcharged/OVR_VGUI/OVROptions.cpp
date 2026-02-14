//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
//#include "BasePanel.h"
#include "OVROptions.h"

#include "vgui_controls/Button.h"
#include "vgui_controls/CheckButton.h"
#include "vgui_controls/PropertySheet.h"
#include "vgui_controls/Label.h"
#include "vgui_controls/QueryBox.h"
#include "vgui_controls/Slider.h"
#include "vgui_controls/TextEntry.h"
#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"
#include "overcharged/OVR_VGUI/DataParser.h"
#include "tier1/convar.h"
#include "KeyValues.h"
#include "filesystem.h"


using namespace vgui;

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>
ConVar cl_NewMenu("cl_NewMenu", "0", FCVAR_CLIENTDLL, "Sets the state of advanced options <state>");

void COVROptions::InitialManifest()
{
	KeyValues *m_pMenuManifest = new KeyValues("MenuManifest");
	const char *manifestPath = "resource/OVR_UI/UI_Manifest.txt";

	if (m_pMenuManifest->LoadFromFile(filesystem, manifestPath))
	{

		while (m_pMenuManifest)
		{
			FOR_EACH_SUBKEY(m_pMenuManifest, pClassname)
			{
				auto pPageMainName = pClassname->GetName();
				auto pPageLocName = pClassname->GetString();

				InitialPage(pPageMainName, pPageLocName);
				cvarStructs.clear();
			}
			m_pMenuManifest = m_pMenuManifest->GetNextKey();

			if (m_pMenuManifest == NULL)
				break;
		}
	}
	m_pMenuManifest->deleteThis();
	m_pMenuManifest = nullptr;
}

void COVROptions::InitialPage(/*COVRCommonPage *pPage, */const char *pPageMainName, const char *pPageLocName)
{
	KeyValues *m_pMenuScheme = new KeyValues("MenuScheme");

	char filename[FILENAME_MAX];

	V_snprintf(filename, sizeof(filename), "resource/OVR_UI/%s.res", pPageMainName);

	if (m_pMenuScheme->LoadFromFile(filesystem, filename))
	{
		while (m_pMenuScheme)
		{
			FOR_EACH_SUBKEY(m_pMenuScheme, pClassname)
			{
				//auto name = pClassname->GetName();

				auto fVal = pClassname->GetFirstValue();
				if (fVal)
				{	
					auto elemName = fVal->GetString();
					if (!CheckIsTemplate(elemName)) continue;
				}

				//if (CheckIsTemplate(name)) continue;

				//MakeStruct
				ConVarList cvarStruct;

				FOR_EACH_VALUE(pClassname, pSubValue)
				{
					//Set element type by enum
					if (FStrEq(pSubValue->GetName(), "ControlName"))
					{
						if (FStrEq(pSubValue->GetString(), "CheckButton"))
						{
							cvarStruct.eType = _CBOX;
						}
						if (FStrEq(pSubValue->GetString(), "Slider"))
						{
							cvarStruct.eType = _SLIDER;
						}
						if (FStrEq(pSubValue->GetString(), "TextEntry"))
						{
							cvarStruct.eType = _TEXT;
						}
					}

					//Set convar name
					if (FStrEq(pSubValue->GetName(), "fieldName"))
					{
						cvarStruct.cvarName = pSubValue->GetString();
					}
					//Set localization name
					if (FStrEq(pSubValue->GetName(), "labelText"))
					{
						cvarStruct.resName = pSubValue->GetString();
					}
					//Set localization name
					if (FStrEq(pSubValue->GetName(), "linkedCommands"))
					{
						CUtlVector<char*, CUtlMemory<char*> > arr;

						V_SplitString(pSubValue->GetString(), ",", arr);

						for (int i = 0; i < arr.Count(); i++)
						{
							const char *name = arr.Element(i);

							if (name[0] == '!')
							{
								char newName[256];

								V_StrRight(name, V_strlen(name)-1, newName, sizeof(newName));

								cvarStruct.pLinkedCommandNegate.push_back(true);

								cvarStruct.pLinkedCommands.push_back(newName);
							}
							else
							{
								cvarStruct.pLinkedCommandNegate.push_back(false);

								cvarStruct.pLinkedCommands.push_back(name);
							}
						}
					}

					switch (cvarStruct.eType)
					{
						case _SLIDER: //Set slider range
						{
							if (FStrEq(pSubValue->GetName(), "rightText"))
							{
								cvarStruct.iRangeMax = pSubValue->GetFloat();
							}

							if (FStrEq(pSubValue->GetName(), "leftText"))
							{
								cvarStruct.iRangeMin = pSubValue->GetFloat();
							}

							if (FStrEq(pSubValue->GetName(), "divider"))
							{
								cvarStruct.divider = pSubValue->GetFloat();
							}
						}
						break;
						default:
						{
							cvarStruct.iRangeMin = 0.f;
							cvarStruct.iRangeMax = 0.f;
						}
						break;

						/*case _CBOX:
						{
							cvarStruct.iRangeMin = 0.f;
							cvarStruct.iRangeMax = 0.f;
						}
						break;
						case _INT:
						{

						}
						break;
						case _TEXT:
						{

						}
						break;*/
					}
				}

				//pPage->FillGrid(...);

				cvarStructs.push_back(cvarStruct);

				//pPage->FillGrid(cvarStruct);

			}

			m_pMenuScheme = m_pMenuScheme->GetNextKey();

			if (m_pMenuScheme == NULL)
				break;
		}
	}

	/*cvarStructsArr.push_back(cvarStructs);

	pagesNames.push_back(pPageMainName);
	pagesLocNames.push_back(pPageLocName);

	auto button = new COVRCommonButton(this, "pPageMainName", "#GameUI_AdvancedEllipsis");
	button->RefPage = pPageMainName;

	if (_idx2 == 0)
		button->SetPos(200, 300);
	if (_idx2 == 1)
		button->SetPos(30, 40);
	if (_idx2 == 2)
		button->SetPos(40, 50);
	if (_idx2 == 2)
		button->SetPos(50, 60);
	if (_idx2 == 2)
		button->SetPos(70, 80);
	if (_idx2 == 2)
		button->SetPos(90, 100);

	pButtons.push_back(button);
	button->SetCommand(new KeyValues(pPageMainName));

	_idx2++;*/



	auto pPage = new COVRCommonPage(this, pPageMainName, cvarStructs);
	AddPage(pPage, pPageLocName);
	pPages.AddToTail(pPage);



	m_pMenuScheme->deleteThis();
	m_pMenuScheme = nullptr;
}

void COVROptions::SavePagesInfo()
{
	for ( int i = 0; i < pPages.Count(); i++ )
	{
		auto page = pPages[i];
		page->SavePageInfo(cvarStructs);
	}
}

void COVROptions::UpdatePagesInfo()
{
	for ( int i = 0; i < pPages.Count(); i++ )
	{
		auto page = pPages[i];
		page->UpdatePageInfo();
	}
}

/*bool GetShadowsValue(void)
{
	// Now grab the hl2/cfg/config.cfg and suss out the sv_unlockedchapters cvar to estimate how far they got in HL2

	char fullpath[MAX_PATH];
	g_pFullFileSystem->RelativePathToFullPath("cfg/config.cfg", "GAME", fullpath, sizeof(fullpath));
	Q_FixSlashes(fullpath, '/');

	if (filesystem->FileExists(fullpath))
	{
		FileHandle_t fh = filesystem->Open(fullpath, "rb");
		if (FILESYSTEM_INVALID_HANDLE != fh)
		{
			// read file into memory
			int size = filesystem->Size(fh);
			char *configBuffer = new char[size + 1];
			filesystem->Read(configBuffer, size, fh);
			configBuffer[size] = 0;
			filesystem->Close(fh);

			// loop through looking for all the cvars to apply
			const char *search = Q_stristr(configBuffer, "oc_enable_global_illumination");
			if (search)
			{
				// read over the token
				search = strtok((char *)search, " \n");
				search = strtok(NULL, " \n");

				if (search[0] == '\"')
					++search;

				// read the value
				int iValue = Q_atoi(search);
				oc_enable_global_illumination.SetValue(iValue);
			}
			cl_NewMenu.GetDefault();
			// free
			delete[] configBuffer;
		}
	}

	return true;
}*/

void SaveSizeToFile( int a, int b )
{
	KeyValues *kv = new KeyValues( "Size" );
	kv->SetInt( "wide", a  );
	kv->SetInt(	"tall", b );

	kv->SaveToFile( g_pFullFileSystem, "cfg/settings.txt", "MOD" );
}


int GetValueFromKV( const char *key )
{
	int val = -1;

	KeyValues *kv = new KeyValues( "Size" );
	if ( kv )
	{
		if ( kv->LoadFromFile(g_pFullFileSystem, "cfg/settings.txt") )
		{
			for ( KeyValues *control = kv->GetFirstSubKey(); control != NULL; control = control->GetNextKey() )
			{	
				if ( !Q_strcasecmp( control->GetName(), key ) )
				{	
					val = control->GetInt();
				}
			}			
		}
		kv->deleteThis();
	}
	return val;
}

//-----------------------------------------------------------------------------
// Purpose: Basic help dialog
//-----------------------------------------------------------------------------
COVROptions::COVROptions(vgui::Panel *parent) : PropertyDialog(parent, "OVROptionsDialog")
{
	InitialManifest();

	SetDeleteSelfOnClose(true);

	//vgui::ivgui()->AddTickSignal(GetVPanel(), 30);


	SetSize( GetValueFromKV( "wide" ), GetValueFromKV("tall") );
	int wide, tall;
	GetSize(wide, tall);
	SetSizeable(true);//true

	SetTitle("#GameUI_OVROptions", true);
	SetCancelButtonVisible( false );

	SetAlpha(1);

	SetApplyButtonVisible(true);
	GetPropertySheet()->SetTabWidth(84);

	pDefButton = new COVRCommonButton(this, "OVRDefButton", "#GameUI_DefButton");
	if (pDefButton)
	{
		pDefButton->SetPinCorner(PIN_BOTTOMLEFT, 8, -10);
		pDefButton->UpdateSiblingPin();
		OnSizeChanged(wide, tall);
	}
}

void COVROptions::PerformLayout()
{
	BaseClass::PerformLayout();
}

void COVROptions::OnTick()
{
	PerformLayout();
	BaseClass::OnTick();
}

void COVROptions::OnSizeChanged(int newWide, int newTall)
{
	SaveSizeToFile( newWide, newTall );
	BaseClass::OnSizeChanged(newWide, newTall);
}
//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
COVROptions::~COVROptions()
{
}

//-----------------------------------------------------------------------------
// Purpose: Brings the dialog to the fore
//-----------------------------------------------------------------------------
void COVROptions::Activate()
{
	BaseClass::Activate();
	EnableApplyButton(true);
}

//-----------------------------------------------------------------------------
// Purpose: Opens the dialog
//-----------------------------------------------------------------------------
void COVROptions::Run()
{
	SetTitle("#GameUI_OVROptions", true);
	Activate();
}

void COVROptions::SpawnPage(const char* pPageMainName)
{
	/*int i;
	for (i = 0; i < (int)pagesNames.size(); i++)
	{
		if (FStrEq(pagesNames.at(i), pPageMainName))
			break;
	}

	auto cvarStructs = cvarStructsArr.at(i);
	auto locName = pagesLocNames.at(i);

	auto pPage = new COVRCommonPage(this, pPageMainName, cvarStructs);
	AddPage(pPage, locName);
	pPages.push_back(pPage);*/

}

void COVROptions::OnCommand(const char* pcCommand)
{
	//BaseClass::OnCommand(pcCommand);
	/*if ((bool)pButtons.size())
	{
		for each (auto button in pButtons)
		{
			if (FStrEq(pcCommand, button->GetName()))
			{
				SpawnPage(pcCommand);
			}
		}
	}*/


	if (!Q_stricmp(pcCommand, "PressButton"))
	{
		engine->ClientCmd("OffAdvOptions");
	}
	if (!Q_stricmp(pcCommand, "Cancel"))
	{
		engine->ClientCmd("OffAdvOptions");
	}
	if (!Q_stricmp(pcCommand, "OK"))
	{
		SavePagesInfo();

		engine->ClientCmd("OffAdvOptions");
	}
	if (!Q_stricmp(pcCommand, "Apply"))
	{
		SavePagesInfo();
	}
	/*if (!Q_stricmp(pcCommand, "Default"))
	{
		char filename[FILENAME_MAX];

		Q_snprintf(filename, sizeof(filename), "exec %s", cvar->FindVar("oc_config_default_preset")->GetString());

		engine->ClientCmd(filename);
	}*/
	if (!Q_stricmp(pcCommand, "Close"))
	{
		engine->ClientCmd("OffAdvOptions");
	}
}
