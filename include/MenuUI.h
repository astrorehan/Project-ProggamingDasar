#ifndef MENUUI_H
#define MENUUI_H

#include "InventoryManager.h"
#include "FileManager.h"

class MenuUI {
private:
    InventoryManager manager;
    FileManager filemgr;

public:
    void tampilMenu();
    void jalankan();
};

#endif
