#include "linear.h"
// Suppress warnings in third-party code.
#include <framework/disable_all_warnings.h>
DISABLE_WARNINGS_PUSH()
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
DISABLE_WARNINGS_POP()
#include <iostream>
#include <algorithm>
#include <numbers>

std::string to_string(const Matrix3& matrix)
{
    return "matrix with columns:\n Col1 " + to_string(matrix.col1) + "\n Col2 " + to_string(matrix.col2) + "\n Col3 " + to_string(matrix.col3);
}

// ==================================
// ========    Exercise 0    ========
// ==================================
// Multiplication of a vector with a scalar
glm::vec3 mul(const glm::vec3& lhs, float rhs)
{
    glm::vec3 result {lhs.x*rhs, lhs.y*rhs, lhs.z*rhs};
    // Your solution goes here
    // Do *NOT* use glm functionality here, but implement the multiplication yourself.

    return result;
}

// Dot product of two vectors
float dot3(const glm::vec3& lhs, const glm::vec3& rhs)
{
    float result;
    // Your solution goes here
    // Do *NOT* use glm::dot here, but implement the dot product yourself.
    result = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    return result;
}

// Cross product of two vectors
glm::vec3 cross3(const glm::vec3& lhs, const glm::vec3& rhs)
{
    glm::vec3 result{lhs.y*rhs.z - lhs.z*rhs.y, lhs.z*rhs.x - lhs.x*rhs.z, lhs.x*rhs.y - lhs.y*rhs.x};
    // Your solution goes here
    // Do *NOT* use glm::cross here, but implement the cross product yourself.
    return result;
}

// Length of a vector
float length(const glm::vec3& lhs)
{
    float result;
    // Your solution goes here
    // Do *NOT* use glm::length here, but implement the length yourself.
    result = std::sqrt(lhs.x*lhs.x + lhs.y*lhs.y + lhs.z*lhs.z);
    return result;
}

// For the following exercises, a matrix is defined as:
// | m00  m01  m02 |
// | m10  m11  m12 |
// | m20  m21  m22 |
//
// The columns are stored as Vector3's, where:
// col1 = (m00, m10, m20)
// col2 = (m01, m11, m21)
// col3 = (m02, m12, m22)
//
// For a Matrix3 matrix object, these can be accessed via matrix.col1, matrix.col2, matrix.col3

// Matrix multiplication with a scalar
Matrix3 mul(const Matrix3& lhs, float rhs)
{
    // Your solution goes here
    glm::vec3 column1 = mul(lhs.col1, rhs);
    glm::vec3 column2 = mul(lhs.col2, rhs);
    glm::vec3 column3 = mul(lhs.col3, rhs);
    Matrix3 result {column1, column2, column3};
    return result;
}

// Taking the transpose of a matrix means changing it's columns into rows and vice versa.
// Given a matrix of the form:
// | m00  m01  m02 |
// | m10  m11  m12 |
// | m20  m21  m22 |
// its transpose is given as:
// | m00  m10  m20 |
// | m01  m11  m21 |
// | m02  m12  m22 |
Matrix3 transpose(const Matrix3& m)
{
    // Your solution goes here
    glm::vec3 column1 = m.col1;
    glm::vec3 column2 = m.col2;
    glm::vec3 column3 = m.col3;

    glm::vec3 res1{column1.x, column2.x, column3.x};
    glm::vec3 res2{column1.y, column2.y, column3.y};
    glm::vec3 res3{column1.z, column2.z, column3.z};

    Matrix3 result {res1, res2, res3};
    return result;
}

// The determinant is needed to compute the inverse of a matrix.
// If you need a Linear Algebra refresher, please check out:
// https://www.tudelft.nl/en/eemcs/study/online-education/math-explained/linear-algebra/#c144161
float determinant(const Matrix3& m)
{
    float result;
    // Your solution goes here
    glm::vec3 column1 = m.col1;
    glm::vec3 column2 = m.col2;
    glm::vec3 column3 = m.col3;

    result = dot3(column1, cross3(column2, column3));

    return result;
}

// Computing the inverse of the given matrix. If you implemented it correctly then matrix M multiplied
// by its inverse should give the identity matrix). More information on how to compute the inverse of a
// 3x3 matrix can be found here:
// https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
// For this method, you can assume that the given matrix is invertable, i.e., that the determinant is
// not zero. However, you are responsible for checking that all matrices passed to your function in your 
// own code are invertible.
float determinant2(float a, float b, float c, float d){
    return a*d - b*c;
}

// | m00  m01  m02 |
// | m10  m11  m12 |
// | m20  m21  m22 |

Matrix3 inverse(const Matrix3& matrix)
{
    // Hint:
    // You can follow, e.g., the method described here:
    // https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html

    // Step 0: It is probably handy to define a method that computes the determinant of a 2x2 matrix.
    // Step 1: Compute the Matrix of Minors.
    // Step 2: Compute the Matrix of Cofactors
    // Step 3: Adjugate the Matrix (Note that you have the transpose available from above).
    // Step 4: Multiply by 1/determinant (Note that you have the multiplication available from above).

    const float m00 = matrix.col1.x, m01 = matrix.col2.x, m02 = matrix.col3.x;
    const float m10 = matrix.col1.y, m11 = matrix.col2.y, m12 = matrix.col3.y;
    const float m20 = matrix.col1.z, m21 = matrix.col2.z, m22 = matrix.col3.z;

    glm::vec3 column1{determinant2(m11, m21, m12, m22), -determinant2(m01, m21, m02, m22), determinant2(m01, m11, m02, m12)};
    glm::vec3 column2{-determinant2(m10, m20, m12, m22), determinant2(m00, m20, m02, m22), -determinant2(m00, m10, m02, m12)};
    glm::vec3 column3{determinant2(m10, m20, m11, m21), -determinant2(m00, m20, m01, m21), determinant2(m00, m10, m01, m11)};

    Matrix3 minorMatrixSigned {column1, column2, column3};
    Matrix3 adjugate = transpose(minorMatrixSigned);

    const float detOriginal = determinant(matrix);

    const float a00 = adjugate.col1.x/detOriginal, a01 = adjugate.col2.x/detOriginal, a02 = adjugate.col3.x/detOriginal;
    const float a10 = adjugate.col1.y/detOriginal, a11 = adjugate.col2.y/detOriginal, a12 = adjugate.col3.y/detOriginal;
    const float a20 = adjugate.col1.z/detOriginal, a21 = adjugate.col2.z/detOriginal, a22 = adjugate.col3.z/detOriginal;

    glm::vec3 new_column1{a00, a10, a20};
    glm::vec3 new_column2{a01, a11, a21};
    glm::vec3 new_column3{a02, a12, a22};

    Matrix3 result {new_column1, new_column2, new_column3};
    return result;
}

// ==================================
// ========    Exercise 1    ========
// ==================================
// Given a set of vertices of a regular or irregular n-Gon (n>2) on a plane in 3D, we want to order them clock- or counterclockwise
// You may assume that the n-Gon is convex.
std::vector<int> orderOfnGonVertices(const std::vector<glm::vec3> nGon)
{
    std::vector<int> result;
    // You can assume that all vertices of the n-Gon are residing in some plane in 3D, that there are at least 3 vertices in the n-Gon,
    // and that the n-Gon itself is convex.
    // Your solution here, result should have the indices of the vertices from the n-Gon in either counter- or clockwise order.

    float sumx = 0.0f;
    float sumy = 0.0f;
    float sumz = 0.0f;
    int count = 0;

    for(glm::vec3 vector : nGon){
        sumx += vector.x;
        sumy += vector.y;
        sumz += vector.z;
        count += 1;
    }

    float centerX = sumx/count;
    float centerY = sumy/count;
    float centerZ = sumz/count;

    glm::vec3 center = {centerX, centerY, centerZ};
    glm::vec3 reference = {nGon[0].x - centerX, nGon[0].y - centerY, nGon[0].z - centerZ};

    std::vector<std::pair<float, int>> angleAndIndex;

    glm::vec3 edge1 = { nGon[1].x - nGon[0].x, nGon[1].y - nGon[0].y, nGon[1].z - nGon[0].z };
    glm::vec3 edge2 = { nGon[2].x - nGon[0].x, nGon[2].y - nGon[0].y, nGon[2].z - nGon[0].z };
    glm::vec3 normal = cross3(edge1, edge2);

    for(int i = 0; i < static_cast<int>(nGon.size()); i++){
        glm::vec3 d = { nGon[i].x - centerX, nGon[i].y - centerY, nGon[i].z - centerZ };
        float Cosangle = acos(dot3(reference, d) / (length(reference) * length(d)));
        Cosangle = std::clamp(Cosangle, -1.0f, 1.0f);
        float angle = std::acos(Cosangle);
        float side = dot3(normal, cross3(reference, d));

        if(side < 0.0f){
            angle = 2.0f*std::numbers::pi_v<float> - angle;
        }

        angleAndIndex.push_back({ angle, i });
    }

    std::ranges::sort(angleAndIndex);

    for(const std::pair<float, int>& p : angleAndIndex){
        result.push_back(p.second);
    }

    return result;
}


// ==================================
// ========    Exercise 2    ========
// ==================================
// To visualize a given plane, we want to find four points on this plane that span a rectangle.
std::array<glm::vec3, 4> rectangleOnPlane(const Plane& plane)
{
    std::array<glm::vec3, 4> result;

    // Hint:
    // You are given the normal vector and a base point of the plane via the Plane struct.
    // (1) Find a vector that is perpendicular to the normal vector. You can assume that the normal vector is not the zero-vector. 
    //     You can use the dot product you implemented above to check that the vectors are indeed perpendicular.
    // (2) Use the cross-product to compute a second vector that is perpendicular to both the vector found in (1) and the normal 
    //     of the given plane. Again, you can check yourself using the dot product implemented above.
    // (3) As these two vectors you found span the plane, use them to offset the base point in four different directions.
    //     To be able to draw a nice rectangle from them, be sure to order them either clockwise or counter-clockwise.

    // Regarding the visuals: It's really about passing four points that lie on that plane. The rectangles can be tiny, intersect, 
    // be rotated, ... whatever, we don't care. The one thing you should check is that the four points actually lie on the plane 
    // and have the shape of (roughly) a square.

    glm::vec3 helper{ 1.0f, 0.0f, 0.0f }; 
    glm::vec3 u = glm::cross(plane.n, helper);

    if(glm::length(u) < 1e-6f){
        u = glm::cross(plane.n, glm::vec3{0.0f, 1.0f, 0.0f});
    }

    u = glm::normalize(u);

    glm::vec3 v = glm::cross(u, plane.n);

    v = glm::normalize(v);

    glm::vec3 ne = plane.p + u + v;
    glm::vec3 se = plane.p + u - v;
    glm::vec3 sw = plane.p - u - v;
    glm::vec3 nw = plane.p - u + v;

    result = {ne, se, sw, nw};

    return result;
}

// A solid can be given by the planes that are surrounding it. We want to find the vertices of a solid given by its planes.
std::vector<glm::vec3> verticesFromPlanes(std::span<const Plane> planes)
{
    std::vector<glm::vec3> result;

    // Hint:
    // You are given a set of planes.
    // A triple of these planes can intersect in a point.
    // There are two things to watch out for:
    // - a triple of planes might not have a common intersection.
    // - a triple of planes might have a common intersection point that is not within the solid.

    // Therefore:
    // - Iterate over all triples (p1,p2,p3) of given planes.
    // - Set up a linear system that represents the intersection of the three planes, you can ignore the case where the three planes intersect in a line.
    // - Test whether the system has a solution (you can, e.g., use the determinant for matrices).
    // - If it has a solution, compute it (e.g., via using the inverse matrix).
    // - Assuming that the normal of the plane points to the inside of the solid, test for all other planes whether the computed point of intersection is indeed within the solid.

    for(int i = 0; i < planes.size(); i++){
        for(int j = i+1; j < planes.size(); j++){
            for(int k = j+1; k < planes.size(); k++){
                glm::vec3 b = {glm::dot(planes[i].n, planes[i].p), glm::dot(planes[j].n, planes[j].p), glm::dot(planes[k].n, planes[k].p)};
                Matrix3 A = transpose({planes[i].n, planes[j].n, planes[k].n});

                if(std::abs(determinant(A)) < 1e-6f){
                    continue;
                }
                Matrix3 inv = inverse(A);
                glm::vec3 x = b.x * inv.col1 + b.y * inv.col2 + b.z * inv.col3;

                bool inside = true;

                for(const Plane& m : planes){
                    if(glm::dot(m.n, x - m.p) < -1e-4f){
                        inside = false;
                    }
                }

                if(inside){
                    result.push_back(x);
                }

            }
        }
    }

    return result;
}

// ==================================
// ========    Exercise 3    ========
// ==================================
// Given a (possibly irregular) polygon by its vertices (at least 3, ordered either clock- or counterclockwise) that all lie on some 2D plane, 
// compute its area by splitting it into triangles and summing up their areas.
// You may assume that the n-Gon is convex.

float areaOfTriangle(const std::array<glm::vec3, 3> triangle)
{
    float result = 0.0f;
    // Your solution here
    glm::vec3 vector1 = triangle[0] - triangle[1];
    glm::vec3 vector2 = triangle[0] - triangle[2];
    glm::vec3 cross = cross3(vector1, vector2);

    result = length(cross)/2;

    return result;
}

std::vector<std::array<glm::vec3, 3>> splitNGonIntoTriangles(const std::vector<glm::vec3> nGon)
{
    std::vector<std::array<glm::vec3, 3>> result;
    // Your solution here
    for(size_t i = 1; i + 1 < nGon.size(); i++){
        std::array<glm::vec3, 3> tri = {nGon[0], nGon[i], nGon[i+1]};
        result.push_back({tri});
    }
    return result;
}

float areaOfIrregularNGon(const std::vector<glm::vec3> nGon)
{
    // Split the nGon into triangles
    std::vector<std::array<glm::vec3, 3>> triangles = splitNGonIntoTriangles(nGon);
    // Sum up their areas
    float area = 0.;
    for (const auto& triangle : triangles) {
        area += areaOfTriangle(triangle);
    }
    return area;
}
