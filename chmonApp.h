/***************************************************************
 * Name:      chmonApp.h
 * Purpose:   Defines Application Class
 * Author:    Zend (airbagi@mail.ru)
 * Created:   2019-02-09
 * Copyright: Zend (airbagi.ru)
 * License:
 **************************************************************/

#ifndef CHMONAPP_H
#define CHMONAPP_H

#include <wx/app.h>

class chmonApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // CHMONAPP_H
