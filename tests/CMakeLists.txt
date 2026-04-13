include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723  # или хэш коммита для детерминированности
)
FetchContent_MakeAvailable(googletest)
find_package(Threads REQUIRED)

add_subdirectory("Player")
add_subdirectory("Controller")