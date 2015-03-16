namespace OpenXmlEdit
{
    partial class WinMain
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WinMain));
            this.splitVert = new System.Windows.Forms.SplitContainer();
            this.splitHor = new System.Windows.Forms.SplitContainer();
            this.xmlTree = new System.Windows.Forms.TreeView();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolNodeAdd = new System.Windows.Forms.ToolStripButton();
            this.toolNodeDel = new System.Windows.Forms.ToolStripButton();
            this.toolSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.toolNodeCpy = new System.Windows.Forms.ToolStripButton();
            this.toolNodePst = new System.Windows.Forms.ToolStripButton();
            this.toolPropDel = new System.Windows.Forms.ToolStripButton();
            this.toolPropAdd = new System.Windows.Forms.ToolStripButton();
            this.xmlGrid = new System.Windows.Forms.DataGridView();
            this.xmlGridProp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.xmlGridVal = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.xmlText = new System.Windows.Forms.RichTextBox();
            this.menuBase = new System.Windows.Forms.MenuStrip();
            this.menuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFileCreate = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFileSep = new System.Windows.Forms.ToolStripSeparator();
            this.menuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFileSave = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFileSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.menuServ = new System.Windows.Forms.ToolStripMenuItem();
            this.menuServSaveBtn = new System.Windows.Forms.ToolStripMenuItem();
            this.menuServFont = new System.Windows.Forms.ToolStripComboBox();
            this.menuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSave = new System.Windows.Forms.ToolStripMenuItem();
            this.menuText = new System.Windows.Forms.ToolStripMenuItem();
            this.menuServSintax = new System.Windows.Forms.ToolStripMenuItem();
            this.splitVert.Panel1.SuspendLayout();
            this.splitVert.Panel2.SuspendLayout();
            this.splitVert.SuspendLayout();
            this.splitHor.Panel1.SuspendLayout();
            this.splitHor.Panel2.SuspendLayout();
            this.splitHor.SuspendLayout();
            this.toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.xmlGrid)).BeginInit();
            this.menuBase.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitVert
            // 
            this.splitVert.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitVert.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitVert.Location = new System.Drawing.Point(0, 0);
            this.splitVert.Name = "splitVert";
            // 
            // splitVert.Panel1
            // 
            this.splitVert.Panel1.Controls.Add(this.splitHor);
            // 
            // splitVert.Panel2
            // 
            this.splitVert.Panel2.Controls.Add(this.xmlText);
            this.splitVert.Panel2.Controls.Add(this.menuBase);
            this.splitVert.Size = new System.Drawing.Size(792, 465);
            this.splitVert.SplitterDistance = 202;
            this.splitVert.TabIndex = 0;
            // 
            // splitHor
            // 
            this.splitHor.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitHor.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitHor.Location = new System.Drawing.Point(0, 0);
            this.splitHor.Name = "splitHor";
            this.splitHor.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitHor.Panel1
            // 
            this.splitHor.Panel1.Controls.Add(this.xmlTree);
            this.splitHor.Panel1.Controls.Add(this.toolStrip);
            // 
            // splitHor.Panel2
            // 
            this.splitHor.Panel2.Controls.Add(this.xmlGrid);
            this.splitHor.Size = new System.Drawing.Size(202, 465);
            this.splitHor.SplitterDistance = 233;
            this.splitHor.TabIndex = 0;
            // 
            // xmlTree
            // 
            this.xmlTree.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.xmlTree.Location = new System.Drawing.Point(-1, 28);
            this.xmlTree.Name = "xmlTree";
            this.xmlTree.PathSeparator = "/";
            this.xmlTree.Size = new System.Drawing.Size(200, 204);
            this.xmlTree.TabIndex = 0;
            this.xmlTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.xmlTree_AfterSelect);
            // 
            // toolStrip
            // 
            this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip.ImageScalingSize = new System.Drawing.Size(22, 22);
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolNodeAdd,
            this.toolNodeDel,
            this.toolSeparator,
            this.toolNodeCpy,
            this.toolNodePst,
            this.toolPropDel,
            this.toolPropAdd});
            this.toolStrip.Location = new System.Drawing.Point(0, 0);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(198, 29);
            this.toolStrip.TabIndex = 2;
            // 
            // toolNodeAdd
            // 
            this.toolNodeAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolNodeAdd.Image = global::OpenXmlEdit.Properties.Resources.NodeAdd;
            this.toolNodeAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolNodeAdd.Name = "toolNodeAdd";
            this.toolNodeAdd.Size = new System.Drawing.Size(26, 26);
            this.toolNodeAdd.ToolTipText = "Добавить узел";
            this.toolNodeAdd.Click += new System.EventHandler(this.toolNodeAdd_Click);
            // 
            // toolNodeDel
            // 
            this.toolNodeDel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolNodeDel.Image = global::OpenXmlEdit.Properties.Resources.NodeDel;
            this.toolNodeDel.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolNodeDel.Name = "toolNodeDel";
            this.toolNodeDel.Size = new System.Drawing.Size(26, 26);
            this.toolNodeDel.Text = "toolStripButton2";
            this.toolNodeDel.ToolTipText = "Удалить узел";
            this.toolNodeDel.Click += new System.EventHandler(this.toolNodeDel_Click);
            // 
            // toolSeparator
            // 
            this.toolSeparator.Name = "toolSeparator";
            this.toolSeparator.Size = new System.Drawing.Size(6, 29);
            // 
            // toolNodeCpy
            // 
            this.toolNodeCpy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolNodeCpy.Image = global::OpenXmlEdit.Properties.Resources.NodeCpy;
            this.toolNodeCpy.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolNodeCpy.Name = "toolNodeCpy";
            this.toolNodeCpy.Size = new System.Drawing.Size(26, 26);
            this.toolNodeCpy.Text = "toolStripButton1";
            this.toolNodeCpy.ToolTipText = "Копировать узел";
            this.toolNodeCpy.Click += new System.EventHandler(this.toolNodeCpy_Click);
            // 
            // toolNodePst
            // 
            this.toolNodePst.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolNodePst.Enabled = false;
            this.toolNodePst.Image = global::OpenXmlEdit.Properties.Resources.NodePst;
            this.toolNodePst.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolNodePst.Name = "toolNodePst";
            this.toolNodePst.Size = new System.Drawing.Size(26, 26);
            this.toolNodePst.Text = "toolStripButton2";
            this.toolNodePst.ToolTipText = "Вставить узел";
            this.toolNodePst.Click += new System.EventHandler(this.toolNodePst_Click);
            // 
            // toolPropDel
            // 
            this.toolPropDel.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolPropDel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolPropDel.Image = global::OpenXmlEdit.Properties.Resources.PropDel;
            this.toolPropDel.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolPropDel.Name = "toolPropDel";
            this.toolPropDel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.toolPropDel.Size = new System.Drawing.Size(26, 26);
            this.toolPropDel.Text = "toolStripButton4";
            this.toolPropDel.ToolTipText = "Удалить атрибут из узла";
            this.toolPropDel.Click += new System.EventHandler(this.toolPropDel_Click);
            // 
            // toolPropAdd
            // 
            this.toolPropAdd.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolPropAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolPropAdd.Image = global::OpenXmlEdit.Properties.Resources.PropAdd;
            this.toolPropAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolPropAdd.Name = "toolPropAdd";
            this.toolPropAdd.Size = new System.Drawing.Size(26, 26);
            this.toolPropAdd.Text = "toolStripButton3";
            this.toolPropAdd.ToolTipText = "Добавить атрибут в узел";
            this.toolPropAdd.Click += new System.EventHandler(this.toolPropAdd_Click);
            // 
            // xmlGrid
            // 
            this.xmlGrid.AllowUserToAddRows = false;
            this.xmlGrid.AllowUserToDeleteRows = false;
            this.xmlGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.xmlGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.xmlGrid.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(250)))), ((int)(((byte)(250)))), ((int)(((byte)(250)))));
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.xmlGrid.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.xmlGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.xmlGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.xmlGridProp,
            this.xmlGridVal});
            this.xmlGrid.Location = new System.Drawing.Point(-1, -1);
            this.xmlGrid.Name = "xmlGrid";
            this.xmlGrid.RowHeadersVisible = false;
            this.xmlGrid.RowTemplate.Height = 18;
            this.xmlGrid.Size = new System.Drawing.Size(200, 226);
            this.xmlGrid.TabIndex = 0;
            this.xmlGrid.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.xmlGrid_CellLeave);
            // 
            // xmlGridProp
            // 
            this.xmlGridProp.HeaderText = "Атрибут";
            this.xmlGridProp.Name = "xmlGridProp";
            // 
            // xmlGridVal
            // 
            this.xmlGridVal.HeaderText = "Значение";
            this.xmlGridVal.Name = "xmlGridVal";
            this.xmlGridVal.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // xmlText
            // 
            this.xmlText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.xmlText.Location = new System.Drawing.Point(0, 27);
            this.xmlText.Name = "xmlText";
            this.xmlText.Size = new System.Drawing.Size(582, 435);
            this.xmlText.TabIndex = 3;
            this.xmlText.Text = "";
            this.xmlText.Leave += new System.EventHandler(this.menuText_Click);
            // 
            // menuBase
            // 
            this.menuBase.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFile,
            this.menuServ,
            this.menuHelp,
            this.menuSave,
            this.menuText});
            this.menuBase.Location = new System.Drawing.Point(0, 0);
            this.menuBase.Name = "menuBase";
            this.menuBase.Size = new System.Drawing.Size(582, 24);
            this.menuBase.TabIndex = 2;
            // 
            // menuFile
            // 
            this.menuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFileCreate,
            this.menuFileSep,
            this.menuFileOpen,
            this.menuFileSave,
            this.menuFileSaveAs});
            this.menuFile.Name = "menuFile";
            this.menuFile.Size = new System.Drawing.Size(45, 20);
            this.menuFile.Text = "Файл";
            // 
            // menuFileCreate
            // 
            this.menuFileCreate.Name = "menuFileCreate";
            this.menuFileCreate.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.menuFileCreate.Size = new System.Drawing.Size(241, 22);
            this.menuFileCreate.Text = "Создать новый";
            this.menuFileCreate.Click += new System.EventHandler(this.menuFileCreate_Click);
            // 
            // menuFileSep
            // 
            this.menuFileSep.Name = "menuFileSep";
            this.menuFileSep.Size = new System.Drawing.Size(238, 6);
            // 
            // menuFileOpen
            // 
            this.menuFileOpen.Name = "menuFileOpen";
            this.menuFileOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.menuFileOpen.Size = new System.Drawing.Size(241, 22);
            this.menuFileOpen.Text = "Открыть";
            this.menuFileOpen.Click += new System.EventHandler(this.menuFileOpen_Click);
            // 
            // menuFileSave
            // 
            this.menuFileSave.Name = "menuFileSave";
            this.menuFileSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.menuFileSave.Size = new System.Drawing.Size(241, 22);
            this.menuFileSave.Text = "Сохранить";
            this.menuFileSave.Click += new System.EventHandler(this.menuFileSave_Click);
            // 
            // menuFileSaveAs
            // 
            this.menuFileSaveAs.Name = "menuFileSaveAs";
            this.menuFileSaveAs.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
                        | System.Windows.Forms.Keys.S)));
            this.menuFileSaveAs.Size = new System.Drawing.Size(241, 22);
            this.menuFileSaveAs.Text = "Сохранить как...";
            this.menuFileSaveAs.Click += new System.EventHandler(this.menuFileSaveAs_Click);
            // 
            // menuServ
            // 
            this.menuServ.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuServSintax,
            this.menuServSaveBtn,
            this.menuServFont});
            this.menuServ.Name = "menuServ";
            this.menuServ.Size = new System.Drawing.Size(38, 20);
            this.menuServ.Text = "Вид";
            // 
            // menuServSaveBtn
            // 
            this.menuServSaveBtn.Checked = true;
            this.menuServSaveBtn.CheckState = System.Windows.Forms.CheckState.Checked;
            this.menuServSaveBtn.Name = "menuServSaveBtn";
            this.menuServSaveBtn.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.B)));
            this.menuServSaveBtn.Size = new System.Drawing.Size(248, 22);
            this.menuServSaveBtn.Text = "Дополнительная кнопка";
            this.menuServSaveBtn.Click += new System.EventHandler(this.menuServSaveBtn_Click);
            // 
            // menuServFont
            // 
            this.menuServFont.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.menuServFont.Items.AddRange(new object[] {
            "Шрифт 8,25",
            "Шрифт 9,5",
            "Шрифт 10",
            "Шрифт 12",
            "Шрифт 14"});
            this.menuServFont.Name = "menuServFont";
            this.menuServFont.Size = new System.Drawing.Size(175, 21);
            this.menuServFont.SelectedIndexChanged += new System.EventHandler(this.menuServFont_SelectedIndexChanged);
            // 
            // menuHelp
            // 
            this.menuHelp.Name = "menuHelp";
            this.menuHelp.ShortcutKeys = System.Windows.Forms.Keys.F1;
            this.menuHelp.Size = new System.Drawing.Size(62, 20);
            this.menuHelp.Text = "Справка";
            this.menuHelp.Click += new System.EventHandler(this.menuHelp_Click);
            // 
            // menuSave
            // 
            this.menuSave.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.menuSave.Name = "menuSave";
            this.menuSave.Size = new System.Drawing.Size(116, 20);
            this.menuSave.Text = "Сохранить (Ctrl+S)";
            this.menuSave.Click += new System.EventHandler(this.menuFileSave_Click);
            // 
            // menuText
            // 
            this.menuText.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.menuText.Name = "menuText";
            this.menuText.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.menuText.Size = new System.Drawing.Size(149, 20);
            this.menuText.Text = "Применить текст (Ctrl+R)";
            this.menuText.Click += new System.EventHandler(this.menuText_Click);
            // 
            // menuServSintax
            // 
            this.menuServSintax.Checked = true;
            this.menuServSintax.CheckState = System.Windows.Forms.CheckState.Checked;
            this.menuServSintax.Name = "menuServSintax";
            this.menuServSintax.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.M)));
            this.menuServSintax.Size = new System.Drawing.Size(248, 22);
            this.menuServSintax.Text = "Подсветка синтаксиса";
            this.menuServSintax.Click += new System.EventHandler(this.menuServSintax_Click);
            // 
            // WinMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 465);
            this.Controls.Add(this.splitVert);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "WinMain";
            this.Text = "Свободный Xml Конфигуратор";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.WinMain_FormClosing);
            this.splitVert.Panel1.ResumeLayout(false);
            this.splitVert.Panel2.ResumeLayout(false);
            this.splitVert.Panel2.PerformLayout();
            this.splitVert.ResumeLayout(false);
            this.splitHor.Panel1.ResumeLayout(false);
            this.splitHor.Panel1.PerformLayout();
            this.splitHor.Panel2.ResumeLayout(false);
            this.splitHor.ResumeLayout(false);
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.xmlGrid)).EndInit();
            this.menuBase.ResumeLayout(false);
            this.menuBase.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitVert;
        private System.Windows.Forms.SplitContainer splitHor;
        private System.Windows.Forms.TreeView xmlTree;
        private System.Windows.Forms.DataGridView xmlGrid;
        private System.Windows.Forms.MenuStrip menuBase;
        private System.Windows.Forms.ToolStripMenuItem menuFile;
        private System.Windows.Forms.ToolStripMenuItem menuFileCreate;
        private System.Windows.Forms.ToolStripSeparator menuFileSep;
        private System.Windows.Forms.ToolStripMenuItem menuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem menuFileSave;
        private System.Windows.Forms.ToolStripMenuItem menuFileSaveAs;
        private System.Windows.Forms.ToolStripMenuItem menuServ;
        private System.Windows.Forms.ToolStripMenuItem menuHelp;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripButton toolNodeAdd;
        private System.Windows.Forms.ToolStripButton toolNodeDel;
        private System.Windows.Forms.ToolStripButton toolPropAdd;
        private System.Windows.Forms.ToolStripButton toolPropDel;
        private System.Windows.Forms.DataGridViewTextBoxColumn xmlGridProp;
        private System.Windows.Forms.DataGridViewTextBoxColumn xmlGridVal;
        private System.Windows.Forms.RichTextBox xmlText;
        private System.Windows.Forms.ToolStripMenuItem menuServSaveBtn;
        private System.Windows.Forms.ToolStripSeparator toolSeparator;
        private System.Windows.Forms.ToolStripButton toolNodeCpy;
        private System.Windows.Forms.ToolStripButton toolNodePst;
        private System.Windows.Forms.ToolStripComboBox menuServFont;
        private System.Windows.Forms.ToolStripMenuItem menuText;
        private System.Windows.Forms.ToolStripMenuItem menuSave;
        private System.Windows.Forms.ToolStripMenuItem menuServSintax;


    }
}