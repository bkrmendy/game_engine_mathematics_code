//
// Created by Berci on 2020. 12. 06..
//

#include <catch2/catch.hpp>
#include "rapidcheck.h"

#include "../src/Vector/Vector.h"
#include "../src/Line/Line.h"
#include "../src/Plane/Plane.h"
#include "../src/intersection/intersection.h"

TEST_CASE("Line", "[line]") {
    SECTION("Point along line") {
        GEM::Line line{GEM::Vector<4, float>{{0, 0, 0, 1}},
                        GEM::Vector<4, float>{{0, 1, 0, 0}}};

        auto point = GEM::point_along_line(line, 3);

        REQUIRE(point.at(0) == Approx(0).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(1) == Approx(3).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(2) == Approx(0).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(3) == 1);
    }

    SECTION("Point along line, Property") {
        rc::check("Point along line", [](float s1, float s2, float s3, float v1, float v2, float v3, float t) {
               GEM::Line line{GEM::Vector<4, float>{{s1, s2, s3, 1}},
                              GEM::Vector<4, float>{{v1, v2, v3, 0}}};

               auto point = GEM::point_along_line(line, t);

               float p1_pos = line.origin().at(0) + line.direction().at(0) * t;
               float p2_pos = line.origin().at(1) + line.direction().at(1) * t;
               float p3_pos = line.origin().at(2) + line.direction().at(2) * t;

               float tolerance = 0.001f;

               REQUIRE(point.at(0) == Approx(p1_pos).epsilon(tolerance));
               REQUIRE(point.at(1) == Approx(p2_pos).epsilon(tolerance));
               REQUIRE(point.at(2) == Approx(p3_pos).epsilon(tolerance));
               REQUIRE(point.at(3) == 1);
        });
    }

    SECTION("Line intersection with parallel plane") {
        GEM::Line line{GEM::Vector<4, float>{{0, 0, 0, 1}},
                       GEM::Vector<4, float>{{0, 1, 0, 0}}};

        GEM::Plane plane{GEM::Vector<4, float>{ { 1, 0, 0, 0 } }};

        auto intersection_point = GEM::intersects(line, plane);

        REQUIRE(intersection_point == std::nullopt);
    }

    SECTION("Line intersection with perpendicular plane") {
        GEM::Line line{GEM::Vector<4, float>{{0, 0, 0, 1}},
                       GEM::Vector<4, float>{{0, 1, 0, 0}}};

        GEM::Plane plane{GEM::Vector<4, float>{ { 0, 1, 0, 0 } }};

        auto intersection_point = GEM::intersects(line, plane);

        REQUIRE(intersection_point.has_value());

        auto point = intersection_point.value();

        REQUIRE(point.at(0) == Approx(0).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(1) == Approx(0).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(2) == Approx(0).epsilon(std::numeric_limits<float>::epsilon()));
        REQUIRE(point.at(3) == 1);
    }
}