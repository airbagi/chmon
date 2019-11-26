/***************************************************************
 * Name:      chmonApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Zend (airbagi@mail.ru)
 * Created:   2019-02-09
 * Copyright: Zend (airbagi.ru)
 * License:
 **************************************************************/

#include "chmonApp.h"

//(*AppHeaders
#include "chmonMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(chmonApp);

bool chmonApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	chmonDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
