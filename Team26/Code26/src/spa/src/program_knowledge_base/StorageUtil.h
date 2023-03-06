#pragma once

#include <memory>
#include <string>
#include "program_knowledge_base/entity/entity_child_managers/AssignManager.h"
#include "program_knowledge_base/entity/entity_child_managers/PrintStmtNoManager.h"
#include "program_knowledge_base/entity/entity_child_managers/PrintVariableManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ReadStmtNoManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ReadVariableManager.h"
#include "program_knowledge_base/entity/entity_child_managers/StmtManager.h"
#include "program_knowledge_base/entity/entity_child_managers/VariableManager.h"
#include "program_knowledge_base/entity/entity_child_managers/IfManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ConstantManager.h"
#include "program_knowledge_base/entity/entity_child_managers/CallManager.h"
#include "program_knowledge_base/entity/entity_child_managers/ProcedureManager.h"
#include "program_knowledge_base/entity/entity_child_managers/WhileManager.h"
#include "program_knowledge_base/pattern/PatternManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/FollowsTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ParentTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/UsesSManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/ModifiesSManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/NextManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/CallPManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/CallSManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/CallsTManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/IfCondManager.h"
#include "program_knowledge_base/relationship/relationship_child_managers/WhileCondManager.h"

class StorageUtil {
 private:
    // relationship managers
    std::shared_ptr<FollowsManager> followsManager;
    std::shared_ptr<FollowsTManager> followsTManager;

    std::shared_ptr<ParentManager> parentManager;
    std::shared_ptr<ParentTManager> parentTManager;

    std::shared_ptr<UsesPManager> usesPManager;
    std::shared_ptr<UsesSManager> usesSManager;

    std::shared_ptr<ModifiesPManager> modifiesPManager;
    std::shared_ptr<ModifiesSManager> modifiesSManager;

    std::shared_ptr<NextManager> nextManager;

    std::shared_ptr<CallPManager> callPManager;
    std::shared_ptr<CallSManager> callSManager;
    std::shared_ptr<CallsTManager> callsTManager;

    // entity managers
    std::shared_ptr<AssignManager> assignManager;
    std::shared_ptr<CallManager> callManager;
    std::shared_ptr<ConstantManager> constantManager;
    std::shared_ptr<IfManager> ifManager;
    std::shared_ptr<PrintStmtNoManager> printStmtNoManager;
    std::shared_ptr<PrintVariableManager> printVariableManager;
    std::shared_ptr<ProcedureManager> procedureManager;
    std::shared_ptr<ReadStmtNoManager> readStmtNoManager;
    std::shared_ptr<ReadVariableManager> readVariableManager;
    std::shared_ptr<StmtManager> stmtManager;
    std::shared_ptr<VariableManager> variableManager;
    std::shared_ptr<WhileManager> whileManager;

    // pattern managers
    std::shared_ptr<PatternManager> patternManager;
    std::shared_ptr<IfCondManager> ifCondManager;
    std::shared_ptr<WhileCondManager> whileCondManager;


 public:
    StorageUtil() {
        followsManager = std::make_shared<FollowsManager>();
        followsTManager = std::make_shared<FollowsTManager>();
        parentManager = std::make_shared<ParentManager>();
        parentTManager = std::make_shared<ParentTManager>();
        usesPManager = std::make_shared<UsesPManager>();
        usesSManager = std::make_shared<UsesSManager>();
        modifiesPManager = std::make_shared<ModifiesPManager>();
        modifiesSManager = std::make_shared<ModifiesSManager>();
        nextManager = std::make_shared<NextManager>();
        callPManager = std::make_shared<CallPManager>();
        callSManager = std::make_shared<CallSManager>();
        callsTManager = std::make_shared<CallsTManager>();
        nextManager = std::make_shared<NextManager>();
        assignManager = std::make_shared<AssignManager>();
        callManager = std::make_shared<CallManager>();
        constantManager = std::make_shared<ConstantManager>();
        ifManager = std::make_shared<IfManager>();
        printStmtNoManager = std::make_shared<PrintStmtNoManager>();
        procedureManager = std::make_shared<ProcedureManager>();
        readStmtNoManager = std::make_shared<ReadStmtNoManager>();
        stmtManager = std::make_shared<StmtManager>();
        variableManager = std::make_shared<VariableManager>();
        patternManager = std::make_shared<PatternManager>();
        whileManager = std::make_shared<WhileManager>();
        ifCondManager = std::make_shared<IfCondManager>();
        whileCondManager = std::make_shared<WhileCondManager>();
        readVariableManager = std::make_shared<ReadVariableManager>();
        printVariableManager = std::make_shared<PrintVariableManager>();
    }

    std::shared_ptr<FollowsManager> getFollowsManager() {
        return followsManager;
    }

    std::shared_ptr<FollowsTManager> getFollowsTManager() {
        return followsTManager;
    }

    std::shared_ptr<ParentManager> getParentManager() {
        return parentManager;
    }

    std::shared_ptr<ParentTManager> getParentTManager() {
        return parentTManager;
    }

    std::shared_ptr<UsesPManager> getUsesPManager() {
        return usesPManager;
    }

    std::shared_ptr<UsesSManager> getUsesSManager() {
        return usesSManager;
    }

    std::shared_ptr<ModifiesPManager> getModifiesPManager() {
        return modifiesPManager;
    }

    std::shared_ptr<ModifiesSManager> getModifiesSManager() {
        return modifiesSManager;
    }

    std::shared_ptr<NextManager> getNextManager() {
        return nextManager;
    }
    std::shared_ptr<CallPManager> getCallPManager() {
        return callPManager;
    }

    std::shared_ptr<CallSManager> getCallSManager() {
        return callSManager;
    }

    std::shared_ptr<CallsTManager> getCallsTManager() {
        return callsTManager;
    }

    std::shared_ptr<IfCondManager> getIfCondManager() {
        return ifCondManager;
    }

    std::shared_ptr<WhileCondManager> getWhileCondManager() {
        return whileCondManager;
    }

    std::shared_ptr<AssignManager> getAssignManager() {
        return assignManager;
    }

    std::shared_ptr<CallManager> getCallManager() {
        return callManager;
    }

    std::shared_ptr<ConstantManager> getConstantManager() {
        return constantManager;
    }

    std::shared_ptr<IfManager> getIfManager() {
        return ifManager;
    }

    std::shared_ptr<PrintStmtNoManager> getPrintStmtNoManager() {
        return printStmtNoManager;
    }

    std::shared_ptr<PrintVariableManager> getPrintVariableManager() {
        return printVariableManager;
    }

    std::shared_ptr<ProcedureManager> getProcedureManager() {
        return procedureManager;
    }

    std::shared_ptr<ReadStmtNoManager> getReadStmtNoManager() {
        return readStmtNoManager;
    }

    std::shared_ptr<ReadVariableManager> getReadVariableManager() {
        return readVariableManager;
    }

    std::shared_ptr<StmtManager> getStmtManager() {
        return stmtManager;
    }

    std::shared_ptr<VariableManager> getVariableManager() {
        return variableManager;
    }

    std::shared_ptr<WhileManager> getWhileManager() {
        return whileManager;
    }

    std::shared_ptr<PatternManager> getPatternManager() {
        return patternManager;
    }
};
