#ifndef CNODEPROPERTIES_H
#define CNODEPROPERTIES_H

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

class CNodePropertySheet : public PropertyDialog
{
public:
	DECLARE_CLASS_SIMPLE( CNodePropertySheet, PropertyDialog );

	CNodePropertySheet(CBaseNode *pNode, CNodeView *parent, const char *panelName);
	~CNodePropertySheet();

	CBaseNode *GetNode();

	virtual void ResetAllData();

	KeyValues *GetPropertyContainer();

protected:
	virtual bool OnOK(bool applyOnly);
	virtual void OnCancel();

	CBaseNode *n;
	KeyValues *pKV_NodeSettings;
	KeyValues *pKV_NodeSettings_Original;

	CNodeView *pNodeView;

private:
	CNodePropertySheet( const CNodePropertySheet &other );
};


#endif