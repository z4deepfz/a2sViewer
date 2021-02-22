#ifndef TASKBARICON_H
#define TASKBARICON_H

#include <wx/taskbar.h>
#include <wx/frame.h>

// this object should be placed at wxApp
// because it has longer life circle than TopFrame

class TaskBarIcon : public wxTaskBarIcon
{
    public:

        TaskBarIcon(wxFrame* frame=nullptr);
        virtual ~TaskBarIcon();

        void OnLeftButtonDClick(wxTaskBarIconEvent& event); // 暂时只使用双击事件显示和隐藏窗口

    protected:

        wxFrame* frame;


    private: DECLARE_EVENT_TABLE()

};

#endif // TASKBARICON_H
