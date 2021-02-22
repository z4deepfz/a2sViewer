#include "TaskBarIcon.h"

// binding event handler
BEGIN_EVENT_TABLE(TaskBarIcon, wxTaskBarIcon)

    EVT_TASKBAR_LEFT_DCLICK(TaskBarIcon::OnLeftButtonDClick)

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
