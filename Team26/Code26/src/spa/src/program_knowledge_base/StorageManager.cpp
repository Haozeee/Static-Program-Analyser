#include "StorageManager.h"

StorageManager::StorageManager() {
    storageUtil = std::make_shared<StorageUtil>();
}

std::shared_ptr<WriteStorage> StorageManager::getWriteManager() {
    return std::make_shared<WriteStorage>(storageUtil);
}

std::shared_ptr<ReadStroage> StorageManager::getReadManager() {
    return std::make_shared<ReadStroage>(storageUtil);
}
