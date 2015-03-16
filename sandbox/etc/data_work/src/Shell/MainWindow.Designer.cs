namespace Shell
{
    partial class MainWindow
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.BtnRegistrator = new System.Windows.Forms.Button();
            this.BtnArchive = new System.Windows.Forms.Button();
            this.BtnAnalysis = new System.Windows.Forms.Button();
            this.TextTitle = new System.Windows.Forms.TextBox();
            this.BtnExit = new System.Windows.Forms.Button();
            this.BtnAbout = new System.Windows.Forms.Button();
            this.BtnHelp = new System.Windows.Forms.Button();
            this.TimerHide = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // BtnRegistrator
            // 
            this.BtnRegistrator.Location = new System.Drawing.Point(10, 70);
            this.BtnRegistrator.Name = "BtnRegistrator";
            this.BtnRegistrator.Size = new System.Drawing.Size(100, 25);
            this.BtnRegistrator.TabIndex = 4;
            this.BtnRegistrator.Text = "Регистратор";
            this.BtnRegistrator.UseVisualStyleBackColor = true;
            this.BtnRegistrator.Click += new System.EventHandler(this.BtnRegistrator_Click);
            this.BtnRegistrator.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // BtnArchive
            // 
            this.BtnArchive.Location = new System.Drawing.Point(10, 100);
            this.BtnArchive.Name = "BtnArchive";
            this.BtnArchive.Size = new System.Drawing.Size(100, 25);
            this.BtnArchive.TabIndex = 5;
            this.BtnArchive.Text = "Обработчик";
            this.BtnArchive.UseVisualStyleBackColor = true;
            this.BtnArchive.Click += new System.EventHandler(this.BtnArchive_Click);
            this.BtnArchive.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // BtnAnalysis
            // 
            this.BtnAnalysis.Location = new System.Drawing.Point(10, 130);
            this.BtnAnalysis.Name = "BtnAnalysis";
            this.BtnAnalysis.Size = new System.Drawing.Size(100, 25);
            this.BtnAnalysis.TabIndex = 6;
            this.BtnAnalysis.Text = "Анализатор";
            this.BtnAnalysis.UseVisualStyleBackColor = true;
            this.BtnAnalysis.Click += new System.EventHandler(this.BtnAnalysis_Click);
            this.BtnAnalysis.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // TextTitle
            // 
            this.TextTitle.BackColor = System.Drawing.SystemColors.ControlDark;
            this.TextTitle.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TextTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TextTitle.Location = new System.Drawing.Point(10, 10);
            this.TextTitle.Multiline = true;
            this.TextTitle.Name = "TextTitle";
            this.TextTitle.ReadOnly = true;
            this.TextTitle.Size = new System.Drawing.Size(205, 45);
            this.TextTitle.TabIndex = 7;
            this.TextTitle.Text = "Комплекс программ регистрации и обработки данных измерений на изучаемом объекте";
            this.TextTitle.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.TextTitle.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseMove);
            this.TextTitle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseDown);
            this.TextTitle.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseUp);
            this.TextTitle.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // BtnExit
            // 
            this.BtnExit.Location = new System.Drawing.Point(115, 130);
            this.BtnExit.Name = "BtnExit";
            this.BtnExit.Size = new System.Drawing.Size(100, 25);
            this.BtnExit.TabIndex = 10;
            this.BtnExit.Text = "Выход";
            this.BtnExit.UseVisualStyleBackColor = true;
            this.BtnExit.Click += new System.EventHandler(this.BtnExit_Click);
            this.BtnExit.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // BtnAbout
            // 
            this.BtnAbout.Location = new System.Drawing.Point(115, 100);
            this.BtnAbout.Name = "BtnAbout";
            this.BtnAbout.Size = new System.Drawing.Size(100, 25);
            this.BtnAbout.TabIndex = 9;
            this.BtnAbout.Text = "О программе";
            this.BtnAbout.UseVisualStyleBackColor = true;
            this.BtnAbout.Click += new System.EventHandler(this.BtnAbout_Click);
            this.BtnAbout.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // BtnHelp
            // 
            this.BtnHelp.Location = new System.Drawing.Point(115, 70);
            this.BtnHelp.Name = "BtnHelp";
            this.BtnHelp.Size = new System.Drawing.Size(100, 25);
            this.BtnHelp.TabIndex = 8;
            this.BtnHelp.Text = "Помощь";
            this.BtnHelp.UseVisualStyleBackColor = true;
            this.BtnHelp.Click += new System.EventHandler(this.BtnHelp_Click);
            this.BtnHelp.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            // 
            // TimerHide
            // 
            this.TimerHide.Interval = 2000;
            this.TimerHide.Tick += new System.EventHandler(this.TimerHide_Tick);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(230, 165);
            this.Controls.Add(this.BtnExit);
            this.Controls.Add(this.BtnAbout);
            this.Controls.Add(this.BtnHelp);
            this.Controls.Add(this.TextTitle);
            this.Controls.Add(this.BtnAnalysis);
            this.Controls.Add(this.BtnArchive);
            this.Controls.Add(this.BtnRegistrator);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainWindow";
            this.Opacity = 0.95;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Комплекс программ регистрации и обработки данных измерений на изучаемом объекте";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseUp);
            this.MouseEnter += new System.EventHandler(this.MainWindow_MouseEnter);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseDown);
            this.MouseLeave += new System.EventHandler(this.MainWindow_MouseLeave);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseMove);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BtnRegistrator;
        private System.Windows.Forms.Button BtnArchive;
        private System.Windows.Forms.Button BtnAnalysis;
        private System.Windows.Forms.TextBox TextTitle;
        private System.Windows.Forms.Button BtnExit;
        private System.Windows.Forms.Button BtnAbout;
        private System.Windows.Forms.Button BtnHelp;
        private System.Windows.Forms.Timer TimerHide;

    }
}