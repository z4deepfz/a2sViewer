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
    TopFrame* frame = new TopFrame(nullptr, wxID_ANY);
    frame->Show(true);
    return true;
}
