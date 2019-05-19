#ifndef IMGUI_UI_H
#define IMGUI_UI_H

#include <styleEditor.h>
#include <dirent.h>
#include <common.h>
#include <resources.hpp>
#include <fog.hpp>
#include <learnOGL.hpp>
#include <musicPlayer.hpp>

struct ExampleAppLog
{
  ImGuiTextBuffer     Buf;
  ImGuiTextFilter     Filter;
  ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
  bool                AutoScroll;
  bool                ScrollToBottom;

  ExampleAppLog()
  {
    AutoScroll = true;
    ScrollToBottom = false;
    Clear();
  }

  void    Clear()
  {
    Buf.clear();
    LineOffsets.clear();
    LineOffsets.push_back(0);
  }

  void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
  {
    int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);
    Buf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = Buf.size(); old_size < new_size; old_size++)
    if (Buf[old_size] == '\n')
    LineOffsets.push_back(old_size + 1);
    if (AutoScroll)
    ScrollToBottom = true;
  }

  void    Draw(const char* title, bool* p_open = NULL)
  {
    if (!ImGui::Begin(title, p_open))
    {
      ImGui::End();
      return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
      if (ImGui::Checkbox("Auto-scroll", &AutoScroll))
      if (AutoScroll)
      ScrollToBottom = true;
      ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options"))
    ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    Filter.Draw("Filter", -100.0f);

    ImGui::Separator();
    ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (clear)
    Clear();
    if (copy)
    ImGui::LogToClipboard();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    const char* buf = Buf.begin();
    const char* buf_end = Buf.end();
    if (Filter.IsActive())
    {
      // In this example we don't use the clipper when Filter is enabled.
      // This is because we don't have a random access on the result on our filter.
      // A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
      // especially if the filtering function is not trivial (e.g. reg-exp).
      for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
      {
        const char* line_start = buf + LineOffsets[line_no];
        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
        if (Filter.PassFilter(line_start, line_end))
        ImGui::TextUnformatted(line_start, line_end);
      }
    }
    else
    {
      // The simplest and easy way to display the entire buffer:
      //   ImGui::TextUnformatted(buf_begin, buf_end);
      // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
      // Here we instead demonstrate using the clipper to only process lines that are within the visible area.
      // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
      // Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
      // both of which we can handle since we an array pointing to the beginning of each line of text.
      // When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
      // Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
      ImGuiListClipper clipper;
      clipper.Begin(LineOffsets.Size);
      while (clipper.Step())
      {
        for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
        {
          const char* line_start = buf + LineOffsets[line_no];
          const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
          ImGui::TextUnformatted(line_start, line_end);
        }
      }
      clipper.End();
    }
    ImGui::PopStyleVar();

    if (ScrollToBottom)
    ImGui::SetScrollHereY(1.0f);
    ScrollToBottom = false;
    ImGui::EndChild();
    ImGui::End();
  }
};

void ImGui_Initialization(){
  // Setup Dear ImGui context
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard ControlsCousine-Regular.ttf
  io.Fonts->AddFontDefault();
  /*io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 16.0f);
  io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", 15.0f);
  io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", 16.0f);
  io.Fonts->AddFontFromFileTTF("fonts/ProggyTiny.ttf", 10.0f);

  io.Fonts->AddFontFromFileTTF("fonts/comic.ttf", 16.0f);
  io.Fonts->AddFontFromFileTTF("fonts/ariblk.ttf", 15.0f);
  io.Fonts->AddFontFromFileTTF("fonts/Impact.ttf", 16.0f);
  io.Fonts->AddFontFromFileTTF("fonts/verdana.ttf", 14.0f);*/
  for (size_t i = 0; i < fontListVector.size(); i++) {
    io.Fonts->AddFontFromFileTTF(("fonts/"+fontListVector.at(i).name).c_str(), fontListVector.at(i).size);
  }

  // Setup Dear ImGui style
  serializeDefaultStyle(); // Setting Configuration/DefaultStyle.ini (Default Style Configuration).
  setStyleComponents("Configurations/Style.ini"); // Loading saved preferences.
  ImGuiStyle& style = ImGui::GetStyle(); // ImGui style reference.
  stringColor = style.Colors[0]; // Setting tutorial's text color.


  // Setup Platform/Renderer bindings
  ImGui_ImplFreeGLUT_Init();
  ImGui_ImplFreeGLUT_InstallFuncs();
  ImGui_ImplOpenGL2_Init();


  imGui_width = SCR_WIDTH; imGui_height = SCR_HEIGHT;

}

void ImGui_CleanUp(){
  // Cleanup
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplFreeGLUT_Shutdown();
  ImGui::DestroyContext();
}

void imGui_display_code(){

  //Initializing styling variable
  ImGuiStyle& style = ImGui::GetStyle();

  if(!texturesInitFlag){
    initializeTextures();
    setFONT();
    texturesInitFlag = true;
    //loadPLayerImages();
  }
  //Check show menu true/false to show the main menu bar
  if(checkUserData){
    handleUserData();
    firstUseModalAlert();
    //std::cout << firstUseFlag << '\n';
  }

  //set cursor if any of the hyperlinks Hovered
  setCursor();

  //saving last opened tutorial index to user data
  userDataObj.setLastTutOpened(radioButtonIndex, show_text);

  if(showMainWindow){
    //setting main menu bar size and position
    ImGui::SetNextWindowSize(ImVec2(imGui_width, imGui_height-100));
    ImGui::SetNextWindowPos (ImVec2(0, 0));
    //rendering main window
    render_Main_Tutorials_Window();

  }else{ //the else statement below runs if the user choose to hide the main window so it re display only the menuBar

    //rendering menubar after main menu is hidden
    menuBar_After_MW_Hidden();

  }

  // rendering light control window for (learnopengl light tutorial)
  if(renderLOGL_LCwindow){
    logl_LC_window();
  }

  //render toggle tutorial text mode button
  if(!show_text){
    toggleTextModeBT();
  }

  //render radio buttons of the multiple output tutorials.
  multipleOuts_RBs();

  //music player
  player_Ui(openMPlayer);
  //Light controls menu
  simpleLightMenu(EnableLightTut, show_text);

  //render bottom controlers window
  contorlersWindow();

  //Preferences menu which allows the user to edit and change all the UI properties (bk color, fonts, padding, theme,  ... etc)
  if(open_full_edit_menu){
    ImGui::Begin("Preferences", &open_full_edit_menu, ImGuiWindowFlags_MenuBar);
    ShowStyleEditor();
    ImGui::End();//Preferences menu ends here
  }

  //Text-Editor menu which the user use it to write only pure c++/openGl code and avoid the libs, Makefile, flags and includes hassle
  if(openTEflag){
    //setting text editor size and position
    ImGui::SetNextWindowSize(ImVec2(SCR_WIDTH/2,SCR_HEIGHT/1.3),ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(250,100),ImGuiCond_FirstUseEver);
    //start rendering text-editor
    ImGui::Begin("Text-Editor", &openTEflag, ImGuiWindowFlags_MenuBar);
    renderTextEditor();
    teWindowSize = ImGui::GetWindowSize();
    ImGui::End();//text-editor ends here
  }

  //call resources menu
  resourcesMenu(openResourcesFlag);

}// end of my_display_code function

void render_ImGui(){
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplFreeGLUT_NewFrame();

  imGui_display_code();
  // Rendering
  ImGui::Render();
  //reseting shaders effect
  GLint last_program;
  glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
  glUseProgram(0);
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  glUseProgram(last_program);

}

#endif //IMGUI_UI_H
