using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PlanGenSettings
{
    public partial class Form1 : Form
    {
        private PlanetSettings settings = new PlanetSettings();
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ProcessRunner prunner = new ProcessRunner("StandAlone");
            prunner.CallAndLog(settings.ToArgumentArray());
            Application.Exit();
        }

        private void VSyncCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (VSyncCheckBox.Checked)
            {
                VSyncCheckBox.Text = "On";
                settings.VSync = 1;
            }
            else
            {
                VSyncCheckBox.Text = "Off";
                settings.VSync = 0;
            }
        }

        private void FullScreenCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (FullScreenCheckBox.Checked)
            {
                FullScreenCheckBox.Text = "FullScreen";
                settings.FullScreen = 1;
            }
            else
            {
                FullScreenCheckBox.Text = "Windowed";
                settings.FullScreen = 0;
            }
        }

        private void WidthSpinner_ValueChanged(object sender, EventArgs e)
        {
            settings.WindowWidth = Convert.ToInt32(WidthSpinner.Value);
        }

        private void HeightSpinner_ValueChanged(object sender, EventArgs e)
        {
            settings.WindowHeight = Convert.ToInt32(HeightSpinner.Value);
        }

        private void AAComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(AAComboBox.SelectedText == "x1")
                settings.AntiAliasing = 1;
            else if(AAComboBox.SelectedText == "x2")
                settings.AntiAliasing = 2;
            else if(AAComboBox.SelectedText == "x4")
                settings.AntiAliasing = 4;
            else if(AAComboBox.SelectedText == "x8")
                settings.AntiAliasing = 8;
            else if(AAComboBox.SelectedText == "x12")
                settings.AntiAliasing = 12;
        }

        private void DepthSpinner_ValueChanged(object sender, EventArgs e)
        {
            settings.DepthBits = Convert.ToInt32(DepthSpinner.Value);
        }

        private void StencilSpinner_ValueChanged(object sender, EventArgs e)
        {
            settings.StencilBits = Convert.ToInt32(StencilSpinner.Value);
        }

        private void FramesSpinner_ValueChanged(object sender, EventArgs e)
        {
            settings.TargetFPS = Convert.ToInt32(FramesSpinner.Value);
        }

        private void ControlsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            settings.Controls = ControlsComboBox.SelectedIndex;
        }
    }
}
