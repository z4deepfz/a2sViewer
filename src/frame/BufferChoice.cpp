#include "BufferChoice.h"


//////////// assistant function ////////////
template<typename T>
T* copy_to_heap(T obj)
{
    auto&& p = new T(obj);
    return p;
}
////////////////////////////////////////////


void BufferChoice::Refresh() {
    for(auto&& item: buffer) { // not append to GUI yet, insert to buffer first
        auto&& p = copy_to_heap(item);
        auto&& name = item.name;
        this->Append(wxString::FromUTF8(name), p);
    }
    this->SetSelection(0);
    this->Enable(true);
}

quickQuery* BufferChoice::GetClientData(int sel) {
    auto&& p = static_cast<quickQuery*>(wxChoice::GetClientData(sel));
    return p;
}
