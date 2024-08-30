cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets OpenGLWidgets)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MACOSX_BUNDLE_ICON_FILE 3DViewer.icns)
set(app_icon_macos "${CMAKE_SOURCE_DIR}/Resourses/3DViewer.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(PROJECT_SOURCES
        controller.cpp
        controller.h
        gifcreator.h
        gifcreator.cpp
        main.cpp
        model.cpp
        model.h
        openglwidget.cpp
        openglwidget.h
        view.cpp
        view.h
        view.ui
        thirdparty/gifanim/gifanim.h
        thirdparty/gifanim/gifanim.cpp
        Resourses.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_macos}
        memento.h
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3DViewer)
endif()
set_target_properties(3DViewer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 3DViewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

set(SRC model.cpp
)

set(TEST_SOURCES tests/s21_tests.cpp
)

set(TEST_DIR tests_build
)

add_library(s21_viewer STATIC ${SRC})
target_link_libraries(s21_viewer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_include_directories(s21_viewer PRIVATE ${Qt6_INCLUDE_DIRS})
set_target_properties(s21_viewer PROPERTIES PREFIX "" LINKER_LANGUAGE CXX)


add_executable(tests_run ${TEST_SOURCES})
target_link_libraries(tests_run gtest gtest_main s21_viewer gcov Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_include_directories(tests_run PRIVATE ${Qt6_INCLUDE_DIRS})

add_custom_target(coverage
        COMMAND ./tests_run
        DEPENDS tests_run
)

add_custom_target(coverage_report
        COMMAND gcovr -f ../model.cpp --exclude-throw-branches --html --html-details -o coverage.html --exclude "tests/"
        DEPENDS coverage
)

add_custom_target(test_leaks
        COMMAND valgrind --leak-check=full --error-exitcode=1 ./tests_run
        DEPENDS tests_run
)
