#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <framework/include/storage.h>
#include <tinyxml2.h>

extern SciStore::Storage<> * storage;
static std::string picture_formats[]={"jpg", "jpeg", "png", "gif", "tiff", "jp2", "jpx", "bmp", "apng", "emf", "dpx", "svg", "wmf", "webp"};
static std::string XMLFileName = "AssetStores.xml";

static struct StoreConfig{
    std::string name;
    std::string metaPath;
    std::string dataPath;
} StoreConfigI;


#endif
