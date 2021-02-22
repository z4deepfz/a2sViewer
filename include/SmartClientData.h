#ifndef SMARTCLIENTDATA_H
#define SMARTCLIENTDATA_H

#include <memory>
#include <wx/clntdata.h>

/**
    ����ּ�ڽ��item�����ͷ�clientdata������
    ���ʹ�ô�ͳ����ָ�룬ֱ��clear��delete item�ᵼ���ڴ�й¶
    ��classʹ��clientdata��std::shared_ptr�Ķ�̳�
    ʹ�������д�κ��ͷŴ��룬��ɾ��item��ͬʱ�Զ��ͷ��ճֵĽṹ
    ͨ��template���������ٴ�����

    Ψһ��ȱ������Ҫ��wxClientData�л��ԭʼָ�룬��Ҫһ��cast����
    ��Ȼ���ǳ��˵㣬�����ܱȶ�дһ���ڴ����Ҫ�ð�XDDD
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
