
find_program(PANDOC_EXECUTABLE NAMES pandoc)

set(MAN_NAMES awsmockmgr.1 awsmockctl.1 awsmocksqs.1 awsmocks3.1 awslocal.1)
set(MAN_FILES)
foreach(m IN LISTS MAN_NAMES)
    set(mf ${CMAKE_CURRENT_SOURCE_DIR}/man/${m})
    set(ms ${CMAKE_CURRENT_SOURCE_DIR}/man/${m}.md)
    set(PANDOC_OPTS -s -t man -o ${mf})
    add_custom_command(OUTPUT ${mf}
            COMMAND ${PANDOC_EXECUTABLE} ${PANDOC_OPTS} ${ms}
            DEPENDS ${ms}
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Building manpage ${mf}"
            VERBATIM)
    list(APPEND MAN_FILES ${mf})
endforeach()

add_custom_target(man ALL DEPENDS ${MAN_FILES})

