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
        text_port->ChangeValue(wxString::Format("%ud", rsel.port));
    }
    else {
        wxMessageBox("null pointer to selection.", "Unexpceted Exception");
    }
}

// 向远端查询订阅信息时，将通过该函数实行通知
void TopFrame::quickQueryReceiveHandler() {
    std::cerr << "<TopFrame::quickQueryReceiveHandler> handler called.\n";
    auto&& result = sub_response.Parse();
    for(auto&& i: result) {
        std::cerr << i.name << std::endl;
    }
}

void TopFrame::subscribe() {
    auto&& callbak =  boost::bind(quickQueryReceiveHandler, this);
    SendAndReceive(std::function<void()>(callbak),
                   sub_response.getRequestStr(),
                   sub_response.getBufferPointer(),
                   local_res::addr,
                   local_res::port);
}
