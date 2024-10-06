cmake_minimum_required(VERSION 3.16)

# Project declaration
# @project EvaliQ
# @brief This project is a Qt application for candidate evaluation.
#
# The application uses various Qt components, including Widgets and Quick,
# and is set up for C++17.
project(EvaliQ VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of UIC, MOC, and RCC files
set(CMAKE_AUTOUIC ON)  # Automatically handle .ui files
set(CMAKE_AUTOMOC ON)  # Automatically handle Qt meta-object compilation
set(CMAKE_AUTORCC ON)  # Automatically handle Qt resource files

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)  # Set C++17 as the standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++17

# Find required Qt packages
# @note This finds the appropriate version of Qt (Qt5 or Qt6).
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Quick QuickWidgets QuickControls2 Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Quick QuickWidgets QuickControls2 Sql)

# Define project source files
# @var PROJECT_SOURCES
# @brief The list of source files for the EvaliQ application.
set(PROJECT_SOURCES
    main.cpp
    views/mainwindow.cpp
    views/mainwindow.h
    views/mainwindow.ui
    views/savecandidatedialog.h views/savecandidatedialog.cpp views/savecandidatedialog.ui
    sql/sqlserverconnection.h sql/sqlserverconnection.cpp
    models/question.h
    models/candidate.h
    models/makers/questionmaker.h models/makers/questionmaker.cpp
    models/makers/candidatemaker.h models/makers/candidatemaker.cpp
    enums/enums.h
    json/jsonfilereader.h json/jsonfilereader.cpp
    res.qrc
)

# Add executable target based on Qt version
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EvaliQ
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
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

# Link necessary Qt libraries to the executable
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::QuickControls2)
target_link_libraries(EvaliQ PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

# Include directories
target_include_directories(EvaliQ PRIVATE .)

# Set bundle ID for macOS if the version is less than 6.1.0
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EvaliQ)
endif()

# Set properties for the executable target
set_target_properties(EvaliQ PROPERTIES
    ${BUNDLE_ID_OPTION}  # Set the bundle ID option
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}  # Set the bundle version
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}  # Set short version string
    MACOSX_BUNDLE TRUE  # Enable macOS bundle
    WIN32_EXECUTABLE TRUE  # Mark as a Windows executable
)

# Include installation directories
include(GNUInstallDirs)

# Install target configuration
install(TARGETS EvaliQ
    BUNDLE DESTINATION .  # Bundle destination
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # Library destination
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # Runtime destination
)

# Finalize executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EvaliQ)
endif()
