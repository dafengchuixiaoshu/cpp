include_directories(
./
)

link_directories(
)

set(SRC_BASE
./base/util.h
./base/util.cpp
./base/uid.h
./base/uid.cpp
./base/mutex.h
./base/time.h
./base/time.cpp
./base/file.h
./base/file.cpp
./base/stream.h
./base/logger.h
./base/logger.cpp
./base/condition.h
./base/queue.h
./base/atomic.h
./base/exception.h
./base/thread.h
./base/thread.cpp
)

set(SRC_LOG
)

add_library(qiuan ${SRC_BASE} ${SRC_LOG})

target_link_libraries(qiuan)

