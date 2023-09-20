add_library(Base64 Base64.cpp)
add_library(URL URL.cpp)
add_library(ZTEPanel ZTEPanel.cpp)

add_executable(${PROJECT_NAME} 
    ZTEPanel
    Base64
    URL
    main.cpp
)
