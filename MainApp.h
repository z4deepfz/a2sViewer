#ifndef MAINAPP_H
#define MAINAPP_H

#include <memory>
#include <iostream>

#include <wx/app.h>
#include <wx/frame.h>

#include "TopFrame.h"
#include "TaskBarIcon.h"


class MainApp : public wxApp
{
    public:

        MainApp();
        virtual ~MainApp();

        virtual bool OnInit() override;

    protected:

        std::shared_ptr<TaskBarIcon> taskbar;

};

// int main(int argc, char** argv)
IMPLEMENT_APP(MainApp)

#endif // MAINAPP_H
