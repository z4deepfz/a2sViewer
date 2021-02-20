#include "TopFrame.h"

// 点击：查询按钮
void TopFrame::OnQueryClick(wxCommandEvent& event) {
    std::string IP = static_cast<std::string>(text_IP->GetValue());
    wxString port = text_port->GetValue();
    long s32port;
    port.ToLong(&s32port);
    try {
        queryInfo(IP, s32port);
        queryPlayers(IP, s32port);
    }
    catch(...) {
        // boost::asio may throws exception here
        // temprory only shows a warning window when query failed
        // TODO: add exception handler in the future
        wxMessageBox("网络错误", "查询失败");
    }
}


// 选中：快速查询框
// when quick query selection selected, fill its property to IP and port
void TopFrame::OnquickQuerySelect(wxCommandEvent& event) {
    auto sel = choice_quickQuery->GetSelection();
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

