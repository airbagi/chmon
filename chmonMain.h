/***************************************************************
 * Name:      chmonMain.h
 * Purpose:   Defines Application Frame
 * Author:    Zend (airbagi@mail.ru)
 * Created:   2019-02-09
 * Copyright: Zend (airbagi.ru)
 * License:
 **************************************************************/

#ifndef CHMONMAIN_H
#define CHMONMAIN_H

#include <wx/datetime.h>
#include <wx/filename.h>
//(*Headers(chmonDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/filedlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)


class chmonDialog: public wxDialog
  {
  public:

    chmonDialog(wxWindow* parent,wxWindowID id = -1);
    virtual ~chmonDialog();

  private:

    //(*Handlers(chmonDialog)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void Onm_btnSelectFileClick(wxCommandEvent& event);
    void Onm_tmMainTrigger(wxTimerEvent& event);
    void Onm_btnAboutClick(wxCommandEvent& event);
    //*)

    //(*Identifiers(chmonDialog)
    static const long ID_STATICTEXT1;
    static const long ID_BUTTON2;
    static const long ID_TEXTCTRL1;
    static const long ID_BUTTON1;
    static const long ID_STATICTEXT2;
    static const long ID_BUTTON3;
    static const long ID_TIMER1;
    //*)

    //(*Declarations(chmonDialog)
    wxButton* Button1;
    wxButton* m_btnAbout;
    wxButton* m_btnSelectFile;
    wxFileDialog* m_dlgFileOpen;
    wxStaticText* m_lblMain;
    wxStaticText* m_lblTime;
    wxTextCtrl* m_txtAll;
    wxTimer m_tmMain;
    //*)

    DECLARE_EVENT_TABLE()

    wxFileName m_strFileName;
    wxDateTime m_lDateTime;
    wxFile m_file;

    void ReadModifiedFile();
    void CopyModifiedFile(BYTE * buf, DWORD dwLen);
  };

#endif // CHMONMAIN_H
