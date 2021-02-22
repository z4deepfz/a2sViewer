#include "MainApp.h"

MainApp::MainApp()
{
    //ctor
}

MainApp::~MainApp()
{
    //dtor
}

bool MainApp::OnInit()
{
    // create and show frame
    TopFrame* frame = new TopFrame(nullptr, wxID_ANY);
    frame->Show(true);

    // create task bar icon
    taskbar = std::make_shared<TaskBarIcon>(frame); // give frame ptr
    taskbar->SetIcon(wxIcon(wxT("aaaa"))); // set icon

    return true;
}
