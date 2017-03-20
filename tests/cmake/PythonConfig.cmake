find_package (PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
    pkg_search_module (PYTHON QUIET python3>=3.5)
endif ()

if (PYTHON_FOUND)
    set (GEARBOX_PY_LIB_DIRS ${PYTHON_LIBRARY_DIRS})
else ()
    find_package (PythonLibs QUIET) 
    if (PYTHONLIBS_FOUND)
        string(REPLACE "." ";" PYTHON_VERSION ${PYTHONLIBS_VERSION_STRING})
        list (GET PYTHON_VERSION 0 PYTHON_VERSION_MAJOR)
        list (GET PYTHON_VERSION 1 PYTHON_VERSION_MINOR)
        if ((NOT (${PYTHON_VERSION_MAJOR} LESS 3)) AND (NOT (${PYTHON_VERSION_MINOR} LESS 5)))
            set (PYTHON_FOUND 1)
        else ()
            message (WARNING "Python is older than the minimum supported version, consider upgrading to at least 3.5")
        endif ()
    endif()
endif ()

if (PYTHON_FOUND)
    set (GEARBOX_PY_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
    set (GEARBOX_PY_LIBS ${PYTHON_LIBRARIES})
else ()
    message (FATAL_ERROR "Python libraries could not be found. Consider supplying PYTHON_LIBRARY and PYTHON_INCLUDE_DIR to your CMake command-line.")
endif ()
