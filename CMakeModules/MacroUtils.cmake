MACRO(addDLLs TGT_NAME SOURCE_LIBRARY INSTALLATION_TGT)
	FILE(GLOB DLLS_FILES ${SOURCE_LIBRARY}/*.dll)
	foreach(ConfigFile ${DLLS_FILES})
	  #add_custom_command(TARGET ${TGT_NAME} POST_BUILD
	  #                   COMMAND ${CMAKE_COMMAND} -E
	  #                       copy ${ConfigFile} ${TARGET_LIBRARY})
	  install(FILES ${ConfigFile} DESTINATION ${INSTALLATION_TGT})
	endforeach()
ENDMACRO(addDLLs)

FUNCTION(SETOUTPUTS TGT_NAME ROOT_TGT)
	#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_TGT}/lib)
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_TGT}/lib)
	#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_TGT}/bin)

	set_target_properties(${TGT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${ROOT_TGT}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${ROOT_TGT}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${ROOT_TGT}/bin"
)
ENDFUNCTION(SETOUTPUTS)


MACRO(STATIC_OR_DYNAMIC_LINKING)
    string(TOUPPER ${SUB_PROJECT_NAME} SUB_PROJ_UC)
	IF(DYNAMIC_LINKING)
		ADD_DEFINITIONS(-DUSE_${SUB_PROJ_UC}_DYN)
	ELSE (DYNAMIC_LINKING)
		ADD_DEFINITIONS(-DUSE_${SUB_PROJ_UC}_STATIC)
	ENDIF(DYNAMIC_LINKING)
ENDMACRO(STATIC_OR_DYNAMIC_LINKING)

#######################################################################################################
#  macro for common setup: it links OPENGL_LIBRARIES in undifferentiated mode (just release version)
#######################################################################################################

MACRO(LINK_OPENGL_LIBRARIES TRGTNAME)
    TARGET_LINK_LIBRARIES(${TRGTNAME} ${OPENGL_LIBRARIES})
ENDMACRO(LINK_OPENGL_LIBRARIES TRGTNAME)



#######################################################################################################
# Macro for linking libraries that come from Findxxxx commands, so there is a variable that contains the
# full path of the library name. in order to differentiate release and debug, this macro get the
# NAME of the variables, so the macro gets as arguments the target name and the following list of parameters
# is intended as a list of variable names each one containing  the path of the libraries to link to
# The existance of a varibale name with _DEBUG appended is tested and, in case it' s value is used
# for linking to when in debug mode
#######################################################################################################

MACRO(LINK_WITH_VARIABLES TRGTNAME)
    FOREACH(varname ${ARGN})
        IF(${varname}_DEBUG)
            TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}_DEBUG}")
        ELSE(${varname}_DEBUG)
            TARGET_LINK_LIBRARIES(${TRGTNAME} "${${varname}}" )
        ENDIF(${varname}_DEBUG)
    ENDFOREACH(varname)
ENDMACRO(LINK_WITH_VARIABLES TRGTNAME)
        

######################################################################
# This sets up the libraries to link to, the variable TARGET_COMMON_LIBRARIES
# can hold a common libraries for applications / examples.
# The suffix ${CMAKE_DEBUG_POSTFIX} is used for differentiating optimized and debug
#
# a second variable TARGET_EXTERNAL_LIBRARIES hold the list of libraries not differentiated between debug and optimized 
##################################################################################
    
MACRO(SETUP_LINK_LIBRARIES)
    IF(TARGET_COMMON_LIBRARIES)
      TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME} ${TARGET_COMMON_LIBRARIES})
    ENDIF(TARGET_COMMON_LIBRARIES)
    
    IF(TARGET_ADDITIONAL_LIBRARIES)
		  TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME} ${TARGET_ADDITIONAL_LIBRARIES})
    ENDIF(TARGET_ADDITIONAL_LIBRARIES)
	
    IF(TARGET_VARS_LIBRARIES)
		  LINK_WITH_VARIABLES(${TARGET_TARGETNAME} ${TARGET_VARS_LIBRARIES})
    ENDIF(TARGET_VARS_LIBRARIES)
ENDMACRO(SETUP_LINK_LIBRARIES)


###########################################################
# this is the macro for application setup
###########################################################

MACRO(SETUP_EXE)
    IF(NOT TARGET_TARGETNAME)
            SET(TARGET_TARGETNAME "${TARGET_DEFAULT_PREFIX}${TARGET_NAME}")
    ENDIF(NOT TARGET_TARGETNAME)
    IF(NOT TARGET_LABEL)
            SET(TARGET_LABEL "${TARGET_DEFAULT_LABEL_PREFIX} ${TARGET_NAME}")
    ENDIF(NOT TARGET_LABEL)

    ADD_EXECUTABLE(${TARGET_TARGETNAME} ${TARGET_SRC} ${TARGET_H} ${ADDITIONAL_FILES})
    
    IF(MODULE_DEPENDENCIES)
       ADD_DEPENDENCIES(${TARGET_TARGETNAME} ${MODULE_DEPENDENCIES} )
    ENDIF(MODULE_DEPENDENCIES)

    SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES PROJECT_LABEL "${TARGET_LABEL}")
    SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})

    IF(MSVC)
		  SET_TARGET_PROPERTIES(${TARGET_TARGETNAME} PROPERTIES PREFIX "../")    
    ENDIF(MSVC)

    SETUP_LINK_LIBRARIES()    
ENDMACRO(SETUP_EXE)



###########################################################
# this is the main entry point for compiling an application
###########################################################

MACRO(SETUP_APPLICATION APPLICATION_NAME)
        SET(TARGET_NAME ${APPLICATION_NAME} )
        SETUP_EXE()
        INSTALL(TARGETS ${TARGET_TARGETNAME} RUNTIME DESTINATION bin  )
ENDMACRO(SETUP_APPLICATION)

# setup application with automatic linking to opengl-libs (which means the linking is 
# done here and not in the application's-cmake-file)
MACRO(SETUP_APPLICATION_WITH_OPENGL_LINKING APPLICATION_NAME)
        SET(TARGET_NAME ${APPLICATION_NAME} )
        SETUP_EXE()
        # do now the opengl linking
        LINK_OPENGL_LIBRARIES(${TARGET_TARGETNAME})
        INSTALL(TARGETS ${TARGET_TARGETNAME} RUNTIME DESTINATION bin  )
ENDMACRO(SETUP_APPLICATION_WITH_OPENGL_LINKING)


###########################################################
# this is the main entry point for compiling an example
###########################################################

MACRO(SETUP_EXAMPLE EXAMPLE_NAME)
        SET(TARGET_NAME ${EXAMPLE_NAME} )
        SETUP_EXE()
        INSTALL(TARGETS ${TARGET_TARGETNAME} RUNTIME DESTINATION share/bin  )
ENDMACRO(SETUP_EXAMPLE)


# setup example with automatic linking to opengl-libs (which means the linking is 
# done here and not in the example's-cmake-file)
MACRO(SETUP_EXAMPLE_WITH_OPENGL_LINKING EXAMPLE_NAME)
        SET(TARGET_NAME ${EXAMPLE_NAME} )
        SETUP_EXE()
        # do now the opengl linking
        LINK_OPENGL_LIBRARIES(${TARGET_TARGETNAME})
        INSTALL(TARGETS ${TARGET_TARGETNAME} RUNTIME DESTINATION share/bin  )
ENDMACRO(SETUP_EXAMPLE_WITH_OPENGL_LINKING)