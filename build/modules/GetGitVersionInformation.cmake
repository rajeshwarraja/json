function(get_git_version_information _version)
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" rev-list --count HEAD
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE NCOMMIT
		ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if("${PROJECT_VERSION}" STREQUAL "")
		set(PROJECT_VERSION "0.0.0")
	endif()

	set(${_version} ${PROJECT_VERSION}.${NCOMMIT} PARENT_SCOPE)
endfunction()