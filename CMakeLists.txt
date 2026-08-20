cmake_minimum_required(VERSION 3.20)
project(zari VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)
find_library(NCURSESW_LIBRARY ncursesw REQUIRED)
include(GNUInstallDirs)

add_library(zari_core
  src/config.cpp src/filesystem.cpp src/keymap.cpp src/search.cpp
  src/tab.cpp src/task.cpp src/theme.cpp src/preview.cpp src/manager.cpp)
target_include_directories(zari_core PUBLIC include)
target_compile_options(zari_core PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(zari_core PUBLIC pthread)

add_executable(zari src/main.cpp src/app.cpp src/ui.cpp)
target_include_directories(zari PRIVATE include ${CURSES_INCLUDE_DIRS})
target_compile_options(zari PRIVATE -Wall -Wextra -Wpedantic)
target_compile_definitions(zari PRIVATE ZARI_VERSION="${PROJECT_VERSION}" ZARI_DATA_DIR="${CMAKE_INSTALL_FULL_DATADIR}/zari")
target_link_libraries(zari PRIVATE zari_core ${NCURSESW_LIBRARY})

install(TARGETS zari RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY themes/ DESTINATION ${CMAKE_INSTALL_DATADIR}/zari/themes)
install(FILES LICENSE COPYRIGHT README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

include(CTest)
if(BUILD_TESTING)
  add_executable(zari_tests tests/tests.cpp)
  target_link_libraries(zari_tests PRIVATE zari_core)
  target_compile_options(zari_tests PRIVATE -Wall -Wextra -Wpedantic)
  add_test(NAME zari_tests COMMAND zari_tests)
endif()

set(CPACK_PACKAGE_NAME "zari")
set(CPACK_PACKAGE_VENDOR "Zari contributors")
set(CPACK_PACKAGE_CONTACT "nihitdev@users.noreply.github.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fast, keyboard-driven terminal file manager")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://get-zari.vercel.app")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libncursesw6 (>= 6)")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "xdg-utils")
include(CPack)
