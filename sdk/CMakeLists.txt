set(TARGET_NAME blob-sdk-module)

# OpenCV 是依赖库
find_package(OpenCV REQUIRED)

# 添加一个动态库的 target，并且定义它的源文件、头文件和链接对象
add_library(${TARGET_NAME} SHARED)

# 这里头文件设置为PUBLIC是为了让link当前target的地方也能include
target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(${TARGET_NAME}
PRIVATE
    ./blob_sdk.cpp
)

# 不同平台对OpenCV的处理方式有区别
if(WIN32)
    target_link_libraries(${TARGET_NAME}
    PUBLIC     
        opencv_world)
else()
    target_link_libraries(${TARGET_NAME}
    PUBLIC  
        pthread   
        ${OpenCV_LIBS})
endif()

# 增加预处理宏用于win下导出符号
target_compile_definitions(${TARGET_NAME} PRIVATE SM_EXPORT)