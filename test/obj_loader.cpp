#include <gtest/gtest.h>
#include <tricore/model/Mesh.h>
#include <sstream>

using namespace tri::core;

TEST(ObjLoader, SimpleObj){
    std::stringstream stream;
    stream << "v  0  0  0" << std::endl
           << "v  1  0  0" << std::endl
           << "v  1  1  0" << std::endl
           << "v  0  1  0" << std::endl
           << "v  0.5 0.5 1.6" << std::endl
           << "f  5  2  3" << std::endl
           << "f  4  5  3" << std::endl
           << "f  6  3  2" << std::endl
           << "f  5  6  2" << std::endl
           << "f  4  6  5" << std::endl
           << "f  6  4  3";

    const auto [vertices, normals, textures] = Mesh::fromStream(stream);
    ASSERT_EQ(vertices.size(), 18);
    ASSERT_EQ(textures.size(), 0);
    ASSERT_EQ(normals.size(), 18);
}

TEST(ObjLoader, ComplexObj){

}