#include "about.h"
#include <wx/mstream.h>

//(*InternalHeaders(about)
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(about)
const long about::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(about,wxDialog)
  //(*EventTable(about)
  //*)
END_EVENT_TABLE()

const long about::ID_ANIMATIONCTRL1 = wxNewId();

about::about(wxWindow* parent,wxWindowID id)
  {
  //(*Initialize(about)
  wxBoxSizer* m_boxAni;
  wxFlexGridSizer* FlexGridSizer1;
  wxStdDialogButtonSizer* StdDialogButtonSizer1;
  Create(parent, wxID_ANY, _("About ChMon"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(497,554));
  FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
  StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Changes Monitor Utility (c) Zend, 2019"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
  FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  m_boxAni = new wxBoxSizer(wxHORIZONTAL);
  FlexGridSizer1->Add(m_boxAni, 1, wxALL|wxEXPAND, 5);
  StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
  StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
  StdDialogButtonSizer1->Realize();
  FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  SetSizer(FlexGridSizer1);
  SetSizer(FlexGridSizer1);
  Layout();
  //*)
  const void* data = NULL;
  size_t outLen = 0;
  m_ani = new wxAnimationCtrl(this, ID_ANIMATIONCTRL1, wxNullAnimation, wxPoint(0,0), wxSize(291,291), wxAC_DEFAULT_STYLE, _T("ID_ANIMATIONCTRL1"));
  // load the icon directory resource
  if ( !wxLoadUserResource(&data, &outLen, "ID_ANIM", RT_RCDATA) )
    {
    wxLogError(_("Failed to load icons from resource"));
    }
  else
    {
    wxMemoryInputStream stream(data, outLen);
    if (m_ani->Load(stream))
      m_ani->Play();
    }
  //
  m_boxAni->Add(m_ani);
  Fit();
  Layout();
  }

about::~about()
  {
  //(*Destroy(about)
  //*)
  }

