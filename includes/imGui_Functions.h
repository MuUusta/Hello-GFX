#ifndef IMGUI_FUNCTIONS_H
#define IMGUI_FUNCTIONS_H


static void ImGui_ImplFreeGLUT_UpdateKeyboardMods(){
  ImGuiIO& io = ImGui::GetIO();
  int mods = glutGetModifiers();
  io.KeyCtrl = (mods & GLUT_ACTIVE_CTRL) != 0;
  io.KeyShift = (mods & GLUT_ACTIVE_SHIFT) != 0;
  io.KeyAlt = (mods & GLUT_ACTIVE_ALT) != 0;
}

void build_Test_Proj(){
  saveAllFunc("testerFiles/");

  DIR *dirp;
  struct dirent *directory;std::string s;
  dirp = opendir("testerFiles/");
  if (dirp)
  {
    while ((directory = readdir(dirp)) != NULL)
    {
      s = directory->d_name;

      if(s == "exe")
      {
        s = "found";
        break;
      }

    }
  }
  if(s=="found"){
    string command = "cd "+workingDirectory+"/testerFiles/ && rm -f exe && make";
    system(command.c_str());
  }
  else
  {
    string command = "cd "+workingDirectory+"/testerFiles/ && make";
    system(command.c_str());
  }
}

void run_Test_Proj(){
  if(checkFileOnDisk("testerFiles/exe")){
    //string command = "gnome-terminal -x sh -c 'cd "+workingDirectory+"/testerFiles/ && date \"+[%d/%m/%y]-[%H:%M:%S]\" > terminalOutput.txt && ./exe >> terminalOutput.txt' ";
    string command = "cd "+workingDirectory+"/testerFiles/ && date \"+[%d/%m/%y]-[%H:%M:%S]\" > terminalOutput.txt && ./exe >> terminalOutput.txt";
    system(command.c_str());
  }else{
    string command = "cd "+workingDirectory+"/testerFiles/ && echo \"Build project first!.\" > terminalOutput.txt";
    system(command.c_str());
  }

}

void saveAllFunc(string folder){
  string saveFilesTMP = folder + "main.cpp";
  //save files to main.cpp
  ofstream writeData(saveFilesTMP.c_str());
  if (writeData.is_open())
  {
    //includes
    writeData << teIncludedFiles;
    writeData << "\n\n";
    //global variables
    writeData << teGlobalVars;
    writeData << "\n\n\n";
    //functions
    for (size_t i = 0; i < teTabs.size(); i++) {
      if(teTabs.at(i).tType == Function_Tab){
        writeData << teTabs.at(i).tabText;
        writeData << "\n\n";
      }
    }
    //main function
    writeData << mainFunctionText;

    writeData.flush();
    writeData.close();

  }

  //save header files
  for (size_t i = 0; i < teTabs.size(); i++) {
    if(teTabs.at(i).tFile == Header){
      saveFilesTMP = folder + "/includes/headers/" + teTabs.at(i).tab_Name;
      ofstream writeHeaderData(saveFilesTMP.c_str());
      if (writeHeaderData.is_open())
      {
        writeHeaderData << teTabs.at(i).tabText;
        writeHeaderData.flush();
        writeHeaderData.close();
      }
    }
  }

  //save shader files
  for (size_t i = 0; i < teTabs.size(); i++) {
    if(teTabs.at(i).tFile == Shader){
      saveFilesTMP = folder + "/includes/shaders/" + teTabs.at(i).tab_Name;
      ofstream writeShaderData(saveFilesTMP.c_str());
      if (writeShaderData.is_open())
      {
        writeShaderData << teTabs.at(i).tabText;
        writeShaderData.flush();
        writeShaderData.close();
      }
    }
  }

  //save text files
  for (size_t i = 0; i < teTabs.size(); i++) {
    if(teTabs.at(i).tFile == Text){
      saveFilesTMP = folder + "/includes/textFiles/" + teTabs.at(i).tab_Name;
      ofstream writeTxtData(saveFilesTMP.c_str());
      if (writeTxtData.is_open())
      {
        writeTxtData << teTabs.at(i).tabText;
        writeTxtData.flush();
        writeTxtData.close();
      }
    }
  }

  //save other files
  for (size_t i = 0; i < teTabs.size(); i++) {
    if(teTabs.at(i).tFile == Other){
      saveFilesTMP = folder + "/includes/other/" + teTabs.at(i).tab_Name;
      ofstream writeOtherData(saveFilesTMP.c_str());
      if (writeOtherData.is_open())
      {
        writeOtherData << teTabs.at(i).tabText;
        writeOtherData.flush();
        writeOtherData.close();
      }
    }
  }
}

void exportAsProject(){
  static char projName[128] = "";
  ImGui::Text("Extra Files:");
  ImGui::SameLine();HelpMarker("These folders will not be exported with your project unless you check the boxes!.");
  ImGui::Separator();
  if(ImGui::Checkbox("learnopengl", &copyLearnOpenglFolderFlag)){}
  ImGui::SameLine();HelpMarker("Includes folder in learnOpenGL tutorials (camera.h - mesh.h - model.h - shader_s.h - shader_m.h).");
  if(ImGui::Checkbox("resources", &copyResourcesFolderFlag)){}
  ImGui::SameLine();HelpMarker("Resources folder in learnOpenGL tutorials that contains textures and 3D models.");
  ImGui::Separator();
  ImGui::InputText("##proj name", projName, IM_ARRAYSIZE(projName));
  ImGui::SameLine();
  if(ImGui::Button("Export##proj")){

    string tmpString = "Saved-Projects/";
    tmpString += projName;
    createTesterDirectories(tmpString);

    if(!copyLearnOpenglFolderFlag && !copyResourcesFolderFlag){
      tmpString = "cd "+workingDirectory+"/testerFiles/ && cp -r `ls -A | grep -v \"resources\" | grep -v \"learnopengl\"` " + workingDirectory + "/Saved-Projects/";
    }
    if(!copyLearnOpenglFolderFlag && copyResourcesFolderFlag){
      tmpString = "cd "+workingDirectory+"/testerFiles/ && cp -r `ls -A | grep -v \"learnopengl\"` " + workingDirectory + "/Saved-Projects/";
    }
    if(copyLearnOpenglFolderFlag && !copyResourcesFolderFlag){
      tmpString = "cd "+workingDirectory+"/testerFiles/ && cp -r `ls -A | grep -v \"resources\"` " + workingDirectory + "/Saved-Projects/";
    }
    if(copyLearnOpenglFolderFlag && copyResourcesFolderFlag){
      tmpString = "cd "+workingDirectory+"/testerFiles/ && cp -r `ls -A` " + workingDirectory + "/Saved-Projects/";
    }

    tmpString += projName;
    system(tmpString.c_str());

    tmpString = "Saved-Projects/";
    tmpString += projName;
    tmpString += "/";
    saveAllFunc(tmpString);
    ImGui::SetWindowFocus("Text-Editor");

  }ImGui::SameLine();HelpMarker("You will find your project saved in the folder \"Saved-Projects\"");
}

void addFuncToTextEditor(){
  if (ImGui::BeginMenu("Add Function"))
  {
    if (ImGui::MenuItem("Display function")) {
      globalTabType = Function_Tab; globalTabFunc = DisplayFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Reshape function")) {
      globalTabType = Function_Tab; globalTabFunc = ReshapeFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Keyboard function")) {
      globalTabType = Function_Tab; globalTabFunc = KeyboardFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Keyboard Up function")) {
      globalTabType = Function_Tab; globalTabFunc = KeyboardUpFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Special function")) {
      globalTabType = Function_Tab; globalTabFunc = SpecialFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Special Up function")) {
      globalTabType = Function_Tab; globalTabFunc = SpecialUpFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Motion function")) {
      globalTabType = Function_Tab; globalTabFunc = MotionFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Mouse function")) {
      globalTabType = Function_Tab; globalTabFunc = MouseFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Idle function")) {
      globalTabType = Function_Tab; globalTabFunc = IdleFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    if (ImGui::MenuItem("Timer function")) {
      globalTabType = Function_Tab; globalTabFunc = TimerFunc;
      teTabsNumber++;
      teTabs.push_back(Tabs(globalTabType, globalTabFunc, teTabsNumber));
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Custom##1")){

      ImGui::InputText("##func name", customFuncText, IM_ARRAYSIZE(customFuncText));
      ImGui::SameLine();
      if(ImGui::Button("Add##func")){
        globalTabType = Function_Tab; globalTabFunc = CustomFunction;
        teTabsNumber++;
        teTabs.push_back(Tabs(globalTabType, globalTabFunc, customFuncText, teTabsNumber));
        strcpy(customFuncText, "");
        ImGui::SetWindowFocus("Text-Editor");
      }
      ImGui::SameLine();
      HelpMarker("Enter the function name only, Then edit parameters and return type in the generated file.");
      ImGui::EndMenu();
    }

    ImGui::EndMenu();
  }
}

void addFileToTextEditor(){
  if (ImGui::BeginMenu("Add File"))
  {
    if (ImGui::BeginMenu("Header file##1")){

      ImGui::InputText("##file name1", customFileText, IM_ARRAYSIZE(customFileText));
      ImGui::SameLine();
      if(ImGui::Button("Add##file1")){
        globalTabType = File_Tab; globalTabFile = Header;
        teTabsNumber++;
        teTabs.push_back(Tabs(globalTabType, globalTabFile, customFileText, teTabsNumber, true));
        strcpy(customFileText, "");
        ImGui::SetWindowFocus("Text-Editor");
      }
      ImGui::SameLine();
      HelpMarker("Enter full file name : file.h or file.txt ... etc not just the file name");

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Shader file##2")){

      ImGui::InputText("##file name2", customFileText, IM_ARRAYSIZE(customFileText));
      ImGui::SameLine();
      if(ImGui::Button("Add##file2")){
        globalTabType = File_Tab; globalTabFile = Shader;
        teTabsNumber++;
        teTabs.push_back(Tabs(globalTabType, globalTabFile, customFileText, teTabsNumber, true));
        strcpy(customFileText, "");
        ImGui::SetWindowFocus("Text-Editor");
      }
      ImGui::SameLine();
      HelpMarker("Enter full file name : file.h or file.txt ... etc not just the file name");

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Text file##3")){

      ImGui::InputText("##file name3", customFileText, IM_ARRAYSIZE(customFileText));
      ImGui::SameLine();
      if(ImGui::Button("Add##file3")){
        globalTabType = File_Tab; globalTabFile = Text;
        teTabsNumber++;
        teTabs.push_back(Tabs(globalTabType, globalTabFile, customFileText, teTabsNumber, true));
        strcpy(customFileText, "");
        ImGui::SetWindowFocus("Text-Editor");
      }
      ImGui::SameLine();
      HelpMarker("Enter full file name : file.h or file.txt ... etc not just the file name");

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Other##4")){

      ImGui::InputText("##file name4", customFileText, IM_ARRAYSIZE(customFileText));
      ImGui::SameLine();
      if(ImGui::Button("Add##file4")){
        globalTabType = File_Tab; globalTabFile = Other;
        teTabsNumber++;
        teTabs.push_back(Tabs(globalTabType, globalTabFile, customFileText, teTabsNumber, true));
        strcpy(customFileText, "");
        ImGui::SetWindowFocus("Text-Editor");
      }
      ImGui::SameLine();
      HelpMarker("Enter full file name : file.h or file.txt ... etc not just the file name");

      ImGui::EndMenu();
    }


    ImGui::EndMenu();
  }
}

void textEditorConsolLog(){
  //Console log
  static ExampleAppLog log;
  ImGui::SetNextWindowSize(ImVec2(SCR_WIDTH/3.5,SCR_HEIGHT/1.3),ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowPos(ImVec2((SCR_WIDTH/2)+250,100),ImGuiCond_FirstUseEver);
  log.Draw("Console-Log", &openTEflag);
  if(ImGui::Button("Build")){
    build_Test_Proj();
    string sLog = readFile("testerFiles/error.log");
    if(sLog == ""){
      log.AddLog("Your Program Built Successfully & Ready To Run.\n");
    }
    else{
      sLog += "\n";
      log.AddLog(sLog.c_str() );
    }

  }
  ImGui::SameLine();
  if(ImGui::Button("Run")){
    run_Test_Proj();
    string sLog = readFile("testerFiles/terminalOutput.txt") + "\n";
    log.AddLog(sLog.c_str() );
  }
}

static void HelpMarker(const char* desc){
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void renderTextEditor(){

  if (ImGui::BeginMenuBar())
  {
    //menu bar
    if (ImGui::BeginMenu("Options"))
    {
      ImGui::CheckboxFlags("Disable Input", (unsigned int*)&teTabsFlags, ImGuiInputTextFlags_ReadOnly);
      ImGui::CheckboxFlags("Indent Using (TAB)", (unsigned int*)&teTabsFlags, ImGuiInputTextFlags_AllowTabInput);

      ImGui::Separator();
      if (ImGui::BeginMenu("Export As")) {
        exportAsProject();
        ImGui::EndMenu();
      }

      if (ImGui::MenuItem("Save All")) {
        saveAllFunc("testerFiles/");
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Add##TEmenuBarItem"))
    {
      addFuncToTextEditor();
      addFileToTextEditor();

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Open##DeactivatedTabs"))
    {

      for (size_t i = 0; i < teTabs.size(); i++) {
        ImGui::Checkbox(teTabs.at(i).tab_Name.c_str(), &teTabs.at(i).open);
      }

      ImGui::EndMenu();
    }

    ImGui::SameLine();
    HelpMarker("Write your C++/openGL Code here & Don't worry about libraries and Makefile");

    ImGui::EndMenuBar();
  }

  //Text editor tabs
  if (ImGui::BeginTabBar("##TE-Tabs", ImGuiTabBarFlags_None))
  {
    if (ImGui::BeginTabItem("Includes"))
    {
      ImGui::InputTextMultiline("##teIncludes", teIncludedFiles, IM_ARRAYSIZE(teIncludedFiles), ImVec2(teWindowSize.x-15, teWindowSize.y-100), teTabsFlags);

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Global-Vars"))
    {
      ImGui::InputTextMultiline("##teGlobVars", teGlobalVars, IM_ARRAYSIZE(teGlobalVars), ImVec2(teWindowSize.x-15, teWindowSize.y-100), teTabsFlags);

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Main"))
    {
      ImGui::InputTextMultiline("##mainFunc", mainFunctionText, IM_ARRAYSIZE(mainFunctionText), ImVec2(teWindowSize.x-15, teWindowSize.y-100), teTabsFlags);

      ImGui::EndTabItem();
    }

    for (size_t i = 0; i < teTabs.size(); i++) {
      teTabs.at(i).renderTab();
    }

    ImGui::EndTabBar();
  }

  textEditorConsolLog();
}

void ShowFontSelector(const char* label, const char* helpMsg){
  ImGuiIO& io = ImGui::GetIO();
  ImFont* font_current = ImGui::GetFont();
  if (ImGui::BeginCombo(label, font_current->GetDebugName()))
  {
    for (int n = 0; n < io.Fonts->Fonts.Size; n++)
    {
      ImFont* font = io.Fonts->Fonts[n];
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_current))
      io.FontDefault = font;
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }
  ImGui::SameLine();
  HelpMarker(helpMsg);
}

void modalAlert(const char *name, const char* msg){

  if (ImGui::BeginPopupModal(name, NULL, ImGuiWindowFlags_AlwaysAutoResize))
  {
    if(strcmp(msg,"")==0){
      ImGui::Text("Whatever you are looking for is not available at this moment!");
      ImGui::Separator();
      ImGui::Indent(157);
      if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
    }
    else{
      ImGui::Text(msg);
      ImGui::Separator();
      ImGui::Indent(57);
      if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
    }
    ImGui::SetItemDefaultFocus();

    ImGui::EndPopup();
  }
}

void firstUseModalAlert(){
  if (ImGui::BeginPopupModal("Hello-GFX", NULL, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("Welcome To Hello-GFX, Please Enter Your Name.");
    ImGui::Text("UserName:");ImGui::SameLine();ImGui::InputText("##username", usrName, IM_ARRAYSIZE(usrName));
    if(ImGui::IsItemHovered()){
      ImGui::SetTooltip("Don't include symbols or spaces!");
    }
    ImGui::SameLine();
    if (ImGui::Button("Start", ImVec2(0, 0))) {
      string  x(usrName);
      if (x.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
      {
        errMsg = "Invalid Format!";
      }
      else if(x == ""){
        errMsg = "Empty Field!";
      }else{
        userDataObj.setUserName(usrName);
        userDataObj.set_very_First_App_Use_Time();
        userDataObj.setTutorialsTitles(tutorials->get_Tutorial_Titles());
        userDataObj.setLastTutOpened(0, show_text);
        userDataObj.setNextTutSuggestion();
        firstUseFlag = false;
        checkUserData = false;
        ImGui::CloseCurrentPopup();
      }

    }
    if(errMsg == "")
    ImGui::SameLine();
    else{
      ImGui::Dummy(ImVec2(65,0));ImGui::SameLine();
    }
    ImGui::TextColored(ImVec4(1.0, 0.3, 0.3, 1.0),errMsg.c_str());ImGui::SameLine();

    ImGui::SetItemDefaultFocus();

    ImGui::EndPopup();
  }
}

void currentTutRateModal(){

  if (ImGui::BeginPopupModal("Tutorial Competence", NULL, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("On a scale of 1 to 10,");
    ImGui::Text("How efficient can you apply this tutorial?");
    ImGui::SliderInt("##compt slider", &userDataObj.tutorailCompetence, 1, 10);
    ImGui::SameLine();
    if(ImGui::Button("Submit")){
      userDataObj.setLastTutDone(radioButtonIndex,userDataObj.tutorailCompetence);
      userDataObj.setCurrentTut(radioButtonIndex);
      userDataObj.setCurrentTutStatus(1);
      userDataObj.setNextTutSuggestion();
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();

    ImGui::EndPopup();
  }
}

void logl_LC_window(){
  ImGui::SetNextWindowPos(ImVec2(1600,200));
  ImGui::SetNextWindowSize(ImVec2(150,100));
  if(ImGui::Begin("Light Types:")){
    ImGui::BeginGroup();
    logl_LightCasters_lightingShader.use();
    if(ImGui::RadioButton("Directional Light", &logl_LC_RBpointer, 5551)){
      logl_LightCasters_lightingShader.setInt("dLightOn", 1);
      logl_LightCasters_lightingShader.setInt("pLightOn", 0);
      logl_LightCasters_lightingShader.setInt("sLightOn", 0);
    }
    if(ImGui::RadioButton("Point Light", &logl_LC_RBpointer, 5552)){
      logl_LightCasters_lightingShader.setInt("dLightOn", 0);
      logl_LightCasters_lightingShader.setInt("pLightOn", 1);
      logl_LightCasters_lightingShader.setInt("sLightOn", 0);
    }
    if(ImGui::RadioButton("Spot Light", &logl_LC_RBpointer, 5553)){
      logl_LightCasters_lightingShader.setInt("dLightOn", 0);
      logl_LightCasters_lightingShader.setInt("pLightOn", 0);
      logl_LightCasters_lightingShader.setInt("sLightOn", 1);
    }
    ImGui::EndGroup();
  }ImGui::End();
}

void resetFunc(){
  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  resetScrollY = true;

  renderLOGL_LCwindow = false;
  logl_reset_Camera();

  resetLight();
  resetFog();
  resetSceneVars();
  if(!menuFlag)
  glutDetachMenu(GLUT_RIGHT_BUTTON);

  multipleOutputs = 0;
  multipleOutputsIndex = 1;

  ImGuiIO& io = ImGui::GetIO();
  if(!show_text)
  io.MousePos.x = SCR_WIDTH/2;
}

void viewTutorialImages(int i) {
  for (unsigned int j = 0; j < t_ImageVec.size(); j++) {
    if(t_ImageVec.at(j)->tutNum == radioButtonIndex && t_ImageVec.at(j)->lineNum == i){
      ImGui::Image((void*)t_ImageVec.at(j)->id,ImVec2(t_ImageVec.at(j)->width/2, t_ImageVec.at(j)->height/2));
      if (ImGui::IsItemHovered())
      {
        ImGui::BeginTooltip();
        ImGui::Image((void*)t_ImageVec.at(j)->id,ImVec2(t_ImageVec.at(j)->width, t_ImageVec.at(j)->height));
        ImGui::EndTooltip();
      }
    }
  }
}

void viewTutorialContent(){
  ImGuiListClipper clipper(tutorials->get_Tutorial_Text_At(radioButtonIndex).size());
  while (clipper.Step()){
    for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++){
      // View Resources Links if exists for the current tutorial
      for (size_t k = 0; k < t_ResourcesVec.size(); k++) {
        t_ResourcesVec.at(k)->renderResources(radioButtonIndex, i);
        isHyprLinkHoveredVec.at(k) = t_ResourcesVec.at(k)->isHovered;
      }
      // View tutorial text
      if(wrappedText)
      ImGui::TextWrapped(tutorials->get_Tutorial_Text_At(radioButtonIndex).at(i).c_str(), i);
      else
      ImGui::TextColored(stringColor,tutorials->get_Tutorial_Text_At(radioButtonIndex).at(i).c_str(), i);
      // View tutorial images
      viewTutorialImages(i);
    }
  }
  ImGui::SetWindowFontScale(window_scale);
  ImGui::Text("\n");
}

void viewUserInfo() {
  //User Info
  string inforStringTmp;
  ImGui::Text(" ");
  ImGui::BulletText("User Information: ");
  ImGui::Text("----------------------");
  inforStringTmp = "Name: " + userDataObj.getUserName();
  ImGui::Text(inforStringTmp.c_str());
  ImGui::Text("First APP Use On: ");
  ImGui::Text(userDataObj.get_very_First_App_Use_Time().c_str());
  ImGui::Separator();
  ImGui::Text("Current Tutorial: ");
  ImGui::Text("----------------------");
  ImGui::BulletText(userDataObj.getCurrentTut().c_str());
  inforStringTmp = "Status: " + userDataObj.getCurrentTutStatus();
  ImGui::BulletText(inforStringTmp.c_str());
  ImGui::Separator();
  ImGui::Text("Last Opened Tutorial: ");
  ImGui::Text("----------------------");
  ImGui::BulletText(userDataObj.getLastTutOpened().c_str());
  ImGui::Separator();
  ImGui::Text("Next Tutorial suggestion: ");
  ImGui::Text("----------------------");
  ImGui::BulletText(userDataObj.getNextTutSuggestion().c_str());
  ImGui::Separator();
  ImGui::Text("Last Done Tutorial: ");
  ImGui::Text("----------------------");
  ImGui::BulletText(userDataObj.getLastTutDone().c_str());
  ImGui::Text("Started On: ");
  ImGui::Text(userDataObj.get_Done_Tut_Start_Time().c_str());
  ImGui::Text("Ended On: ");
  ImGui::Text(userDataObj.get_Done_Tut_Finish_Time().c_str());
  ImGui::Text("Duration: ");
  ImGui::Text(userDataObj.getDoneTutDuration().c_str());
  ImGui::Separator();
  if(ImGui::TreeNode("Tutorials need review:")){

    for (unsigned int i = 0; i < userDataObj.getNeedReviewTuts().size(); i++) {
      ImGui::BulletText(userDataObj.getNeedReviewTuts().at(i).c_str());
    }

    ImGui::TreePop();
  }
  ImGui::Separator();
  ImGui::Text("Progress:");
  ImGui::ProgressBar(userDataObj.getProgressPercent(), ImVec2(130.0f,15.0f));
  ImGui::Text(userDataObj.getRemainingDuration().c_str());
  /////////////////////////////////////////////////////////
}

void Show_Fps_mouse_Pos(){
  ImGuiIO& io = ImGui::GetIO();
  ImGuiStyle& style = ImGui::GetStyle();

  ImGui::Text(fps);ImGui::SameLine();ImGui::Text("   ");ImGui::SameLine();
  float defFrameRounding = style.FrameRounding;
  style.FrameRounding = 8.0f;
  fpsRework = ( fpsFloat/60 )*100;
  ImGui::PushID(40);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
  ImGui::PopStyleVar(1);

  style.Colors[40] = ImVec4(((60.0f - fpsFloat)/60.0f), 1-((60.0f - fpsFloat)/60.0f), 0.0f, 0.6f);
  ImGui::PopID();
  ImGui::ProgressBar(fpsRework*.01, ImVec2(130.0f,15.0f));
  if (ImGui::IsItemHovered()){
    string tmp = "Application performance is at :" + to_string(fpsRework) + "%%";
    ImGui::SetTooltip(tmp.c_str());
  }
  style.Colors[40] = ImVec4(.0, .5, .5, 1);
  style.FrameRounding = defFrameRounding;

  ImGui::Text("---------");

  if (ImGui::IsMousePosValid())
  ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
  else
  ImGui::Text("Mouse Position: <invalid>");


}

void simpleLightMenu(bool enable, bool text){
  if(enable && !text){
    ImGui::Begin("Light-Controls");

    ImGui::Checkbox("Light On/Off", &lightsOn);
    ImGui::Checkbox("Shininess On/Off", &shininessOn);
    ImGui::Checkbox("Auto-Rotate On/Off", &circularMotion);
    ImGui::Text("Light-Position");
    ImGui::SliderFloat("X-Axis",     &LightPosition[0],  -2.0f,   2.0f);
    ImGui::SliderFloat("Y-Axis",     &LightPosition[1],  -2.0f,   2.0f);
    ImGui::SliderFloat("Z-Axis",     &LightPosition[2],  -4.0f,   4.0f);

    ImGui::End();
  }
}

void searchingMenuItem(){
  if (ImGui::BeginMenu("Search##!"))
  {
    if(useMouseForImGui){
      ImGui::InputText("##searchBar", searchStr, IM_ARRAYSIZE(searchStr));
      searchTMP =  searchStr; int found = 0;searchResults.erase(searchResults.begin(), searchResults.end());
      if(searchTMP != "")
      {
        for (unsigned int i = 0; i < tutorials->tutDisplayList.size(); i++) {
          for (unsigned int j = 0; j < tutorials->tutDisplayList.at(i).size(); j++) {
            found = tutorials->tutDisplayList.at(i).at(j).find(searchTMP);
            if(found != string::npos){
              searchResults.push_back(tutorials->get_Tutorial_Title_at(i));
              break;
            }
          }
        }
        if(searchResults.size() == 0){
          ImGui::Separator();
          ImGui::Text("Can't Be Found!.");
        }else{
          ImGui::Text("Found in:");
          ImGui::Separator();
        }

      }

      for (unsigned int i = 0; i < searchResults.size(); i++) {
        ImGui::Text(searchResults.at(i).c_str());
      }
    }
    ImGui::EndMenu();
  }else{
    strcpy(searchStr,"");
  }
}

void immediate_Mode_Tutorials_List(){
  if(ImGui::CollapsingHeader("Immediate Mode##tutorials")){
    ImGui::Text(" ");
    if(ImGui::TreeNode("BASICS:")){

      if(ImGui::RadioButton(" Setup", &radioButtonIndex, 0)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Initialization", &radioButtonIndex, 1)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Resizing Window", &radioButtonIndex, 2)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Animation", &radioButtonIndex, 3)){
        applyTutorialsFunc(radioButtonIndex);

      }

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("INPUT:")){
      if(ImGui::RadioButton(" Keyboard", &radioButtonIndex, 4)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Moving Camera I", &radioButtonIndex, 5)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Advanced Keyboard", &radioButtonIndex, 6)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Moving Camera II", &radioButtonIndex, 7)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Mouse", &radioButtonIndex, 8)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton(" Moving Camera III", &radioButtonIndex, 9)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }


    if(ImGui::TreeNode("POP-UP MENUS:")){
      if(ImGui::RadioButton("PopUp Menu Basics", &radioButtonIndex, 10)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("SubMenus", &radioButtonIndex, 11)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Modifying Menus", &radioButtonIndex, 12)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Swapping Menus", &radioButtonIndex, 13)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }


    if(ImGui::TreeNode("FONTS:")){
      if(ImGui::RadioButton("Bitmap Fonts", &radioButtonIndex, 14)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Bitmaps & Ortho View", &radioButtonIndex, 15)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Stroke Fonts", &radioButtonIndex, 16)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("SUBWINDOWS:")){
      if(ImGui::RadioButton("Create/Destroy SW", &radioButtonIndex, 17)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Reshape SW", &radioButtonIndex, 18)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Render to SW", &radioButtonIndex, 19)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("All in one", &radioButtonIndex, 20)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("AVOID IDLE FUNC:")){
      if(ImGui::RadioButton("glutPostRedisplay", &radioButtonIndex, 21)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }


    if(ImGui::TreeNode("EXTRAS:")){
      if(ImGui::RadioButton("Frames Per Second", &radioButtonIndex, 22)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Fog", &radioButtonIndex, 23)){
        applyTutorialsFunc(radioButtonIndex);

      }
      if(ImGui::RadioButton("Transparency", &radioButtonIndex, 24)){
        applyTutorialsFunc(radioButtonIndex);

      }
      if(ImGui::RadioButton("Light", &radioButtonIndex, 25)){
        applyTutorialsFunc(radioButtonIndex);

      }

      if(ImGui::RadioButton("Graphics Pipe-Line", &radioButtonIndex, 26)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }

    ImGui::Text(" ");
    ImGui::Separator();

  }
}

void retained_Mode_Tutorials_List(){
  if(ImGui::CollapsingHeader("Retained Mode##tutorials")){
    ImGui::Text(" ");
    if(ImGui::TreeNode("GETTING STARTED")){

      if(ImGui::RadioButton("OpenGl", &radioButtonIndex, 27)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Creating a window", &radioButtonIndex, 28)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Hello Window", &radioButtonIndex, 29)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Hello Triangle", &radioButtonIndex, 30)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Shaders", &radioButtonIndex, 31)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Textures", &radioButtonIndex, 32)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Transformations", &radioButtonIndex, 33)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Coordinate Systems", &radioButtonIndex, 34)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Camera", &radioButtonIndex, 35)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Review", &radioButtonIndex, 36)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }
    if(ImGui::TreeNode("LIGHTING")){

      if(ImGui::RadioButton("Colors", &radioButtonIndex, 37)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Basic Lighting", &radioButtonIndex, 38)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Materials", &radioButtonIndex, 39)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Lighting Maps", &radioButtonIndex, 40)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Light Casters", &radioButtonIndex, 41)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Multiple Lights", &radioButtonIndex, 42)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Review", &radioButtonIndex, 43)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }
    if(ImGui::TreeNode("MODEL LOADING")){

      if(ImGui::RadioButton("Assimp", &radioButtonIndex, 44)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Mesh", &radioButtonIndex, 45)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Model", &radioButtonIndex, 46)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }
    if(ImGui::TreeNode("ADVANCED OPENGL")){

      if(ImGui::RadioButton("Depth Testing", &radioButtonIndex, 47)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Stencil Testing", &radioButtonIndex, 48)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Blending##2", &radioButtonIndex, 49)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Face Culling", &radioButtonIndex, 50)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Framebuffers", &radioButtonIndex, 51)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Cubemaps", &radioButtonIndex, 52)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Advanced Data", &radioButtonIndex, 53)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Advanced GLSL", &radioButtonIndex, 54)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Geometry Shader", &radioButtonIndex, 55)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Instancing", &radioButtonIndex, 56)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Anti Aliasing", &radioButtonIndex, 57)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }
    if(ImGui::TreeNode("ADVANCED LIGHTING")){

      if(ImGui::RadioButton("Advanced Lighting##rb", &radioButtonIndex, 58)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Gamma Correction", &radioButtonIndex, 59)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::TreeNode("Shadows")){

        if(ImGui::RadioButton("Shadow Mapping", &radioButtonIndex, 60)){
          applyTutorialsFunc(radioButtonIndex);
        }
        if(ImGui::RadioButton("Point Shadows", &radioButtonIndex, 61)){
          applyTutorialsFunc(radioButtonIndex);
        }

        ImGui::TreePop();
      }

      if(ImGui::RadioButton("Normal Mapping", &radioButtonIndex, 62)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Parallax Mapping", &radioButtonIndex, 63)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("HDR", &radioButtonIndex, 64)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Bloom", &radioButtonIndex, 65)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("Deferred Shading", &radioButtonIndex, 66)){
        applyTutorialsFunc(radioButtonIndex);
      }
      if(ImGui::RadioButton("SSAO", &radioButtonIndex, 67)){
        applyTutorialsFunc(radioButtonIndex);
      }

      ImGui::TreePop();
    }
    ImGui::Text(" ");
  }
}

void mainWindow_LeftPane(){
  ImGui::BeginChild("left pane", ImVec2(220, 0), true); //main window's first child
  ImGui::BeginGroup();//start radio button group

  if(openTutorialsHeaders){
    ImGui::GetStateStorage()->SetInt(ImGui::GetID("Immediate Mode##tutorials"), 1);
    ImGui::GetStateStorage()->SetInt(ImGui::GetID("Retained Mode##tutorials"), 1);
    openTutorialsHeaders = false;
  }

  //display list of immediate mode tutorials
  immediate_Mode_Tutorials_List();

  //display list of retained mode tutorials
  retained_Mode_Tutorials_List();

  ImGui::EndGroup();// radioButtons group ends here

  ImGui::Separator();

  //User Info
  viewUserInfo();

  ImGui::EndChild();//main window's first child ends here
  ImGui::SameLine();
}

void rightPane_CodeTab(){
  for (unsigned int i = 0; i < t_CodeVec.size(); i++) {
    if(t_CodeVec.at(i)->tutNum == radioButtonIndex){
      if (ImGui::BeginTabItem(t_CodeVec.at(i)->codeTabName))
      {
        ImGui::InputTextMultiline(to_string(i).c_str(), t_CodeVec.at(i)->codeText, IM_ARRAYSIZE(t_CodeVec.at(i)->codeText), ImVec2(SCR_WIDTH-248, SCR_HEIGHT-225), ImGuiInputTextFlags_ReadOnly);
        if(ImGui::Button("Copy Code")){
          string tmp = "xclip -in -selection c "+t_CodeVec.at(i)->url;
          system(tmp.c_str());
        }
        ImGui::SameLine();HelpMarker("If you want to copy the entire code to somewhere outside the app just click \"Copy Code\" button.\n"
        "If you want to copy code within the application just select the code with your mouse and \"Ctrl+c\" then \"Ctrl+v\" whereever you want to past it.");
        ImGui::EndTabItem();
      }

    }
  }
}

void start_end_Tutorial_Buttons(){
  if(userDataObj.allTutsStatus.size() > 0){
    if(userDataObj.allTutsStatus.at(radioButtonIndex).status == -1){
      if(ImGui::Button("Begin")){ //Setting the actuall start time of the current tutorial since it's needed in user data calculations
      userDataObj.setCurrentTut(radioButtonIndex);
      userDataObj.setCurrentTutStatus(0);
      userDataObj.setNextTutSuggestion();
      userDataObj.set_Current_Tut_Start_Time();
    }
  }else if(userDataObj.allTutsStatus.at(radioButtonIndex).status == 0){
    if(ImGui::Button("Done With This Tutorial")){ //Setting the actuall end time & Competence of the current tutorial since it's needed in user data calculations
    ImGui::OpenPopup("Tutorial Competence");
  }
}
}
ImGui::Text("\n\n");
}

void view_Output_Button(){
  if (ImGui::Button("View Output")) { //Rendering the current tutorial output button

    switch (radioButtonIndex) {
      case 0:   case 2:   case 6:   case 8:   case 15:  case 17:
      case 18:  case 19:  case 21:  case 26:  case 27:  case 28:
      case 36:  case 43:  case 44:  case 45:  case 53:
      ImGui::OpenPopup("Tutorial Output Alert!");
      break;
      default:
      ImGuiIO& io = ImGui::GetIO();
      io.MousePos.x += 60;
      show_text = false;imGui_width = 235;
      if(radioButtonIndex == 20){
        create_subWindows();
      }
      break;
    }

  }
}

void mainWindow_RightPane(){
  if(show_text){ //only show the right pane if (show_text) is true
    //Right pane of the main window
    ImGui::BeginGroup();//starting group for tutorial components
    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); //main window's second child, <<<< -ImGui::GetFrameHeightWithSpacing() >>>> Leave room for 1 line below us
    //getting tutorials titles
    ImGui::Text(tutorials->get_Tutorial_Title_at(radioButtonIndex).c_str(), radioButtonIndex);

    if(resetScrollY){
      ImGui::SetScrollHereY(0.0);
      resetScrollY = false;
    }
    ImGui::Separator();
    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
    {
      if (ImGui::BeginTabItem("Tutorial"))
      {
        viewTutorialContent();
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("About"))
      {
        tutorials->get_About_At(radioButtonIndex).renderAbout();
        ImGui::EndTabItem();
      }
      //Code tab function
      rightPane_CodeTab();
      ImGui::EndTabBar();
    }
    ImGui::EndChild();//main window's second child ends here

    //Display view the current tutorial output button.
    view_Output_Button();
    ImGui::SameLine();
    //Display the start and done of the current tutorial buttons.
    start_end_Tutorial_Buttons();

    modalAlert("Tutorial Output Alert!","No Output For The Current Tutorial\nPlease Check The Following Parts!");
    currentTutRateModal();

    ImGui::EndGroup();
  }
}

void showHotKeysMenu(){
  ImGui::MenuItem("(Keyboard-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Red Triangle","F1");
  ImGui::MenuItem("Green Triangle","F2");
  ImGui::MenuItem("Blue Triangle","F3");
  ImGui::Separator();
  ImGui::MenuItem("(Moving camera I-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Move Forward","Up Arrow");
  ImGui::MenuItem("Move Backward","Down Arrow");
  ImGui::MenuItem("Move Left","Left Arrow");
  ImGui::MenuItem("Move Right","Right Arrow");
  ImGui::Separator();
  ImGui::MenuItem("(Moving camera II-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Move Forward","Up Arrow");
  ImGui::MenuItem("Move Backward","Down Arrow");
  ImGui::MenuItem("Look Left","Left Arrow");
  ImGui::MenuItem("Look Right","Right Arrow");
  ImGui::Separator();
  ImGui::MenuItem("(Moving camera III-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Move Forward","Up Arrow");
  ImGui::MenuItem("Move Backward","Down Arrow");
  ImGui::MenuItem("Start Moving Camera","Left Mouse Click");
  ImGui::Separator();
  ImGui::MenuItem("(PopUp Menus-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Shrink Menu","s");
  ImGui::MenuItem("Color Menu","c");
  ImGui::Separator();
  ImGui::MenuItem("(SubWindows-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Exit","Esc");
  ImGui::Separator();
  ImGui::MenuItem("(Transparency-Tutorial)", NULL, false, false);
  ImGui::MenuItem("Less Transparent","t");
  ImGui::MenuItem("More Transparent","Shift+t");
  ImGui::Separator();
  ImGui::MenuItem("(Retained Mode-Tutorials)", NULL, false, false);
  ImGui::MenuItem("Start Moving Camera","Right Mouse Click");
  ImGui::MenuItem("Zoom","Mouse Scroll");
  ImGui::MenuItem("Exit Moving Camera","Esc");
  ImGui::MenuItem("Move Forward","w");
  ImGui::MenuItem("Move Backward","s");
  ImGui::MenuItem("Move Left","a");
  ImGui::MenuItem("Move Right","d");

}

void showLicenseText(){
  ImGui::MenuItem("The MIT License (MIT)\n\n"
  "Copyright (c) 2019 Mustafa Gamal\n\n"
  "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
  "of this software and associated documentation files (the \"Software\"), to deal\n"
  "in the Software without restriction, including without limitation the rights\n"
  "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
  "copies of the Software, and to permit persons to whom the Software is\n"
  "furnished to do so, subject to the following conditions:\n\n"
  "The above copyright notice and this permission notice shall be included in all\n"
  "copies or substantial portions of the Software.\n\n"
  "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
  "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
  "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
  "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
  "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
  "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.", NULL, false, false);
}

void showAboutH_GFXText(){
  ImGui::MenuItem("Hello-GFX is an OpenGL/C++ program devoloped to help computer graphics students\n"
  "and hobbyists to learn computer graphics and OpenGl by providing tutorials\n"
  "for both immediate and retained mode with the output of each tutorial,\n"
  "Also a simple text editor is provided for the user to be able to write C++/OpenGl code\n"
  "and click build & run to see the output of his code.\n\n"
  "Since i can't put all of the online tutorials in this tool i used LightHouse3D\n"
  "for immediate mode tutorials & Joey De Vries (LearnOpenGL) for retained mode tutorials\n"
  "and all other books, youtube video, website tutorials for opengl \nor any other online related website that i know, "
  "can be found in the resources Tab.\n\n"
  "This Is A Free Open Source Software Under MIT License.", NULL, false, false);
}

void render_Main_Tutorials_Window(){
  //start rendering main window
  if (ImGui::Begin("Main-Bar", &showMainWindow, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
  {
    if (ImGui::BeginMenuBar())// menuBar for the main window
    {
      if (ImGui::BeginMenu("Main"))//menuBar button
      {
        ImGui::MenuItem("~Tutorials UI~", NULL, false, false);
        if (ImGui::MenuItem("Hide")){ showMainWindow = false; }//menuBar item
        ImGui::Separator();

        if (ImGui::MenuItem("Close","Esc")){
          destroyWindows();
          destroyPopupMenus();
          exit(0);
        }//menuBar item

        ImGui::EndMenu();
      }
      ////
      if (ImGui::BeginMenu("Open"))//menuBar button
      {
        if (ImGui::MenuItem("Text-Editor##MenuItem1")){  //menuBar item
          openTEflag = true;
          ImGui::SetWindowFocus("Console-Log");
          ImGui::SetWindowFocus("Text-Editor");
        }
        if(ImGui::MenuItem("Preferences##MenuItem1")){  //menuBar item
          open_full_edit_menu = true;
          ImGui::SetWindowFocus("Preferences");
        }

        if(ImGui::MenuItem("Resources##MenuItem1")){  //menuBar item
          openResourcesFlag = true;
          ImGui::SetWindowFocus("Resources##Menu");
        }

        if (ImGui::MenuItem("Music Player##MenuItem1")){  //menuBar item
          openMPlayer = true;
          ImGui::SetWindowFocus("Music-Player");
        }

        ImGui::EndMenu();
      }
      ////
      searchingMenuItem();
      ////
      if (ImGui::BeginMenu("Help"))
      {
        if (ImGui::BeginMenu("HotKeys"))
        {
          showHotKeysMenu();
          ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("About")){
          showAboutH_GFXText();
          ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("License")){
          showLicenseText();
          ImGui::EndMenu();
        }

        ImGui::EndMenu();
      }

      // Date and time display
      date_Time_Display();

      /// MusicPlayer External Controls
      MP_ExternalControls();

      ImGui::EndMenuBar();//menuBar code ends here
    }

    //Left pane of the main window
    mainWindow_LeftPane();

    //Right pane of the main window
    mainWindow_RightPane();

  }
  ImGui::End();//main window ends here
}

void menuBar_After_MW_Hidden(){
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Main"))
    {
      ImGui::MenuItem("~Tutorials UI~", NULL, false, false);
      if (ImGui::MenuItem("Show")){ showMainWindow = true; }
      ImGui::Separator();
      if (ImGui::MenuItem("Close","Esc")){
        destroyWindows();
        destroyPopupMenus();
        exit(0);
      }
      ImGui::EndMenu();
    }
    ////
    if (ImGui::BeginMenu("Open"))
    {
      if (ImGui::MenuItem("Text-Editor##MenuItem2")){
        openTEflag = true;
        ImGui::SetWindowFocus("Console-Log");
        ImGui::SetWindowFocus("Text-Editor");
      }
      if(ImGui::MenuItem("Preferences##MenuItem2")){
        open_full_edit_menu = true;
        ImGui::SetWindowFocus("Preferences");
      }
      if(ImGui::MenuItem("Resources##MenuItem2")){
        openResourcesFlag = true;
        ImGui::SetWindowFocus("Resources##Menu");
      }
      if (ImGui::MenuItem("Music Player##MenuItem")){
        openMPlayer = true;
        ImGui::SetWindowFocus("Music-Player");
      }

      ImGui::EndMenu();
    }
    ////
    searchingMenuItem();
    ////
    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::BeginMenu("HotKeys"))
      {
        showHotKeysMenu();
        ImGui::EndMenu();
      }

      if(ImGui::BeginMenu("About")){
        showAboutH_GFXText();
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("License"))
      {
        showLicenseText();
        ImGui::EndMenu();
      }

      ImGui::EndMenu();
    }
    // Date and time display
    date_Time_Display();
    /// MusicPlayer External Controls
    MP_ExternalControls();

    ImGui::EndMainMenuBar();
  }
}

void toggleTextModeBT(){
  float width = 0.1, widthMargin;
  ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
  if(showMainWindow){
    ImGui::SetNextWindowPos(ImVec2(imGui_width+5, SCR_HEIGHT/2-150));
    widthMargin = imGui_width + 60;
  }
  else{
    ImGui::SetNextWindowPos(ImVec2(5, SCR_HEIGHT/2-150));
    widthMargin = 60;
  }

  float defBorder = ImGui::GetStyle().WindowBorderSize;
  ImGuiStyle& thisSHWtextModeStyle = ImGui::GetStyle();
  thisSHWtextModeStyle.WindowBorderSize = 0.0f;
  static bool *shwTextBtn;
  if (ImGui::Begin("TextModeBTNMenu", shwTextBtn, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
  {
    if(ImGui::GetIO().MousePos.x < widthMargin)
    width = 12.0;
    else
    width = 0.1;
    if(ImGui::Button(">", ImVec2(width,150))){
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
      show_text = true;
      imGui_width = SCR_WIDTH;
      if(!showMainWindow){
        showMainWindow = true;
      }
    }
    thisSHWtextModeStyle.WindowBorderSize = defBorder;
  }
  if(ImGui::IsItemHovered()){
    ImGui::SetTooltip("View Tutorial");
  }
  ImGui::End();
}

void multipleOuts_RBs(){
  static bool *p_open;
  if(multipleOutputs > 0 && !show_text){
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2(SCR_WIDTH/2.1, SCR_HEIGHT-150));
    if (ImGui::Begin("MultipleInput RBTNS", p_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
    {

      ImGui::BeginGroup();
      for(int i=1; i<= multipleOutputs; i++){
        string nameID = "##RadioButOP"+to_string(i);
        ImGui::RadioButton(nameID.c_str(), &multipleOutputsIndex, i);ImGui::SameLine();
      }
      ImGui::EndGroup();

    }

    ImGui::End();
  }
}

void contorlersWindow(){
  //Controlers menu size and position
  ImGui::SetNextWindowSize(ImVec2(SCR_WIDTH, 100.0));
  ImGui::SetNextWindowPos (ImVec2(0, SCR_HEIGHT-100));
  //Start rendering controlers menu
  if (ImGui::Begin("Controlers"))
  {
    ImGui::Columns(5, " ");
    int misc_flags = (ImGuiColorEditFlags_HDR ) | (ImGuiColorEditFlags_NoDragDrop) | (ImGuiColorEditFlags_AlphaPreviewHalf) | ( ImGuiColorEditFlags_NoOptions);
    ImGui::Text("Set Clear/Background Color:\n\n");
    ImGui::SameLine(); HelpMarker("OpenGL ClearColor/BackGround.");
    ImGui::ColorEdit4("BackGround Color", (float*)&colorBG, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);

    if(ImGui::BeginPopup("bk color popup")){
      ImGui::Text("Set Clear/Background Color:");
      ImGui::SameLine(); HelpMarker("OpenGL ClearColor/BackGround.");
      ImGui::ColorPicker4("##picker", (float*)&colorBG, misc_flags);
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    if(ImGui::Button("palette")){
      ImGui::OpenPopup("bk color popup");
    }
    ImGui::NextColumn();

    ///////
    ImGui::Text("Set Tutorial Text Color:\n\n");
    ImGui::SameLine(); HelpMarker("This color will not be applied permanently, if you want a permanent change then edit in \"Preferences\" window.");
    ImGui::ColorEdit4("Tutorial Text Color", (float*)&stringColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);

    if(ImGui::BeginPopup("tut text popup")){
      ImGui::Text("Set Tutorial Text Color:");
      ImGui::SameLine(); HelpMarker("This color will not be applied permanently, if you want a permanent change then edit in \"Preferences\" window.");
      ImGui::ColorPicker4("##picker2", (float*)&stringColor, misc_flags);
      ImGui::EndPopup();
    }
    ImGui::SameLine();
    if(ImGui::Button("palette2")){
      ImGui::OpenPopup("tut text popup");
    }
    ImGui::NextColumn();

    ///////
    if(ImGui::Checkbox("FullScreen",&fullScrFlag)){
      if(fullScrFlag == true){
        glutFullScreen();
        //show_text = true;
      }
      else{
        glutReshapeWindow(SCR_WIDTH, SCR_HEIGHT);
        //show_text = true;
      }

    }
    ImGui::SameLine(172.5);
    if(ImGui::Button("Preferences")){
      open_full_edit_menu = true;
    }

    ImGui::Text(" ");
    static int style_idx = 1;
    if (ImGui::Combo("Theme", &style_idx, "Classic\0Dark\0Light\0"))
    {
      ImGuiStyle& style = ImGui::GetStyle();
      switch (style_idx)
      {
        case 0: ImGui::StyleColorsClassic(); break;
        case 1: ImGui::StyleColorsDark(); break;
        case 2: ImGui::StyleColorsLight(); break;
      }
      stringColor = style.Colors[0];
    }
    ImGui::SameLine();
    HelpMarker("This skin will not be applied permanently, if you want a permanent change then edit in \"Preferences\" window.");
    ImGui::NextColumn();

    ///////
    ImGuiIO& io = ImGui::GetIO();
    ShowFontSelector("Fonts","Edit your fonts here!");
    ImGui::DragFloat("Tut Font Size", &window_scale, 0.005f, 0.3f, 2.0f, "%.2f");
    ImGui::DragFloat("global Font Size", &io.FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.2f");      // scale everything
    ImGui::NextColumn();

    //////
    Show_Fps_mouse_Pos();



  }ImGui::End();// Controlers menu ends here
}

void initializeTextures(){
  load_logl_Textures();
  for(unsigned int i=0; i< t_ImageVec.size(); i ++){
    t_ImageVec.at(i)->loadTheImage();
  }
}

void handleUserData(){
  if(userDataObj.isFirstUsage()){
    firstUseFlag = true;
    ImGui::OpenPopup("Hello-GFX");
  }else{
    firstUseFlag = false;
    deSerializeUserData();
  }
}

void date_Time_Display(){
  auto t = chrono::system_clock::now();
  time_t dt = chrono::system_clock::to_time_t(t);
  string dateTimeString = ctime(&dt);
  ImGui::SameLine();ImGui::Dummy(ImVec2(SCR_WIDTH/2.8,0));ImGui::SameLine();
  ImGui::Text(dateTimeString.c_str());
}

#endif //IMGUI_FUNCTIONS_H
