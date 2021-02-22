#include "MainApp.h"

/// BEGIN OF IMPLEMENMT
    // I don't know why wxSmith implement app in header file(originally in MainApp.h)
    // It's quite stupid because it may cause duplicated symbol
    // So I move it to cpp file. Now "MainApp.h" could be included anywhere
IMPLEMENT_APP(MainApp)
/// END OF IMPLEMENT



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
