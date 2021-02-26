#include "frame/taskbar/TaskBarIcon.h"

// macro convert enum to int
#define e2i(expression) static_cast<int>(expression)

// binding event handler
BEGIN_EVENT_TABLE(TaskBarIcon, wxTaskBarIcon)

    ///// event for self /////
    EVT_TASKBAR_LEFT_DCLICK(TaskBarIcon::OnLeftButtonDClick)

    ///// event for pop-up menu /////
    EVT_MENU(e2i(TaskBarIcon::PU::EXIT), TaskBarIcon::PopMenuOnExit)

END_EVENT_TABLE()



void TaskBarIcon::PopMenuOnExit(wxCommandEvent& event) {
    // invoke `close` to send a close event
    // frame would exit if it could
    frame->Close(false);
}
