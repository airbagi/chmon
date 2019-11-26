#ifndef ABOUT_H
#define ABOUT_H

//(*Headers(about)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)
#include <wx/animate.h>s

class about: public wxDialog
{
public:
    static const long ID_ANIMATIONCTRL1;
    about(wxWindow* parent,wxWindowID id=wxID_ANY);
    virtual ~about();
    wxAnimationCtrl* m_ani;
    //(*Declarations(about)
    wxStaticText* StaticText1;
    //*)

protected:

    //(*Identifiers(about)
    static const long ID_STATICTEXT1;
    //*)

private:

    //(*Handlers(about)
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
