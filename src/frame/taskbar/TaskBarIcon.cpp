#include <wx/menu.h>

#include "frame/taskbar/TaskBarIcon.h"

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
    menu->Append(static_cast<int>(PU::EXIT), _("&Exit"));
    return menu;
}

