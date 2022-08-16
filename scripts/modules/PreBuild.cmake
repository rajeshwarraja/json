include(GitInformation)

get_git_assembly_version(GIT_VERSION)
get_git_info(GIT_INFO)
configure_file(
	"${CMAKE_SOURCE_DIR}/scripts/version.c.in"
	"${CMAKE_CURRENT_BINARY_DIR}/version.c"
	@ONLY
)

include_directories(${CMAKE_SOURCE_DIR}/scripts)