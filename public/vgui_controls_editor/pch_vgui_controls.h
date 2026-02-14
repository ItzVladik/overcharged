//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PCH_VGUI_CONTROLS_H
#define PCH_VGUI_CONTROLS_H

#ifdef _WIN32
#pragma once
#endif

// general includes
#include <ctype.h>
#include <stdlib.h>
#include "tier0/dbg.h"
#include "tier0/valve_off.h"
#include "tier1/KeyValues.h"

#include "tier0/valve_on.h"
#include "tier0/memdbgon.h"

#include "filesystem.h"
#include "tier0/validator.h"

// vgui includes
#include "vgui/IBorder.h"
#include "vgui/IInput.h"
#include "vgui/ILocalize.h"
#include "vgui/IPanel.h"
#include "vgui/IScheme.h"
#include "vgui/ISurface.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"
#include "vgui/KeyCode.h"
#include "vgui/Cursor.h"
#include "vgui/MouseCode.h"

// vgui controls includes
#include "vgui_controls_editor/controls.h"

#include "vgui_controls_editor/animatingimagepanel.h"
#include "vgui_controls_editor/animationcontroller.h"
#include "vgui_controls_editor/bitmapimagepanel.h"
#include "vgui_controls_editor/buildgroup.h"
#include "vgui_controls_editor/buildmodedialog.h"
#include "vgui_controls_editor/button.h"
#include "vgui_controls_editor/checkbutton.h"
#include "vgui_controls_editor/checkbuttonlist.h"
#include "vgui_controls_editor/combobox.h"
#include "vgui_controls_editor/controls.h"
#include "vgui_controls_editor/dialogmanager.h"
#include "vgui_controls_editor/directoryselectdialog.h"
#include "vgui_controls_editor/divider.h"
#include "vgui_controls_editor/editablepanel.h"
#include "vgui_controls_editor/fileopendialog.h"
#include "vgui_controls_editor/focusnavgroup.h"
#include "vgui_controls_editor/frame.h"
#include "vgui_controls_editor/graphpanel.h"
#include "vgui_controls_editor/html.h"
#include "vgui_controls_editor/image.h"
#include "vgui_controls_editor/imagelist.h"
#include "vgui_controls_editor/imagepanel.h"
#include "vgui_controls_editor/label.h"
#include "vgui_controls_editor/listpanel.h"
#include "vgui_controls_editor/listviewpanel.h"
#include "vgui_controls_editor/menu.h"
#include "vgui_controls_editor/menubar.h"
#include "vgui_controls_editor/menubutton.h"
#include "vgui_controls_editor/menuitem.h"
#include "vgui_controls_editor/messagebox.h"
#include "vgui_controls_editor/panel.h"
#ifndef HL1
#include "vgui_controls_editor/panelanimationvar.h"
#endif
#include "vgui_controls_editor/panellistpanel.h"
#include "vgui_controls_editor/phandle.h"
#include "vgui_controls_editor/progressbar.h"
#include "vgui_controls_editor/progressbox.h"
#include "vgui_controls_editor/propertydialog.h"
#include "vgui_controls_editor/propertypage.h"
#include "vgui_controls_editor/propertysheet.h"
#include "vgui_controls_editor/querybox.h"
#include "vgui_controls_editor/radiobutton.h"
#include "vgui_controls_editor/richtext.h"
#include "vgui_controls_editor/scrollbar.h"
#include "vgui_controls_editor/scrollbarslider.h"
#include "vgui_controls_editor/sectionedlistpanel.h"
#include "vgui_controls_editor/slider.h"
#ifndef HL1
#include "vgui_controls_editor/splitter.h"
#endif
#include "vgui_controls_editor/textentry.h"
#include "vgui_controls_editor/textimage.h"
#include "vgui_controls_editor/togglebutton.h"
#include "vgui_controls_editor/tooltip.h"
#ifndef HL1
#include "vgui_controls_editor/toolwindow.h"
#endif
#include "vgui_controls_editor/treeview.h"
#ifndef HL1
#include "vgui_controls_editor/treeviewlistcontrol.h"
#endif
#include "vgui_controls_editor/urllabel.h"
#include "vgui_controls_editor/wizardpanel.h"
#include "vgui_controls_editor/wizardsubpanel.h"

#ifndef HL1
#include "vgui_controls_editor/keyboardeditordialog.h"
#include "vgui_controls_editor/inputdialog.h"
#endif

#endif // PCH_VGUI_CONTROLS_H
