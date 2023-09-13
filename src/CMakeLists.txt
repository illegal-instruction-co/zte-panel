add_library(Base64 Base64.cpp)
add_library(ZTEPanel ZTEPanel.cpp)

add_executable(Panel 
    ZTEPanel
    Base64
    main.cpp
)
