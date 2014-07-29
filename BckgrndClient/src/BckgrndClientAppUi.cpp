/*
 ============================================================================
 Name		: BckgrndClientAppUi.cpp
 Author	     : Oleg Ziakun
 Copyright   : Oleg Ziakun
 Description : CBckgrndClientAppUi implementation
 ============================================================================
 */
// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <hlplch.h>
#include <BckgrndClient_0xE7ADC8DC.rsg>
#include "BckgrndClient.hrh"
#include "BckgrndClient.pan"
#include "BckgrndClientApplication.h"
#include "BckgrndClientAppUi.h"
#include "BckgrndClientAppView.h"

void CBckgrndClientAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = CBckgrndClientAppView::NewL(ClientRect());
	}

CBckgrndClientAppUi::CBckgrndClientAppUi()
	{
	}

CBckgrndClientAppUi::~CBckgrndClientAppUi()
	{
	if (iAppView)
		{
		delete iAppView;
		iAppView = NULL;
		}
	}

void CBckgrndClientAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			
			if (iClientStarter)
				{
				delete iClientStarter;
				}
			
			Exit();
			break;

		case ECommand1:
			{
			iClientStarter = CClientStarter::NewL();
			}
			break;
		case ECommand2:
			{
			if (iClientStarter)
				{
				delete iClientStarter;
				iClientStarter = NULL;
				}
			}
			break;
		case EHelp:
			{
			_LIT(KHelp,"Help");
			_LIT(KHelpMsg,"Choose \"Start client\" to start client\ and \"Stop client\" to stop client :)");

			RunDialog(KHelp, KHelpMsg);
			}
			break;
		case EAbout:
			{
			_LIT(KAbout,"About");
			_LIT(KAboutMsg,"Test task written by Oleg Ziakun");

			RunDialog(KAbout, KAboutMsg);
			}
			break;
		default:
			Panic(EBckgrndClientUi);
			break;
		}
	}

void CBckgrndClientAppUi::RunDialog(const TDesC& aTitle, const TDesC& aMsg)
	{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	dlg->QueryHeading()->SetTextL(aTitle);
	dlg->SetMessageTextL(aMsg);
	dlg->RunLD();
	}

void CBckgrndClientAppUi::HandleStatusPaneSizeChange()
	{
	iAppView->SetRect(ClientRect());
	}
