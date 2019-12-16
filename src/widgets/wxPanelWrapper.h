//
//  wxPanelWrapper.h
//  Audacity
//
//  Created by Paul Licameli on 6/25/16.
//
//

#ifndef __AUDACITY_WXPANEL_WRAPPER__
#define __AUDACITY_WXPANEL_WRAPPER__

#include "../MemoryX.h"
#include <wx/panel.h> // to inherit
#include <wx/dialog.h> // to inherit

#include "../Internat.h"

#include "audacity/Types.h"

void wxTabTraversalWrapperCharHook(wxKeyEvent &event);

template <typename Base>
class AUDACITY_DLL_API wxTabTraversalWrapper : public Base
{
public:
   template <typename... Args>
   wxTabTraversalWrapper(Args&&... args)
   : Base( std::forward<Args>(args)... )
   {
      this->Bind(wxEVT_CHAR_HOOK, wxTabTraversalWrapperCharHook);
   }

   wxTabTraversalWrapper(const wxTabTraversalWrapper&) = delete;
   wxTabTraversalWrapper& operator=(const wxTabTraversalWrapper&) = delete;
   wxTabTraversalWrapper(wxTabTraversalWrapper&&) = delete;
   wxTabTraversalWrapper& operator=(wxTabTraversalWrapper&&) = delete;

};

class AUDACITY_DLL_API wxPanelWrapper : public wxTabTraversalWrapper<wxPanel>
{
public:
   // Constructors
   wxPanelWrapper() {}

   wxPanelWrapper(
         wxWindow *parent,
         wxWindowID winid = wxID_ANY,
         const wxPoint& pos = wxDefaultPosition,
         const wxSize& size = wxDefaultSize,
         long style = wxTAB_TRAVERSAL | wxNO_BORDER,
         // Important:  default window name localizes!
         const TranslatableString& name = XO("Panel"))
   : wxTabTraversalWrapper<wxPanel> (
      parent, winid, pos, size, style, name.Translation() )
   {}

    // Pseudo ctor
    bool Create(
         wxWindow *parent,
         wxWindowID winid = wxID_ANY,
         const wxPoint& pos = wxDefaultPosition,
         const wxSize& size = wxDefaultSize,
         long style = wxTAB_TRAVERSAL | wxNO_BORDER,
         // Important:  default window name localizes!
         const TranslatableString& name = XO("Panel"))
   {
      return wxTabTraversalWrapper<wxPanel>::Create(
         parent, winid, pos, size, style, name.Translation()
      );
   }
   // overload and hide the inherited functions that take naked wxString:
   void SetLabel(const TranslatableString & label);
   void SetName(const TranslatableString & name);
   void SetToolTip(TranslatableString toolTip);
   // Set the name to equal the label:
   void SetName();
};

class AUDACITY_DLL_API wxDialogWrapper : public wxTabTraversalWrapper<wxDialog>
{
public:
   // Constructors
   wxDialogWrapper() {}

   // Constructor with no modal flag - the new convention.
   wxDialogWrapper(
      wxWindow *parent, wxWindowID id,
      const TranslatableString& title,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      long style = wxDEFAULT_DIALOG_STYLE,
      // Important:  default window name localizes!
      const wxString& name = _("Dialog"))
   : wxTabTraversalWrapper<wxDialog>
      ( parent, id, title.Translation(), pos, size, style, name )
   {}

   // Pseudo ctor
   bool Create(
      wxWindow *parent, wxWindowID id,
      const TranslatableString& title,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      long style = wxDEFAULT_DIALOG_STYLE,
      // Important:  default window name localizes!
      const wxString& name = _("Dialog"))
   {
      return wxTabTraversalWrapper<wxDialog>::Create(
         parent, id, title.Translation(), pos, size, style, name
      );
   }

   // overload and hide the inherited functions that take naked wxString:
   void SetTitle(const TranslatableString & title);
   void SetLabel(const TranslatableString & title);
   void SetName(const TranslatableString & title);
   // Set the name to equal the title:
   void SetName();
};

#include <wx/dirdlg.h> // to inherit

class AUDACITY_DLL_API wxDirDialogWrapper : public wxTabTraversalWrapper<wxDirDialog>
{
public:
   // Constructor with no modal flag - the new convention.
   wxDirDialogWrapper(
      wxWindow *parent,
      const wxString& message = _("Select a directory"),
      const wxString& defaultPath = {},
      long style = wxDD_DEFAULT_STYLE,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      // Important:  default window name localizes!
      const wxString& name = _("Directory Dialog"))
   : wxTabTraversalWrapper<wxDirDialog>
      ( parent, message, defaultPath, style, pos, size, name )
   {}

   // Pseudo ctor
   void Create(
      wxWindow *parent,
      const wxString& message = _("Select a directory"),
      const wxString& defaultPath = {},
      long style = wxDD_DEFAULT_STYLE,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      // Important:  default window name localizes!
      const wxString& name = _("Directory Dialog"))
   {
      wxTabTraversalWrapper<wxDirDialog>::Create(
         parent, message, defaultPath, style, pos, size, name
      );
   }
};

#include "../lib-src/FileDialog/FileDialog.h"

class AUDACITY_DLL_API FileDialogWrapper : public wxTabTraversalWrapper<FileDialog>
{
public:
   FileDialogWrapper() {}

   // Constructor with no modal flag - the new convention.
   FileDialogWrapper(
      wxWindow *parent,
      const wxString& message = _("Select a file"),
      const FilePath& defaultDir = {},
      const FilePath& defaultFile = {},
      const wxString& wildCard = wxFileSelectorDefaultWildcardStr,
      long style = wxFD_DEFAULT_STYLE,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& sz = wxDefaultSize,
      // Important:  default window name localizes!
      const wxString& name = _("File Dialog"))
   : wxTabTraversalWrapper<FileDialog>
   ( parent, message, defaultDir, defaultFile, wildCard, style, pos, sz, name )
   {}

   // Pseudo ctor
   void Create(
      wxWindow *parent,
      const wxString& message = _("Select a file"),
      const FilePath& defaultDir = {},
      const FilePath& defaultFile = {},
      const wxString& wildCard = wxFileSelectorDefaultWildcardStr,
      long style = wxFD_DEFAULT_STYLE,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& sz = wxDefaultSize,
      // Important:  default window name localizes!
      const wxString& name = _("File Dialog"))
   {
      wxTabTraversalWrapper<FileDialog>::Create(
         parent, message, defaultDir, defaultFile, wildCard, style, pos, sz, name
      );
   }
};

#include <wx/msgdlg.h>

/**************************************************************************//**

\brief Wrap wxMessageDialog so that caption IS translatable.
********************************************************************************/
class AudacityMessageDialog : public wxTabTraversalWrapper< wxMessageDialog >
{
public:
    AudacityMessageDialog(
         wxWindow *parent,
         const wxString& message,
         const wxString& caption, // don't use = wxMessageBoxCaptionStr,
         long style = wxOK|wxCENTRE,
         const wxPoint& pos = wxDefaultPosition)
   : wxTabTraversalWrapper< wxMessageDialog>
      ( parent, message, caption, style, pos )
   {}
};

#endif
