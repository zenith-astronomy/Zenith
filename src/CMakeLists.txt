target_sources(Zenith PRIVATE
    MainWindow.h
    MainWindow.cpp
)

add_subdirectory(core)
add_subdirectory(dialogs)
add_subdirectory(preferences)
add_subdirectory(services)
add_subdirectory(workspace)
