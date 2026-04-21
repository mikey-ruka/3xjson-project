# Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
# Project is under GPL3-license, read LICENSE.md on the root.

# This was copied from `NK` project. It looks the same one from there.
add_library(XJ_ASanSupportInterface INTERFACE)
if(XJ_ENABLE_ASAN)
    if(MSVC)
        target_compile_options(XJ_ASanSupportInterface INTERFACE
            $<$<CONFIG:Debug>:/fsanitize=address /Zi>
        )
        target_link_options(XJ_ASanSupportInterface INTERFACE
            $<$<CONFIG:Debug>:/incremental:no>
        )
    else()
        target_compile_options(XJ_ASanSupportInterface INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer>
        )
        target_link_options(XJ_ASanSupportInterface INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address>
        )
    endif()
endif()