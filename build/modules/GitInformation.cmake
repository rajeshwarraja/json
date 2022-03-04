function(_get_git_branch _branch)
	if(NOT "$ENV{GITHUB_REF_NAME}" STREQUAL "")
		set(${_branch} $ENV{GITHUB_REF_NAME} PARENT_SCOPE)
	else()
		execute_process(
			COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE BRANCH
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		set(${_branch} ${BRANCH} PARENT_SCOPE)
	endif()
endfunction()

function(_normalize_branch_name _out_name _in_name)
	string(REGEX REPLACE "[^a-zA-Z0-9]" "" _out ${_in_name})
	set(${_out_name} ${_out} PARENT_SCOPE)
endfunction()

function(get_git_version _version)
	# endure project version is available
	if("${PROJECT_VERSION}" STREQUAL "")
		set(PROJECT_VERSION "0.0.0")
	endif()

	if(NOT "$ENV{GITHUB_RUN_NUMBER}" STREQUAL "")
		set(NCOMMIT "$ENV{GITHUB_RUN_NUMBER}")
	else()
		execute_process(
			COMMAND "${GIT_EXECUTABLE}" rev-list --count HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE NCOMMIT
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		if("${NCOMMIT}" STREQUAL "")
			set(NCOMMIT "0")
		endif()
	endif()

	# calculate suffix for GitFlow
	_get_git_branch(GIT_BRANCH)
	if(NOT ${GIT_BRANCH} STREQUAL "")
		_normalize_branch_name(GIT_BRANCH_NORMALIZED ${GIT_BRANCH})
		if("${GIT_BRANCH}" STREQUAL "main" OR "${GIT_BRANCH}" STREQUAL "master" OR "${GIT_BRANCH}" MATCHES "^release\/.+$")
			math(EXPR BUILD_NUMBER "${NCOMMIT} + 100000")
			set(${_version} "${PROJECT_VERSION}.${BUILD_NUMBER}" PARENT_SCOPE)
		else()
			math(EXPR BUILD_NUMBER "${NCOMMIT} + 10000")
			set(${_version} "${PROJECT_VERSION}.${BUILD_NUMBER}-${GIT_BRANCH_NORMALIZED}" PARENT_SCOPE)
		endif()
	else()
		set(${_version} "${PROJECT_VERSION}.${NCOMMIT}" PARENT_SCOPE)
	endif()
endfunction()

function(get_git_repository_url _url)
	if(NOT "$ENV{GITHUB_SERVER_URL}" STREQUAL "")
		set(${_url} "$ENV{GITHUB_SERVER_URL}/$ENV{GITHUB_REPOSITORY}.git" PARENT_SCOPE)
	else()
		execute_process(
			COMMAND "${GIT_EXECUTABLE}" config --get remote.origin.url
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE URL
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		set(${_url} ${URL} PARENT_SCOPE)
	endif()
endfunction()

function(get_git_commit _hash)
	if(NOT "$ENV{GITHUB_SHA}" STREQUAL "")
		set(${_hash} $ENV{GITHUB_SHA} PARENT_SCOPE)
	else()
	_get_git_branch(BRANCH)
		execute_process(
			COMMAND "${GIT_EXECUTABLE}" rev-parse ${BRANCH}
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE HASH
			ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
		)
		set(${_hash} ${HASH} PARENT_SCOPE)
	endif()
endfunction()

function(display_project_label)
	message(STATUS "   Name: ${PROJECT_NAME}")
	get_git_version(GIT_VERSION)
	message(STATUS "Version: ${GIT_VERSION}")
	get_git_repository_url(GIT_REPO_URL)
	message(STATUS "    Url: ${GIT_REPO_URL}")
	_get_git_branch(GIT_BRANCH)
	message(STATUS " Branch: ${GIT_BRANCH}")
	get_git_commit(GIT_COMMIT)
	message(STATUS " Commit: ${GIT_COMMIT}")
endfunction()