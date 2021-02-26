#ifndef MAINAPP_H
#define MAINAPP_H

#include <memory>
#include <vector>
#include <iostream>

#include <wx/app.h>
#include <wx/frame.h>

#include "TopFrame.h"
#include "manual_comp.h"
#include "frame/taskbar/TaskBarIcon.h"

class MainApp : public wxApp
{

    public:

        MainApp();
        virtual ~MainApp();

        virtual bool OnInit() override;

    protected:

        wxFrame* frame;

};

#endif // MAINAPP_H
