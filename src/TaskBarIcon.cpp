#include <wx/menu.h>

#include "TaskBarIcon.h"

// macro convert enum to int
#define e2i(expression) static_cast<int>(expression)

// binding event handler
BEGIN_EVENT_TABLE(TaskBarIcon, wxTaskBarIcon)

    // self event
    EVT_TASKBAR_LEFT_DCLICK(TaskBarIcon::OnLeftButtonDClick)

    // menu event
    EVT_MENU(e2i(TaskBarIcon::PU::EXIT), TaskBarIcon::PopMenuOnExit)

END_EVENT_TABLE()



TaskBarIcon::TaskBarIcon(wxFrame* frame_ptr) {
    frame = frame_ptr;
    std::cerr << "<TaskBarIcon> TaskBarIcon created.\n";
}

TaskBarIcon::~TaskBarIcon() {
    RemoveIcon();
    std::cerr << "<TaskBarIcon> TaskBarIcon deleted.\n";
}


void TaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent& event) {
    if(frame == nullptr) {
        return;
    } // if not set frame, do nothing
    frame->Show(!frame->IsShown());  // if frame shown, hide it; if frame hided, show it.
}


wxMenu* TaskBarIcon::CreatePopupMenu() {
    wxMenu* menu = new wxMenu;    // just leave in heap
    menu->Append(static_cast<int>(PU::EXIT), wxT("&Exit"));
    return menu;
}


// event

void TaskBarIcon::PopMenuOnExit(wxCommandEvent& event) {
    // invoke `close` to send a close event
    // frame would exit if it could
    frame->Close(false);
}
