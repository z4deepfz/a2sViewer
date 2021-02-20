#include "TopFrame.h"
#include "util.h"
#include "local_res.h"


//////////// assistant function ////////////
template<typename T>
T* move_to_heap(T obj)
{
    auto&& p = new T(obj);
    return p;
}
////////////////////////////////////////////



// a2s协议查询的handler
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



// HTTP请求的handler
void TopFrame::quickQueryReceiveHandler(bool success) {
    std::cerr << "<TopFrame::quickQueryReceiveHandler> handler called.\n";
    // When this function called, there was a full HTTP request inside buffer
    // so before parsing, cut HTTP head
    if(success) {
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
    else {
        wxMessageBox("订阅失败", "Failed");
    }
}
