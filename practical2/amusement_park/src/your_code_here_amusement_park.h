#pragma once
// Suppress warnings in third-party code.
#include <framework/disable_all_warnings.h>
DISABLE_WARNINGS_PUSH()
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
DISABLE_WARNINGS_POP()
#include <array>
#include <span>
#include <vector>

static glm::mat4 rotationMatrix(float angle, const glm::vec3& axis)
{
    return glm::rotate(glm::identity<glm::mat4>(), angle, axis);
}
static glm::mat4 translationMatrix(const glm::vec3& translation)
{
    return glm::translate(glm::identity<glm::mat4>(), translation);
}

// !!! DO NOT MODIFY !!!
struct TopSpinState {
    float armAngle { 0 };
    float seatsAngle { 0 };
    float harnessAngle { 0 };
};
// !!! DO NOT MODIFY !!!
struct TopSpinMatrices {
    glm::mat4 supports;
    glm::mat4 arms;
    glm::mat4 seats;
    std::array<glm::mat4, 44> harnesses;
};

// ==========================
// =====    EXERCISE    =====
// ==========================
inline TopSpinMatrices computeTopSpinTransformations(const TopSpinState& topSpinState)
{
    static constexpr int seatsPerRow = 22;
    const float armAngleInRadians = glm::radians(topSpinState.armAngle);
    const float seatsAngleInRadians = glm::radians(topSpinState.seatsAngle);
    const float harnessAngleInRadians = glm::radians(topSpinState.harnessAngle);

    TopSpinMatrices matrices;
    // Place the supports at the origin.
    matrices.supports = glm::identity<glm::mat4>(); // DO NOT CHANGE THIS LINE
    matrices.arms = glm::identity<glm::mat4>();
    matrices.seats = glm::identity<glm::mat4>();
    for (int i = 0; i < 2 * seatsPerRow; ++i) {
        matrices.harnesses[i] = glm::identity<glm::mat4>();
    }

    glm::mat4 m = matrices.supports;
    m = glm::translate(m, glm::vec3(0, 11, 0));
    m = glm::rotate(m, armAngleInRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    matrices.arms = m;

    glm::mat4 s = matrices.arms;
    s = glm::translate(s, glm::vec3(0.0f, -7.8f, 0.0f));
    s = glm::rotate(s, seatsAngleInRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    s = glm::translate(s, glm::vec3(0.0f, -3.0f, 0.0f));
    matrices.seats = s;

    const float firstX = -8.0f + 0.7f / 2.0f;
    const float spacing = (16.0f - 0.7f) / static_cast<float>(seatsPerRow - 1);
    const std::array<float, 2> rowZ {-0.35f, 0.95f};

    for(int row = 0; row < 2; row++){
        for(int seat = 0; seat < seatsPerRow; seat++){
            const float seatX = firstX + static_cast<float>(seat) * spacing;

            glm::mat4 h = matrices.seats;
            h = glm::translate(h, glm::vec3(seatX, 1.5f, rowZ[row]));
            h = glm::rotate(h, harnessAngleInRadians, glm::vec3(1.0f, 0.0f, 0.0f));
            matrices.harnesses[row * seatsPerRow + seat] = h;
        }
    }

    return matrices;
}