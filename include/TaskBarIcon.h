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

        void OnLeftButtonDClick(wxTaskBarIconEvent& event); // ��ʱֻʹ��˫���¼���ʾ�����ش���

    protected:

        wxFrame* frame;


    private: DECLARE_EVENT_TABLE()

};

#endif // TASKBARICON_H
