#ifndef BASIC_STORAGEOBJECT_H
#define BASIC_STORAGEOBJECT_H

#include <iostream>

/**
    basic class for all the storage class
    Any object trying to read/write to local storage should drive from this class
    3 API to implement IO function:
      1. read from string
      2. write from string
      3. object name
*/

class LocalDataManager;

class basic_StorageObject
{
    public:

        basic_StorageObject();
        virtual ~basic_StorageObject();

        // use friend class to allow `LocalDataManager` get access of internal function
        // as well as unaccessable outside
        friend class LocalDataManager;

    protected:

        // manager would read from IO stream and invoke this function to load
        virtual bool storageLoad(const std::string& storage) = 0;

        // manager might invoke this function to save info to file or other objects
        virtual std::string storageSave() = 0;

        // manager distinguish the info belonging to.
        virtual std::string Identifier() const = 0;
};

#endif // BASIC_STORAGEOBJECT_H
