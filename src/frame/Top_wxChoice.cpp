#include <wx/app.h>
#include <wx/wx.h>

#include "TopFrame.h"
#include "util.h"
#include "local_res.h"


// when quick query selection selected, fill its property to IP and port
void TopFrame::OnquickQuerySelect(wxCommandEvent& event) {
    auto sel =  choice_quickQuery->GetSelection();
    const quickQuery* psel = static_cast<quickQuery*>(choice_quickQuery->GetClientData(sel));
    if(psel != nullptr) {
        const quickQuery& rsel = *psel;
        text_IP->ChangeValue(rsel.addr);
        text_port->ChangeValue(wxString::Format("%u", rsel.port));
    }
    else {
        wxMessageBox("null pointer to selection.", "Unexpceted Exception");
    }
}

// assistant functions

template<typename T>
T* move_to_heap(T obj)
{
    auto&& p = new T(obj);
    return p;
}

// end of assistant functions

// 向远端查询订阅信息时，将通过该函数实行通知
void TopFrame::quickQueryReceiveHandler() {
    std::cerr << "<TopFrame::quickQueryReceiveHandler> handler called.\n";
    // When this function called, there was a full HTTP request inside buffer
    // so before parsing, cut HTTP head
    std::string& str = *sub_response.getBufferPointer();
    str = str.substr(str.find('['));

    // finally parse the json string
    auto&& result = sub_response.Parse();

    for(auto&& item: result) {
        auto&& p = move_to_heap(item);
        auto&& name = item.name;
        choice_quickQuery->Append(wxString::FromUTF8(name), p);
    }

    choice_quickQuery->SetSelection(0);
}

void TopFrame::subscribe() {
    auto&& callbak =  boost::bind(quickQueryReceiveHandler, this);
    HTTPSendAndReceive(std::function<void()>(callbak),
                   sub_response.getRequestStr(),
                   sub_response.getBufferPointer(),
                   local_res::addr,
                   local_res::port);
}
