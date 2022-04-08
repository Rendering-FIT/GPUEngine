set(addons_folder_name "geAd")

set(addons AssimpModelLoader QtImageLoader)

foreach(addon ${addons})
    add_subdirectory(${addon})
endforeach()

message(STATUS "Addons configured:")
foreach(addon ${addons})
    if(TARGET ${addon})
        message(STATUS "  ${addon}")
    endif()
endforeach()