#ifndef MANUAL_COMP_H
#define MANUAL_COMP_H

#include "frame/taskbar/TaskBarIcon.h"


namespace manual {

// ����һ���ǳ����ĵ����飺wxTaskBarIcon������wxApp�˳�
// Ҳ����top window�˳��ˣ��¼�ѭ�������ܣ�����Ϊ����û�н���������ͼ�껹����
// �����ʱ��˫��ͼ�꣬�������ڵ���ƣ�taskbaricon�����ͼ����frame��show����
// Ȼ����Ϊframe�Ѿ������ˣ�����һjio���ڿ�ָ���ϣ�����ը
// �����˸��ַ������㲻��������⡣��Ϊtaskbaricon�Ժ����Ҫ���������飬��˷Ž�frame�ֲ�������
// ����wxApp��ͷ�ֲ���ȡ��������������Ϊȫ�ַ��ŵ����ó���......
// �ò���ָ�뵹������ν����������wxWidgets�������ױȽϺ�
// md, wx���������ô��ģ�һ��icon�����������˳�
    extern TaskBarIcon* taskbar;

}

#endif // MANUAL_COMP_H
