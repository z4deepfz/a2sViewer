#ifndef MANUAL_COMP_H
#define MANUAL_COMP_H

#include "frame/taskbar/TaskBarIcon.h"


namespace manual {

// 这是一件非常糟心的事情：wxTaskBarIcon会阻塞wxApp退出
// 也就是top window退出了，事件循环还在跑，表现为进程没有结束，而且图标还留着
// 如果这时候双击图标，按照现在的设计，taskbaricon类会试图调用frame的show函数
// 然后因为frame已经析构了，所以一jio踢在空指针上，程序爆炸
// 我试了各种方法都搞不定这个问题。因为taskbaricon以后可能要做其他事情，因此放进frame又不够解耦
// 放在wxApp里头又不好取，所以最后决定作为全局符号单独拿出来......
// 用不用指针倒是无所谓，但是先入wxWidgets的乡随俗比较好
// md, wx库的作者怎么想的，一个icon能阻塞程序退出
    extern TaskBarIcon* taskbar;

}

#endif // MANUAL_COMP_H
