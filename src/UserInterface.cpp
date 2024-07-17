#include "UserInterface.h"

std::string UI::filepath = "";

float UI::position[3] = { 0.0f,0.0f,0.0f };
float UI::rotation[3] = { 0.0f,0.0f,0.0f };
float UI::scale[3] = { 1.0f,1.0f,1.0f };

void UI::Start(GLFWwindow* window)
{
    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // Setup ImGui style
    ImGui::StyleColorsDark();
}

void UI::Update(GLFWwindow*window)
{
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    FileWindow();
    ModelTransform();
    // Render ImGui
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::FileWindow()
{
    ImGui::Begin("File Info");


    ImGui::Text("Selected file: %s", filepath.c_str());
    ImGui::SameLine();
    if (ImGui::Button("Browse"))
        filepath = OpenFileDialogue();

    ImGui::End();
}

void UI::ModelTransform()
{
    ImGui::Begin("Model Transform");
    ImGui::InputFloat3("Position", position);
    ImGui::InputFloat3("Rotation", rotation);
    ImGui::InputFloat3("Scale", scale);
    ImGui::End();
}

std::string OpenFileDialogue()
{
    char filename[MAX_PATH] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "All Files";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        return std::string(filename);
    }
    return "";
}
