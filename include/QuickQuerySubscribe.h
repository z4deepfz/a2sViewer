#ifndef QUICKQUERYSUBSCRIBE_H
#define QUICKQUERYSUBSCRIBE_H

#include <vector>
#include <nlohmann/json.hpp>
#include "util.h"

// This class receive json string ans parse it to array
class QuickQuerySubscribe
{

public:

    QuickQuerySubscribe();
    virtual ~QuickQuerySubscribe();

    std::vector<quickQuery> Parse();
    std::string* getBufferPointer();
    std::string getRequestStr() const;

    static std::vector<quickQuery> Parse(const std::string& str);

protected:

    std::string buffer;

};

#endif // QUICKQUERYSUBSCRIBE_H
