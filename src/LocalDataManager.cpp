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

    for(auto ptr: managed_objects) {
        auto&& obj = *ptr;
        auto&& fn = prefix + obj.Identifier() + ".conf";
        wxFile f; // out of loop, it would close() and destruct
        wxString str_data;
        if(wxFileExists(fn)) { // if file exists, load it. Or just created it.
            std::cerr << "<LocalDataManager::LoadAll> Opening " << fn << std::endl;
            if(f.Open(fn, wxFile::read) && f.ReadAll(&str_data)) {
                // read successfully, invoke `storageLoad` to let the object load from string
                obj.storageLoad((std::string)str_data);
            }
            else {
                flag = false;
                std::cerr << "<LocalDataManager::LoadAll> Failed when opening file "
                          << fn << std::endl;
            }
        }
        else { // create it and continue
            if(f.Create(fn) == false) {
                flag = false;
                std::cerr << "<LocalDataManager::LoadAll> Failed when creating file "
                          << fn << std::endl;
            }
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
        flag &= f.Write(obj.storageSave());
        // f would be closed and destructed automatically
    }
    return flag;
}


