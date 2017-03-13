namespace CodeToOne
{
    partial class FormMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.PathLbl = new System.Windows.Forms.Label();
            this.PathBox = new System.Windows.Forms.TextBox();
            this.SrcLbl = new System.Windows.Forms.Label();
            this.SrcBox = new System.Windows.Forms.ComboBox();
            this.PathBtn = new System.Windows.Forms.Button();
            this.RelBtn = new System.Windows.Forms.Button();
            this.RelBox = new System.Windows.Forms.TextBox();
            this.RelLbl = new System.Windows.Forms.Label();
            this.OptionBox = new System.Windows.Forms.CheckedListBox();
            this.GoBtn = new System.Windows.Forms.Button();
            this.OptionLbl = new System.Windows.Forms.Label();
            this.LicBox = new System.Windows.Forms.RichTextBox();
            this.LicCheck = new System.Windows.Forms.CheckBox();
            this.LicTimer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // PathLbl
            // 
            this.PathLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PathLbl.AutoSize = true;
            this.PathLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PathLbl.Location = new System.Drawing.Point(221, 9);
            this.PathLbl.Name = "PathLbl";
            this.PathLbl.Size = new System.Drawing.Size(124, 13);
            this.PathLbl.TabIndex = 0;
            this.PathLbl.Text = "Папка исходного кода:";
            // 
            // PathBox
            // 
            this.PathBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PathBox.BackColor = System.Drawing.SystemColors.Info;
            this.PathBox.Location = new System.Drawing.Point(224, 24);
            this.PathBox.Name = "PathBox";
            this.PathBox.Size = new System.Drawing.Size(186, 20);
            this.PathBox.TabIndex = 1;
            this.PathBox.Text = "./";
            // 
            // SrcLbl
            // 
            this.SrcLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.SrcLbl.AutoSize = true;
            this.SrcLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SrcLbl.Location = new System.Drawing.Point(221, 48);
            this.SrcLbl.Name = "SrcLbl";
            this.SrcLbl.Size = new System.Drawing.Size(114, 13);
            this.SrcLbl.TabIndex = 2;
            this.SrcLbl.Text = "Расширения файлов:";
            // 
            // SrcBox
            // 
            this.SrcBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.SrcBox.BackColor = System.Drawing.SystemColors.Info;
            this.SrcBox.FormattingEnabled = true;
            this.SrcBox.Items.AddRange(new object[] {
            "h, cpp, hxx, cxx",
            "vcproj, h, cpp, res, rc, resx",
            "csproj, cs, resx",
            "vbproj, vb, vba",
            "dpr, pas"});
            this.SrcBox.Location = new System.Drawing.Point(224, 64);
            this.SrcBox.Name = "SrcBox";
            this.SrcBox.Size = new System.Drawing.Size(200, 21);
            this.SrcBox.TabIndex = 4;
            this.SrcBox.Text = "h, cpp, hxx, cxx";
            // 
            // PathBtn
            // 
            this.PathBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PathBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PathBtn.Location = new System.Drawing.Point(405, 23);
            this.PathBtn.Name = "PathBtn";
            this.PathBtn.Size = new System.Drawing.Size(19, 22);
            this.PathBtn.TabIndex = 5;
            this.PathBtn.Text = ">";
            this.PathBtn.UseVisualStyleBackColor = true;
            this.PathBtn.Click += new System.EventHandler(this.PathBtn_Click);
            // 
            // RelBtn
            // 
            this.RelBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.RelBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RelBtn.Location = new System.Drawing.Point(405, 103);
            this.RelBtn.Name = "RelBtn";
            this.RelBtn.Size = new System.Drawing.Size(19, 22);
            this.RelBtn.TabIndex = 8;
            this.RelBtn.Text = ">";
            this.RelBtn.UseVisualStyleBackColor = true;
            this.RelBtn.Click += new System.EventHandler(this.RelBtn_Click);
            // 
            // RelBox
            // 
            this.RelBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.RelBox.BackColor = System.Drawing.SystemColors.Info;
            this.RelBox.Location = new System.Drawing.Point(224, 104);
            this.RelBox.Name = "RelBox";
            this.RelBox.Size = new System.Drawing.Size(186, 20);
            this.RelBox.TabIndex = 7;
            this.RelBox.Text = "Result.cpp";
            // 
            // RelLbl
            // 
            this.RelLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.RelLbl.AutoSize = true;
            this.RelLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RelLbl.Location = new System.Drawing.Point(224, 88);
            this.RelLbl.Name = "RelLbl";
            this.RelLbl.Size = new System.Drawing.Size(89, 13);
            this.RelLbl.TabIndex = 6;
            this.RelLbl.Text = "Конечный файл:";
            // 
            // OptionBox
            // 
            this.OptionBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.OptionBox.BackColor = System.Drawing.SystemColors.Info;
            this.OptionBox.FormattingEnabled = true;
            this.OptionBox.Items.AddRange(new object[] {
            "Замена префиксов Tab",
            "Замена Tab в тексте",
            "Установка номеров строк",
            "Снять this* с членов",
            "Убрать System*",
            "Короткие скобки <?="});
            this.OptionBox.Location = new System.Drawing.Point(224, 143);
            this.OptionBox.Name = "OptionBox";
            this.OptionBox.Size = new System.Drawing.Size(200, 79);
            this.OptionBox.TabIndex = 9;
            // 
            // GoBtn
            // 
            this.GoBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.GoBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GoBtn.Location = new System.Drawing.Point(224, 226);
            this.GoBtn.Name = "GoBtn";
            this.GoBtn.Size = new System.Drawing.Size(200, 25);
            this.GoBtn.TabIndex = 10;
            this.GoBtn.Text = "Создать";
            this.GoBtn.UseVisualStyleBackColor = true;
            this.GoBtn.Click += new System.EventHandler(this.GoBtn_Click);
            // 
            // OptionLbl
            // 
            this.OptionLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OptionLbl.AutoSize = true;
            this.OptionLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OptionLbl.Location = new System.Drawing.Point(221, 127);
            this.OptionLbl.Name = "OptionLbl";
            this.OptionLbl.Size = new System.Drawing.Size(92, 13);
            this.OptionLbl.TabIndex = 11;
            this.OptionLbl.Text = "Настройки кода:";
            // 
            // LicBox
            // 
            this.LicBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.LicBox.BackColor = System.Drawing.SystemColors.Info;
            this.LicBox.Location = new System.Drawing.Point(9, 9);
            this.LicBox.Name = "LicBox";
            this.LicBox.ReadOnly = true;
            this.LicBox.Size = new System.Drawing.Size(206, 212);
            this.LicBox.TabIndex = 12;
            this.LicBox.Text = resources.GetString("LicBox.Text");
            // 
            // LicCheck
            // 
            this.LicCheck.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LicCheck.AutoSize = true;
            this.LicCheck.Checked = true;
            this.LicCheck.CheckState = System.Windows.Forms.CheckState.Checked;
            this.LicCheck.ForeColor = System.Drawing.Color.Red;
            this.LicCheck.Location = new System.Drawing.Point(9, 231);
            this.LicCheck.Name = "LicCheck";
            this.LicCheck.Size = new System.Drawing.Size(206, 17);
            this.LicCheck.TabIndex = 13;
            this.LicCheck.Text = "принять лицензионное соглашение";
            this.LicCheck.UseVisualStyleBackColor = true;
            this.LicCheck.CheckedChanged += new System.EventHandler(this.LicCheck_CheckedChanged);
            // 
            // LicTimer
            // 
            this.LicTimer.Interval = 50;
            this.LicTimer.Tick += new System.EventHandler(this.LicTimer_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.ClientSize = new System.Drawing.Size(435, 261);
            this.Controls.Add(this.LicCheck);
            this.Controls.Add(this.LicBox);
            this.Controls.Add(this.OptionLbl);
            this.Controls.Add(this.GoBtn);
            this.Controls.Add(this.OptionBox);
            this.Controls.Add(this.RelBtn);
            this.Controls.Add(this.RelBox);
            this.Controls.Add(this.RelLbl);
            this.Controls.Add(this.PathBtn);
            this.Controls.Add(this.SrcBox);
            this.Controls.Add(this.SrcLbl);
            this.Controls.Add(this.PathBox);
            this.Controls.Add(this.PathLbl);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(443, 296);
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Сборщик кода";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PathLbl;
        private System.Windows.Forms.TextBox PathBox;
        private System.Windows.Forms.Label SrcLbl;
        private System.Windows.Forms.ComboBox SrcBox;
        private System.Windows.Forms.Button PathBtn;
        private System.Windows.Forms.Button RelBtn;
        private System.Windows.Forms.TextBox RelBox;
        private System.Windows.Forms.Label RelLbl;
        private System.Windows.Forms.CheckedListBox OptionBox;
        private System.Windows.Forms.Button GoBtn;
        private System.Windows.Forms.Label OptionLbl;
        private System.Windows.Forms.RichTextBox LicBox;
        private System.Windows.Forms.CheckBox LicCheck;
        private System.Windows.Forms.Timer LicTimer;
    }
}