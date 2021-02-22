#include "TopFrame.h"

// 点击：查询按钮
void TopFrame::OnQueryClick(wxCommandEvent& event) {
    std::string IP = static_cast<std::string>(text_IP->GetValue());
    wxString port = text_port->GetValue();
    long s32port;
    port.ToLong(&s32port);
    clearAll();
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
    const quickQuery* psel = choice_quickQuery->GetClientData(sel);
    if(psel != nullptr) {
        const quickQuery& rsel = *psel;
        text_IP->ChangeValue(rsel.addr);
        text_port->ChangeValue(wxString::Format("%u", rsel.port));
        text_name->ChangeValue(wxString::FromUTF8(rsel.name));
    }
    else {
        wxMessageBox("null pointer to selection.", "Unexpceted Exception");
    }
}



// 按钮：保存配置
void TopFrame::OnSaveConfig(wxCommandEvent& event) {
    long val;
    text_port->GetValue().ToLong(&val);

    quickQuery conf;
    conf.name = text_name->GetValue().utf8_str();
    conf.addr = text_IP->GetValue();
    conf.port = val;

    local.insert(conf);
    //std::cerr << "<TopFrame::OnSaveConfig> Current local storage size: " << local.size() << std::endl;

    // for quicker, insert to choice.buffer and refresh directly
    choice_quickQuery->buffer.insert(conf);
    choice_quickQuery->Refresh();
}



// 按钮：删除配置（按照名称，仅从本地修改）
void TopFrame::OnDeleteConfig(wxCommandEvent& event) {
    quickQuery conf;

    // note: must use utf8_str to get correct string
    // or std::set cannot find it
    conf.name = text_name->GetValue().utf8_str();

    local.erase(conf);
    loadConfigToChoiceBox();
}
