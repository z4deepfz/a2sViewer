#ifndef BUFFERCHOICE_H
#define BUFFERCHOICE_H

#include <set>

#include <wx/choicebk.h>

#include "util.h"



class BufferChoice: public wxChoice
{
    public:

        using wxChoice::wxChoice;

        std::set<quickQuery> buffer;
        void Refresh();

        quickQuery* GetClientData(int sel);

        // official document says it will delete client data automatically..
        // so I don't need to delete them manually
        //void DeleteAllItems();
};

#endif // BUFFERCHOICE_H
