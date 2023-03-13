#pragma once
#include <memory>
#include "NextTCacheableGraph.h"
#include "NextTReverseCacheableGraph.h"
#include "AffectsCacheableGraph.h"
#include "AffectsTCacheableGraph.h"
#include "AffectsTReverseCacheableGraph.h"
#include "program_knowledge_base/StorageManager.h"

class Cache {
 private:
     NextTCacheableGraph nextTCache;

     NextTReverseCacheableGraph nextTReverseCache;

     AffectsCacheableGraph affectsCache;

     AffectsTCacheableGraph affectsTCache;

     AffectsTReverseCacheableGraph affectsTReverseCache;

     /**
      * AffectsT is expensive to initialise as it requires the entire affects
      * to be completed. Hence, only initialise it when it is called.
      * The boolean keeps track if it is initialized.
      */
     bool affectsTInitialised = false;

     bool affectsTReverseInitialised = false;

     void setCacheBase();

 public:
     explicit Cache(StoragePointer storage);

    NextTCacheableGraph* getNextTCache();

    NextTReverseCacheableGraph* getNextTReverseCache();

    AffectsCacheableGraph* getAffectsCacheableGraph();

    AffectsTCacheableGraph* getAffectsTCacheableGraph();

    AffectsTReverseCacheableGraph* getAffectsTReverseCacheableGraph();
};
