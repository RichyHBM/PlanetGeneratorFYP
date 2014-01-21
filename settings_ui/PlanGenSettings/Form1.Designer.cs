namespace PlanGenSettings
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.FullScreenCheckBox = new System.Windows.Forms.CheckBox();
            this.VSyncCheckBox = new System.Windows.Forms.CheckBox();
            this.FramesSpinner = new System.Windows.Forms.NumericUpDown();
            this.StencilSpinner = new System.Windows.Forms.NumericUpDown();
            this.DepthSpinner = new System.Windows.Forms.NumericUpDown();
            this.AAComboBox = new System.Windows.Forms.ComboBox();
            this.HeightSpinner = new System.Windows.Forms.NumericUpDown();
            this.WidthSpinner = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.ViewDisplacementSpinner = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.ControlsComboBox = new System.Windows.Forms.ComboBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FramesSpinner)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.StencilSpinner)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DepthSpinner)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightSpinner)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthSpinner)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ViewDisplacementSpinner)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.FullScreenCheckBox);
            this.groupBox1.Controls.Add(this.VSyncCheckBox);
            this.groupBox1.Controls.Add(this.FramesSpinner);
            this.groupBox1.Controls.Add(this.StencilSpinner);
            this.groupBox1.Controls.Add(this.DepthSpinner);
            this.groupBox1.Controls.Add(this.AAComboBox);
            this.groupBox1.Controls.Add(this.HeightSpinner);
            this.groupBox1.Controls.Add(this.WidthSpinner);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(566, 128);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Window Settings";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 98);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(57, 13);
            this.label10.TabIndex = 15;
            this.label10.Text = "FullScreen";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(299, 99);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(38, 13);
            this.label9.TabIndex = 14;
            this.label9.Text = "VSync";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(7, 73);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(75, 13);
            this.label8.TabIndex = 13;
            this.label8.Text = "Target Frames";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(299, 73);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Stencil Bits";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(299, 47);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(56, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Depth Bits";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(299, 21);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(61, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "AntiAliasing";
            // 
            // FullScreenCheckBox
            // 
            this.FullScreenCheckBox.AutoSize = true;
            this.FullScreenCheckBox.Location = new System.Drawing.Point(157, 97);
            this.FullScreenCheckBox.Name = "FullScreenCheckBox";
            this.FullScreenCheckBox.Size = new System.Drawing.Size(77, 17);
            this.FullScreenCheckBox.TabIndex = 9;
            this.FullScreenCheckBox.Text = "Windowed";
            this.FullScreenCheckBox.UseVisualStyleBackColor = true;
            this.FullScreenCheckBox.CheckedChanged += new System.EventHandler(this.FullScreenCheckBox_CheckedChanged);
            // 
            // VSyncCheckBox
            // 
            this.VSyncCheckBox.AutoSize = true;
            this.VSyncCheckBox.Location = new System.Drawing.Point(440, 98);
            this.VSyncCheckBox.Name = "VSyncCheckBox";
            this.VSyncCheckBox.Size = new System.Drawing.Size(40, 17);
            this.VSyncCheckBox.TabIndex = 8;
            this.VSyncCheckBox.Text = "Off";
            this.VSyncCheckBox.UseVisualStyleBackColor = true;
            this.VSyncCheckBox.CheckedChanged += new System.EventHandler(this.VSyncCheckBox_CheckedChanged);
            // 
            // FramesSpinner
            // 
            this.FramesSpinner.Location = new System.Drawing.Point(157, 71);
            this.FramesSpinner.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.FramesSpinner.Name = "FramesSpinner";
            this.FramesSpinner.Size = new System.Drawing.Size(120, 20);
            this.FramesSpinner.TabIndex = 7;
            this.FramesSpinner.Value = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.FramesSpinner.ValueChanged += new System.EventHandler(this.FramesSpinner_ValueChanged);
            // 
            // StencilSpinner
            // 
            this.StencilSpinner.Location = new System.Drawing.Point(440, 71);
            this.StencilSpinner.Name = "StencilSpinner";
            this.StencilSpinner.Size = new System.Drawing.Size(120, 20);
            this.StencilSpinner.TabIndex = 6;
            this.StencilSpinner.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.StencilSpinner.ValueChanged += new System.EventHandler(this.StencilSpinner_ValueChanged);
            // 
            // DepthSpinner
            // 
            this.DepthSpinner.Location = new System.Drawing.Point(439, 45);
            this.DepthSpinner.Name = "DepthSpinner";
            this.DepthSpinner.Size = new System.Drawing.Size(120, 20);
            this.DepthSpinner.TabIndex = 5;
            this.DepthSpinner.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.DepthSpinner.ValueChanged += new System.EventHandler(this.DepthSpinner_ValueChanged);
            // 
            // AAComboBox
            // 
            this.AAComboBox.FormattingEnabled = true;
            this.AAComboBox.Items.AddRange(new object[] {
            "x1",
            "x2",
            "x4",
            "x8",
            "x12"});
            this.AAComboBox.Location = new System.Drawing.Point(439, 18);
            this.AAComboBox.Name = "AAComboBox";
            this.AAComboBox.Size = new System.Drawing.Size(121, 21);
            this.AAComboBox.TabIndex = 4;
            this.AAComboBox.Text = "x1";
            this.AAComboBox.SelectedIndexChanged += new System.EventHandler(this.AAComboBox_SelectedIndexChanged);
            // 
            // HeightSpinner
            // 
            this.HeightSpinner.Location = new System.Drawing.Point(157, 44);
            this.HeightSpinner.Maximum = new decimal(new int[] {
            6000,
            0,
            0,
            0});
            this.HeightSpinner.Name = "HeightSpinner";
            this.HeightSpinner.Size = new System.Drawing.Size(120, 20);
            this.HeightSpinner.TabIndex = 3;
            this.HeightSpinner.Value = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.HeightSpinner.ValueChanged += new System.EventHandler(this.HeightSpinner_ValueChanged);
            // 
            // WidthSpinner
            // 
            this.WidthSpinner.Location = new System.Drawing.Point(157, 18);
            this.WidthSpinner.Maximum = new decimal(new int[] {
            8000,
            0,
            0,
            0});
            this.WidthSpinner.Name = "WidthSpinner";
            this.WidthSpinner.Size = new System.Drawing.Size(120, 20);
            this.WidthSpinner.TabIndex = 2;
            this.WidthSpinner.Value = new decimal(new int[] {
            800,
            0,
            0,
            0});
            this.WidthSpinner.ValueChanged += new System.EventHandler(this.WidthSpinner_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 46);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(80, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Window Height";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Window Width";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(503, 150);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Run";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(417, 150);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 3;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 153);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(97, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "View Displacement";
            // 
            // ViewDisplacementSpinner
            // 
            this.ViewDisplacementSpinner.DecimalPlaces = 3;
            this.ViewDisplacementSpinner.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.ViewDisplacementSpinner.Location = new System.Drawing.Point(115, 151);
            this.ViewDisplacementSpinner.Name = "ViewDisplacementSpinner";
            this.ViewDisplacementSpinner.Size = new System.Drawing.Size(79, 20);
            this.ViewDisplacementSpinner.TabIndex = 5;
            this.ViewDisplacementSpinner.ValueChanged += new System.EventHandler(this.ViewDisplacementSpinner_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(201, 153);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Controls";
            // 
            // ControlsComboBox
            // 
            this.ControlsComboBox.FormattingEnabled = true;
            this.ControlsComboBox.Items.AddRange(new object[] {
            "Keyboard",
            "Gamepad",
            "Network"});
            this.ControlsComboBox.Location = new System.Drawing.Point(252, 150);
            this.ControlsComboBox.Name = "ControlsComboBox";
            this.ControlsComboBox.Size = new System.Drawing.Size(121, 21);
            this.ControlsComboBox.TabIndex = 0;
            this.ControlsComboBox.Text = "Keyboard";
            this.ControlsComboBox.SelectedIndexChanged += new System.EventHandler(this.ControlsComboBox_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(590, 181);
            this.Controls.Add(this.ControlsComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ViewDisplacementSpinner);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Settings Control";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FramesSpinner)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.StencilSpinner)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DepthSpinner)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightSpinner)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthSpinner)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ViewDisplacementSpinner)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown ViewDisplacementSpinner;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox ControlsComboBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox FullScreenCheckBox;
        private System.Windows.Forms.CheckBox VSyncCheckBox;
        private System.Windows.Forms.NumericUpDown FramesSpinner;
        private System.Windows.Forms.NumericUpDown StencilSpinner;
        private System.Windows.Forms.NumericUpDown DepthSpinner;
        private System.Windows.Forms.ComboBox AAComboBox;
        private System.Windows.Forms.NumericUpDown HeightSpinner;
        private System.Windows.Forms.NumericUpDown WidthSpinner;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
    }
}

