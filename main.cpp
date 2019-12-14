#include "pr.hpp"
#include <iostream>
#include <memory>

int main() {
    using namespace pr;

    Config config;
    config.ScreenWidth = 1920;
    config.ScreenHeight = 1080;
    config.SwapInterval = 1;
    Initialize(config);

    Camera3D camera;
    camera.origin = { 0, 0, 4 };
    camera.lookat = { 0, 0, 0 };
    camera.zUp = false;

    double e = GetElapsedTime();

    while (pr::NextFrame() == false) {
        if (IsImGuiUsingMouse() == false) {
            UpdateCameraBlenderLike(&camera);
        }

        ClearBackground(0.1f, 0.1f, 0.1f, 1);

        BeginCamera(camera);

        PushGraphicState();

        DrawGrid(GridAxis::XY, 1.0f, 10, { 128, 128, 128 });
        DrawXYZAxis(0.2f);

        static float R0 = 1.0f;
        static float R1 = 0.4f;
        static float H = 2.0f;

        glm::vec3 P0 = glm::vec3(0, 0, 0);
        glm::vec3 P1 = glm::vec3(H, 0, 0);
        DrawLine(glm::vec3(0, -R0, 0), glm::vec3(0, R0, 0), { 255, 28, 128 }, 3);
        DrawLine(glm::vec3(H, -R1, 0), glm::vec3(H, R1, 0), { 255, 28, 128 }, 3);

        float sinTheta = (R0 - R1) / H;
        if (sinTheta <= 1.0f) {
            float e0 = R0 * sinTheta;
            float e1 = R1 * sinTheta;
            float cosTheta = sqrt(1.0f - sinTheta * sinTheta);

            glm::vec3 T = glm::normalize(P1 - P0);
            glm::vec3 newP0 = P0 + T * e0;
            glm::vec3 newP1 = P1 + T * e1;
            float newH = H - e0 + e1;

            DrawCircle(P0, glm::vec3(0, 0, 1), { 128, 128, 0 }, R0, 128, 2);
            DrawCircle(P1, glm::vec3(0, 0, 1), { 128, 128, 0 }, R1, 128, 2);

            DrawLine(newP0 + glm::vec3(0, cosTheta*R0, 0), newP0 + T * newH + glm::vec3(0, cosTheta*R1, 0), { 255, 28, 128 }, 3);
            DrawLine(newP0 - glm::vec3(0, cosTheta*R0, 0), newP0 + T * newH - glm::vec3(0, cosTheta*R1, 0), { 255, 28, 128 }, 3);

        }

        PopGraphicState();
        EndCamera();

        BeginImGui();

        ImGui::SetNextWindowSize({ 500, 800 }, ImGuiCond_Once);
        ImGui::Begin("Panel");
        ImGui::Text("fps = %f", GetFrameRate());

        ImGui::SliderFloat("R0", &R0, 0.0f, 4.0f);
        ImGui::SliderFloat("R1", &R1, 0.0f, 4.0f);
        ImGui::SliderFloat("H", &H, 0.0f, 4.0f);

        ImGui::End();

        EndImGui();
    }

    CleanUp();
}
