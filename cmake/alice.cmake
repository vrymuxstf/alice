function(add_target_dll target)
    foreach (dll IN LISTS ARGN)
        list(APPEND dlls ${dll})
    endforeach ()

    set_target_properties(${target} PROPERTIES ALICE_DLLS ${dlls})

endfunction()

function(collect_dlls target)

    get_target_property(dlls ${target} ALICE_DLLS)

    foreach (dll IN LISTS dlls)
        get_filename_component(dll_name ${dll} NAME)

        list(APPEND commands COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll} "$<TARGET_FILE_DIR:${target}>/${dll_name}")
    endforeach ()

    add_custom_target(
            ${target}_collect_dlls
            ${commands}
    )

    add_dependencies(${target} ${target}_collect_dlls)
endfunction()