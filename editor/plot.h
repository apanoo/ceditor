#include "imgui.h"

//-----------------------------------------------------------------------------
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
//-----------------------------------------------------------------------------

// Demonstrate/test rendering huge amount of text, and the incidence of
// clipping.
static void ShowExamplePlot(bool *p_open) {
  ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
  if (!ImGui::Begin("Example: Plot", p_open)) {
    ImGui::End();
    return;
  }

  ImGui::Text("Printing unusually long amount of text.");
  // test plot here

  ImGui::End();
}