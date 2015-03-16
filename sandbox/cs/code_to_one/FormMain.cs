using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace CodeToOne
{
    /// <summary> Главная форма </summary>
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();

            for (int i = 0; i < OptionBox.Items.Count; ++i)
                OptionBox.SetItemChecked(i, true);

            PathBox.Text = Application.StartupPath;
        }

        /// <summary> Кнопка выбора папки </summary>
        private void PathBtn_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            folder.SelectedPath = PathBox.Text;

            if (folder.ShowDialog() != DialogResult.Cancel)
                PathBox.Text = folder.SelectedPath;
        }

        /// <summary> Кнопка выбора файла </summary>
        private void RelBtn_Click(object sender, EventArgs e)
        {
            SaveFileDialog file = new SaveFileDialog();
            file.FileName = RelBox.Text;

            if (file.ShowDialog() != DialogResult.Cancel)
                RelBox.Text = file.FileName;
        }

        /// <summary> Запуск процесса </summary>
        private void GoBtn_Click(object sender, EventArgs e)
        {
            if (!LicCheck.Checked)
            {
                MessageBox.Show("Вы должны принять соглашение\r\n" +
                    "для пользования программой!\r\n\r\n" +
                    "Принимай быстрее пока оно не съебало!",
                    Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                LicTimer.Start();
                return;
            }

            if (!Directory.Exists(PathBox.Text))
            {
                MessageBox.Show("Входная папка задана не верно!",
                    Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            CodeBox code = new CodeBox();
            code.Read(SrcBox.Text, PathBox.Text);
            code.Edit(OptionBox.GetItemChecked(0), OptionBox.GetItemChecked(1),
                OptionBox.GetItemChecked(2), OptionBox.GetItemChecked(3),
                OptionBox.GetItemChecked(3), OptionBox.GetItemChecked(3));
            code.Write(RelBox.Text);
            Process.Start(RelBox.Text);
        }

        /// <summary> Таймер </summary>
        private void LicTimer_Tick(object sender, EventArgs e)
        {
            if (LicTimeCount < 10)
            {
                Width += 5;
            }
            else if (LicTimeCount < 15)
            {
                Location = new Point(Location.X + 10, Location.Y);
                Width -= 10;
            }

            if (LicTimeCount++ == 15)
                LicTimeCount = 0;
        }

        int LicTimeCount = 0;

        /// <summary> Стоп </summary>
        private void LicCheck_CheckedChanged(object sender, EventArgs e)
        {
            LicTimer.Stop();
        }
    }
}
