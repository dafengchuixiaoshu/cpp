include_directories(
./
)

link_directories(
)

set(SRC_CORE
    ./systemutil.h
    ./systemutil.cpp
    ./nocopyable.h
    ./singleton.h
    ./stringutil.h
    ./uuid.h
    ./uuid.cpp
    ./exception.h
)

add_library(core ${SRC_CORE})

target_link_libraries(core)

