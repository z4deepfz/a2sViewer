#ifndef TASKBARICON_H
#define TASKBARICON_H

#include <wx/taskbar.h>
#include <wx/frame.h>

// this object should be placed at wxApp
// because it has longer life circle than TopFrame

class TaskBarIcon : public wxTaskBarIcon
{
    public:

        // popup menu
        enum class PU {
            EXIT
        };

    public:

        TaskBarIcon(wxFrame* frame=nullptr);
        virtual ~TaskBarIcon();

        void OnLeftButtonDClick(wxTaskBarIconEvent& event); // 暂时只使用双击事件显示和隐藏窗口

    protected:

        wxFrame* frame;
        virtual wxMenu* CreatePopupMenu() override; // OS used function to pop up right click menu

    protected:

        void PopMenuOnExit(wxCommandEvent& event);

    private: DECLARE_EVENT_TABLE()

};

#endif // TASKBARICON_H
