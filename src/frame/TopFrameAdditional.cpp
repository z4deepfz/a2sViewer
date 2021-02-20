#include <wx/listctrl.h>
#include "TopFrame.h"
#include "local_res.h"

void TopFrame::queryInfo(const std::string& addr, uint16_t port) {
    recv_buffer.resize(1024);

    auto&& notifier_a2s_info = boost::bind(receiveHandler, this, boost::placeholders::_1);

    SendAndReceive(std::function<void(bool)>(notifier_a2s_info),
                   response.getRequestStr(),
                   &recv_buffer,
                   addr.c_str(), port);
    return;
}


void TopFrame::queryPlayers(const std::string& addr, uint16_t port, uint8_t retry) {
    //                      ^ since may requery, use std::string to hold address instead of const char*
    //                        const char* is not relieable because it may be moved or destructed

    // because query might failed, so use following lambda expression to handle `challenage`
    // origin handler would be invoked inside.
    auto h = [addr,port,retry,this](bool success){
        if(player_response.needResponse()) {
            if(retry > 0) {
                queryPlayers(addr.c_str(), port, retry-1);
            }
            else { // if 3 retries failed, don't retry again!
                playerQueryHandler(false);
            }
        }
        else {
            playerQueryHandler(success);
        }
    };
    //auto&& notifier_a2s_player = boost::bind(playerQueryHandler, this, boost::placeholders::_1);
    SendAndReceive(std::function<void(bool)>(h),
                   player_response.getRequestStr(),
                   player_response.getBufferPtr(),
                   addr.c_str(), port);
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


void TopFrame::subscribe() {
#ifdef ENABLE_SUBSCRIBE // if not enable subscribe, it wouldn'd do anything
    auto&& callbak =  std::bind(quickQueryReceiveHandler, this, std::placeholders::_1);
    try {
        HTTPSendAndReceive(std::function<void(bool)>(callbak),
                       sub_response.getRequestStr(),
                       sub_response.getBufferPointer(),
                       local_res::addr,
                       local_res::port);
    }
    catch(...) {
        // do nothing if failed
    }
#endif // ENABLE_SUBSCRIBE
}


void TopFrame::updatePlayers(const std::vector<std::string>& name,
                             const std::vector<int>& score,
                             const std::vector<float>& time) {
    auto&& size = name.size();
    for(size_t i=0; i<size; i++) {
        auto&& id = list_playerlist->InsertItem(0, wxString::FromUTF8(name[i]));
        list_playerlist->SetItem(id, 1, wxString::Format("%d", score[i]));
        int sec = time[i];
        list_playerlist->SetItem(id, 2, wxString::Format("%02d:%02d", sec/60, sec%60));
    }
}


// clear GUI info, including board and player_list
// quick choice box wouldn't changed
void TopFrame::clearAll() {
    label_servername->SetLabel(wxEmptyString);
    label_mapname->SetLabel(wxEmptyString);
    label_player_count->SetLabel(wxEmptyString);
    label_vac->SetLabel(wxEmptyString);
    label_keywords->SetLabel(wxEmptyString);
    list_playerlist->DeleteAllItems();
}


void TopFrame::loadChoice() {
    auto& choice = *choice_quickQuery;
    auto tmp = local;
    tmp.insert(remote.begin(), remote.end());
    choice.buffer = tmp;
    choice.Refresh();
}
