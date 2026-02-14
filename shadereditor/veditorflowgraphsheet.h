#ifndef C_EDITOR_FG_SHEET_H
#define C_EDITOR_FG_SHEET_H

#include "vsheets.h"

#include "vgui_controls_editor/controls.h"
#include <vgui_controls_editor/propertydialog.h>
#include <vgui_controls_editor/propertysheet.h>
#include <vgui_controls_editor/propertypage.h>
#include <vgui_controls_editor/textentry.h>
#include <vgui_controls_editor/checkbutton.h>
#include <vgui_controls_editor/slider.h>
#include <vgui_controls_editor/combobox.h>
#include <vgui_controls_editor/panellistpanel.h>

class CFlowGraphSheet : public PropertySheet
{
public:
	DECLARE_CLASS_SIMPLE( CFlowGraphSheet, PropertySheet );

	CFlowGraphSheet( Panel *parent, const char *panelName, bool draggableTabs, bool closeableTabs );
	~CFlowGraphSheet();

protected:
   virtual void PerformLayout();

};


#endif