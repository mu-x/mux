namespace Processor
{
    partial class FilterWindow
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
            this.WhereGrid = new System.Windows.Forms.DataGridView();
            this.Param = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Min = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Max = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OperLbl = new System.Windows.Forms.Label();
            this.OperBox = new System.Windows.Forms.ComboBox();
            this.DateLowLbl = new System.Windows.Forms.Label();
            this.DateLowBox = new System.Windows.Forms.DateTimePicker();
            this.DateHigBox = new System.Windows.Forms.DateTimePicker();
            this.DateHigLbl = new System.Windows.Forms.Label();
            this.OkBtn = new System.Windows.Forms.Button();
            this.NullBtn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.WhereGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // WhereGrid
            // 
            this.WhereGrid.AllowUserToAddRows = false;
            this.WhereGrid.AllowUserToDeleteRows = false;
            this.WhereGrid.AllowUserToResizeColumns = false;
            this.WhereGrid.AllowUserToResizeRows = false;
            this.WhereGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.WhereGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.WhereGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Param,
            this.Min,
            this.Max});
            this.WhereGrid.Location = new System.Drawing.Point(12, 12);
            this.WhereGrid.Name = "WhereGrid";
            this.WhereGrid.RowHeadersVisible = false;
            this.WhereGrid.Size = new System.Drawing.Size(304, 285);
            this.WhereGrid.TabIndex = 0;
            // 
            // Param
            // 
            this.Param.HeaderText = "Парамитер";
            this.Param.Name = "Param";
            this.Param.ReadOnly = true;
            this.Param.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // Min
            // 
            this.Min.HeaderText = "От";
            this.Min.Name = "Min";
            this.Min.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // Max
            // 
            this.Max.HeaderText = "До";
            this.Max.Name = "Max";
            this.Max.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // OperLbl
            // 
            this.OperLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OperLbl.AutoSize = true;
            this.OperLbl.Location = new System.Drawing.Point(325, 12);
            this.OperLbl.Name = "OperLbl";
            this.OperLbl.Size = new System.Drawing.Size(56, 13);
            this.OperLbl.TabIndex = 1;
            this.OperLbl.Text = "Оператор";
            // 
            // OperBox
            // 
            this.OperBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OperBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.OperBox.FormattingEnabled = true;
            this.OperBox.Items.AddRange(new object[] {
            "Все"});
            this.OperBox.Location = new System.Drawing.Point(328, 31);
            this.OperBox.Name = "OperBox";
            this.OperBox.Size = new System.Drawing.Size(150, 21);
            this.OperBox.TabIndex = 2;
            // 
            // DateLowLbl
            // 
            this.DateLowLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.DateLowLbl.AutoSize = true;
            this.DateLowLbl.Location = new System.Drawing.Point(325, 60);
            this.DateLowLbl.Name = "DateLowLbl";
            this.DateLowLbl.Size = new System.Drawing.Size(88, 13);
            this.DateLowLbl.TabIndex = 3;
            this.DateLowLbl.Text = "Начальная дата";
            // 
            // DateLowBox
            // 
            this.DateLowBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.DateLowBox.Location = new System.Drawing.Point(328, 79);
            this.DateLowBox.Name = "DateLowBox";
            this.DateLowBox.Size = new System.Drawing.Size(150, 20);
            this.DateLowBox.TabIndex = 4;
            // 
            // DateHigBox
            // 
            this.DateHigBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.DateHigBox.Location = new System.Drawing.Point(328, 126);
            this.DateHigBox.Name = "DateHigBox";
            this.DateHigBox.Size = new System.Drawing.Size(150, 20);
            this.DateHigBox.TabIndex = 6;
            // 
            // DateHigLbl
            // 
            this.DateHigLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.DateHigLbl.AutoSize = true;
            this.DateHigLbl.Location = new System.Drawing.Point(325, 107);
            this.DateHigLbl.Name = "DateHigLbl";
            this.DateHigLbl.Size = new System.Drawing.Size(89, 13);
            this.DateHigLbl.TabIndex = 5;
            this.DateHigLbl.Text = "Последняя дата";
            // 
            // OkBtn
            // 
            this.OkBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OkBtn.Location = new System.Drawing.Point(328, 260);
            this.OkBtn.Name = "OkBtn";
            this.OkBtn.Size = new System.Drawing.Size(150, 37);
            this.OkBtn.TabIndex = 7;
            this.OkBtn.Text = "Применить фильтр";
            this.OkBtn.UseVisualStyleBackColor = true;
            this.OkBtn.Click += new System.EventHandler(this.OkBtn_Click);
            // 
            // NullBtn
            // 
            this.NullBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.NullBtn.Location = new System.Drawing.Point(328, 231);
            this.NullBtn.Name = "NullBtn";
            this.NullBtn.Size = new System.Drawing.Size(150, 23);
            this.NullBtn.TabIndex = 8;
            this.NullBtn.Text = "Сброс условий";
            this.NullBtn.UseVisualStyleBackColor = true;
            this.NullBtn.Click += new System.EventHandler(this.NullBtn_Click);
            // 
            // FilterWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(490, 309);
            this.ControlBox = false;
            this.Controls.Add(this.NullBtn);
            this.Controls.Add(this.OkBtn);
            this.Controls.Add(this.DateHigBox);
            this.Controls.Add(this.DateHigLbl);
            this.Controls.Add(this.DateLowBox);
            this.Controls.Add(this.DateLowLbl);
            this.Controls.Add(this.OperBox);
            this.Controls.Add(this.OperLbl);
            this.Controls.Add(this.WhereGrid);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FilterWindow";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Фильтры";
            ((System.ComponentModel.ISupportInitialize)(this.WhereGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.DataGridView WhereGrid;
        private System.Windows.Forms.Label OperLbl;
        private System.Windows.Forms.ComboBox OperBox;
        private System.Windows.Forms.Label DateLowLbl;
        private System.Windows.Forms.DateTimePicker DateLowBox;
        private System.Windows.Forms.DateTimePicker DateHigBox;
        private System.Windows.Forms.Label DateHigLbl;
        private System.Windows.Forms.Button OkBtn;
        private System.Windows.Forms.Button NullBtn;
        private System.Windows.Forms.DataGridViewTextBoxColumn Param;
        private System.Windows.Forms.DataGridViewTextBoxColumn Min;
        private System.Windows.Forms.DataGridViewTextBoxColumn Max;

    }
}