# Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
# Project is under GPL3-license, read LICENSE.md on the root.

# This was copied from `Progator` project.

function(XJ_TryAddToLibrary library to)
    if(TARGET ${library})
        target_link_libraries(${to} INTERFACE ${library})
        add_dependencies(${to} ${library})
        message(STATUS "Found ${library}")
    else()
        # Can we find this library?
        message(FATAL_ERROR "Could not find: ${library}")
    endif()
endfunction()