cmake_minimum_required(VERSION 2.8)

project(lockfree)

set(LFDS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/liblfds/liblfds/liblfds7.1.0/liblfds710/inc")
set(LFDS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/liblfds/liblfds/liblfds7.1.0/liblfds710/src")
include_directories(${LFDS_INCLUDE_DIR})

set(LFDS_COMMON_SRC
    ${LFDS_SOURCE_DIR}/lfds710_misc/lfds710_misc_globals.c
    ${LFDS_SOURCE_DIR}/lfds710_misc/lfds710_misc_internal_backoff_init.c)
add_library(lfds ${LFDS_COMMON_SRC})

set(LFDS_FREELIST_SRC
    ${LFDS_SOURCE_DIR}/lfds710_freelist/lfds710_freelist_cleanup.c
    ${LFDS_SOURCE_DIR}/lfds710_freelist/lfds710_freelist_init.c
    ${LFDS_SOURCE_DIR}/lfds710_freelist/lfds710_freelist_query.c
    ${LFDS_SOURCE_DIR}/lfds710_freelist/lfds710_freelist_pop.c
    ${LFDS_SOURCE_DIR}/lfds710_freelist/lfds710_freelist_push.c)
add_library(lfds_freelist ${LFDS_FREELIST_SRC})
target_link_libraries(lfds_freelist lfds)

set(LFDS_QUEUE_UMM_SRC
    ${LFDS_SOURCE_DIR}/lfds710_queue_unbounded_manyproducer_manyconsumer/lfds710_queue_unbounded_manyproducer_manyconsumer_cleanup.c
    ${LFDS_SOURCE_DIR}/lfds710_queue_unbounded_manyproducer_manyconsumer/lfds710_queue_unbounded_manyproducer_manyconsumer_dequeue.c
    ${LFDS_SOURCE_DIR}/lfds710_queue_unbounded_manyproducer_manyconsumer/lfds710_queue_unbounded_manyproducer_manyconsumer_enqueue.c
    ${LFDS_SOURCE_DIR}/lfds710_queue_unbounded_manyproducer_manyconsumer/lfds710_queue_unbounded_manyproducer_manyconsumer_init.c
    ${LFDS_SOURCE_DIR}/lfds710_queue_unbounded_manyproducer_manyconsumer/lfds710_queue_unbounded_manyproducer_manyconsumer_query.c)
add_library(lfds_queue_umm ${LFDS_QUEUE_UMM_SRC})
target_link_libraries(lfds_queue_umm lfds)

set(LFDS_RINGBUFFER_SRC
    ${LFDS_SOURCE_DIR}/lfds710_ringbuffer/lfds710_ringbuffer_cleanup.c
    ${LFDS_SOURCE_DIR}/lfds710_ringbuffer/lfds710_ringbuffer_init.c
    ${LFDS_SOURCE_DIR}/lfds710_ringbuffer/lfds710_ringbuffer_query.c
    ${LFDS_SOURCE_DIR}/lfds710_ringbuffer/lfds710_ringbuffer_read.c
    ${LFDS_SOURCE_DIR}/lfds710_ringbuffer/lfds710_ringbuffer_write.c)
add_library(lfds_ringbuffer ${LFDS_RINGBUFFER_SRC})
target_link_libraries(lfds_ringbuffer lfds lfds_freelist lfds_queue_umm)

set(LFDS_STACK_SRC
    ${LFDS_SOURCE_DIR}/lfds710_misc/lfds710_misc_internal_backoff_init.c
    ${LFDS_SOURCE_DIR}/lfds710_stack/lfds710_stack_cleanup.c
    ${LFDS_SOURCE_DIR}/lfds710_stack/lfds710_stack_init.c
    ${LFDS_SOURCE_DIR}/lfds710_stack/lfds710_stack_pop.c
    ${LFDS_SOURCE_DIR}/lfds710_stack/lfds710_stack_push.c
    ${LFDS_SOURCE_DIR}/lfds710_stack/lfds710_stack_query.c)
add_library(lfds_stack ${LFDS_STACK_SRC})
target_link_libraries(lfds_freelist lfds)

if(BUILD_TESTING)
    add_executable(ringbuffer $<TARGET_OBJECTS:range> ringbuffer_test.cpp)
    add_executable(stack stack_test.cpp)
    target_link_libraries(ringbuffer lfds_ringbuffer gtest)
    target_link_libraries(stack lfds_stack gtest)

    add_test(Lockfree_Stack stack)
    add_test(Lockfree_Ringbuffer ringbuffer)

    find_package(Threads)
    if(Threads_FOUND)
        add_executable(stack_racing stack_racing_test.cpp)
        add_executable(stack_timing stack_timing_test.cpp)
        target_link_libraries(stack_racing lfds_stack gtest)
        target_link_libraries(stack_timing lfds_stack gtest)
        add_test(Lockfree_StackRacing stack_racing)
        add_test(Lockfree_StackTiming stack_timing)
    endif()
endif()
