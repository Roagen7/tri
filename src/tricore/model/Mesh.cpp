#include "Mesh.h"
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>


using namespace tri::core;

Mesh& Mesh::setVertices(std::vector<glm::vec3> vertices){
    isNotPredefinedMesh();
    this->vertices = vertices;
    setup();
    return *this;
}
Mesh& Mesh::setIndices(std::vector<glm::ivec3> indices){
    isNotPredefinedMesh();
    this->indices = indices;
    setup();
    return *this;
}

Mesh& Mesh::setNormals(std::vector<glm::vec3> normals){
    isNotPredefinedMesh();
    this->normals = normals;
    setup();
    return *this;
}

void Mesh::draw() const{
    glBindVertexArray(VAO);

    if(indices){
        glDrawElements(GL_TRIANGLES, indices->size() * 3, GL_UNSIGNED_INT, 0);
    } else if (vertices){
        glDrawArrays(GL_TRIANGLES, 0, vertices->size() * 3);
    }
    glBindVertexArray(0);        
}


Mesh& Mesh::setColors(std::vector<glm::vec3> colors){
    isNotPredefinedMesh();
    this->colors = colors;
    setup();
    return *this;
}

Mesh& Mesh::setTextureUnits(std::vector<glm::vec2> textureUnits){
    isNotPredefinedMesh();
    this->texture = textureUnits;
    setup();
    return *this;
}


void Mesh::setup(){
    cleanup();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    if(indices){
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLint) * 3, indices->data(), GL_STATIC_DRAW);
    }
    
    if(vertices){
        glGenBuffers(1, &VBOverts);
        glBindBuffer(GL_ARRAY_BUFFER, VBOverts);
        glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLfloat) * 3, vertices->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
    }

    if(normals){
        glGenBuffers(1, &VBOnormals);
        glBindBuffer(GL_ARRAY_BUFFER, VBOnormals);
        glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(GLfloat) * 3, normals->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(1);
    }

    if(texture){
        glGenBuffers(1, &VBOtexture);
        glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);
        glBufferData(GL_ARRAY_BUFFER, texture->size() * sizeof(GLfloat) * 2, texture->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(2);
    }

    if(normals && texture && vertices){
        // calculate tangents for normal mapping
        // https://computergraphics.stackexchange.com/questions/3990/where-is-the-best-place-for-tangent-bitangent-calculation-in-shader-or-in-c-cpp
        std::vector<glm::vec3> tangents;

        if(indices){
            for(const auto& triangle : *indices) {
                auto tangent = calculateTangent(triangle);
                tangents.push_back(tangent); tangents.push_back(tangent); tangents.push_back(tangent);
            }
        } else {
            for(int i = 0; i < vertices->size(); i+=3) {
                auto tangent = calculateTangent({i, i+1, i+2});
                tangents.push_back(tangent); tangents.push_back(tangent); tangents.push_back(tangent);
            }
        }

        glGenBuffers(1, &VBOtangents);
        glBindBuffer(GL_ARRAY_BUFFER, VBOtangents);
        glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(GLfloat) * 3, tangents.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(3);    
    }

    if(colors){
        glGenBuffers(1, &VBOcolors);
        glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
        glBufferData(GL_ARRAY_BUFFER, colors->size() * sizeof(GLfloat) * 3, colors->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(4);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::cleanup(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBOcolors);
    glDeleteBuffers(1, &VBOverts);
    glDeleteBuffers(1, &VBOnormals);
    glDeleteBuffers(1, &VBOtangents);
    glDeleteBuffers(1, &EBO);
}

// source: https://learnopengl.com/Advanced-Lighting/Normal-Mapping
glm::vec3 Mesh::calculateTangent(const glm::ivec3& triangle){
    assert(vertices);
    assert(texture);
    const auto& verticesNonOpt = *vertices;
    const auto& texturesNonOpt = *texture;
    auto pos1 = verticesNonOpt[triangle.x]; auto pos2 = verticesNonOpt[triangle.y]; auto pos3 = verticesNonOpt[triangle.z];
    auto uv1 = texturesNonOpt[triangle.x]; auto uv2 = texturesNonOpt[triangle.y]; auto uv3 = texturesNonOpt[triangle.z];

    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;  

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    return {
        f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
        f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
        f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
    };
}


Mesh::~Mesh(){
    cleanup(); 
}

Mesh::Mesh(const Mesh& other) {
    vertices = other.vertices;
    indices = other.indices;
    colors = other.colors;
    normals = other.normals;
    texture = other.texture;
    setup();
}

Mesh::Mesh(Mesh&& other) noexcept
    : vertices(std::move(other.vertices)),
      indices(std::move(other.indices)),
      colors(std::move(other.colors)),
      normals(std::move(other.normals)),
      texture(std::move(other.texture)),
      VAO(other.VAO), VBOverts(other.VBOverts), VBOcolors(other.VBOcolors),
      VBOnormals(other.VBOnormals), VBOtexture(other.VBOtexture), VBOtangents(other.VBOtangents), EBO(other.EBO) {
    other.VAO = 0;
    other.VBOverts = 0;
    other.VBOcolors = 0;
    other.VBOnormals = 0;
    other.VBOtexture = 0;
    other.VBOtangents = 0;
    other.EBO = 0;
}

Mesh& Mesh::operator=(const Mesh& other) {
    if (this == &other) {
        return *this;
    }

    vertices = other.vertices;
    indices = other.indices;
    colors = other.colors;
    normals = other.normals;
    texture = other.texture;
    setup();
    
    return *this;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    cleanup();

    vertices = std::move(other.vertices);
    indices = std::move(other.indices);
    colors = std::move(other.colors);
    normals = std::move(other.normals);
    texture = std::move(other.texture);

    VAO = other.VAO;
    VBOverts = other.VBOverts;
    VBOcolors = other.VBOcolors;
    VBOnormals = other.VBOnormals;
    VBOtexture = other.VBOtexture;
    VBOtangents = other.VBOtangents;
    EBO = other.EBO;

    other.VAO = 0;
    other.VBOverts = 0;
    other.VBOcolors = 0;
    other.VBOnormals = 0;
    other.VBOtexture = 0;
    other.VBOtangents = 0;
    other.EBO = 0;

    return *this;
}

bool Mesh::hasVertices(){
    return vertices.has_value();
}

/*
    simple OBJ parser
    OBJ format reference https://en.wikipedia.org/wiki/Wavefront_.obj_file
    NOTE: following case will not work - some vertices have texture/normal coords and some not
*/
Mesh Mesh::fromStream(std::istream& input){
    std::vector<glm::vec3> parsedVertices;
    std::vector<glm::vec3> parsedNormals;
    std::vector<glm::vec2> parsedTextures;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;

    while(!input.eof()){
        std::string line;
        std::getline(input, line);
        std::stringstream lineStream{line};
        std::string skipfirst;
        if(line.starts_with("vt")){
            glm::vec3 vt;
            lineStream >> skipfirst >> vt.x >> vt.y >> vt.z;
            parsedTextures.push_back(vt);
        } else if(line.starts_with("vn")){
            glm::vec3  vn; 
            lineStream >> skipfirst >> vn.x >> vn.y >> vn.z;
            parsedNormals.push_back(vn);
        } else if(line.starts_with("v")){
            glm::vec3  v;
            lineStream >> skipfirst >> v.x >> v.y >> v.z;
            parsedVertices.push_back(v); 
        } else if(line.starts_with("f")){
            lineStream >> skipfirst;
            const auto firstSlashPos = line.find('/');
            const auto secondSlashPos = line.find('/', firstSlashPos + 1);
            const auto nextSpacePos = line.find(' ', firstSlashPos);

            if (firstSlashPos == line.npos){
                // CASE: f v v v    
                glm::ivec3 indices;
                lineStream >> indices.x >> indices.y >> indices.z;
                indices -= glm::ivec3{1, 1, 1};

                auto v1 = parsedVertices[indices.x]; 
                auto v2 = parsedVertices[indices.y];
                auto v3 = parsedVertices[indices.z];
                auto normal = glm::cross(v2 - v1, v3 - v1);
                vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3);
                normals.push_back(normal); normals.push_back(normal); normals.push_back(normal);
            } else if (firstSlashPos + 1 == secondSlashPos){
                // f v1//vn1 v2//vn2 v3//vn3
                glm::ivec3 indices;
                glm::ivec3 indicesNormal;
                boost::replace_all(line, "//", " ");
                std::stringstream modifiedLineStream{line};
                modifiedLineStream >> skipfirst >> indices.x >> indicesNormal.x >> indices.y >> indicesNormal.y >> indices.z >> indicesNormal.z;
                indices -= glm::ivec3{1, 1, 1};
                indicesNormal -= glm::ivec3{1, 1, 1};

                auto v1 = parsedVertices[indices.x]; 
                auto v2 = parsedVertices[indices.y];
                auto v3 = parsedVertices[indices.z];
                auto vn1 = parsedNormals[indicesNormal.x]; 
                auto vn2 = parsedNormals[indicesNormal.y];
                auto vn3 = parsedNormals[indicesNormal.z];
                vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3);
                normals.push_back(vn1); normals.push_back(vn2); normals.push_back(vn3);
            } else if(secondSlashPos > nextSpacePos ) {
                // f v1/vt1 v2/vt2 v3/vt3
                glm::ivec3 indices;
                glm::ivec3 indicesTextures;
                boost::replace_all(line, "/", " ");
                std::stringstream modifiedLineStream{line};
                modifiedLineStream >> skipfirst >> indices.x >> indicesTextures.x >> indices.y >> indicesTextures.y >> indices.z >> indicesTextures.z;
                indices -= glm::ivec3{1, 1, 1};
                indicesTextures -= glm::ivec3{1, 1, 1};
                
                auto v1 = parsedVertices[indices.x]; 
                auto v2 = parsedVertices[indices.y];
                auto v3 = parsedVertices[indices.z];
                auto vt1 = parsedTextures[indicesTextures.x]; 
                auto vt2 = parsedTextures[indicesTextures.y];
                auto vt3 = parsedTextures[indicesTextures.z];
                auto normal = glm::cross(v2 - v1, v3 - v1);
          
                vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3);
                normals.push_back(normal); normals.push_back(normal); normals.push_back(normal);
                textures.push_back(vt1); textures.push_back(vt2); textures.push_back(vt3); 

            } else if (nextSpacePos != line.npos && secondSlashPos != line.npos){
                // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
                glm::ivec3 indices;
                glm::ivec3 indicesNormal;
                glm::ivec3 indicesTextures;
                boost::replace_all(line, "/", " ");
                std::stringstream modifiedLineStream{line};
                modifiedLineStream >> skipfirst >> indices.x >> indicesNormal.x >> indicesTextures.x 
                                >> indices.y >> indicesNormal.y >> indicesTextures.y 
                                >> indices.z >> indicesNormal.z >> indicesTextures.z;
                indices -= glm::ivec3{1, 1, 1};
                indicesTextures -= glm::ivec3{1, 1, 1};
                indicesNormal -= glm::ivec3{1, 1, 1};
                
                auto v1 = parsedVertices[indices.x]; 
                auto v2 = parsedVertices[indices.y];
                auto v3 = parsedVertices[indices.z];
                auto vt1 = parsedTextures[indicesTextures.x]; 
                auto vt2 = parsedTextures[indicesTextures.y];
                auto vt3 = parsedTextures[indicesTextures.z];
                auto vn1 = parsedNormals[indicesNormal.x]; 
                auto vn2 = parsedNormals[indicesNormal.y];
                auto vn3 = parsedNormals[indicesNormal.z];
                vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3);
                normals.push_back(vn1); normals.push_back(vn2); normals.push_back(vn3);
                textures.push_back(vt1); textures.push_back(vt2); textures.push_back(vt3); 
            } else {
                std::cerr << "error in obj file format at " << line << std::endl;
                assert(0);
            }
        } else if(!line.starts_with("#")) {
            // not supported, but log it
            std::cerr << "Warning, OBJ file has unsupported features: " << line << std::endl;
        }
    }
    Mesh mesh;
    mesh.setVertices(vertices).setNormals(normals).setTextureUnits(textures);
    return mesh;
}


Mesh Mesh::fromFile(const std::string& filename) {
    std::ifstream input(filename);
    if(!input.is_open()){
        std::cerr << "[ERROR] COULDN'T OPEN FILE " << filename << std::endl;
        assert(0);
    }
    
    return Mesh::fromStream(input);
}
