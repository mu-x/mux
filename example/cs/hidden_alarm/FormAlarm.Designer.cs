namespace HiddenAlarm
{
    partial class FormAlarm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormAlarm));
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabTime = new System.Windows.Forms.TabPage();
            this.confTestBtn = new System.Windows.Forms.Button();
            this.timeStartBtn = new System.Windows.Forms.Button();
            this.timeStopBox = new System.Windows.Forms.CheckBox();
            this.timeRepeatBox = new System.Windows.Forms.CheckBox();
            this.timeStop = new System.Windows.Forms.DateTimePicker();
            this.timeRepeat = new System.Windows.Forms.DateTimePicker();
            this.timeStart = new System.Windows.Forms.DateTimePicker();
            this.timeStartLabel = new System.Windows.Forms.Label();
            this.tabConf = new System.Windows.Forms.TabPage();
            this.trackDelBtn = new System.Windows.Forms.Button();
            this.trackAddBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.confTrackList = new System.Windows.Forms.ListBox();
            this.confListLabel = new System.Windows.Forms.Label();
            this.confPlayerLabel = new System.Windows.Forms.Label();
            this.confPlayerBtn = new System.Windows.Forms.Button();
            this.confPlayer = new System.Windows.Forms.TextBox();
            this.statusPanel = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabControl.SuspendLayout();
            this.tabTime.SuspendLayout();
            this.tabConf.SuspendLayout();
            this.statusPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl.Controls.Add(this.tabTime);
            this.tabControl.Controls.Add(this.tabConf);
            this.tabControl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tabControl.Location = new System.Drawing.Point(2, 4);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(282, 213);
            this.tabControl.TabIndex = 0;
            // 
            // tabTime
            // 
            this.tabTime.Controls.Add(this.confTestBtn);
            this.tabTime.Controls.Add(this.timeStartBtn);
            this.tabTime.Controls.Add(this.timeStopBox);
            this.tabTime.Controls.Add(this.timeRepeatBox);
            this.tabTime.Controls.Add(this.timeStop);
            this.tabTime.Controls.Add(this.timeRepeat);
            this.tabTime.Controls.Add(this.timeStart);
            this.tabTime.Controls.Add(this.timeStartLabel);
            this.tabTime.Location = new System.Drawing.Point(4, 25);
            this.tabTime.Name = "tabTime";
            this.tabTime.Padding = new System.Windows.Forms.Padding(3);
            this.tabTime.Size = new System.Drawing.Size(274, 184);
            this.tabTime.TabIndex = 0;
            this.tabTime.Text = "Будильник";
            this.tabTime.UseVisualStyleBackColor = true;
            // 
            // confTestBtn
            // 
            this.confTestBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.confTestBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.confTestBtn.Location = new System.Drawing.Point(0, 161);
            this.confTestBtn.Name = "confTestBtn";
            this.confTestBtn.Size = new System.Drawing.Size(110, 23);
            this.confTestBtn.TabIndex = 10;
            this.confTestBtn.Text = "Проверить плеер";
            this.confTestBtn.UseVisualStyleBackColor = true;
            this.confTestBtn.Click += new System.EventHandler(this.confTestBtn_Click);
            // 
            // timeStartBtn
            // 
            this.timeStartBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.timeStartBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.timeStartBtn.Location = new System.Drawing.Point(121, 161);
            this.timeStartBtn.Name = "timeStartBtn";
            this.timeStartBtn.Size = new System.Drawing.Size(150, 23);
            this.timeStartBtn.TabIndex = 9;
            this.timeStartBtn.Text = "Запустить будильник";
            this.timeStartBtn.UseVisualStyleBackColor = true;
            this.timeStartBtn.Click += new System.EventHandler(this.timeStartBtn_Click);
            // 
            // timeStopBox
            // 
            this.timeStopBox.AutoSize = true;
            this.timeStopBox.Location = new System.Drawing.Point(1, 55);
            this.timeStopBox.Name = "timeStopBox";
            this.timeStopBox.Size = new System.Drawing.Size(170, 17);
            this.timeStopBox.TabIndex = 7;
            this.timeStopBox.Text = "отключать через интервал в";
            this.timeStopBox.UseVisualStyleBackColor = true;
            this.timeStopBox.CheckedChanged += new System.EventHandler(this.timeStopBox_CheckedChanged);
            // 
            // timeRepeatBox
            // 
            this.timeRepeatBox.AutoSize = true;
            this.timeRepeatBox.Location = new System.Drawing.Point(0, 29);
            this.timeRepeatBox.Name = "timeRepeatBox";
            this.timeRepeatBox.Size = new System.Drawing.Size(169, 17);
            this.timeRepeatBox.TabIndex = 6;
            this.timeRepeatBox.Text = "повторять через интервал в";
            this.timeRepeatBox.UseVisualStyleBackColor = true;
            this.timeRepeatBox.CheckedChanged += new System.EventHandler(this.timeRepeatBox_CheckedChanged);
            // 
            // timeStop
            // 
            this.timeStop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.timeStop.Enabled = false;
            this.timeStop.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeStop.Location = new System.Drawing.Point(174, 52);
            this.timeStop.Name = "timeStop";
            this.timeStop.Size = new System.Drawing.Size(100, 20);
            this.timeStop.TabIndex = 5;
            // 
            // timeRepeat
            // 
            this.timeRepeat.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.timeRepeat.Enabled = false;
            this.timeRepeat.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeRepeat.Location = new System.Drawing.Point(174, 26);
            this.timeRepeat.Name = "timeRepeat";
            this.timeRepeat.Size = new System.Drawing.Size(100, 20);
            this.timeRepeat.TabIndex = 3;
            this.timeRepeat.Value = new System.DateTime(2010, 1, 1, 0, 5, 0, 0);
            // 
            // timeStart
            // 
            this.timeStart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.timeStart.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeStart.Location = new System.Drawing.Point(174, 0);
            this.timeStart.Name = "timeStart";
            this.timeStart.Size = new System.Drawing.Size(100, 20);
            this.timeStart.TabIndex = 1;
            // 
            // timeStartLabel
            // 
            this.timeStartLabel.AutoSize = true;
            this.timeStartLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.timeStartLabel.Location = new System.Drawing.Point(-3, 4);
            this.timeStartLabel.Name = "timeStartLabel";
            this.timeStartLabel.Size = new System.Drawing.Size(146, 13);
            this.timeStartLabel.TabIndex = 0;
            this.timeStartLabel.Text = "Время запуска будильника";
            // 
            // tabConf
            // 
            this.tabConf.Controls.Add(this.trackDelBtn);
            this.tabConf.Controls.Add(this.trackAddBtn);
            this.tabConf.Controls.Add(this.label1);
            this.tabConf.Controls.Add(this.confTrackList);
            this.tabConf.Controls.Add(this.confListLabel);
            this.tabConf.Controls.Add(this.confPlayerLabel);
            this.tabConf.Controls.Add(this.confPlayerBtn);
            this.tabConf.Controls.Add(this.confPlayer);
            this.tabConf.Location = new System.Drawing.Point(4, 25);
            this.tabConf.Name = "tabConf";
            this.tabConf.Padding = new System.Windows.Forms.Padding(3);
            this.tabConf.Size = new System.Drawing.Size(274, 184);
            this.tabConf.TabIndex = 1;
            this.tabConf.Text = "Настройки";
            this.tabConf.UseVisualStyleBackColor = true;
            // 
            // trackDelBtn
            // 
            this.trackDelBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.trackDelBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.trackDelBtn.Location = new System.Drawing.Point(0, 154);
            this.trackDelBtn.Name = "trackDelBtn";
            this.trackDelBtn.Size = new System.Drawing.Size(39, 30);
            this.trackDelBtn.TabIndex = 11;
            this.trackDelBtn.Text = "–";
            this.trackDelBtn.UseVisualStyleBackColor = true;
            this.trackDelBtn.Click += new System.EventHandler(this.trackDelBtn_Click);
            // 
            // trackAddBtn
            // 
            this.trackAddBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.trackAddBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.trackAddBtn.Location = new System.Drawing.Point(0, 118);
            this.trackAddBtn.Name = "trackAddBtn";
            this.trackAddBtn.Size = new System.Drawing.Size(39, 30);
            this.trackAddBtn.TabIndex = 10;
            this.trackAddBtn.Text = "+";
            this.trackAddBtn.UseVisualStyleBackColor = true;
            this.trackAddBtn.Click += new System.EventHandler(this.trackAddBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(-3, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "треков";
            // 
            // confTrackList
            // 
            this.confTrackList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.confTrackList.FormattingEnabled = true;
            this.confTrackList.Location = new System.Drawing.Point(42, 26);
            this.confTrackList.Name = "confTrackList";
            this.confTrackList.Size = new System.Drawing.Size(232, 160);
            this.confTrackList.TabIndex = 8;
            // 
            // confListLabel
            // 
            this.confListLabel.AutoSize = true;
            this.confListLabel.Location = new System.Drawing.Point(-3, 28);
            this.confListLabel.Name = "confListLabel";
            this.confListLabel.Size = new System.Drawing.Size(44, 13);
            this.confListLabel.TabIndex = 7;
            this.confListLabel.Text = "Список";
            // 
            // confPlayerLabel
            // 
            this.confPlayerLabel.AutoSize = true;
            this.confPlayerLabel.Location = new System.Drawing.Point(-3, 3);
            this.confPlayerLabel.Name = "confPlayerLabel";
            this.confPlayerLabel.Size = new System.Drawing.Size(39, 13);
            this.confPlayerLabel.TabIndex = 2;
            this.confPlayerLabel.Text = "Плеер";
            // 
            // confPlayerBtn
            // 
            this.confPlayerBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.confPlayerBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.confPlayerBtn.Location = new System.Drawing.Point(249, -2);
            this.confPlayerBtn.Name = "confPlayerBtn";
            this.confPlayerBtn.Size = new System.Drawing.Size(25, 22);
            this.confPlayerBtn.TabIndex = 1;
            this.confPlayerBtn.Text = "..";
            this.confPlayerBtn.UseVisualStyleBackColor = true;
            this.confPlayerBtn.Click += new System.EventHandler(this.confPlayerBtn_Click);
            // 
            // confPlayer
            // 
            this.confPlayer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.confPlayer.Location = new System.Drawing.Point(42, 0);
            this.confPlayer.Name = "confPlayer";
            this.confPlayer.ReadOnly = true;
            this.confPlayer.Size = new System.Drawing.Size(208, 20);
            this.confPlayer.TabIndex = 0;
            this.confPlayer.Text = "C:\\Program Files\\Windows Media Player\\wmplayer.exe";
            // 
            // statusPanel
            // 
            this.statusPanel.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel});
            this.statusPanel.Location = new System.Drawing.Point(0, 221);
            this.statusPanel.Name = "statusPanel";
            this.statusPanel.Size = new System.Drawing.Size(285, 22);
            this.statusPanel.TabIndex = 1;
            this.statusPanel.Text = "statusStrip1";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(118, 17);
            this.statusLabel.Text = "Программа загружена";
            // 
            // FormAlarm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(285, 243);
            this.Controls.Add(this.statusPanel);
            this.Controls.Add(this.tabControl);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormAlarm";
            this.Text = "Скрытый будильник";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormAlarm_FormClosing);
            this.tabControl.ResumeLayout(false);
            this.tabTime.ResumeLayout(false);
            this.tabTime.PerformLayout();
            this.tabConf.ResumeLayout(false);
            this.tabConf.PerformLayout();
            this.statusPanel.ResumeLayout(false);
            this.statusPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabTime;
        private System.Windows.Forms.TabPage tabConf;
        private System.Windows.Forms.DateTimePicker timeRepeat;
        private System.Windows.Forms.DateTimePicker timeStart;
        private System.Windows.Forms.Label timeStartLabel;
        private System.Windows.Forms.CheckBox timeStopBox;
        private System.Windows.Forms.CheckBox timeRepeatBox;
        private System.Windows.Forms.DateTimePicker timeStop;
        private System.Windows.Forms.Button timeStartBtn;
        private System.Windows.Forms.Button confPlayerBtn;
        private System.Windows.Forms.TextBox confPlayer;
        private System.Windows.Forms.Label confPlayerLabel;
        private System.Windows.Forms.Label confListLabel;
        private System.Windows.Forms.StatusStrip statusPanel;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.Button confTestBtn;
        private System.Windows.Forms.ListBox confTrackList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button trackDelBtn;
        private System.Windows.Forms.Button trackAddBtn;
    }
}