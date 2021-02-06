#ifndef MAINAPP_H
#define MAINAPP_H

#include <wx/app.h>
#include "TopFrame.h"
#include <iostream>

class MainApp : public wxApp
{
    public:
        MainApp();
        virtual ~MainApp();

        virtual bool OnInit() override;

    protected:

    private:
};

IMPLEMENT_APP(MainApp)

#endif // MAINAPP_H
