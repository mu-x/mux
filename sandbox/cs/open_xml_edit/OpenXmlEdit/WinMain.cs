using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;
using System.Windows.Forms;

namespace OpenXmlEdit
{
    // На будующее XSD Validation:
    // msdn.microsoft.com/en-us/library/ms162371%28v=VS.85%29.aspx

    public partial class WinMain : Form
    {
        XmlDocument xmlDoc = new XmlDocument(); // Узел соответсвующий выбраному узлу дерева
        XmlNode selectedNode = null; // Объектный XML
        string xmlFileName = ""; // Открытый файл
        XmlNode copyNode = null; // Скопированый узел
        bool xmlEdited = false; // Редктирован?

    #region Вспомогательные функции
        // Настройка интерфейса
        public WinMain(string[] args)
        {
            InitializeComponent();
            menuFileCreate_Click(this, null);

            if (args.Length == 1)
                makeXmlFromFile(args[0]);

            menuServFont.SelectedIndex = 2;
            xmlEdited = false;
        }

        // Узел в дерево (рекурсивно)
        private void makeTreeNode(XmlNode xml, TreeNodeCollection tree)
        {
            tree.Clear();
            foreach (XmlNode xmlNode in xml.ChildNodes)
            {
                string xmlNodeName = xmlNode.Name;
                try {
                    xmlNodeName += " (" + xmlNode.Attributes["name"].Value.ToString() + ")";
                } catch (Exception) { }
                TreeNode treeNode = tree.Add(xmlNodeName);
                makeTreeNode(xmlNode, treeNode.Nodes);
            }
        }

        // Xml из документа в текст
        private void makeXmlText()
        {
            var strWrite = new StringWriter();
            var xmlWrite = new XmlTextWriter(strWrite);

            xmlWrite.Formatting = Formatting.Indented;
            xmlDoc.WriteTo(xmlWrite);
            xmlWrite.Close();
            xmlText.Text = strWrite.ToString();
            makeXmlSintax();
            xmlEdited = true;
        }

        // Загрузка xml из файла
        private void makeXmlFromFile(string file)
        {
            try
            {
                var read = new StreamReader(xmlFileName = file);
                xmlText.Text = read.ReadToEnd();
                read.Close();

                menuText_Click(this, null);
                makeXmlText();
                xmlTree.SelectedNode = xmlTree.Nodes[0];
            }
            catch (System.Exception ex)
            {
                InOutBox.Error(Messages.File.E, ex);
            }
        }

        // Подсветка синтаксиса
        private void makeXmlSintax()
        {
            if (!menuServSaveBtn.Checked)
            {
                markXmlSintax(null, Color.Black, false);
                return;
            }

            markXmlSintax(null, Color.Blue, false);
            markXmlSintax("\\<[a-zA-Z]+.", Color.Black, true);
            markXmlSintax("\\<[\\?\\/][a-zA-Z]+.", Color.Black, true);
            markXmlSintax("[\\?\\/]\\>", Color.Black, true);
            markXmlSintax("\\=", Color.Black, true);
            markXmlSintax("\\\"[^\\\"]+\\\"", Color.Red, false);
        }

        // Применение подсветки
        private void markXmlSintax(string reg, Color color, bool bold)
        {
            var font_l = new Font(xmlText.Font, FontStyle.Regular);
            var font_b = new Font(xmlText.Font, FontStyle.Bold);
            
            if (reg == null)
            {
                xmlText.SelectionStart = 0;
                xmlText.SelectionLength = xmlText.Text.Length;
                xmlText.SelectionColor = color;
                xmlText.SelectionFont = bold ? font_b : font_l;
                return;
            }
            
            Regex regex = new Regex(reg);
            MatchCollection matches = regex.Matches(xmlText.Text.Replace("\r\n", " "));
            
            foreach (Match mat in matches)
            {
                xmlText.SelectionStart = mat.Index;
                xmlText.SelectionLength = mat.Length;
                xmlText.SelectionColor = color;
                xmlText.SelectionFont = bold ? font_b : font_l;
            }
        }
    #endregion

    #region Кнопки меню
        // Новый файл
        private void menuFileCreate_Click(object sender, EventArgs e)
        {
            string name = "root";

            if (xmlText.Text != "")
            {
                var res = InOutBox.Question(Messages.File.T,
                    Messages.File.Q, MessageBoxButtons.YesNoCancel);
                if (res == DialogResult.Yes)
                    menuFileSave_Click(sender, e);
                else if (res == DialogResult.Cancel)
                    return;

                if (DialogResult.OK != InOutBox.Input(Messages.File.T,
                Messages.File.N, ref name))
                    return;
            }

            xmlText.Text =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?><" + name + "/>";
            menuText_Click(this, null);
            
            makeXmlText();
            xmlTree.SelectedNode = xmlTree.Nodes[0];
            xmlEdited = false;
        }

        // Открыть файл
        private void menuFileOpen_Click(object sender, EventArgs e)
        {
            var dlg = new OpenFileDialog();
            dlg.FileName = xmlFileName;
            
            if (dlg.ShowDialog() == DialogResult.Cancel)
                return;

            makeXmlFromFile(dlg.FileName);
            xmlEdited = false;
        }

        // Сохранить файл
        private void menuFileSave_Click(object sender, EventArgs e)
        {
            if (xmlFileName == "")
            {
                menuFileSaveAs_Click(sender, e);
                return;
            }

            var text = new StreamWriter(xmlFileName);
            text.Write(xmlText.Text);
            text.Close();
            xmlEdited = false;
        }

        // Сохраниь как файл
        private void menuFileSaveAs_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.FileName = xmlFileName;

            if (dlg.ShowDialog() == DialogResult.Cancel)
                return;

            xmlFileName = dlg.FileName;
            menuFileSave_Click(sender, e);
        }

        // Вкл / Откл проверка синтаксиса
        private void menuServSintax_Click(object sender, EventArgs e)
        {
            menuServSintax.Checked = !menuServSintax.Checked;
            makeXmlSintax();
        }

        // Вкл / Откл доп кнопку
        private void menuServSaveBtn_Click(object sender, EventArgs e)
        {
            menuServSaveBtn.Checked = !menuServSaveBtn.Checked;
            menuSave.Visible = menuServSaveBtn.Checked;
        }

        // Размер шрифта
        private void menuServFont_SelectedIndexChanged(object sender, EventArgs e)
        {
            Font font = new Font("Lucida Console", Convert.ToSingle(
                menuServFont.SelectedItem.ToString().Split(' ')[1]));
            xmlText.Font = font;
            xmlTree.Font = font;
            xmlGrid.Font = font;

            bool save = xmlEdited;
            makeXmlText();
            xmlEdited = save;
        }

        // Применить изменения текста
        private void menuText_Click(object sender, EventArgs e)
        {
            try
            {
                xmlDoc.InnerXml = xmlText.Text;
                makeTreeNode(xmlDoc, xmlTree.Nodes);
                toolNodePst.Enabled = false;
                xmlTree.ExpandAll();
                makeXmlText();
            }
            catch (System.Exception ex)
            {
                InOutBox.Error(Messages.File.E, ex);
            }
        }
        private void menuServGo_Click(object sender, EventArgs e)
        {
        }

        // Вызов справки
        private void menuHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Справочная информация:\r\n\r\n" + 
                "Справозная информация находится в стадии\r\n" +
                "разработки, воспользуйтесь головой (=\r\n\r\n" +
                "Разработано Усковым М. В.\r\n" +
                "ООО внедренческая фирма \"ЭЛНА\" 2011",
                "Справочная информация",
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        // Выход
        private void menuExit_Click(object sender, EventArgs e)
        {
            Close();
        }
    #endregion
        
    #region Мини панель инструментов
        // Добавить узел
        private void toolNodeAdd_Click(object sender, EventArgs e)
        {
            try
            {
                XmlNode xml;
                var tree = xmlTree.SelectedNode.Nodes;

                string node = "node";
                if (DialogResult.OK != InOutBox.Input(Messages.Node.T,
                    Messages.Node.N, ref node))
                    return;

                xml = xmlDoc.CreateElement(node);
                selectedNode.AppendChild(xml);
                tree.Add(node).Expand();
                makeXmlText();
            }
            catch (Exception ex)
            {
                InOutBox.Error(Messages.Node.E, ex);
            }
        }

        // Удалить узел
        private void toolNodeDel_Click(object sender, EventArgs e)
        {
            try
            {
                var node = xmlTree.SelectedNode;
                if (DialogResult.No == InOutBox.Question(Messages.Node.T,
                    Messages.Node.Q.Replace("X", node.FullPath)))
                    return;

                if (selectedNode == copyNode)
                    toolNodePst.Enabled = false;

                selectedNode.ParentNode.RemoveChild(selectedNode);
                node.Remove();
                xmlTree.SelectedNode = xmlTree.Nodes[0];
                makeXmlText();
            }
            catch (Exception ex)
            {
                InOutBox.Error(Messages.Node.E, ex);
            }
        }

        // Скопировать узел
        private void toolNodeCpy_Click(object sender, EventArgs e)
        {
            copyNode = selectedNode;
            toolNodePst.Enabled = true;
        }

        // Вставить узел
        private void toolNodePst_Click(object sender, EventArgs e)
        {
            if (copyNode == null)
            {
                toolNodePst.Enabled = false;
                return;
            }

            try
            {
                var newNode = copyNode.Clone();
                selectedNode.AppendChild(newNode);

                string nodeName = copyNode.Name;
                try {
                    nodeName += " (" + copyNode.Attributes["name"].Value + ")";
                } catch (System.Exception ex) { }

                var newTree = xmlTree.SelectedNode.Nodes.Add(nodeName);
                makeTreeNode(copyNode, newTree.Nodes);
                newTree.Expand();
                makeXmlText();
            }
            catch (Exception ex)
            {
                InOutBox.Error(Messages.Node.E, ex);
            }
        }

        // Добавить свойство
        private void toolPropAdd_Click(object sender, EventArgs e)
        {
            try
            {
                string prop = "attr";
                if (DialogResult.OK != InOutBox.Input(Messages.Prop.T,
                    Messages.Prop.N, ref prop))
                        return;

                selectedNode.Attributes.Append(xmlDoc.CreateAttribute(prop));
                xmlTree_AfterSelect(xmlTree, new TreeViewEventArgs(xmlTree.SelectedNode));
                makeXmlText();
            }
            catch (System.Exception ex)
            {
                InOutBox.Error(Messages.Prop.E, ex);
            }
        }

        // Удалить свойство
        private void toolPropDel_Click(object sender, EventArgs e)
        {
            try
            {
                int idx = xmlGrid.SelectedCells[0].RowIndex;
                var attr = xmlGrid.Rows[idx].Cells[0].Value.ToString();

                if (DialogResult.No == InOutBox.Question(Messages.Prop.T,
                    Messages.Prop.Q.Replace("X", attr).Replace("Y", selectedNode.Name)))
                        return;

                XmlAttributeCollection ac = selectedNode.Attributes;
                ac.Remove((XmlAttribute)ac.GetNamedItem(attr));
                xmlTree_AfterSelect(xmlTree, new TreeViewEventArgs(xmlTree.SelectedNode));
                makeXmlText();
            }
            catch (System.Exception ex)
            {
                InOutBox.Error(Messages.Prop.E, ex);
            }
        }
    #endregion

    #region Специальные события
        // Выбор узла
        private void xmlTree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            var path = new List<int>();
            var node = e.Node;

            do
                path.Insert(0, node.Index);
            while ((node = node.Parent) != null);

            selectedNode = xmlDoc;
            foreach (int idx in path)
                selectedNode = selectedNode.ChildNodes[idx];

            xmlGrid.Rows.Clear();
            xmlGrid.Rows.Add(new object[] { "(Name)", e.Node.FullPath });
            xmlGrid.Rows[0].ReadOnly = true;

            if (selectedNode.Attributes == null)
                return;
            foreach (XmlAttribute attr in selectedNode.Attributes)
                xmlGrid.Rows.Add(new object[] { attr.Name, attr.Value });
        }

        // Изменение свойств узла
        private void xmlGrid_CellLeave(object sender, DataGridViewCellEventArgs e)
        {
            selectedNode.Attributes.RemoveAll();

            foreach (DataGridViewRow row in xmlGrid.Rows)
            {
                if (row.Cells[0].Value.ToString() == "(Name)")
                    continue;
                XmlElement el = (XmlElement)selectedNode;
                el.SetAttribute(row.Cells[0].Value.ToString(),
                   row.Cells[1].Value.ToString());
                if (row.Cells[0].Value.ToString() == "name")
                    xmlTree.SelectedNode.Text = selectedNode.Name +
                        " (" + row.Cells[1].Value.ToString() + ")";
            }

            makeXmlText();
        }

        // Попытка выхода
        private void WinMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!xmlEdited)
                return;

            switch (InOutBox.Question("Выход", Messages.File.Q,
                MessageBoxButtons.YesNoCancel))
            {
                case DialogResult.Yes:
                    menuFileSave_Click(sender, e);
                    break;

                case DialogResult.Cancel:
                    e.Cancel = true;
                    break;
            }
        }
    #endregion





    }
}
