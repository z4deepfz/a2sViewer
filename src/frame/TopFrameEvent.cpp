#include "TopFrame.h"

// �������ѯ��ť
void TopFrame::OnQueryClick(wxCommandEvent& event) {
    wxString IP = text_IP->GetValue();
    wxString port = text_port->GetValue();
    long s32port;
    port.ToLong(&s32port);
    queryInfo(IP.c_str(), s32port);
}


// ѡ�У����ٲ�ѯ��
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

