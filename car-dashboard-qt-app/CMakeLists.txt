cmake_minimum_required(VERSION 3.16)

project(car-dashboard-subscription VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Automatically run moc for files with Q_OBJECT
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Network Multimedia)
# find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Test Network)

# Main application
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appcar-dashboard-subscription
    main.cpp
)

qt_add_qml_module(appcar-dashboard-subscription
    URI car-dashboard-subscription
    VERSION 1.0
    QML_FILES
        Main.qml
        Dashboard.qml
        Fuel.qml
        FuelNeedle.qml
        Gear.qml
        Info.qml
        Speed.qml
        SpeedNeedle.qml
        Turn.qml
    SOURCES
        CarData.h
        CarData.cpp
        RESOURCES rc.qrc
)

# Separate Unit Test Target
# add_executable(unitest_cardata unitest_cardata.cpp)

# Link Qt6 test and network modules to unit tests
# target_link_libraries(unitest_cardata Qt6::Test Qt6::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS, you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcar-dashboard-subscription PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Link Qt modules for the main application
target_link_libraries(appcar-dashboard-subscription
    PRIVATE Qt6::Quick Qt6::Network Qt6::Multimedia
)

# Install Targets
include(GNUInstallDirs)
install(TARGETS appcar-dashboard-subscription
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
