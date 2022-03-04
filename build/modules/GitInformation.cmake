function(_get_git_branch _branch)
	if(NOT "$ENV{GITVERSION_BRANCHNAME}" STREQUAL "")
		set(${_branch} $ENV{GITVERSION_BRANCHNAME} PARENT_SCOPE)
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

function(get_git_version _version)
	if(NOT "$ENV{GITVERSION_SEMVER}" STREQUAL "")
		set(${_version} "$ENV{GITVERSION_SEMVER}" PARENT_SCOPE)
	else()
		set(${_version} "0.0.0" PARENT_SCOPE)
	endif()
endfunction()

function(get_git_assembly_version _version)
	if(NOT "$ENV{GITVERSION_ASSEMBLYSEMFILEVER}" STREQUAL "")
		set(${_version} "$ENV{GITVERSION_ASSEMBLYSEMFILEVER}" PARENT_SCOPE)
	else()
		set(${_version} "0.0.0.0" PARENT_SCOPE)
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