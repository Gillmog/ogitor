cmake_minimum_required(VERSION 2.8.10)

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

project(QtOfs)

find_package(Qt5Widgets REQUIRED)

if(NOT Qt5Widgets_FOUND)
	message(SEND_ERROR "Failed to find Qt 5.0.0 or greater.")
else(NOT Qt5Widgets_FOUND)
	set(CMAKE_PACKAGE_QTGUI TRUE)
	
	file(GLOB UI_FILES *.ui)

	set(SRCS
		./include/filelistwidget.hxx
		./src/filelistwidget.cpp
		./src/main.cpp
		./include/mainwindow.hxx
		./src/mainwindow.cpp
		./src/mainwindowactions.cpp
	)

	SET(MOC_SRCS2 
		./include/filelistwidget.hxx
		./include/mainwindow.hxx
	)

    set(OFS_QT_PREPROCESSOR "")

	qt5_wrap_cpp(MOC_SRCS ${MOC_SRCS2} OPTIONS ${OFS_QT_PREPROCESSOR})
	qt5_wrap_ui(UI_SRCS ${UI_FILES})

	source_group("Moc Files" FILES ${MOC_SRCS})
	source_group("Ui Files" FILES ${UI_FILES})

	# if we don't include this CMake will not include ui headers properly:
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
	include_directories(./include)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/OFS/include")

	qt5_add_resources(RESOURCE_SRCS ./res/qtOfs.qrc)
	source_group("Qrc Files" FILES ${RESOURCE_SRCS})

	set(SRCS ${SRCS} ${MOC_SRCS} ${UI_FILES})

	if(WIN32)
		file(GLOB qtOfs_res ./res/*.rc)
	endif(WIN32)

	if(UNIX)
	  ogitor_add_executable(qtOfs ${SRCS} ${RESOURCE_SRCS} ${qtOfs_res})
	endif(UNIX)
	if(WIN32)
	  ogitor_add_executable(qtOfs WIN32 ${SRCS} ${RESOURCE_SRCS} ${qtOfs_res})
	endif(WIN32)
	
	qt5_use_modules(qtOfs Widgets)

	if(WIN32)
		set_target_properties(qtOfs PROPERTIES DEBUG_POSTFIX _d)
		set_property(TARGET qtOfs PROPERTY WIN32_EXECUTABLE 1) 
	endif(WIN32)

	target_link_libraries(qtOfs ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES} OFS)

	if(WIN32)
	  target_link_libraries(qtOfs Qt5::WinMain)
	endif(WIN32)

	install(TARGETS qtOfs RUNTIME DESTINATION bin)
endif(NOT Qt5Widgets_FOUND)

# vim: set sw=2 ts=2 noet:
