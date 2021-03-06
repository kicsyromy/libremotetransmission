macro (libgearbox_test_find_python)
    set (PYTHON_FOUND         0)
    set (PYTHON_INCLUDE_DIRS "")
    set (PYTHON_LIBRARIES    "")
    set (PYTHON_LIB_VERSION  "")

    find_package (PkgConfig QUIET)
    if (PKG_CONFIG_FOUND)
        pkg_search_module (PYTHON QUIET python3>=3.5)
        set (PYTHON_LIB_VERSION ${PYTHON_VERSION})
    endif ()

    if (NOT PYTHON_FOUND)
        find_package (PythonLibs QUIET)
        if (PYTHONLIBS_FOUND)
            string (REPLACE "." ";" PYTHON_LIB_VERSION ${PYTHONLIBS_VERSION_STRING})
            list (GET PYTHON_LIB_VERSION 0 PY_LIB_VERSION_MAJOR)
            list (GET PYTHON_LIB_VERSION 1 PY_LIB_VERSION_MINOR)
            set (PYTHON_LIB_VERSION "${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}")
            if ((NOT (${PY_LIB_VERSION_MAJOR} LESS 3)) AND (NOT (${PY_LIB_VERSION_MINOR} LESS 4)))
                set (PYTHON_FOUND 1)
            else ()
                message (FATAL_ERROR "Found Python ${PYTHON_LIB_VERSION} but is older than the minimum supported version, consider upgrading to at least 3.5")
            endif ()
        endif()
    endif ()

    if (PYTHON_FOUND)
    else ()
        message (FATAL_ERROR "Missing or incompatible Python libraries. Consider supplying PYTHON_LIBRARY and PYTHON_INCLUDE_DIR to the CMake command-line.")
    endif ()
endmacro ()

function (libgearbox_test_find_python_binary RESULT)
    libgearbox_test_find_python()

    find_program(PYTHON_BINARY python NAMES python python3 python3.5 python3.6)
    if (NOT PYTHON_BINARY MATCHES "PYTHON_BINARY-NOTFOUND")
        execute_process(COMMAND ${PYTHON_BINARY} --version OUTPUT_VARIABLE PYTHON_BIN_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
        string (REPLACE "Python " "" PYTHON_BIN_VERSION ${PYTHON_BIN_VERSION})
        string (REPLACE "." ";" PYTHON_BIN_VERSION ${PYTHON_BIN_VERSION})
        list (GET PYTHON_BIN_VERSION 0 PY_BIN_VERSION_MAJOR)
        list (GET PYTHON_BIN_VERSION 1 PY_BIN_VERSION_MINOR)
        set (PYTHON_BIN_VERSION "${PY_BIN_VERSION_MAJOR}.${PY_BIN_VERSION_MINOR}")
        if (NOT ${PYTHON_BIN_VERSION} MATCHES ${PYTHON_LIB_VERSION})
            message (FATAL_ERROR "Python binary version ${PYTHON_BIN_VERSION} does not match library version ${PYTHON_LIB_VERSION}")
        endif ()
        message (STATUS "Found Python binary version ${PYTHON_BIN_VERSION} at ${PYTHON_BINARY}")
    else ()
        message (FATAL_ERROR "Failed to find Python binary; make sure the Python executable is in PATH")
    endif ()

    set (${RESULT} ${PYTHON_BINARY} PARENT_SCOPE)
endfunction ()

function (libgearbox_test_find_python_include_dirs RESULT)
    if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "WindowsStore")
        libgearbox_test_find_python()
        message (STATUS "Found Python headers for version ${PYTHON_LIB_VERSION} at ${PYTHON_INCLUDE_DIRS}")
    else ()
        set (PYTHON_INCLUDE_DIRS "")
        message (STATUS "Building for Universal Windows Platform, leaving Python include dirs unconfigured")
    endif ()

    set (${RESULT} ${PYTHON_INCLUDE_DIRS} PARENT_SCOPE)
endfunction ()

function (libgearbox_test_find_python_libraries RESULT)
    if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "WindowsStore")
        libgearbox_test_find_python()
        message (STATUS "Found Python libraries for version ${PYTHON_LIB_VERSION} at ${PYTHON_LIBRARIES}")
    else ()
        set (PYTHON_LIBRARIES "")
        message (STATUS "Building for Universal Windows Platform, leaving Python libraries unconfigured")
    endif ()

    set (${RESULT} ${PYTHON_LIBRARIES} PARENT_SCOPE)
endfunction ()
