//
//          Tracy profiler
//         ----------------
//
// For fast integration, compile and
// link with this source file (and none
// other) in your executable (or in the
// main DLL / shared object on multi-DLL
// projects).
//

// Define TRACY_ENABLE to enable profiler.

#ifdef TRACY_ENABLE
#include "tracy_profiler/common/TracySystem.cpp"


#ifdef _MSC_VER
#  pragma warning(push, 0)
#endif

#include "tracy_profiler/common/tracy_lz4.cpp"
#include "tracy_profiler/client/TracyProfiler.cpp"
#include "tracy_profiler/client/TracyCallstack.cpp"
#include "tracy_profiler/client/TracySysPower.cpp"
#include "tracy_profiler/client/TracySysTime.cpp"
#include "tracy_profiler/client/TracySysTrace.cpp"
#include "tracy_profiler/common/TracySocket.cpp"
#include "tracy_profiler/client/tracy_rpmalloc.cpp"
#include "tracy_profiler/client/TracyDxt1.cpp"
#include "tracy_profiler/client/TracyAlloc.cpp"
#include "tracy_profiler/client/TracyOverride.cpp"
#include "tracy_profiler/client/TracyKCore.cpp"

#if defined(TRACY_HAS_CALLSTACK)
#  if TRACY_HAS_CALLSTACK == 2 || TRACY_HAS_CALLSTACK == 3 || TRACY_HAS_CALLSTACK == 4 || TRACY_HAS_CALLSTACK == 6
#    include "tracy_profiler/libbacktrace/alloc.cpp"
#    include "tracy_profiler/libbacktrace/dwarf.cpp"
#    include "tracy_profiler/libbacktrace/fileline.cpp"
#    include "tracy_profiler/libbacktrace/mmapio.cpp"
#    include "tracy_profiler/libbacktrace/posix.cpp"
#    include "tracy_profiler/libbacktrace/sort.cpp"
#    include "tracy_profiler/libbacktrace/state.cpp"
#    if TRACY_HAS_CALLSTACK == 4
#      include "tracy_profiler/libbacktrace/macho.cpp"
#    else
#      include "tracy_profiler/libbacktrace/elf.cpp"
#    endif
#    include "tracy_profiler/common/TracyStackFrames.cpp"
#  endif
#endif

#ifdef _MSC_VER
#  pragma comment(lib, "ws2_32.lib")
#  pragma comment(lib, "dbghelp.lib")
#  pragma comment(lib, "advapi32.lib")
#  pragma comment(lib, "user32.lib")
#  pragma warning(pop)
#endif

#endif
