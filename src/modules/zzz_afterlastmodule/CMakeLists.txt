# CMakeLists.txt for src/modules/zzz_afterlastmodule
if(APPLE)
	get_target_property(QT_LIBRARY_DIR Qt${QT_VERSION_MAJOR}::Core LOCATION)
	get_filename_component(QT_LIBRARY_DIR ${QT_LIBRARY_DIR} PATH)
	#MESSAGE(STATUS "Qt Library dir is ${QT_LIBRARY_DIR}")

	install(CODE "
	    file(GLOB_RECURSE KVIRC_INSTALLED_MODULES
	      \"${KVIRC_MOD_PATH}/*.so\")
	    include(BundleUtilities)
	    fixup_bundle(\"${CMAKE_INSTALL_PREFIX}\" \"\${KVIRC_INSTALLED_MODULES}\" \"${QT_LIBRARY_DIR}\" IGNORE_ITEM Python)
	    " COMPONENT Runtime)
endif()
