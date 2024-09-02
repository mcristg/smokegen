#include "ppcallbacks.h"
#include <clang/Basic/FileManager.h>

void SmokegenPPCallbacks::InjectQObjectDefs(clang::SourceLocation Loc) {
    #include "qobjectdefs-injected.h"
    auto Buf = llvm::MemoryBuffer::getMemBuffer(Injected, "qobjectdefs-injected.moc");
    Loc = pp.getSourceManager().getFileLoc(Loc);
    pp.EnterSourceFile(pp.getSourceManager().createFileID(std::move(Buf), clang::SrcMgr::C_User, 0, 0, Loc), nullptr, Loc);
}

void SmokegenPPCallbacks::FileChanged(clang::SourceLocation Loc, FileChangeReason Reason,
        clang::SrcMgr::CharacteristicKind FileType, clang::FileID PrevFID) {

#if LLVM_VERSION <= 17
    auto F = pp.getSourceManager().getFileEntryForID(PrevFID);
#else
    auto F = pp.getSourceManager().getFileEntryRefForID(PrevFID);
#endif
    if (!F)
        return;

    llvm::StringRef name = F->getName();

#if LLVM_VERSION <= 17
    if (name.endswith("qobjectdefs.h")) {
#else
    if (name.ends_with("qobjectdefs.h")) { 
#endif
        InjectQObjectDefs(Loc);
    }
    
}
