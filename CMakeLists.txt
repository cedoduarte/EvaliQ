cmake_minimum_required(VERSION 3.16)

project(EvaliQ VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Quick QuickWidgets QuickControls2 Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Quick QuickWidgets QuickControls2 Sql)

set(PROJECT_SOURCES
    main.cpp
    views/mainwindow.cpp
    views/mainwindow.h
    views/mainwindow.ui
    sql/sqlserverconnection.h sql/sqlserverconnection.cpp
    models/question.h
    makers/questionmaker.h makers/questionmaker.cpp
    enums/enums.h
    json/jsonfilereader.h json/jsonfilereader.cpp
    res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EvaliQ
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        views/savecandidatedialog.h views/savecandidatedialog.cpp views/savecandidatedialog.ui
        models/candidate.h
        makers/candidatemaker.h makers/candidatemaker.cpp
    )
else()
    if(ANDROID)
        add_library(EvaliQ SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(EvaliQ
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::QuickControls2)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

target_include_directories(EvaliQ PRIVATE .)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EvaliQ)
endif()
set_target_properties(EvaliQ PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EvaliQ
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EvaliQ)
endif()
