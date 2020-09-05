#include "imgui.h"
#include "plot/implot.h"

typedef float t_float;
typedef ImVec2 t_float2;
#define Sin sinf
#define Cos cosf
#define Pow powf
#define Log logf
#define Fmod fmodf

// helper
inline t_float RandomRange(t_float min, t_float max) {
  t_float scale = rand() / (t_float)RAND_MAX;
  return min + scale * (max - min);
}

// end felper

//-----------------------------------------------------------------------------
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
//-----------------------------------------------------------------------------

// Demonstrate/test rendering huge amount of text, and the incidence of
// clipping.
static void ShowExamplePlot(bool *p_open) {
  ImPlot::CreateContext();

  ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
  if (!ImGui::Begin("Example: Plot", p_open)) {
    ImGui::End();
    return;
  }

  //   ImGui::Text("Printing unusually long amount of text.");
  // test plot here
  //   ImPlot::ShowDemoWindow();
  static t_float xs1[101], ys1[101], ys2[101], ys3[101];
  srand(0);
  for (int i = 0; i < 101; ++i) {
    xs1[i] = (float)i;
    ys1[i] = RandomRange(400, 450);
    ys2[i] = RandomRange(275, 350);
    ys3[i] = RandomRange(150, 225);
  }
  static bool show_lines = true;
  static bool show_fills = true;
  static float fill_ref = 0;
  ImGui::Checkbox("Lines", &show_lines);
  ImGui::SameLine();
  ImGui::Checkbox("Fills", &show_fills);
  ImGui::DragFloat("Reference", &fill_ref, 1, -100, 500);

  ImPlot::SetNextPlotLimits(0, 100, 0, 500);
  if (ImPlot::BeginPlot("Stock Prices", "Days", "Price")) {
    if (show_fills) {
      ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
      ImPlot::PlotShaded("Stock 1", xs1, ys1, 101, fill_ref);
      ImPlot::PlotShaded("Stock 2", xs1, ys2, 101, fill_ref);
      ImPlot::PlotShaded("Stock 3", xs1, ys3, 101, fill_ref);
      ImPlot::PopStyleVar();
    }
    if (show_lines) {
      ImPlot::PlotLine("Stock 1", xs1, ys1, 101);
      ImPlot::PlotLine("Stock 2", xs1, ys2, 101);
      ImPlot::PlotLine("Stock 3", xs1, ys3, 101);
    }
    ImPlot::EndPlot();
  }

  static t_float xs[1001], ys11[1001], ys22[1001], ys33[1001];
  for (int i = 0; i < 1001; ++i) {
    xs[i] = i * 0.1f;
    ys11[i] = Sin(xs[i]) + 1;
    ys22[i] = Log(xs[i]);
    ys33[i] = Pow(10.0f, xs[i]);
  }
  ImGui::BulletText(
      "Open the plot context menu (double right click) to change scales.");

  ImPlot::SetNextPlotLimits(0.1, 100, 0, 10);
  if (ImPlot::BeginPlot("Log Plot", NULL, NULL, ImVec2(-1, 0),
                        ImPlotFlags_Default,
                        ImPlotAxisFlags_Default | ImPlotAxisFlags_LogScale)) {
    ImPlot::PlotLine("f(x) = x", xs, xs, 1001);
    ImPlot::PlotLine("f(x) = sin(x)+1", xs, ys11, 1001);
    ImPlot::PlotLine("f(x) = log(x)", xs, ys22, 1001);
    ImPlot::PlotLine("f(x) = 10^x", xs, ys33, 21);
    ImPlot::EndPlot();
  }

  ImGui::End();
  ImPlot::DestroyContext();
}