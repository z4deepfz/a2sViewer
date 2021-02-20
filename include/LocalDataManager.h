#ifndef LOCALDATAMANAGER_H
#define LOCALDATAMANAGER_H

#include <vector>
#include "basic_StorageObject.h"

/**
    responsibility:
        1. a proxy to load and save appdata
        2. manage multiple text-able object, read and write for them
        0xff. fine I know it break the SRP
    note:
        1. all config would be saved at %APPDATA% in their file
        2. filename would be the return of identifyName()
*/

class LocalDataManager
{
    public:
        LocalDataManager();
        virtual ~LocalDataManager();

        bool LoadAll();
        bool SaveAll();
        void addStorageObject(basic_StorageObject* obj);

    protected:

        std::vector<basic_StorageObject*> managed_objects;
        const std::string appdata;  // %APPDATA%/Local/a2sViewer
        const std::string prefix;   // prefix + `filename` == target path

};


#endif // LOCALDATAMANAGER_H
