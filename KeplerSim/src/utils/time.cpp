#include "time.h"

#include <GLFW/glfw3.h>

double Time::m_LastTime = 0.0;
double Time::m_DeltaTime = 0.0f;
uint32_t Time::m_FPS = 0;

void Time::Update() {
    double currentTime = glfwGetTime();
    if (m_LastTime == 0) {
        m_LastTime = currentTime;
    }
    m_DeltaTime = (currentTime - m_LastTime) / 1000.0;  // Convertir en secondes
    m_LastTime = currentTime;

    m_FPS = static_cast<uint32_t>(std::floor(1.0f / m_DeltaTime));
}
