#ifndef SMARTCLIENTDATA_H
#define SMARTCLIENTDATA_H

#include <memory>
#include <wx/clntdata.h>

/**
    该类旨在解决item容器释放clientdata的问题
    如果使用传统的裸指针，直接clear或delete item会导致内存泄露
    该class使用clientdata和std::shared_ptr的多继承
    使得无需编写任何释放代码，在删除item的同时自动释放握持的结构
    通过template泛型最大减少代码量

    唯一的缺点是想要从wxClientData中获得原始指针，需要一次cast才行
    虽然丑是丑了点，但是总比多写一个内存管理要好吧XDDD
*/


template<class T>
class SmartClientData: public std::shared_ptr<T>, public wxClientData
{
    protected:
        using shared_ptr = typename std::shared_ptr<T>;
    public:

        using typename shared_ptr::shared_ptr;
        SmartClientData(T* p) {
            this->reset(p);
        }
        virtual ~SmartClientData() {
            //std::cerr << "<SmartClientData> Destructed.\n";
        }

};

template<class T>
T* getRawPtr(wxClientData* ptr) {
    return dynamic_cast<std::shared_ptr<T>*>(ptr)->get();
}

#endif // SMARTCLIENTDATA_H
