/*
 ============================================================================
 Name		: BckgrndClientAppView.cpp
 Author	  : Oleg Ziakun
 Copyright   : Oleg Ziakun
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "BckgrndClientAppView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBckgrndClientAppView* CBckgrndClientAppView::NewL(const TRect& aRect)
	{
	CBckgrndClientAppView* self = CBckgrndClientAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBckgrndClientAppView* CBckgrndClientAppView::NewLC(const TRect& aRect)
	{
	CBckgrndClientAppView* self = new (ELeave) CBckgrndClientAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBckgrndClientAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	// Activate the window, which makes it ready to be drawn
	ActivateL();
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::CBckgrndClientAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBckgrndClientAppView::CBckgrndClientAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::~CBckgrndClientAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBckgrndClientAppView::~CBckgrndClientAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CBckgrndClientAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.Clear(drawRect);

	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CBckgrndClientAppView::SizeChanged()
	{
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CBckgrndClientAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CBckgrndClientAppView::HandlePointerEventL(
		const TPointerEvent& aPointerEvent)
	{

	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

// End of File
