#ifndef SERVERCONFIGSTORAGE_H
#define SERVERCONFIGSTORAGE_H

#include "basic_StorageObject.h"
#include "util.h"

#include <set>


class serverConfigStorage : public basic_StorageObject
{
    public:
        serverConfigStorage();
        virtual ~serverConfigStorage();

        // reuse quickQuery to load and save config
        std::set<quickQuery> getLoadedRecord() const;

        void addItem(const quickQuery& item);
        void delItem(const quickQuery& item);

    protected:

        virtual bool storageLoad(const std::string& storage) override;
        virtual std::string storageSave() override;
        virtual std::string Identifier() const override;

        std::set<quickQuery> data;

};

#endif // SERVERCONFIGSTORAGE_H
