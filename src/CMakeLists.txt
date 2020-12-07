set (CMAKE_CXX_STANDARD 17)

add_library(gem
        Vector/Vector.h

        Matrix/Matrix.h

        Transforms/Transforms.h

        Utility/Utility.h
        Utility/FloatingPointEquals.h

        Quaternion/Quaternion.h

        Line/Line.h
        Line/Line.cpp

        Plane/Plane.h
        Plane/Plane.cpp

        intersection/intersection.h
        intersection/intersection.cpp
        )

add_executable(gem_main main.cpp)

target_link_libraries(
        gem_main
        PRIVATE project_options
                project_warnings
                CONAN_PKG::docopt.cpp
                CONAN_PKG::fmt
                CONAN_PKG::spdlog)
