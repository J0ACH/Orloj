
# LIB SETUP ###################################################

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_subdirectory(clocks)
add_subdirectory(test)

add_library( Orloj SHARED 
	${Orloj_hdr}
	${Orloj_src}
)

target_link_libraries(Orloj
	PRIVATE
		Qt5::Core
)

target_include_directories(Orloj
	PRIVATE 
		${CMAKE_CURRENT_LIST_DIR}/clocks
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:${PROJECT_NAME}_${PROJECT_VERSION}/include>
)

add_custom_command(TARGET Orloj
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Orloj_hdr} ${CMAKE_BINARY_DIR}/include
)

# TESTER SETUP ###################################################

add_executable(OrlojTest 
	${OrlojTest_hdr}
	${OrlojTest_src}
)

target_include_directories(OrlojTest 
	PRIVATE 
		${CMAKE_CURRENT_LIST_DIR}/test
		${CMAKE_CURRENT_LIST_DIR}/clocks
)
target_link_libraries(OrlojTest 
	PRIVATE
		Orloj
		Qt5::Core
		Qt5::Widgets
)

# BUILD SETUP ###################################################

string(TOUPPER ${CMAKE_CONFIGURATION_TYPES} configType)
set_target_properties( Orloj OrlojTest
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY_${configType} ${CMAKE_BINARY_DIR}/lib
		LIBRARY_OUTPUT_DIRECTORY_${configType} ${CMAKE_BINARY_DIR}/lib
		RUNTIME_OUTPUT_DIRECTORY_${configType} ${CMAKE_BINARY_DIR}/bin
		DEBUG_POSTFIX d
)

# PACKAGE SETUP ###################################################
include(CMakePackageConfigHelpers)
configure_package_config_file (
	${CMAKE_CURRENT_LIST_DIR}/OrlojConfig.cmake.in
	${CMAKE_BINARY_DIR}/cmake/OrlojConfig.cmake
	INSTALL_DESTINATION Orloj_${PROJECT_VERSION}/cmake
)
write_basic_package_version_file(
	${CMAKE_BINARY_DIR}/cmake/OrlojConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion 
)
cmake_policy(SET CMP0022 NEW)
export ( 
	TARGETS Orloj
	FILE ${CMAKE_BINARY_DIR}/cmake/OrlojTargets-${CMAKE_CONFIGURATION_TYPES}.cmake 
	EXPORT_LINK_INTERFACE_LIBRARIES
)

# LIB INSTALL ###################################################

install(
	TARGETS Orloj
	EXPORT OrlojTargets
	ARCHIVE DESTINATION Orloj_${PROJECT_VERSION}/lib
    LIBRARY DESTINATION Orloj_${PROJECT_VERSION}/lib
	RUNTIME DESTINATION Orloj_${PROJECT_VERSION}/bin
)
install(
	FILES ${library_hdr}
	DESTINATION Orloj_${PROJECT_VERSION}/include
)
install(
	FILES
		${CMAKE_BINARY_DIR}/cmake/OrlojConfig.cmake
		${CMAKE_BINARY_DIR}/cmake/OrlojConfigVersion.cmake
	DESTINATION	Orloj_${PROJECT_VERSION}/cmake
)
install(
	EXPORT OrlojTargets
	DESTINATION Orloj_${PROJECT_VERSION}/cmake
	FILE OrlojTargets.cmake
)
#[[
#]]

