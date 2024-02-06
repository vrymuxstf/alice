function(get_targets target out_targets)
    list(APPEND targets ${target})

    get_target_property(link_libs ${target} INTERFACE_LINK_LIBRARIES)

    if (link_libs)
        foreach (link_lib IN LISTS link_libs)

            if (TARGET ${link_lib})
                list(APPEND targets ${link_lib})

                get_targets(${link_lib} ${link_lib}_targets)

                list(APPEND targets ${${link_lib}_targets})
            endif ()

        endforeach ()
    endif ()

    list(REMOVE_DUPLICATES targets)

    set(${out_targets} ${targets} PARENT_SCOPE)
endfunction()

function(add_target_dll target)
    foreach (dll IN LISTS ARGN)
        list(APPEND dlls ${dll})
    endforeach ()

    set_target_properties(${target} PROPERTIES ALICE_DLLS "${dlls}")

endfunction()

function(add_target_asset target)
    foreach (asset IN LISTS ARGN)
        list(APPEND assets ${asset})
    endforeach ()

    set_target_properties(${target} PROPERTIES ALICE_ASSETS "${assets}")

endfunction()

function(collect_dlls target)

    get_targets(${target} required_targets)

    foreach (required_target IN LISTS required_targets)

        get_target_property(dlls ${required_target} ALICE_DLLS)

        if (NOT ${dlls} STREQUAL "dlls-NOTFOUND")

            foreach (dll IN LISTS dlls)
                get_filename_component(dll_name ${dll} NAME)

                list(APPEND commands COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll} "$<TARGET_FILE_DIR:${target}>/${dll_name}")
            endforeach ()
        endif ()

    endforeach ()

    add_custom_target(
            ${target}_collect_dlls
            ${commands}
    )

    add_dependencies(${target} ${target}_collect_dlls)
endfunction()

function(collect_assets target)

    get_targets(${target} required_targets)

    foreach (required_target IN LISTS required_targets)

        get_target_property(assets ${required_target} ALICE_ASSETS)

        if (NOT "${assets}" STREQUAL "assets-NOTFOUND")

            foreach (asset IN LISTS assets)

                list(APPEND commands COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${asset} "$<TARGET_FILE_DIR:${target}>/${asset}")

            endforeach ()
        endif ()

    endforeach ()

    add_custom_target(
            ${target}_collect_assets
            ${commands}
    )

    add_dependencies(${target} ${target}_collect_assets)
endfunction()