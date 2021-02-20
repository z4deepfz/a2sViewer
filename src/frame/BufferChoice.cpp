#include "BufferChoice.h"
#include "SmartClientData.h"


//////////// assistant function ////////////
template<typename T>
SmartClientData<T>* copy_to_heap(T obj)
{
    auto&& p = new T(obj); // copy to heap
    auto&& ret = new SmartClientData<T>(p); // construct SmartClientData from heap pointer
    return ret;
}
////////////////////////////////////////////


void BufferChoice::Refresh() {
    // remove all them first
    Clear(); // It's safe, because class `SmartClientData` will free them

    // them refill it
    for(auto&& item: buffer) { // not append to GUI yet, insert to buffer first
        auto&& p = copy_to_heap(item);
        auto&& name = item.name;
        this->Append(wxString::FromUTF8(name), p);
    }
    this->SetSelection(0);
    this->Enable(true);
}


quickQuery* BufferChoice::GetClientData(int sel) {
    auto&& p = getRawPtr<quickQuery>(wxChoice::GetClientObject(sel));
    return p;
}

