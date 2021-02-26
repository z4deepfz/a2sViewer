#include "LocalDataManager.h"

#include <wx/stdpaths.h>
#include <wx/msgdlg.h>
#include <wx/file.h>
#include <wx/dir.h>

LocalDataManager::LocalDataManager():
    appdata( wxStandardPaths::Get().GetUserLocalDataDir() ),
    prefix( appdata + "\\" ) {
    //wxMessageBox(path);
    if(wxDirExists(appdata) == false) {
        wxMkdir(appdata);
    }
}

LocalDataManager::~LocalDataManager() {
    //dtor
}


void LocalDataManager::addStorageObject(basic_StorageObject* obj) {
    managed_objects.push_back(obj);
}


bool LocalDataManager::LoadAll() {
    bool flag = true;

    for(auto it=managed_objects.begin(); it!=managed_objects.end(); it++) {
        auto&& ptr = *it;
        auto& obj = *ptr;
        auto&& fn = prefix + obj.Identifier() + ".conf";
        bool suc = true;
        wxFile f; // out of loop, it would close() and destruct
        if(wxFileExists(fn)) { // if file exists, load it. Or just created it.
            //std::cerr << "<LocalDataManager::LoadAll> Opening " << fn << std::endl;
            if(f.Open(fn, wxFile::read)) {
                // read successfully, invoke `storageLoad` to let the object load from string
                auto&& len = f.Length();
                // use unique_ptr to manage memory
                // make sure that if exception occured, memory could be freed
                auto&& ptr = std::make_unique<char[]>(len+1);
                auto&& rptr = ptr.get();

                f.Read(rptr, len);
                ptr[len] = 0; // make sure std::string could find eof

                std::string str_data(rptr, rptr+len+1);
                suc = obj.storageLoad(str_data);
                f.Close();
            }
            else {
                flag = suc = false;
                std::cerr << "<LocalDataManager::LoadAll> Failed when opening file "
                          << fn << std::endl;
            }
        }
        else { // create it and continue
            if(f.Create(fn) == false) { // if success, show nothing. if failed, output error message
                flag = suc = false;
                std::cerr << "<LocalDataManager::LoadAll> Failed when creating file "
                          << fn << std::endl;
            }
        }
        // remove this proxy if load failed
        if(suc == false) {
            std::cerr << "<LocalDataManager::LoadAll> Load " << obj.Identifier() << " failed. Remove this proxy.\n";
            it = managed_objects.erase(it);
        }
    }

    return flag;
}

bool LocalDataManager::SaveAll() {
    bool flag = true;
    for(auto ptr: managed_objects) {
        auto&& obj = *ptr;
        auto&& fn = prefix + obj.Identifier() + ".conf";
        wxFile f(fn, wxFile::OpenMode::write);
        auto&& str_to_save = obj.storageSave();
        //std::cerr << "<LocalDataManager::SaveAll> Saving:\n\t" << str_to_save << std::endl;
        flag &= f.Write(str_to_save.c_str(), str_to_save.size());
    }
    return flag;
}


