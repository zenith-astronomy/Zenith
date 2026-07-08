target_sources(Zenith PRIVATE
    MainWindow.h
    MainWindow.cpp
)

add_subdirectory(core)
add_subdirectory(workspace)
add_subdirectory(services)
add_subdirectory(dialogs)
