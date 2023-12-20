Project(SudokuLib)

set(SOURCE_FILES
        Digit.cpp
        Digit.h
        DigitContainer.cpp
        DigitContainer.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        ItemVisitor.cpp
        ItemVisitor.h
        MainFrame.cpp
        MainFrame.h
        Sparty.cpp
        Sparty.h
        Xray.cpp
        Xray.h
        SudokuView.cpp
        StopWatch.cpp
        StopWatch.h
        Background.h
        Background.cpp
        Given.cpp
        Given.h
        EatDigitVisitor.cpp
        EatDigitVisitor.h
        DigitSpitVisitor.cpp
        DigitSpitVisitor.h
        GivenCheck.cpp
        GivenCheck.h
        AnimatedText.cpp
        AnimatedText.h
        DigitCheck.h
        DigitCheck.cpp
        SolveVisitor.cpp
        SolveVisitor.h

)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)