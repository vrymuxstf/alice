function(alice_add_program target)
    add_executable(${target})
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_SYSTEM_PROCESSOR}/${target}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_SYSTEM_PROCESSOR}/${target}
    )
endfunction()

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

function(alice_link_dlls target)

    foreach (dll IN LISTS ARGN)
        list(APPEND dlls ${dll})
    endforeach ()

    set_target_properties(${target} PROPERTIES ALICE_DLLS "${dlls}")

endfunction()

function(alice_copy_dlls target)

    get_targets(${target} required_targets)

    foreach (required_target IN LISTS required_targets)

        get_target_property(dlls ${required_target} ALICE_DLLS)

        if (dlls)

            foreach (dll IN LISTS dlls)

                list(APPEND commands COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll} "$<TARGET_FILE_DIR:${target}>")

            endforeach ()

        endif ()

    endforeach ()

    add_custom_target(
            ${target}_copy_dlls
            ${commands}
    )

    add_dependencies(${target} ${target}_copy_dlls)

endfunction()