///////////////////ImGui/////////////////
#include <imgui/imgui.h>               //
#include <imgui/imgui_impl_freeglut.h> //
#include <imgui/imgui_impl_opengl2.h>  //
/////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif
////
#include <math.h>
#include <styleEditor.h>
#include <common.h>

static int style_idx = -1;static string fontName = "ProggyClean.ttf, 13px", extractedFontName;
float fontScale = 1.0,extractedfontScale;

static void HelpMarker(const char* desc)
{
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

bool ShowStyleSelector(const char* label)
{
  if (ImGui::Combo(label, &style_idx, "Classic\0Dark\0Light\0"))
  {
    switch (style_idx)
    {
      case 0: ImGui::StyleColorsClassic(); stringColor = ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f); break;
      case 1: ImGui::StyleColorsDark(); stringColor = ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f); break;
      case 2: ImGui::StyleColorsLight(); stringColor = ImVec4(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 255.0f/255.0f); break;
    }
    return true;
  }
  return false;
}

void ShowFontSelector(const char* label)
{
  ImGuiIO& io = ImGui::GetIO();
  ImFont* font_current = ImGui::GetFont();
  if (ImGui::BeginCombo(label, font_current->GetDebugName()))
  {
    for (int n = 0; n < io.Fonts->Fonts.Size; n++)
    {
      ImFont* font = io.Fonts->Fonts[n];
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_current)){
        io.FontDefault = font;
        fontName = font->GetDebugName();
        fontScale = font->Scale;
      }

      ImGui::PopID();
    }
    ImGui::EndCombo();
  }
}
void setFONT(){
  //set Font
  ImGuiIO& io = ImGui::GetIO();
  for (int n = 0; n < io.Fonts->Fonts.Size; n++)
  {
    ImFont* font = io.Fonts->Fonts[n];
    ImGui::PushID((void*)font);
    string fname = font->GetDebugName();
    if(fname == extractedFontName){
      font->Scale = extractedfontScale;
      io.FontDefault = font;
    }
    ImGui::PopID();
  }
}

void serializeDefaultStyle()
{
  ImGuiStyle& style = ImGui::GetStyle();
  const char* fileName = "Configurations/DefaultStyle.ini";
  PreffObj DefPfSerialize(style, 1, "ProggyClean.ttf, 13px", 1.0f);
  // Save data
  {
    // Create an output archive
    std::ofstream ofs(fileName);
    boost::archive::text_oarchive ar(ofs);

    // Write data
    ar & DefPfSerialize;
  }
}

void setStyleComponents(const char* fileName)
{
  ImGuiStyle& style = ImGui::GetStyle();
  PreffObj pfDeserialize;
  {
    std::ifstream ifs(fileName);
    // Create and input archive
    if(ifs){
      boost::archive::text_iarchive ar(ifs);
      // Load data
      ar & pfDeserialize;
      //set styles
      style = pfDeserialize.styleT;
      //set theme
      switch (pfDeserialize.style_idx)
      {
        case 0: ImGui::StyleColorsClassic(); break;
        case 1: ImGui::StyleColorsDark(); break;
        case 2: ImGui::StyleColorsLight(); break;
      }
      //set font
      extractedFontName = pfDeserialize.font;
      extractedfontScale = pfDeserialize.fontScale;

    }else{
      cout<<"Can't Open File -> "+workingDirectory<< fileName <<endl;
    }


  }
}

void ShowStyleEditor(ImGuiStyle* ref)
{
  // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
  ImGuiStyle& style = ImGui::GetStyle();
  static ImGuiStyle ref_saved_style;

  // Default to using internal storage as reference
  static bool init = true;
  if (init && ref == NULL)
  ref_saved_style = style;
  init = false;
  if (ref == NULL)
  ref = &ref_saved_style;

  ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

  if (ShowStyleSelector("Themes##Selector"))
  ref_saved_style = style;
  ShowFontSelector("Fonts##Selector");

  // Simplified Settings
  if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
  style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
  { bool window_border = (style.WindowBorderSize > 0.0f); if (ImGui::Checkbox("WindowBorder", &window_border)) style.WindowBorderSize = window_border ? 1.0f : 0.0f; }
  ImGui::SameLine();
  { bool frame_border = (style.FrameBorderSize > 0.0f); if (ImGui::Checkbox("FrameBorder", &frame_border)) style.FrameBorderSize = frame_border ? 1.0f : 0.0f; }
  ImGui::SameLine();
  { bool popup_border = (style.PopupBorderSize > 0.0f); if (ImGui::Checkbox("PopupBorder", &popup_border)) style.PopupBorderSize = popup_border ? 1.0f : 0.0f; }

  // Save/Revert button
  if (ImGui::Button("Save")){
    *ref = ref_saved_style = style;
    const char* fileName = "Configurations/Style.ini";
    PreffObj pfSerialize(style, style_idx, fontName, fontScale);
    // Save data
    {
      // Create an output archive
      std::ofstream ofs(fileName);
      boost::archive::text_oarchive ar(ofs);

      // Write data
      ar & pfSerialize;
    }

  }

  ImGui::SameLine();
  if (ImGui::Button("Revert"))
  style = *ref;
  ImGui::SameLine();
  if(ImGui::Button("Reset Default")){
    setStyleComponents("Configurations/DefaultStyle.ini");
    setFONT();
  }ImGui::SameLine();HelpMarker("Click \"Save\" button after \"Revert\" or \"Reset Default\" to apply changes permanently!.");

  ImGui::Separator();

  if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
  {
    if (ImGui::BeginTabItem("Sizes"))
    {
      ImGui::Text("Main");
      ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
      ImGui::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
      ImGui::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
      ImGui::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
      ImGui::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
      ImGui::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
      ImGui::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
      ImGui::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
      ImGui::Text("Borders");
      ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
      ImGui::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
      ImGui::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
      ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
      ImGui::SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
      ImGui::Text("Rounding");
      ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
      ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
      ImGui::Text("Alignment");
      ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
      ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
      ImGui::SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
      ImGui::Text("Safe Area Padding"); ImGui::SameLine(); HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
      ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Colors"))
    {
      static int output_dest = 0;
      static bool output_only_modified = true;

      static ImGuiTextFilter filter;
      filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

      static ImGuiColorEditFlags alpha_flags = 0;
      ImGui::RadioButton("Opaque", &alpha_flags, 0); ImGui::SameLine();
      ImGui::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine();
      ImGui::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); ImGui::SameLine();
      HelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");

      ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
      ImGui::PushItemWidth(-160);
      for (int i = 0; i < ImGuiCol_COUNT; i++)
      {
        const char* name = ImGui::GetStyleColorName(i);
        if (!filter.PassFilter(name))
        continue;
        ImGui::PushID(i);
        ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
        if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
        {
          // Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
          // Read the FAQ and misc/fonts/README.txt about using icon fonts. It's really easy and super convenient!
          ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) ref->Colors[i] = style.Colors[i];
          ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) style.Colors[i] = ref->Colors[i];
        }
        ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
        ImGui::TextUnformatted(name);
        ImGui::PopID();
      }
      ImGui::PopItemWidth();
      ImGui::EndChild();

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Fonts"))
    {
      ImGuiIO& io = ImGui::GetIO();
      ImFontAtlas* atlas = io.Fonts;
      HelpMarker("Read FAQ and misc/fonts/README.txt for details on font loading.");
      ImGui::PushItemWidth(120);
      for (int i = 0; i < atlas->Fonts.Size; i++)
      {
        ImFont* font = atlas->Fonts[i];
        ImGui::PushID(font);
        bool font_details_opened = ImGui::TreeNode(font, "Font %d: \"%s\"\n%.2f px, %d glyphs, %d file(s)", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
        ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) { io.FontDefault = font; fontName = font->GetDebugName();fontScale = font->Scale;}
        if (font_details_opened)
        {
          ImGui::PushFont(font);
          ImGui::Text("The quick brown fox jumps over the lazy dog");
          ImGui::PopFont();
          ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font

          ImGui::TreePop();
        }
        ImGui::PopID();
      }

      ImGui::PopItemWidth();

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Rendering"))
    {
      ImGui::Checkbox("Anti-aliased lines", &style.AntiAliasedLines); ImGui::SameLine(); HelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
      ImGui::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
      ImGui::PushItemWidth(100);
      ImGui::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, "%.2f", 2.0f);
      if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;
      ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
      ImGui::PopItemWidth();

      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  ImGui::PopItemWidth();
}
