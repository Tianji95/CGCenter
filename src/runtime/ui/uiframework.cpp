#include "uiframework.h"
#include <iostream>
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static double lastX = 0;
static double lastY = 0;
static bool isFirstMouse = true;
static bool rightButtonClick = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;
    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_W:
        UIFramework::Instance().camera->MoveForward(1);
        break;
    case GLFW_KEY_S:
        UIFramework::Instance().camera->MoveBack(1);
        break;

    case GLFW_KEY_A:
        UIFramework::Instance().camera->MoveLeft(1);
        break;

    case GLFW_KEY_D:
        UIFramework::Instance().camera->MoveRight(1);
        break;

    default:
        break;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    switch (action) {
    case GLFW_PRESS:
    {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            rightButtonClick = true;
            break;
        default:
            return;
        }
        break;
    }
    case GLFW_RELEASE: {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            rightButtonClick = false;
            break;
        default:
            return;
        }
        break;
    }
    }
    return;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    //if (height == 0)  									// Prevent A Divide By Zero By
    //{
    //    height = 1;										// Making Height Equal One
    //}
    //if (h > 0)
    //    ratio = (float)w / (float)h;
    //glViewport(0, 0, w, h); // Setup viewport
    //width = w;
    //height = h;
    //glViewport(0, 0, width, height);						// Reset The Current Viewport
    //glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    //glLoadIdentity();									// Reset The Projection Matrix
    //// Calculate The Aspect Ratio Of The Window
    //gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    //glLoadIdentity();
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (isFirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (rightButtonClick) {
        float sensitivity = 0.05f;//ÁéÃô¶È
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        UIFramework::Instance().camera->RotateCamera(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "xoffset:" << xoffset << "   yoffset:" << yoffset << std::endl;
    UIFramework::Instance().camera->AddFov(yoffset);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool UIFramework::Init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return false;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "CGCenter", NULL, NULL);
    if (window == NULL)
        return false;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    bool err = glewInit() != GLEW_OK;
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return false;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    camera = new Camera();
    render = new Render(camera);
    render->GenResources();

    return true;
}

bool UIFramework::Draw()
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        static float f = 50.0f;
        static bool open = true;
        ImGui::SetNextWindowSize(ImVec2(400, 600));
        ImGui::Begin("options");
        
        if (ImGui::SliderFloat("camera speed", &f, 0.1f, 100.0f)) {
            camera->SetCameraSpeed(f);
        }
        ImGui::ColorEdit3("light Ambient color", (float*)&ambientColor);
        ImGui::ColorEdit3("light diffuse color", (float*)&diffuseColor);
        ImGui::ColorEdit3("light specular color", (float*)&specularColor);
        ImGui::SliderFloat("light constant", &cons, 0.1f, 10.0f);
        ImGui::SliderFloat("light linear", &lin, 0.0f, 0.001f, "%.6f");
        ImGui::SliderFloat("light quadratic", &quad, 0.0f, 0.000001f, "%.9f");
        ImGui::SliderFloat("light cutOff", &cutOff, 30.0f, 150.0f);
        ImGui::SliderFloat("light outerCutOff", &outerCutOff, 30.0f, 150.0f);

        ImGui::SliderInt("shadow Light Size", &render->shadowLightSize, 1, 10);

        if (ImGui::BeginCombo("##Draw Mode", render->renderModeList[render->rendermode])) {
            for (int n = 0; n < IM_ARRAYSIZE(render->renderModeList); n++) {
                bool is_selected = (render->renderModeList[render->rendermode] == render->renderModeList[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(render->renderModeList[n], is_selected))
                {
                   render->rendermode = n;
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("##Shadow Map", render->shadowMapTypeList[render->shadowType])) {
            for (int n = 0; n < IM_ARRAYSIZE(render->shadowMapTypeList); n++) {
                bool is_selected = (render->shadowMapTypeList[render->shadowType] == render->shadowMapTypeList[n]);
                if (ImGui::Selectable(render->shadowMapTypeList[n], is_selected)) {
                    render->shadowType = n;
                }
            }
            ImGui::EndCombo();
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    render->UpdateWindowSize(display_w, display_h);
    glViewport(0, 0, display_w, display_h);

    glClearColor(0.6f, 0.7f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render->DrawScene();
    // Rendering
    ImGui::Render(); 
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    return true;
}
bool UIFramework::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

bool UIFramework::Destroy()
{
    delete render;
    delete camera;
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return true;
}
