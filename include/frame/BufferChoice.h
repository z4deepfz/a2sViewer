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
};

#endif // BUFFERCHOICE_H
