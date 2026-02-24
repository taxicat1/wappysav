cmake_minimum_required(VERSION 3.16)

project(wappysav2 VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        save_proc.c
        save_proc.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/res.rc")

    qt_add_executable(wappysav2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        mainwindow.h save_proc.c save_proc.h
        ${app_icon_resource_windows}


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET wappysav2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(wappysav2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(wappysav2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(wappysav2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.wappysav2)
endif()
target_compile_features(wappysav2 PUBLIC cxx_std_20)

set_target_properties(wappysav2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS wappysav2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)




if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(wappysav2)
endif()
