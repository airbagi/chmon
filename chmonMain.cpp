/***************************************************************
 * Name:      chmonMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Zend (airbagi@mail.ru)
 * Created:   2019-02-09
 * Copyright: Zend (airbagi.ru)
 * License:
 **************************************************************/


#include "chmonMain.h"
#include <wx/msgdlg.h>
#include <wx/log.h>
#include "about.h"

//(*InternalHeaders(chmonDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
  {
  short_f, long_f
  };

wxString wxbuildinfo(wxbuildinfoformat format)
  {
  wxString wxbuild(wxVERSION_STRING);
  if (format == long_f )
    {
#if defined(__WXMSW__)
    wxbuild << _T("-Windows");
#elif defined(__UNIX__)
    wxbuild << _T("-Linux");
#endif
#if wxUSE_UNICODE
    wxbuild << _T("-Unicode build");
#else
    wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }
  return wxbuild;
  }

//(*IdInit(chmonDialog)
const long chmonDialog::ID_STATICTEXT1 = wxNewId();
const long chmonDialog::ID_BUTTON2 = wxNewId();
const long chmonDialog::ID_TEXTCTRL1 = wxNewId();
const long chmonDialog::ID_BUTTON1 = wxNewId();
const long chmonDialog::ID_STATICTEXT2 = wxNewId();
const long chmonDialog::ID_BUTTON3 = wxNewId();
const long chmonDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(chmonDialog,wxDialog)
  //(*EventTable(chmonDialog)
  //*)
END_EVENT_TABLE()

chmonDialog::chmonDialog(wxWindow* parent,wxWindowID id)
  {
  //(*Initialize(chmonDialog)
  wxFlexGridSizer* FlexGridSizer1;

  Create(parent, id, _("CHMon"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
  FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
  m_lblMain = new wxStaticText(this, ID_STATICTEXT1, _("Changes Monitor Application:"), wxDefaultPosition, wxSize(469,13), wxALIGN_LEFT, _T("ID_STATICTEXT1"));
  FlexGridSizer1->Add(m_lblMain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  m_btnSelectFile = new wxButton(this, ID_BUTTON2, _("Select File:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
  FlexGridSizer1->Add(m_btnSelectFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  m_txtAll = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(437,435), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  wxFont m_txtAllFont = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);
  if ( !m_txtAllFont.Ok() ) m_txtAllFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
  m_txtAll->SetFont(m_txtAllFont);
  FlexGridSizer1->Add(m_txtAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  Button1 = new wxButton(this, ID_BUTTON1, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
  FlexGridSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  m_lblTime = new wxStaticText(this, ID_STATICTEXT2, _("..."), wxDefaultPosition, wxSize(395,13), wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
  FlexGridSizer1->Add(m_lblTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  m_btnAbout = new wxButton(this, ID_BUTTON3, _("About..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
  FlexGridSizer1->Add(m_btnAbout, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  SetSizer(FlexGridSizer1);
  m_dlgFileOpen = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
  m_tmMain.SetOwner(this, ID_TIMER1);
  m_tmMain.Start(10, false);
  FlexGridSizer1->Fit(this);
  FlexGridSizer1->SetSizeHints(this);

  Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&chmonDialog::Onm_btnSelectFileClick);
  Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&chmonDialog::OnQuit);
  Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&chmonDialog::Onm_btnAboutClick);
  Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&chmonDialog::Onm_tmMainTrigger);
  //*)
  }

chmonDialog::~chmonDialog()
  {
  //(*Destroy(chmonDialog)
  //*)
  }

void chmonDialog::OnQuit(wxCommandEvent& event)
  {
  Close();
  }

void chmonDialog::OnAbout(wxCommandEvent& event)
  {
  wxString msg = wxbuildinfo(long_f);
  wxMessageBox(msg, _("Welcome to..."));
  }

void chmonDialog::Onm_btnSelectFileClick(wxCommandEvent& event)
  {
  if (m_dlgFileOpen->ShowModal()== wxID_OK )
    {
    m_strFileName = m_dlgFileOpen->GetPath();
    wxString strLblTxt =strLblTxt.Format(_("Monitoring... %s"),m_strFileName.GetFullName());
    m_lblMain->SetLabel(strLblTxt);
    m_lDateTime = m_strFileName.GetModificationTime();
    m_lblTime->SetLabel( m_lDateTime.FormatISOCombined(' '));
    ReadModifiedFile();
    }
  }

void chmonDialog::ReadModifiedFile()
  {
  if (!m_file.IsOpened())
    {
    if (!m_file.Open(m_strFileName.GetFullPath()))
      {
      m_lblMain->SetLabel(_("error opening file"));
      }
    m_file.Seek(0);
    DWORD flen = m_file.Length();
    // if file length==0 then wait 100ms
    if (0==flen)
      {
      Sleep(100);
      flen = m_file.Length();
      }
    BYTE *buf = new BYTE[flen];
    m_file.Read(buf,flen);
    m_file.Close();
    //
    CopyModifiedFile(buf, flen);
    //
    m_txtAll->Clear();
    wxString strFileData = wxEmptyString;
    for (int i=0; i<flen; i++)
      {
      strFileData += wxString::Format("%02X", buf[i]);
      if (0 == ((i+1) % 0x10))
        strFileData += "\n";
      else
        strFileData += " ";
      }
    m_txtAll->SetValue(strFileData);
    //
    delete [] buf;
    //
    }
  }

void chmonDialog::Onm_tmMainTrigger(wxTimerEvent& event)
  {
  if (!m_strFileName.IsOk())
    {
    m_lblTime->SetLabel("...");
    return;
    }
  wxDateTime dt = m_strFileName.GetModificationTime();
  if (dt != m_lDateTime)
    {
    m_lDateTime = m_strFileName.GetModificationTime();
    //
    ReadModifiedFile();
    //
    m_lblTime->SetLabel( m_lDateTime.FormatISOCombined(' '));
    }
  }


void chmonDialog::CopyModifiedFile(BYTE * buf, DWORD dwLen)
  {
  wxString strPath, strName, strExt, strVol;
  wxFileName filename;
  strName = m_strFileName.GetName()+ m_lDateTime.Format(_T("%d_%m_%Y_%H_%M_%S"));
  filename.Assign(m_strFileName.GetVolume(), m_strFileName.GetPath(),strName, m_strFileName.GetExt(), 1);
  wxFile afile;
  afile.Open(filename.GetFullPath(), wxFile::write);
  afile.Write(buf, dwLen);
  afile.Close();
  }

void chmonDialog::Onm_btnAboutClick(wxCommandEvent& event)
  {
  wxDialog* pDlg = new about(this);
  pDlg->ShowModal();
  pDlg->Destroy();
  delete pDlg;
  }
