#ifndef MENUUI_H
#define MENUUI_H

#include "InventoryManager.h"
#include "FileManager.h"
#include <string>
using namespace std;

class MenuUI {
private:
    InventoryManager manager;
    FileManager filemgr;

    void tampilImportFile(string file);

public:
    void tampilMenu();
    void jalankan();
};

#endif
