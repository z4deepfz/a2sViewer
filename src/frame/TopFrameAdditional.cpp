#include <wx/wx.h>
#include <wx/app.h>
#include "TopFrame.h"

void TopFrame::OnQueryClick(wxCommandEvent& event) {
    wxString IP = text_IP->GetValue();
    wxString port = text_port->GetValue();
    long s32port;
    port.ToLong(&s32port);
    queryInfo(IP.c_str(), s32port);
}

void TopFrame::queryInfo(const char* addr, uint16_t port) {
    recv_buffer.resize(1024);
    SendAndReceive(std::function<void(bool)>(boost::bind(receiveHandler, this, boost::placeholders::_1)),
                   response.getRequestStr(),
                   &recv_buffer,
                   addr,
                   port);
    //std::cerr << "<TopFrame::queryInfo> function returns.\n";
    return;
}

void TopFrame::receiveHandler(bool success) {
    //std::cerr << "<TopFrame::receiveHandler> receive handler called.\n";
    //std::cerr << "<TopFrame::receiveHandler> buffer_size=" << recv_buffer.size() << std::endl;
    if(success) {
        response.Parse(recv_buffer.c_str());
        text_rawData->ChangeValue(convertByteToHexString(recv_buffer));
        Refresh();
    }
    else {
        wxMessageBox("查询失败", "Failed");
    }
}



void TopFrame::updateBoard(
    const wxString& server_name,
    const wxString& map_name,
    const wxString& players,
    const wxString& vac,
    const wxString& keywords
) {
    //std::cout << server_name;
    label_servername->SetLabel(server_name);
    label_mapname->SetLabel(map_name);
    label_player_count->SetLabel(players);
    label_vac->SetLabel(vac);
    label_keywords->SetLabel(keywords);
}



void TopFrame::updateBoard(
    const std::tuple<
        std::string,
        std::string,
        uint8_t,uint8_t,
        bool,
        std::string,
        bool >& response
) {
    if(std::get<6>(response)) {
        updateBoard(
            wxString::FromUTF8(std::get<0>(response)),
            wxString::FromUTF8(std::get<1>(response)), /// 注意a2s协议的名称字段都是UTF-8
            wxString::Format("%d / %d%s", std::get<2>(response), std::get<3>(response),
                             std::get<2>(response)==0?" (无人在家)":
                             (std::get<2>(response)==std::get<3>(response)?" (全员恶人)":"")),
            std::get<4>(response)?"VAC已启用":"VAC未启用",
            std::get<5>(response)
        );
    }
    else {
        wxMessageBox("未知错误");
    }
}



void TopFrame::Refresh() {
    updateBoard(getNeededAttributesFromA2sResponse(response));
}

